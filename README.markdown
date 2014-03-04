## Exercice de synchronisation entre threads en C

Cela faisait des années que je n'avais plus manipuler des thread directement et la pogrammation concurrente est un sujet que je trouve passionnant. J'ai retrouvé un vieux sujet d'exercice qui m'avait beaucoup marqué à l'époque lors d'un TP d'un cours de "système d'exploitation" en Licence à l'université. C'est une reformulation du problème [des fumeurs de cigarette](http://en.wikipedia.org/wiki/Cigarette_smokers_problem).

> Synchronisation : le problème des cuisinières
>
> Six cuisinières désirent préparer un gâteau nécessitant quatre ingrédients. Chacune de ces cuisinières dispose d’une quantité illimitée de deux des ingrédients, et deux cuisi- nières ne disposent jamais des mêmes ingrédients (ce qui explique qu’elles soient six). Il est impossible qu’elles partagent des denrées.
>
>D’autre part, un épicier vient périodiquement fournir deux ingrédients en quantité suf- fisante pour la préparation d’un gâteau, et attend que le gâteau soit prêt pour repartir chercher deux nouveaux ingrédients. Les deux ingrédients de l’épicier sont toujours choisis au hasard. 
> 
> a) En modélisant chaque personnage par un thread, donnez l’algorithme exécuté par chaque thread, en précisant les données locales à chaque thread et les données par- tagées par tous les threads, ainsi que les objets de synchronisation nécessaires à une exécution correcte de ce modèle. Vous prendrez soin de minimiser le nombre d’objets de synchronisation utilisés.
>
> b) Le problème serait-il plus simple si chaque cuisinière disposait de trois ingré- dients, et si l’épicier apportait un seul ingrédient 
