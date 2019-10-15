
/* c401.c: **********************************************************}
{* Tema: Rekurzivni implementace operaci nad BVS
**                                         Vytvoril: Petr Prikryl, listopad 1994
**                                         Upravy: Andrea Nemcova, prosinec 1995
**                                                      Petr Prikryl, duben 1996
**                                                   Petr Prikryl, listopad 1997
**                                  Prevod do jazyka C: Martin Tucek, rijen 2005
**                                         Upravy: Bohuslav Krena, listopad 2009
**                                                 Karel Masarik, rijen 2013
**                                                 Radek Hranicky 2014-2018
**
** Implementujte rekurzivnim zpusobem operace nad binarnim vyhledavacim
** stromem (BVS; v anglictine BST - Binary Search Tree).
**
** Klicem uzlu stromu je jeden znak (obecne jim muze byt cokoliv, podle
** ceho se vyhledava). Uzitecnym (vyhledavanym) obsahem je zde integer.
** Uzly s mensim klicem lezi vlevo, uzly s vetsim klicem lezi ve stromu
** vpravo. Vyuzijte dynamickeho pridelovani pameti.
** Rekurzivnim zpusobem implementujte nasledujici funkce:
**
**   BSTInit ...... inicializace vyhledavaciho stromu
**   BSTSearch .... vyhledavani hodnoty uzlu zadaneho klicem
**   BSTInsert .... vkladani nove hodnoty
**   BSTDelete .... zruseni uzlu se zadanym klicem
**   BSTDispose ... zruseni celeho stromu
**
** ADT BVS je reprezentovan korenovym ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje klic (typu char), podle
** ktereho se ve stromu vyhledava, vlastni obsah uzlu (pro jednoduchost
** typu int) a ukazatel na levy a pravy podstrom (LPtr a RPtr). Presnou definici typu
** naleznete v souboru c401.h.
**
** Pozor! Je treba spravne rozlisovat, kdy pouzit dereferencni operator *
** (typicky pri modifikaci) a kdy budeme pracovat pouze se samotnym ukazatelem
** (napr. pri vyhledavani). V tomto prikladu vam napovi prototypy funkci.
** Pokud pracujeme s ukazatelem na ukazatel, pouzijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {
/*   -------
** Funkce provede pocatecni inicializaci stromu pred jeho prvnim pouzitim.
**
** Overit, zda byl jiz strom predany pres RootPtr inicializovan, nelze,
** protoze pred prvni inicializaci ma ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Programator vyuzivajici ADT BVS tedy musi zajistit, aby inicializace
** byla volana pouze jednou, a to pred vlastni praci s BVS. Provedeni
** inicializace nad neprazdnym stromem by totiz mohlo vest ke ztrate pristupu
** k dynamicky alokovane pameti (tzv. "memory leak").
**
** Vsimnete si, ze se v hlavicce objevuje typ ukazatel na ukazatel.
** Proto je treba pri prirazeni pres RootPtr pouzit dereferencni operator *.
** Ten bude pouzit i ve funkcich BSTDelete, BSTInsert a BSTDispose.
**/

	*RootPtr = NULL;

}

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{
/*  ---------
** Funkce vyhleda uzel v BVS s klicem K.
**
** Pokud je takovy nalezen, vraci funkce hodnotu TRUE a v promenne Content se
** vraci obsah prislusneho uzlu.'Pokud prislusny uzel neni nalezen, vraci funkce
** hodnotu FALSE a obsah promenne Content neni definovan (nic do ni proto
** neprirazujte).
**
** Pri vyhledavani v binarnim stromu bychom typicky pouzili cyklus ukonceny
** testem dosazeni listu nebo nalezeni uzlu s klicem K. V tomto pripade ale
** problem reste rekurzivnim volani teto funkce, pricemz nedeklarujte zadnou
** pomocnou funkci.
**/

	if(RootPtr == NULL)
		return FALSE;

	//AK najdeme hladany kluc priradime obsah uzlu do premennej Content
	else if(RootPtr->Key == K)
	{
		*Content = RootPtr->BSTNodeCont;
		return TRUE;
	}

	//Ak je hladany kluc vacsi ako kluc korena pokracujeme v hladani v pravej casti stromu
	else if (K > RootPtr->Key)
		return BSTSearch(RootPtr->RPtr, K, Content);

	//Ak je hladany kluc mensi ako kluc korena pokracujeme v hladani v lavej casti stromu
	return	BSTSearch(RootPtr->LPtr, K, Content);
}


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{
/*   ---------
** Vlozi do stromu RootPtr hodnotu Content s klicem K.
**
** Pokud jiz uzel se zadanym klicem ve stromu existuje, bude obsah uzlu
** s klicem K nahrazen novou hodnotou. Pokud bude do stromu vlozen novy
** uzel, bude vlozen vzdy jako list stromu.
**
** Funkci implementujte rekurzivne. Nedeklarujte zadnou pomocnou funkci.
**
** Rekurzivni implementace je mene efektivni, protoze se pri kazdem
** rekurzivnim zanoreni uklada na zasobnik obsah uzlu (zde integer).
** Nerekurzivni varianta by v tomto pripade byla efektivnejsi jak z hlediska
** rychlosti, tak z hlediska pametovych naroku. Zde jde ale o skolni
** priklad, na kterem si chceme ukazat eleganci rekurzivniho zapisu.
**/

	//Ak je ukazovatel NULL alokujeme strukutu pre novy uzol a naplnime ju
	if(*RootPtr == NULL)
	{
		*RootPtr = malloc(sizeof(struct tBSTNode));
		if(RootPtr == NULL)
			return;
		(*RootPtr)->LPtr = NULL;
		(*RootPtr)->RPtr = NULL;
		(*RootPtr)->Key = K;
		(*RootPtr)->BSTNodeCont = Content;
	}
	//Uzol s klucom "K" uz existuje, prepiseme obsah uzlu
	else if((*RootPtr)->Key == K)
		(*RootPtr)->BSTNodeCont = Content;
	//Ak je K vacsie ako Key na ktory prave ukazovatel ukazuje ideme do praveho podstromu
	else if(K > (*RootPtr)->Key)
		BSTInsert(&(*RootPtr)->RPtr, K, Content);
	//Ak je K mensie ako Key na ktory prave ukazovatel ukazuje ideme do laveho podstromu
	else
		BSTInsert(&(*RootPtr)->LPtr, K, Content);

}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
/*   ------------------
** Pomocna funkce pro vyhledani, presun a uvolneni nejpravejsiho uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do ktereho bude presunuta hodnota
** nejpravejsiho uzlu v podstromu, ktery je urcen ukazatelem RootPtr.
** Predpoklada se, ze hodnota ukazatele RootPtr nebude NULL (zajistete to
** testovanim pred volani teto funkce). Tuto funkci implementujte rekurzivne.
**
** Tato pomocna funkce bude pouzita dale. Nez ji zacnete implementovat,
** prectete si komentar k funkci BSTDelete().
**/

	//Pokial RPtr sa != NULL rekurzivne volame funkciu
	if((*RootPtr)->RPtr)
		ReplaceByRightmost(PtrReplaced, &(*RootPtr)->RPtr);
	//Nasli sme uzol najviac v pravo koncime rekurziu a ulozime hodnoty
	else
	{
			PtrReplaced->Key = (*RootPtr)->Key;
			PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
	}

}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{
/*   ---------
** Zrusi uzel stromu, ktery obsahuje klic K.
**
** Pokud uzel se zadanym klicem neexistuje, nedela funkce nic.
** Pokud ma ruseny uzel jen jeden podstrom, pak jej zdedi otec ruseneho uzlu.
** Pokud ma ruseny uzel oba podstromy, pak je ruseny uzel nahrazen nejpravejsim
** uzlem leveho podstromu. Pozor! Nejpravejsi uzel nemusi byt listem.
**
** Tuto funkci implementujte rekurzivne s vyuzitim drive deklarovane
** pomocne funkce ReplaceByRightmost.
**/

	if(!*RootPtr)
		return;

	tBSTNodePtr delete = *RootPtr;
	//Ak K < Key (prvoku na ktory prave ukazujeme) ideme do lavej casti podstromu
 	if(K < (*RootPtr)->Key)
	{
		if((*RootPtr)->LPtr)
			BSTDelete(&(*RootPtr)->LPtr, K);
	}
	//Ak K > Key (prvoku na ktory prave ukazujeme) ideme do pravej casti podstromu
	else if(K > (*RootPtr)->Key)
	{
		if((*RootPtr)->RPtr)
			BSTDelete(&(*RootPtr)->RPtr, K);
	}
	//Ked najdeme odpovedajuci uzol nasmu klucu, ideme "previazat" strom
	else if((*RootPtr)->Key == K)
	{
		//Ak ma ruseny uzol iba lavy poduzol
		if(!(*RootPtr)->RPtr && (*RootPtr)->LPtr)
		{
			*RootPtr = (*RootPtr)->LPtr;	//Nastavime ukazatel na dalsi poduzol v lavej casti stromu
		 	free(delete);
		}
		//Ak ma ruseny uzol iba pravy poduzol
		else if((*RootPtr)->RPtr && !(*RootPtr)->LPtr)
		{
			*RootPtr = (*RootPtr)->RPtr;	//Nastavime ukazatel na dalsi poduzol v pravej casti stromu
			free(delete);
		}
		//Ak ma ruseny uzol oba poduzly
		else if((*RootPtr)->RPtr && (*RootPtr)->LPtr)
		{
			ReplaceByRightmost(delete, &(*RootPtr)->LPtr); 	//Do delete ulozime najpravsi uzol
			BSTDelete(&(*RootPtr)->LPtr, delete->Key); 			//Najpravsi uzol zmazeme
		}
		//Ak nema ruseny prvok ziadne poduzly
		else
		{
			free(*RootPtr);
			*RootPtr = NULL;
		}
	 }

}

void BSTDispose (tBSTNodePtr *RootPtr) {
/*   ----------
** Zrusi cely binarni vyhledavaci strom a korektne uvolni pamet.
**
** Po zruseni se bude BVS nachazet ve stejnem stavu, jako se nachazel po
** inicializaci. Tuto funkci implementujte rekurzivne bez deklarovani pomocne
** funkce.
**/

	//Podmienka pre ukoncenie rekurzie
	if(*RootPtr == NULL)
		return;

	//Rekurzne zavolame funkcie pre pravy aj lavy poduzol
	BSTDispose(&(*RootPtr)->RPtr);
	BSTDispose(&(*RootPtr)->LPtr);
	free(*RootPtr);
	*RootPtr = NULL;


}

/* konec c401.c */
