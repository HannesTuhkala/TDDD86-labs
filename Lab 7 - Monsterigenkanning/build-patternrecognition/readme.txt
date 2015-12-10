/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N		brute [s]      sortering [s]
 ----------------------------------
    150		0.008			0.001
    200		0.019			0.003
    300		0.070			0.006
    400		0.155			0.018
    800		1.087			0.065
   1600		8.576			0.208
   3200		68.321			
   6400		548.040
  12800		4395.437


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *	
 **********************************************************************
 *	Brute force.
 *	Det värsta fallet som kan inträffa för denna algoritm är att alla 
 *	punkter i filen ligger på en och samma linje. Detta är för att 
 *	programmet försöker optimera bort några beräkningar genom att inte 
 *	loopa genom alla punkter för den fjärde punkten om de tre första 
 *	första punkterna inte ligger på samma linje. Om alla punkter däremot
 *	ligger på samma linje, kommer den alltid att behöva kolla den fjärde
 *	punkten. Detta gör att programmet måste besöka alla kombinationer av 
 *	fyra punkter i filen, alltså nCr(n, 4) besök. Alla andra steg i 
 *	programmet, som sortering och inläsning, tar konstant, linjär 
 *	nlog(n) tid, så dessa kan försummas eftersom nCr(n, 4) växer mycket
 *	snabbare än allt annat.
 *	
 *	Algoritmen ligger därför i O(nCr(n, 4)) i det värsta fallet.
 *	
 **********************************************************************
 *	
 *	
 *	
 *	
 *	
 *	
 **********************************************************************/

Brute:

Sortering:
