# RGSS Linker
DLL permettant d'utiliser l'interface d'extension Ruby contenue dans RGSS104E.dll
## Comment l'utiliser ?
Avant toute chose, il vaut que RGSS Linker soit initialisé, sachez que le RGSS peut se trouver à différents endroits de la mémoire donc RGSSLinker doit retrouver le RGSS.
Pour initialiser le RGSS Linker il suffit d'insérer les lignes suivantes dans l'extesion principale :
```if(RGSSLinker_Initialize("RGSS104E.dll"))
  //Démarrer l'intialisation des extensions
else
  //Stopper toute opérations, le RGSSLinker n'a pas pu s'initialiser```
Vous devez l'initialiser qu'une fois, je vous recommande d'utiliser l'initialisation par le RGSS qui se fait de la manière suivante :
```unless $RGSS_Linker
  $RGSS_Linker = Win32API.new("RGSSLinker.dll","RGSSLinker_Initialize","p","i")
  if($RGSS_Linker.call("RGSS104E.dll") != 1)
    exit(0) #Echec de l'initialisation, on arrête le jeu
  else
    #Ici on charge les extensions supplémentaires
  end
end
```

## Recommandations d'usage
Vous allez probablement charger vos extensions dans le RGSS, je vous recommande de toujours stocker la fonction d'initialisation de l'extension dans **une variable qui n'est JAMAIS purgée**.
Si jamais la variable est effacée, l'extension sera automatiquement libérée de la mémoire donc les fonctions seront déchargés et quand Ruby voudra accéder aux fonctions ajoutés, il va sauter dans des zones mémoire non-alloués ce qui provoquera inévitablemen un SEGMENTATION FAULT.

## Mise en garde
Ce logiciel permet d'utiliser certaines fonctions du RGSS, si jamais Enterbrain pose son véto sur l'utilisation ou l'existence de cette application, sa décision devra être respectée et toute exploitation de ce logiciel devra cesser. 