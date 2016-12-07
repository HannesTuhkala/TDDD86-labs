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
   3200		68.321			0.704
   6400		548.040			3.119
  12800		4395.437		14.028


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
 *	punkten. Detta gör att programmet kör fyra nästlade for-loopar, med
 *  varje loop som börjar från värdet av variabeln i for-loopen och slutar på
 *  N - 3 + loopens nivå (0-4), vilket ger komplexiteten O(N^4). Alla andra steg i 
 *	programmet, som sortering och inläsning, tar konstant, linjär och
 *	nlog(N) tid, så dessa kan försummas eftersom N^4 växer mycket
 *	snabbare än allt annat.
 *	
 *	Algoritmen ligger därför i O(N^4) i det värsta fallet.
 *	
 **********************************************************************
 *	Fast.
 *	Det värsta fallet för denna algoritm är, till skillnad från brute force, 
 *	inträffar när inga punkter ligger på en linje med 4 eller fler punkter.
 *	Då blir while-loopen som letar efter punkter på rad linjär, då den söker
 *	genom N-3 punkter. Den mest kostsammma funktionen i den stora for-loopen blir 
 *	därför sorteringen av jämförelselistan den kostsammaste funktionen, som 
 *	kostar O(nlog(n)) tid. Eftersom den är i den stora for-loopen som itererar
 *	över alla punkter, utförs sorteringen n gånger.
 *	
 *	Algoritmen ligger därför i O(N^2log(N)).
 *	
 **********************************************************************/

Brute: O(N^4)

Sortering: O(N^2log(N))
