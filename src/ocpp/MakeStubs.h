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

#ifndef MakeStubs_h
#define MakeStubs_h

#include <iostream>
#include <string>

class PreProcessor;

class MakeStubs
{
  public:
    MakeStubs(PreProcessor& Processor, bool UserOnly, bool PhonyTargets, const std::string& InputFile,
              const std::string& OutputFile, const std::string& Targets, const std::string& QuotedTargets) :
        preProcessor(Processor),
        userOnly(UserOnly),
        phonyTargets(PhonyTargets),
        inputFile(InputFile),
        outputFile(OutputFile),
        targets(Targets),
        quotedTargets(QuotedTargets)
    {
    }
    void Run(std::ostream* out);

  protected:
    std::string Escape(const std::string& string);

  private:
    PreProcessor& preProcessor;
    bool userOnly;
    bool phonyTargets;
    const std::string& inputFile;
    const std::string& outputFile;
    const std::string& targets;
    const std::string& quotedTargets;
};

#endif