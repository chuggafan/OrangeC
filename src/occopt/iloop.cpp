/* Software License Agreement
 *
 *     Copyright(C) 1994-2025 David Lindauer, (LADSoft)
 *
 *     This file is part of the Orange C Compiler package.
 *
 *     The Orange C Compiler package is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     The Orange C Compiler package is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with Orange C.  If not, see <http://www.gnu.org/licenses/>.
 *
 *     contact information:
 *         email: TouchStone222@runbox.com <David Lindauer>
 *
 *
 */

#include <cstdio>
#include <malloc.h>
#include <cstring>
#include <climits>
#include <stack>
#include "ioptimizer.h"
#include "beinterfdefs.h"
#include "Utils.h"
#include "iblock.h"
#include "OptUtils.h"
#include "ildata.h"
#include "iflow.h"
#include "memory.h"
#include "ilocal.h"
#include "ireshape.h"
#include "ioptutil.h"

/* Basic loop identity and data gathering
 * note: some optimizations depend on the fact that the loop numbers
 * are assigned in reverse postorder
 */
namespace Optimizer
{
std::vector<Loop*> loopArray;
int loopCount;

static BriggsSet* loopItems;

static const char* lptype(Loop* lp)
{
    if (lp->type == LT_ROOT)
        return "root";
    else if (lp->type == LT_SINGLE)
        return "single";
    else if (lp->type == LT_MULTI)
        return "multi";
    else
        return "block";
}
static void dump_loops(void)
{
    int i;
    for (i = 0; i < loopCount; i++)
    {
        Loop* lp = loopArray[i];
        if (lp && lp->type != LT_BLOCK)
        {
            LIST* lt = lp->contains;
            fprintf(icdFile, "; %d/%s/B(%d)/", i + 1, lptype(lp), lp->entry->blocknum + 1);
            while (lt)
            {
                lp = (Loop*)lt->data;
                if (lp->type == LT_BLOCK)
                    fprintf(icdFile, "B(%d) ", lp->entry->blocknum + 1);
                else
                    fprintf(icdFile, "L(%d) ", lp->loopnum + 1);
                lt = lt->next;
            }
            fprintf(icdFile, "\n");
        }
    }
}
static void findInfinite(Block* b)
{
    if (!b->visiteddfst)
    {
        BLOCKLIST* l = b->pred;
        b->visiteddfst = true;
        while (l)
        {
            findInfinite(l->block);
            l = l->next;
        }
    }
}
/* add a thunk block to get us out of an infinite loop */
static void makeNonInfinite(Block* b)
{
    BLOCKLIST *bi = newBlock(), *bi2, **bt;
    QUAD *quad, *quad2;

    blockArray[bi->block->blocknum] = bi->block;
    bi->block->unuseThunk = true;

    bi->block->succ = oAllocate<BLOCKLIST>();
    bi->block->succ->block = blockArray[exitBlock];

    bi->block->pred = oAllocate<BLOCKLIST>();
    bi->block->pred->block = b;

    bt = &b->succ;
    while (*bt)
        bt = &(*bt)->next;
    *bt = bi;

    bi2 = oAllocate<BLOCKLIST>();
    bi2->block = bi->block;

    bt = &blockArray[exitBlock]->pred;
    while (*bt)
        bt = &(*bt)->next;
    *bt = bi2;

    /* note : the following does NOT insert jmps for the
     * newly added block
     */
    *criticalThunkPtr = quad = Allocate<QUAD>();
    criticalThunkPtr = &quad->fwd;
    quad->dc.opcode = i_block;
    quad->block = bi->block;
    quad->dc.v.label = bi->block->blocknum;

    *criticalThunkPtr = quad2 = Allocate<QUAD>();
    criticalThunkPtr = &quad2->fwd;
    quad2->back = quad;
    quad2->dc.opcode = i_blockend;
    quad2->block = bi->block;
    //	quad2->dc.v.label = bi->block->blocknum;

    bi->block->head = quad;
    bi->block->tail = quad2;
}
void CancelInfinite(int orgBlockCount)
{
    int i;
    (void)orgBlockCount;
    while (true)
    {
        for (i = 0; i < blockCount; i++)
        {
            if (blockArray[i])
                blockArray[i]->visiteddfst = false;
        }
        findInfinite(blockArray[exitBlock]);
        for (i = exitBlock; i >= 0; i--)
        {
            if (blockArray[i] && !blockArray[i]->visiteddfst)
            {
                makeNonInfinite(blockArray[i]);
                break;
            }
        }
        if (i < 0)
            break;
    }
}
void RemoveInfiniteThunks(void)
{
    int i;
    for (i = 0; i < blockCount; i++)
    {
        Block* b = blockArray[i];
        if (b && b->unuseThunk)
        {
            BLOCKLIST** l;
            if (b->pred)
            {
                l = &b->pred->block->succ;
                while (*l)
                {
                    if ((*l)->block == b)
                    {
                        (*l) = (*l)->next;
                        break;
                    }
                    l = &(*l)->next;
                }
            }
            if (b->succ)
            {
                l = &b->succ->block->pred;
                while (*l)
                {
                    if ((*l)->block == b)
                    {
                        (*l) = (*l)->next;
                        break;
                    }
                    l = &(*l)->next;
                }
            }
            blockArray[i] = nullptr;
        }
    }
}
/* may return either a block or loop */
static Loop* LoopAncestor(Block* b)
{
    Loop* head = b->loopParent;
    if (!head)
        return b->loopName;
    while (head->parent != nullptr)
        head = head->parent;
    return head;
}
static void FindBody(BLOCKLIST* gen, Block* head, enum e_lptype type)
{
    LIST *queue = nullptr, **qx;
    Loop *lp, **lpp;
    int i;
    if (!gen)
        return;
    briggsClear(loopItems);
    while (gen)
    {
        Loop* l = LoopAncestor(gen->block);
        if (l && !briggsTest(loopItems, l->loopnum))
        {
            LIST* bl = oAllocate<LIST>();
            bl->data = l;
            bl->next = queue;
            queue = bl;
            briggsSet(loopItems, l->loopnum);
        }
        gen = gen->next;
    }
    while (queue)
    {
        if (((Loop*)queue->data)->entry)
        {
            BLOCKLIST* p = ((Loop*)queue->data)->entry->pred;
            queue = queue->next;
            while (p)
            {
                if (p->block != head)
                {
                    Loop* l = LoopAncestor(p->block);
                    if (l && !briggsTest(loopItems, l->loopnum))
                    {
                        LIST* bl = oAllocate<LIST>();
                        bl->data = l;
                        bl->next = queue;
                        queue = bl;
                        briggsSet(loopItems, l->loopnum);
                    }
                }
                p = p->next;
            }
        }
        else
            queue = queue->next;
    }
    if (loopCount >= loopArray.size())
        loopArray.resize(loopCount + 1000);
    lp = oAllocate<Loop>();
    lp->loopnum = loopCount;
    loopArray[loopCount++] = lp;
    lp->type = type;
    lp->entry = head;
    lp->parent = nullptr;
    head->loopParent = lp;
    qx = &lp->contains;
    *qx = oAllocate<LIST>();
    (*qx)->data = head->loopName;
    qx = &(*qx)->next;
    for (i = 0; i < loopItems->top; i++)
    {
        LIST* l = oAllocate<LIST>();
        int n = loopItems->data[i];
        l->data = loopArray[n];
        *qx = l;
        qx = &(*qx)->next;
        if (loopArray[n]->type == LT_BLOCK)
            loopArray[n]->entry->loopParent = lp;
        else
            loopArray[n]->parent = lp;
    }
}
static Block* findCommonDominator(Block* one, Block* two)
{
    int i = one->blocknum;
    while (i)
    {
        int j = two->blocknum;
        while (j)
        {
            if (i == j)
                return blockArray[i];
            j = blockArray[j]->idom;
        }
        i = blockArray[i]->idom;
    }
    return blockArray[0];
}
static void FindLoop(Block* b)
{
    BLOCKLIST* loop = nullptr;
    BLOCKLIST* bl;
    Block* Z = b;
    bl = b->pred;
    while (bl)
    {
        if (getEdgeType(bl->block->blocknum, b->blocknum) == F_BACKEDGE)
        {
            Z = findCommonDominator(Z, bl->block);
            if (bl->block != b)  // we don't care about duplicates, they will be filtered later
            {
                BLOCKLIST* bm = oAllocate<BLOCKLIST>();
                bm->block = bl->block;
                bm->next = loop;
                loop = bm;
            }
        }
        bl = bl->next;
    }
    if (Z != b)
    {
        /* again we don't care about duplicates */
        BLOCKLIST** bp = &Z->loopGenerators;
        while (*bp)
            bp = &(*bp)->next;
        (*bp) = loop;
    }
    else
    {
        FindBody(loop, b, LT_SINGLE);
    }
}
static void FindLoopOuter(Block* b)
{
    BLOCKLIST* bl;
    if (b->visiteddfst)
        return;
    bl = b->succ;
    b->visiteddfst = true;
    while (bl)
    {
        FindLoopOuter(bl->block);
        bl = bl->next;
    }
    if (b->loopGenerators)
    {
        FindBody(b->loopGenerators, b, LT_MULTI);
    }
    FindLoop(b);
}
static void CalculateLoopedBlocks(Loop* l)
{
    if (l->type != LT_BLOCK)
    {
        LIST* l1 = l->contains;
        while (l1)
        {
            CalculateLoopedBlocks((Loop*)l1->data);
            l1 = l1->next;
        }
        l1 = l->contains;
        l->blocks = briggsAlloc(blockCount);
        while (l1)
        {
            Loop* lm = (Loop*)l1->data;
            if (lm->type == LT_BLOCK)
                briggsSet(l->blocks, lm->entry->blocknum);
            else
            {
                int i;
                for (i = 0; i < lm->blocks->top; i++)
                    briggsSet(l->blocks, lm->blocks->data[i]);
            }
            l1 = l1->next;
        }
    }
}
/* finds all the successors to the loop */
static void CalculateSuccessors(Loop* lp)
{
    LIST* contains;
    contains = lp->contains;
    while (contains)
    {
        Loop* current = (Loop*)contains->data;
        if (lp->type != LT_BLOCK)
            CalculateSuccessors(current);
        contains = contains->next;
    }
    contains = lp->contains;
    while (contains)
    {
        Loop* inner = (Loop*)contains->data;
        if (inner->type == LT_BLOCK)
        {
            BLOCKLIST* bl = inner->entry->succ;
            while (bl)
            {
                BLOCKLIST* newExit = oAllocate<BLOCKLIST>();
                newExit->next = lp->successors;
                lp->successors = newExit;
                newExit->block = bl->block;
                bl = bl->next;
            }
        }
        else
        {
            /* only have to add blocks that exited an inner loop
             * and only if they also exit this loop
             */
            BLOCKLIST* prevSuccessors = inner->successors;
            while (prevSuccessors)
            {
                if (!briggsTest(inner->blocks, prevSuccessors->block->blocknum))
                {
                    BLOCKLIST* newExit = oAllocate<BLOCKLIST>();
                    newExit->next = lp->successors;
                    lp->successors = newExit;
                    newExit->block = prevSuccessors->block;
                }
                prevSuccessors = prevSuccessors->next;
            }
        }
        contains = contains->next;
    }
}
void BuildLoopTree(void)
{
    BLOCKLIST bl;
    Block* b;
    int i;
    QUAD* tail;
    bool skip = false;
    loopArray.clear();
    loopCount = 0;
    loopItems = briggsAlloc((blockCount) * 4);
    loopArray.resize(blockCount);
    for (i = 0; i < blockCount; i++)
    {
        if (blockArray[i])
        {
            blockArray[i]->visiteddfst = false;
            blockArray[i]->loopParent = nullptr;
            blockArray[i]->loopName = oAllocate<Loop>();
            blockArray[i]->loopName->type = LT_BLOCK;
            blockArray[i]->loopName->entry = blockArray[i];
            blockArray[i]->loopName->loopnum = loopCount;
            blockArray[i]->loopGenerators = nullptr;
            loopArray[loopCount++] = blockArray[i]->loopName;
        }
    }
    FindLoopOuter(blockArray[0]);
    //	CalculateSuccessors(loopArray[loopCount-1]);

    memset(&bl, 0, sizeof(bl));
    bl.block = blockArray[exitBlock];
    FindBody(&bl, blockArray[0], LT_ROOT);
    CalculateLoopedBlocks(loopArray[loopCount - 1]);
    //   if (cparams.prm_icdfile)
    //   {
    //       fprintf(icdFile, "; loop dump\n");
    //       dump_loops();
    //   }
    tail = intermed_tail;
    b = tail->block;
    while (tail)
    {
        switch (tail->dc.opcode)
        {
            case i_skipcompare:
                skip = !skip;
                break;
            case i_block:
                b = tail->block;
                break;
            default:
                break;
        }
        if (tail->block)
        {
            if (skip)
            {
                tail->block->inclusiveLoopParent = b->loopParent;
            }
            else
            {
                tail->block->inclusiveLoopParent = tail->block->loopParent;
            }
        }
        tail = tail->back;
    }
    if (loopCount >= blockCount * 4)
        Utils::Fatal("Internal error - Loop Count");
}
bool isAncestor(Loop* l1, Loop* l2)
{
    if (l1 == l2)
        return false;
    while (l2)
    {
        if (l1 == l2)
            return true;
        l2 = l2->parent;
    }
    return false;
}
static Loop* nearestAncestor(Loop* l1, Loop* l2)
{
    if (!l1)
        return l2;
    if (!l2)
        return l1;
    if (l1 == l2 || isAncestor(l2, l1))
        return l2;
    while (!isAncestor(l1, l2))
    {
        l1 = l1->parent;
    }
    return l1;
}
/* if loop we are interested in encloses loop variable is modified in */
static bool isInvariant(int tnum, Loop* l)
{
    Loop* varl = tempInfo[tnum]->variantLoop;
    while (varl)
    {
        if (varl == l)
        {
            return false;
        }
        varl = varl->parent;
    }
    return true;
}
static void CalculateLoopInvariants(Block* b)
{
    BLOCKLIST* children = b->dominates;
    QUAD* head;
    int i;
    if (b == blockArray[0])
        for (i = 0; i < tempCount; i++)
            tempInfo[i]->variantLoop = 0;
    /* again the PHI nodes are first, which satisfies the algorithm need
     * to evaluate them first
     */
    head = b->head;
    while (head != b->tail->fwd)
    {
        if (head->dc.opcode == i_phi)
        {
            PHIDATA* pd = head->dc.v.phi;
            tempInfo[pd->T0]->variantLoop = b->loopParent;
        }
        else if ((head->temps & TEMP_ANS) && head->ans->mode == i_direct)
        {
            Loop* varying = b->loopParent;
            Loop* t_varying;
            int tnum;
            if ((head->temps & TEMP_LEFT) && head->dc.left->mode == i_direct)
            {
                tnum = head->dc.left->offset->sp->i;
                t_varying = nearestAncestor(tempInfo[tnum]->variantLoop, b->loopParent);
                varying = t_varying;
            }
            if ((head->temps & TEMP_RIGHT) && head->dc.right->mode == i_direct)
            {
                tnum = head->dc.right->offset->sp->i;
                t_varying = nearestAncestor(tempInfo[tnum]->variantLoop, b->loopParent);
                // if t_varying is a more inner level than varying, we need to choose
                // t_varying because we need the innermost loop
                if (isAncestor(varying, t_varying))
                    varying = t_varying;
            }
            tnum = head->ans->offset->sp->i;
            tempInfo[tnum]->variantLoop = varying;
        }
        head = head->fwd;
    }
    while (children)
    {
        CalculateLoopInvariants(children->block);
        children = children->next;
    }
}
static BriggsSet* candidates;
static std::stack<unsigned> inductionCandidateStack;

static void PruneInductionCandidate(int tnum, Loop* l)
{
    if (tempInfo[tnum]->size >= ISZ_FLOAT)
    {
        briggsReset(candidates, tnum);
    }
    else
    {
        QUAD* I = tempInfo[tnum]->instructionDefines;
        if (I)
        {
            switch (I->dc.opcode)
            {
                case i_phi: {
                    PHIDATA* pd = I->dc.v.phi;
                    struct _phiblock* pb = pd->temps;
                    while (pb)
                    {
                        if (!briggsTest(candidates, pb->Tn) && !isInvariant(pb->Tn, l))
                        {
                            briggsReset(candidates, tnum);
                            break;
                        }
                        pb = pb->next;
                    }
                }
                break;
                case i_add:
                case i_sub:
                    if (I->temps & TEMP_RIGHT)
                    {
                        int tn2 = I->dc.right->offset->sp->i;
                        if (!briggsTest(candidates, tn2))
                            briggsReset(candidates, tnum);
                    }
                    /* FALLTHROUGH */
                case i_neg:
                case i_assn:
                    if (I->temps & TEMP_LEFT)
                    {
                        int tn2 = I->dc.left->offset->sp->i;
                        if (!briggsTest(candidates, tn2))
                            briggsReset(candidates, tnum);
                    }
                    break;
                default:
                    diag("PruneInductionCandidate: invalid form");
                    break;
            }
        }
        else
        {
            briggsReset(candidates, tnum);
        }
    }
}
/* minor problem: if an induction variable spans multiple loops
 * an induction set will be created for each loop.  These sets will
 * be identical
 */
static void CalculateInductionCandidates(Loop* l)
{
    LIST *blocks, *p;
    int i;
    briggsClear(candidates);
    while (!inductionCandidateStack.empty())
        inductionCandidateStack.pop();

    /* done here just in case for some reason an induction set drills down
     * into a lower loop
     */
    for (i = 0; i < tempCount; i++)
        tempInfo[i]->onstack = false;

    for (i = 0; i < l->blocks->top; i++)
    {
        Block* b = blockArray[l->blocks->data[i]];
        if (b)
        {
            QUAD* head = b->head;
            while (head != b->tail->fwd)
            {
                switch (head->dc.opcode)
                {
                    case i_add:
                    case i_sub:
                        if ((head->temps & TEMP_ANS) && head->ans->mode == i_direct)
                        {
                            if (head->dc.left->mode == i_immed || ((head->temps & TEMP_LEFT) && head->dc.left->mode == i_direct))
                                if (head->dc.right->mode == i_immed ||
                                    ((head->temps & TEMP_RIGHT) && head->dc.right->mode == i_direct))
                                {
                                    if (head->ans->size < ISZ_FLOAT && head->dc.left->size < ISZ_FLOAT &&
                                        head->dc.right->size < ISZ_FLOAT)
                                    {
                                        int tnum = head->ans->offset->sp->i;
                                        briggsSet(candidates, tnum);
                                        inductionCandidateStack.push(tnum);
                                        tempInfo[tnum]->onstack = true;
                                    }
                                }
                        }
                        break;
                    case i_neg:
                    case i_assn:
                        if ((head->temps & TEMP_ANS) && head->ans->mode == i_direct)
                        {
                            if (head->dc.left->mode == i_immed || ((head->temps & TEMP_LEFT) && head->dc.left->mode == i_direct))
                            {
                                if (head->ans->size < ISZ_FLOAT && head->dc.left->size < ISZ_FLOAT)
                                {
                                    int tnum = head->ans->offset->sp->i;
                                    briggsSet(candidates, tnum);
                                    inductionCandidateStack.push(tnum);
                                    tempInfo[tnum]->onstack = true;
                                }
                            }
                        }
                        break;
                    case i_phi: {
                        PHIDATA* pd = head->dc.v.phi;
                        int tnum = pd->T0;
                        if (tempInfo[tnum]->size < ISZ_FLOAT)
                        {
                            briggsSet(candidates, tnum);
                            inductionCandidateStack.push(tnum);
                            tempInfo[tnum]->onstack = true;
                        }
                    }
                    break;
                    default:
                        break;
                }
                /* prep for reshaping */
                switch (head->dc.opcode)
                {
                    case i_add:
                    case i_sub:
                    case i_mul:
                    case i_lsl:
                        if (head->ans->size < ISZ_FLOAT && head->dc.left->size < ISZ_FLOAT)
                        {
                            if (head->temps & TEMP_ANS)
                            {
                                int tnum = head->ans->offset->sp->i;
                                auto uses1 = tempInfo[tnum]->instructionUses;
                                if (uses1)
                                {
                                    for (auto uses : *uses1)
                                    {
                                        if ((uses->temps & TEMP_ANS) && uses->ans->mode == i_ind)
                                        {
                                            if (tnum == uses->ans->offset->sp->i)
                                            {
                                                tempInfo[tnum]->expressionRoot = true;
                                            }
                                        }
                                        if (uses->temps & TEMP_LEFT)
                                        {
                                            if (tnum == uses->dc.left->offset->sp->i)
                                            {
                                                if (uses->dc.left->mode == i_ind)
                                                    tempInfo[tnum]->expressionRoot = true;
                                                else if (head->dc.opcode != i_not && head->dc.opcode != i_neg)
                                                    if (!matchesop(head->dc.opcode, uses->dc.opcode))
                                                        tempInfo[tnum]->expressionRoot = true;
                                            }
                                        }
                                        if (uses->temps & TEMP_RIGHT)
                                        {
                                            if (tnum == uses->dc.right->offset->sp->i)
                                            {
                                                if (uses->dc.right->mode == i_ind)
                                                    tempInfo[tnum]->expressionRoot = true;
                                                else if (head->dc.opcode != i_not && head->dc.opcode != i_neg)
                                                    if (!matchesop(head->dc.opcode, uses->dc.opcode))
                                                        tempInfo[tnum]->expressionRoot = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
                head = head->fwd;
            }
        }
    }
    while (!inductionCandidateStack.empty())
    {
        int tnum = inductionCandidateStack.top();
        inductionCandidateStack.pop();
        tempInfo[tnum]->onstack = false;
        PruneInductionCandidate(tnum, l);
        if (!briggsTest(candidates, tnum))
        {
            auto uses1 = tempInfo[tnum]->instructionUses;
            if (uses1)
            {
                for (auto uses : *uses1)
                {
                    if (briggsTest(l->blocks, uses->block->blocknum))
                    {
                        if (uses->temps & TEMP_ANS)
                        {
                            int tnum = uses->ans->offset->sp->i;
                            if (briggsTest(candidates, tnum))
                            {
                                if (!tempInfo[tnum]->onstack)
                                    inductionCandidateStack.push(tnum);
                            }
                        }
                    }
                }
            }
        }
    }
}
static int max_dfs = 0;
static std::stack<unsigned> strongStack;
LIST* strongRegiondfs(int tnum)
{
    TempInfo* t = tempInfo[tnum];
    auto uses1 = t->instructionUses;
    LIST* rv = nullptr;
    t->temp = t->dfstOrder = max_dfs++;
    strongStack.push(tnum);
    t->visiteddfst = true;
    t->onstack = true;
    if (uses1)
    {
        for (auto uses : *uses1)
        {
            int ux = -1;
            switch (uses->dc.opcode)
            {
                case i_phi: {
                    PHIDATA* pd = uses->dc.v.phi;
                    if (tempInfo[pd->T0]->size < ISZ_FLOAT)
                        ux = pd->T0;
                }
                break;
                case i_add:
                case i_sub:
                case i_assn:
                case i_neg:
                    if (uses->temps & TEMP_ANS)
                    {
                        ux = uses->ans->offset->sp->i;
                        if (tempInfo[ux]->size >= ISZ_FLOAT)
                            ux = -1;
                    }
                    break;
                default:
                    break;
            }
            if (ux >= 0)
            {
                TempInfo* up = tempInfo[ux];
                if (!up->visiteddfst)
                {
                    LIST* l3 = strongRegiondfs(ux);
                    if (up->temp < t->temp)
                        t->temp = up->temp;
                    if (l3)
                    {
                        l3->next = rv;
                        rv = l3;
                    }
                }
                else if (up->onstack)
                {
                    if (up->dfstOrder < t->temp)
                        t->temp = up->dfstOrder;
                }
            }
        }
    }
    if (t->temp == t->dfstOrder)
    {
        int vp;
        ILIST* region = nullptr;
        LIST* temp;
        ILIST* temp1;
        do
        {
            vp = strongStack.top();
            strongStack.pop();
            tempInfo[vp]->onstack = false;
            temp1 = oAllocate<ILIST>();
            temp1->data = vp;
            temp1->next = region;
            region = temp1;
        } while (vp != tnum);
        temp = oAllocate<LIST>();
        temp->data = region;
        temp->next = rv;
        rv = temp;
    }
    return rv;
}
/* this returns a two-layer list
 * the top layer is a linked list of strong regions
 * each secondary layer is the induction set for the region
 * first element of list is the anchors
 */
static LIST* strongRegions(Loop* lp, ILIST** anchors)
{
    int i;
    QUAD* head;
    LIST* rv = nullptr;
    *anchors = nullptr;
    max_dfs = 0;
    for (i = 0; i < tempCount; i++)
    {
        tempInfo[i]->dfstOrder = 0;
        tempInfo[i]->visiteddfst = false;
        tempInfo[i]->temp = INT_MAX;
    }
    head = lp->entry->head->fwd;
    while (head != lp->entry->tail->fwd && (head->ignoreMe || head->dc.opcode == i_label))
        head = head->fwd;
    while (head != lp->entry->tail->fwd && head->dc.opcode == i_phi)
    {
        PHIDATA* pd = head->dc.v.phi;
        if (briggsTest(candidates, pd->T0) && tempInfo[pd->T0]->size < ISZ_FLOAT)
        {
            LIST* l1 = strongRegiondfs(pd->T0);
            if (l1)
            {
                l1->next = rv;
                rv = l1;
            }
            ILIST* l2 = oAllocate<ILIST>();
            l2->data = pd->T0;
            l2->next = *anchors;
            *anchors = l2;
        }
        head = head->fwd;
    }
    return rv;
}
void CalculateInduction(void)
{
    int i;

    candidates = briggsAlloc(tempCount);
    CalculateLoopInvariants(blockArray[0]);

    for (i = 0; i < loopArray.size(); i++)
    {
        Loop* lp = loopArray[i];
        if (lp && lp->type == LT_SINGLE)
        {
            LIST* strongTemps;
            ILIST* anchors = nullptr;
            CalculateInductionCandidates(lp);
            strongTemps = strongRegions(lp, &anchors);
            if (strongTemps && anchors)
            {
                LIST* regions = strongTemps;
                while (regions)
                {
                    ILIST* r = (ILIST*)regions->data;
                    if (r->next)
                    {
                        ILIST* t = anchors;
                        while (t)
                        {
                            while (r)
                            {
                                if (t->data == r->data)
                                    break;
                                r = r->next;
                            }
                            if (!r || t->data == r->data)
                                break;
                            t = t->next;
                        }
                        if (t || r)
                        {
                            INDUCTION_LIST* temp = oAllocate<INDUCTION_LIST>();
                            ILIST* q;
                            temp->vars = (ILIST*)regions->data;
                            temp->next = lp->inductionSets;
                            lp->inductionSets = temp;
                            q = (ILIST*)regions->data;
                            while (q)
                            {
                                /* the dominator walk will visit inner loops first,
                                 * the outer loops have higher indexes
                                 * we want the outermost loop
                                 */
                                tempInfo[(int)q->data]->inductionLoop = imax(i, tempInfo[(int)q->data]->inductionLoop);
                                q = q->next;
                            }
                        }
                    }
                    regions = regions->next;
                }
            }
        }
    }
    while (!strongStack.empty())
        strongStack.pop();
    while (!inductionCandidateStack.empty())
        inductionCandidateStack.pop();
}
}  // namespace Optimizer