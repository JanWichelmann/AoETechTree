## OVERVIEW

This is a new implementation of the ingame tech tree view (F2) completely replacing the old one. It is much easier moddable, as there are no hardcoded elements. Basically each element only requires its ID, type, age and rendering mode. The positioning is done by the rendering algorithm completely.

At the moment there is only one renderer, the "vanilla renderer". It uses the original tech tree SLPs, hence has hardcoded resolutions and age count. It is planned to add another renderer that uses modular graphics, so the tree appearance is more customizable.

As a consequence, the DAT tech tree structure used by this implementation is incompatible with the original one.
You can edit it with this tool: https://github.com/Janworks/AoETechTreeTool

## USAGE

The launcher starts the age2_x1.exe process and injects the TechTree.dll containing the code changes to add a new age.
I created this software while working on the (german) Agearena AddOn (http://www.agearena.de/forum/index.php?mode=viewforum&forum_id=7) and will update it periodically.

> AoETechTree.exe PARAMS

PARAMS is the usual call to the Age of Empires process, e.g.: age2_x1.exe nostartup

For mod developers using their own Games/[MODNAME] subfolder, the call may be: 
> AoETechTree.exe age2_x1.exe game=[MODNAME] nostartup


## SYSTEM REQUIREMENTS

As this software is build with Microsoft Visual Studio 2015, you'll need the appropiate Visual C++ redistributable: (https://www.microsoft.com/de-de/download/details.aspx?id=48145)

This software was tested with the UserPatch v1.4 installed, so there should be no incompabilities.

Also some virus scanners may have problems with this software, as it uses DLL injection to patch the running Age of Empires II process. This method is also used by many viruses, so some virus scanners block it by default. If you have problems running this software, try to create an exception in the scanners filter rules.


## TODO

* Recognize additional information the game gives, i.e. researched items, civs of allies...
* Add another renderer that is easier moddable and less hardcoded than the vanilla one in terms of age count, resolution and background images.


## LEGAL INFO & CREDITS

This software is published under the MIT/X11 license. Please read the LICENSE for further information.

The general approach to do a DLL injection ist based on the Code-Project article "A More Complete DLL Injection Solution Using CreateRemoteThread" (http://www.codeproject.com/Articles/20084/A-More-Complete-DLL-Injection-Solution-Using-Creat).
I would like to thank the author for his detailed explanations and examples and recommend this article to everybody who wants to get a deeper understanding of how a DLL injection is performed.