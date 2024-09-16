/*****************************************************************************
 *   ELWCRAPS.C   V2.0(6.x+)                                   C R A P S !   *
 *                                                                           *
 *   Copyright (C) 1989,2004,2024 Rick Hadsall.  All Rights Reserved.        *
 *                                                                           *
 *   Description:        Craps - A small casino game module                  *
 *                 Asks user to bet from 1-x credits on dice roll            *
 *                   *** A fun, addictive mini-casino game! ***              *
 *                                                                           *
 *                                         - first started R. Hadsall 1989   *
 *                                         - v5.x code R. Hadsall 01/03/1990 *
 *                                         - v6.x code R. Hadsall 10/24/2004 *
 *                                         - WG32 code R. Hadsall 02/12/2006 *
 *                                         - v10  code R. Hadsall 09/15/2022 *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      * 
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "elwcraps.h"

/* function declarations */
GBOOL loncr(VOID);
GBOOL crapsrou(VOID);
VOID  clscr(VOID);
VOID  initrnd(VOID);
INT   getrnd(INT lo, INT hi);
INT   roll(GBOOL init);

struct module elwcraps={      /* module interface block               */
     "",                      /*    name used to refer to this module */
     loncr,                   /*    user logon supplemental routine   */
     crapsrou,                /*    input routine if selected         */
     dfsthn,                  /*    status-input routine if selected  */
     NULL,                    /*    "injoth" routine for this module  */
     NULL,                    /*    user logoff supplemental routine  */
     NULL,                    /*    hangup (lost carrier) routine     */
     NULL,                    /*    midnight cleanup routine          */
     NULL,                    /*    delete-account routine            */
     clscr                    /*    finish-up (sys shutdown) routine  */
};

                              /* Craps Game and Input Variables       */
INT bet,                      /* Credits the user bet for the game    */
    point,                    /* The point for the point phase        */
    rolltot;                  /* Total roll score                     */
    
                              /* Craps MSG configuration variables    */
LONG maxbet;                  /* Maximum allowable bet per game       */
INT crapmsv;                  /* Display logon message?               */

static
HMCVFILE crmb;                /* Message file pointer                 */

static
INT crstt;					      /* User Craps State                     */

#define VERSION "2.1"       

void EXPORT
init__elwcraps()              /* initialize Craps                     */
{   
     stzcpy(elwcraps.descrp,gmdnam("ELWCRAPS.MDF"),MNMSIZ);
     crstt=register_module(&elwcraps);     
     
     crmb=opnmsg("elwcraps.mcv");
     maxbet=lngopt(MAX2BET,1,1000000L);
     crapmsv=ynopt(CRAPMSV);

     shocst(spr("ELW Craps v%s",VERSION),"(C) Copyright 1989-2024 Elwynor Technologies - www.elwynor.com");
}

GBOOL
loncr(VOID)                   /* Display User Logon Message           */
{
  if (crapmsv) {
     setmbk(crmb);
     prfmsg(LOGIN);
     outprf(usrnum);
  }
  return(0);
}

GBOOL
crapsrou(VOID)                /* Craps main input routine             */
{
  setmbk(crmb);
  switch (usrptr->substt) {
  case 0: // Just entered module
       prfmsg(MMENU);
       usrptr->substt=1;
       break;
  case 1: // Main Game Menu
       if (sameas(margv[0],"x")) {
         prfmsg(LEAVE,usaptr->userid);
         return(0);
       }
       else if (sameas(margv[0],"?")) {
         prfmsg(MMENU);
         usrptr->substt=1;
       }
       else if (sameas(margv[0],"\0") || sameas(margv[0],"")) {
         prfmsg(SHMENU);
         usrptr->substt=1;
       }
       else if (sameas(margv[0],"i")) {
         prfmsg(CRINS);
         prfmsg(SHMENU);
         usrptr->substt=1;
       }
       else if (sameas(margv[0],"c")) {
         prfmsg(CREDS,ltoa(usaptr->creds));
         prfmsg(SHMENU);
         usrptr->substt=1;
       }
       else if (sameas(margv[0],"p")) {
         if (!hasmkey(CRAPKEY)) {  // doesn't have the right key to play
           prfmsg(NOTLIV,usaptr->userid);
           prfmsg(SHMENU);
           usrptr->substt=1;
         }
         else { // make your bet!
           prfmsg(GIVBET,maxbet);
           usrptr->substt=2;
           break;
         }
       }
       else {                 /* Selection Invalid */
         prfmsg(NOGOOD);
         prfmsg(SHMENU);
         usrptr->substt=1;
       }
       break;
  case 2: // Come Out Roll
       if (atoi(margv[0]) > 0 && atoi(margv[0]) < maxbet+1 || sameas(margv[0],"0")) {
         bet=atoi(margv[0]);

         // make sure the input was good, and the user has credits
         if (bet <= 0) {
           prfmsg(NOTZER,maxbet);
           prfmsg(GIVBET,maxbet);
           usrptr->substt=2;
           break;
         }
         if (usaptr->creds == 0) {
           prfmsg(NOCREDS,usaptr->userid);
           usrptr->substt=1;
           break;
         }
         if (!rtstcrd(bet)) {
           prfmsg(NOTENF,ltoa(usaptr->creds));
           prfmsg(GIVBET,maxbet);
           usrptr->substt=2;
           break;
         }
   
         rolltot=roll(TRUE);   

         if (rolltot == 7 || rolltot == 11) { // natural - a win
           prfmsg(YOUWIN,usaptr->userid,bet);
           addcrd(usaptr->userid,ltoa(bet),1);
           prfmsg(SHMENU);
           usrptr->substt=1;
         }
         else if (rolltot < 4 || rolltot == 12) { // craps - a loss
           prfmsg(UCRAPO,usaptr->userid,bet);
           rdedcrd(bet,0);
           prfmsg(SHMENU);
           usrptr->substt=1;
           break;
         }
         else { // set the point for the point phase
           prfmsg(POINT,usaptr->userid,rolltot);
           point = rolltot;
           prfmsg(HITKEY);
           usrptr->substt=3;
           break;
         }
         usrptr->substt=1;
         break;
       }
       if (sameas(margv[0],"x") || margc==0) { // quitting game
         prfmsg(ABORT);
         prfmsg(MMENU);
         usrptr->substt=1;
         break;
       }
       else { // input was invalid, try again
         prfmsg(BADBET,maxbet);
         prfmsg(GIVBET,maxbet);
         usrptr->substt=2;
         break;
       }
  case 3: // Point Phase
       rolltot = roll(FALSE);
       if (rolltot == point) { // point matched - a win
         prfmsg(UGOTPT,usaptr->userid,bet);
         addcrd(usaptr->userid,ltoa(bet),1);
         prfmsg(SHMENU);
         usrptr->substt=1;
         break;
       }
       else if (rolltot == 7) { // 7 rolled - a loss
         prfmsg(UGOT7,usaptr->userid,bet);
         rdedcrd(bet,0);
         prfmsg(SHMENU);
         usrptr->substt=1;
         break;
       }
       else { // roll again!
         prfmsg(NOTPT,usaptr->userid,point);
         prfmsg(HITKEY);
         usrptr->substt=3;
         break;
       }
  }
  outprf(usrnum);
  return(1);
}

INT
roll(GBOOL init)              /* roll the dice!                       */
{
  INT die1, die2, total;
  
  setmbk(crmb);
  prfmsg(ROLLIP);
  if (init) initrnd();
  die1=getrnd(1,6); 
  prfmsg(DIE1+die1 - 1);
  die2=getrnd(1,6);
  prfmsg(DIE1+die2 - 1);
  total = die1 + die2;
  prfmsg(DIETOT,total);

  return(total);   
}

VOID
initrnd(VOID)                 /* initialize random number seed        */
{
#ifdef __BUILDV10MODULE  
  srand((unsigned)time(NULL)); // BBSV10
#else
  randomize(); // WG32, MBBS6/WG1/WG2
#endif
}

INT
getrnd(INT lo,INT hi)         /* Returns random # between lo and hi   */
{
#ifdef __BUILDV10MODULE
  return(lo + rand() % (hi - lo + 1)); // BBSV10
#else
  return (random(hi - lo + 1) + lo); //WG32, MBBS6/WG1/WG2
#endif
}

VOID
clscr(VOID)                                        /* close Craps file for shutdown */
{
  clsmsg(crmb);
}
