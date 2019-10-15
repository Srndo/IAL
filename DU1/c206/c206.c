
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou19796139
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int errflg;
int solved;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/

    L->First  = NULL;
    L->Act    = NULL;
    L->Last   = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free.
**/

  tDLElemPtr tmp;
  while(L->First != NULL)
  {
    tmp = L->First;
    L->First = tmp->rptr;
    free(tmp);
  }

  L->First  = NULL;
  L->Act    = NULL;
  L->Last   = NULL;
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

  tDLElemPtr tmp = malloc(sizeof(struct tDLElem));

  if(!tmp)
    DLError();
  else
  {
  tmp->data = val;          // priradime hodnotu
  tmp->lptr = NULL;         // pred tmp (prvym prvkom) nic nebude
  tmp->rptr = L->First;    // tmp bude ukazovat na byvali prvy prvok

  if(L->First == NULL)    // ak je zoznam prazdny tak tmp je zaroven aj poslednym prvkom
    L->Last = tmp;
  else
    L->First->lptr = tmp; // ak nieje prazdny tak previazeme tmp s nasledujucim prvokm

  L->First = tmp;         // nastavime tmp ako prvy prvok zoznamu
  }
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

  tDLElemPtr tmp = malloc(sizeof(struct tDLElem));

  if(!tmp)
    DLError();
  else
  {
  tmp->data = val;          // priradime hodnotu
  tmp->lptr = L->Last;      // tmp bude ukazovat na byvali posledny prvok
  tmp->rptr = NULL;         // za tmp (poslednym prvkom) nic nebude

  if(L->First == NULL)    // ak je zoznam prazdny tak tmp je zaroven aj prvym prvkom
    L->First = tmp;
  else
    L->Last->rptr = tmp; // ak nieje prazdny tak previazeme posledný prvok s tmp

  L->Last = tmp;         // nastavime tmp ako posledny prvok zoznamu
  }
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

  L->Act = L->First;

}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

  L->Act = L->Last;

}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
  if(!L->First)
    DLError();
  else
    *val = L->First->data;
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

if(!L->First)
  DLError();
else
  *val = L->Last->data;

}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
  if(!L->First)
    return;

  if(L->First == L-> Act)   //ak bol prvy prvok aktivny, aktivita sa straca
    L->Act = NULL;

  tDLElemPtr tmp = L->First;
  L->First = tmp->rptr;         //nastavenie druheho prvku na prvy prvok
  L->First->lptr = NULL;        //nastavenie noveho prveho prvku aby "pred seba ukazoval" na NULL

  if(L->First->rptr == NULL)    //Ak je nas novy prvy prvok zaroven aj poslednym
    L->Last = L->First;

  free(tmp);
}

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
  if(!L->First)
    return;

  if(L->Last == L-> Act)   //ak bol posledny prvok aktivny, aktivita sa straca
    L->Act = NULL;

    tDLElemPtr tmp = L->Last;


    L->Last = tmp->lptr;         //nastavenie predposledneho prvku na posledny prvok

    if(!L->Last)                 //ak sa posledný prvok == NULL, zoznam je prázdny
		  L->First = NULL;
    else
      L->Last->rptr = NULL;     //inac nastavime previazanie zoznamu a to tak ze pointer za posledny prvok bude NULL

      free(tmp);

}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/

  if(!L->Act)
    return;

  if(L->Act == L->Last)
    return;

    tDLElemPtr del = L->Act->rptr;

    if(!del->rptr)      //ak je situacia Act| del | NULL
    {
      L->Act->rptr = NULL;
      L->Last = L->Act;   //Potom aktualny prvok je zaroven poslednym
    }
    else
    {
      L->Act->rptr = del->rptr;   // previazanie prvkov
      del->rptr->lptr = L->Act;   // previazanie prvokv
    }

    free(del);
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/

  if(!L->Act)
    return;

  if(L->Act == L->First)
    return;

    tDLElemPtr del = L->Act->lptr;

    if(!del->lptr)      //ak je situacia NULL | del | Act
    {
      L->Act->lptr = NULL;
      L->First = L->Act;   //Potom aktualny prvok je zaroven prvym
    }
    else                // prvok | del | Act
    {
      L->Act->lptr = del->lptr;   // previazanie prvkov
      del->lptr->rptr = L->Act;   // previazanie prvokv
    }

    free(del);

}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
  if(!L->Act)
    return;

  tDLElemPtr tmp = malloc(sizeof(struct tDLElem));
  if(!tmp)
  {
    DLError();
    return;
  }

  tmp->data = val;
  tmp->lptr = L->Act;
  tmp->rptr = L->Act->rptr;

  if(tmp->rptr == NULL) //stal sa poslednym prvkom zoznamu
      L->Last = tmp;

  else
    L->Act->rptr->lptr = tmp;

  L->Act->rptr = tmp;
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
  if(!L->Act)
    return;

  tDLElemPtr tmp = malloc(sizeof(struct tDLElem));
  if(!tmp)
  {
    DLError();
    return;
  }

  tmp->data = val;
  tmp->lptr = L->Act->lptr;
  tmp->rptr = L->Act;

  if(tmp->lptr == NULL) //stal sa prvym prvkom zoznamu
      L->First = tmp;

  else
    L->Act->lptr->rptr = tmp;

  L->Act->lptr = tmp;
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
  if(!L->Act)
  {
    DLError();
    return;
  }

  *val = L->Act->data;

}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
  if(!L->Act)
    return;

  L->Act->data = val;

}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
  if(!L->Act)
    return;

    L->Act = L->Act->rptr;

}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
  if(!L->Act)
    return;

    L->Act = L->Act->lptr;

}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/

  return L->Act ? 1 : 0;
}

/* Konec c206.c*/
