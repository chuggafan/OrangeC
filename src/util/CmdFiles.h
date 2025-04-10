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

#ifndef CMDFILES_H
#define CMDFILES_H

#include <vector>
#include <string>

class CmdSwitchFile;
class CmdFiles
{
    typedef std::vector<std::string> FileName;

  public:
    CmdFiles() {}
    CmdFiles(char** fileList, bool recurseSubdirs = false) { Add(fileList, recurseSubdirs); }
    CmdFiles(const std::string& name, bool recurseSubdirs = false) { Add(name, recurseSubdirs); }
    ~CmdFiles();

    bool Add(const std::string& name, bool recurseSubdirs = false, bool subdirs = false);
    bool AddFromPath(const std::string& name, const std::string& path);
    bool Add(char** fileList, bool recurseSubdirs = false);
    bool Add(CmdFiles& other)
    {
        for (auto a : other.names)
        {
            Add(a);
        }
        return true;
    }
    bool Add(CmdSwitchFile& switchFile);
    void Remove(const std::string& name);
    typedef FileName::iterator iterator;

    iterator begin() { return names.begin(); }
    iterator end() { return names.end(); }
    size_t size() const { return names.size(); }
    inline std::string operator[](int index) const { return names[index]; }
    static const char* DIR_SEP;
    static const char* PATH_SEP;

  protected:
    bool RecurseDirs(const std::string& path, const std::string& name, bool recurseDirs);

  private:
    FileName names;
};
#endif
