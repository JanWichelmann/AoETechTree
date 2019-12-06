## OVERVIEW

This is a new implementation of the ingame tech tree view (F2) completely replacing the old one. It is much easier moddable, as there are no hardcoded elements. Basically each element only requires its ID, type, age and rendering mode. The positioning is done by the rendering algorithm completely.

At the moment there is only one renderer, the "vanilla renderer". It uses the original tech tree node placement (including compression using spare place in subtrees of the same parent building), everything else like background graphics, control positions and sizes, age count and much more is completely customizable. This design data is also stored in the DAT file.

As a consequence, the DAT tech tree structure used by this implementation is incompatible with the original one (but an unmodified game executable will still work with the new DAT file format, because the old tech tree data persists).
You can edit it with this tool: https://github.com/Janworks/AoETechTreeTool

If you want to do more modding than just changing the tech tree view itself, use the TechTreeEditor, which also exports the new tech tree format: https://github.com/Janworks/TechTreeEditor

I created this software while working on the (german) Agearena AddOn (https://agearena.de/forum/viewtopic.php?f=6&t=1014) and will update it periodically.


## USAGE

Unpack the EXE and DLL files to the age2_x1 folder of Age of Empires II. If you haven't already created a custom empires2_x1_p1.dat with the new tech tree, you can unpack the empires2_x1_p1.dat of the archive into the DATA folder, replacing the old one (do not forget a backup!).

The launcher starts the age2_x1.exe process and injects the TechTree.dll containing the code changes to add a new age.

> AoETechTree.exe PARAMS

PARAMS is the usual call to the Age of Empires process, e.g.: age2_x1.exe nostartup

For mod developers using their own Games/[MODNAME] subfolder, the call may be: 
> AoETechTree.exe age2_x1.exe game=[MODNAME] nostartup

This mod can also be loaded with [aoc-mmmod](https://github.com/SiegeEngineers/aoc-mmmod) instead of using the custom launcher. To do so, unpack TechTree.dll into the Games/[MODNAME]/mmmods/ folder for your mod.

## SYSTEM REQUIREMENTS

As this software is build with Microsoft Visual Studio 2017, you'll need the appropiate Visual C++ redistributable: (https://go.microsoft.com/fwlink/?LinkId=746572)

This software was tested with the UserPatch v1.4 installed, so there should not be any incompabilities.

Also some virus scanners may have problems with this software, as it uses DLL injection to patch the running Age of Empires II process. This method is also used by many viruses, so some virus scanners block it by default. If you have problems running this software, try to create an exception in the scanner's filter rules.


## LEGAL INFO & CREDITS

This software is published under the MIT/X11 license. Please read the LICENSE for further information.

The general approach to do a DLL injection is based on the Code-Project article "A More Complete DLL Injection Solution Using CreateRemoteThread" (http://www.codeproject.com/Articles/20084/A-More-Complete-DLL-Injection-Solution-Using-Creat).
I would like to thank the author for his detailed explanations and examples and recommend this article to everybody who wants to get a deeper understanding of how a DLL injection is performed.
