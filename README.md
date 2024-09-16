<pre> 
            ______                      __
           / ____/________ _____  _____/ /
          / /   / ___/ __ `/ __ \/ ___/ / 
         / /___/ /  / /_/ / /_/ (__  )_/  
         \____/_/   \__,_/ .___/____(_)   
                        /_/               
                                          
                  version 2.1
     Copyright (c) 2024 Elwynor Technologies
</pre>
          
## WHAT IS CRAPS?

 Craps! is a simple single-player Craps implementation that allows users to 
 bet credits on the pass-line.
 
## GAMEPLAY
 
 The game asks users to bet credits (your system must provide credits to users
 in order to use this game) on the pass-line and roll the dice. 
 
 The pass-line bet form of Craps is when you bet in the "come out roll" that 
 you will roll a 7 or 11 (a natural - a win), avoiding 2, 3, or 11 (craps - a
 loss), otherwise the roll becomes a point. Then, in the Point Phase, you must 
 continue to roll until you re-roll your point (a win) or roll a 7 (a loss).
 
## COMMANDS
 
 The in-game commands are simple - enter the amount to bet, and roll!
 
 The following are main menu commands:
<pre>
 I  ...  Read instructions
 C  ...  Shows number of credits available
 P  ...  Play Craps!
 X  ...  Exits Craps!
</pre> 

## INSTALLATION AND CONFIGURATION
  
 Simply unzip the module archive to your BBS directory, add it to your menu,
 configure the MSG file to your liking, and start the BBS! It's that easy!
 
 In LEVEL3, you can set a key required to play the game. In LEVEL4, you can
 decide whether or not to show a login message, and set a maximum credit bet.
 LEVEL6 has a number of text blocks to customize.
 
## GAME HISTORY
 
 Craps! was originally written and developed by Rick Hadsall under the Netcom
 Software TPD name (the predecessor to Elwynor Technologies) in 1989. The game
 was distributed as shareware for The Major BBS v5.x. It was shelved until
 being revived along with many other modules in 2004 at the start of The Major
 BBS Restoration Project.
 
 Its first Major BBS 6, Worldgroup 1, and Worldgroup 2 DOS release was in 
 October 2004. In February 2006, it was released for Worldgroup 3.2
 
 In September 2024 it was released for Major BBS V10 and open sourced. 
 
## LICENSE

 This project is licensed under the AGPL v3. Additional terms apply to 
 contributions and derivative projects. Please see the LICENSE file for 
 more details.

## CONTRIBUTING

 We welcome contributions from the community. By contributing, you agree to the
 terms outlined in the CONTRIBUTING file.

## CREATING A FORK

 If you create an entirely new project based on this work, it must be licensed 
 under the AGPL v3, assign all right, title, and interest, including all 
 copyrights, in and to your fork to Rick Hadsall and Elwynor Technologies, and 
 you must include the additional terms from the LICENSE file in your project's 
 LICENSE file.

## COMPILATION

 This is a Worldgroup 3.2 / Major BBS v10 module. It's compiled using Borland
 C/C++ 5.0 for Worldgroup 3.2. If you have a working Worldgroup 3.2 development
 kit, a simple "make -f ELWCRAPS" should do it! For Major BBS v10, import this
 project folder in the isv/ subtree of Visual Studio 2022, right click the
 project name and choose build! When ready to build for "release", ensure you
 are building for release.

 Note: this module will also compile for Worldgroup 2 for DOS using the mkv2p 
 builder. I haven't tested this version on WG2 however. 

## PACKING UP

 The DIST folder includes all of the items that should be packaged up in a 
 ELWCRAPS.ZIP. When unzipped in a Worldgroup 3.2 or Major BBS V10 installation 
 folder, it "installs" the module.
 
 When packaging for WG2, include the GALV3.DLL in case the SysOp doesn't 
 already have it.
 