README (Just for Distribution KALI LINUX/UBUNTU/DEBIAN):

Le programme développé ici est un Hashbreaker qui rentre comme projet de BAC 2 Dévelopement option "Sécurité des Systèmes" HENALLUX programmé entièrement par gil_cedrick utilisant une architecture client-serveur. Le
client se charge d’effectuer une demande de condensat (l'utilisateur aura la possibilité d'interagir avec le server-client pour saisir des entrées manuellement afin d'établir le handshake et le reste se fera automatiquement fin la programmation séquentiel sous forme décentralisé fera le reste)

Le client attendra une entrée manuelle "demande de hash" et automatiquement le server recevra la demande de hash ( vous l'aurez compris le hash est pris en paramètre par le serveur lorsque vous éxecuterez le fichier make vous devrez passez <ip> <port> <list hash> (c'est une liste qui doit contenir le/les hash(s) cible(s) à break celui ci devrai être un type MD5) et le client juste l'ip et le port. Le client reçoit la liste de hash après ça demande et procède à une exploration où il sera question de générer toutes les chaînes de caractères possibles de façon récursive le mien est à "5" vous pouvez le modifier dans le programme de calculer à chaque string géneré son empreinte ici c'est le MD5 (on peut facile rajouter d'autre hash SHA256..) dans mon cas ici c'es le 'MD5' et le client compare cette empreinte au hash envoyé par le serveur et tout ça automatiquement tandisque vous consommez un bon café et des clops pour ceux qui en fûment moi non. Si celles-ci sont équivalentes, le client renvoie le hash au serveur qui l'enregistre dans le fichier "hashFound.txt" qui est crée automatiquement  et le processus se reproduit en boucle donc vous aurez juste à consultez tous les hashs break dans le fichier le programme travail pour vous et la logique du break est unique car il émane de mes skills en mathématiques et probabilités issu d'un Baccalauréat scientifique série C "Sciences" et après plusieurs semaines de comment break un hash facilement avec gain de temps tout en parcourant une exploration alors j'ai découvert que il est plus facile si on a 5 ou 7 caractères de préfixé le premier aini ne plus le faire bouger prennons le cas de 7 caractères débutant par A faire balayer récursirvement 6 caractères en testant toutes combinaison possible de façon récursive en un moment on trouvera le bon hash la durée peut dépendre de la longueur des caractères éffectivement c'est pour çaque la prochaine version update le programme Server prendra en charge un Bot de machone Cliente qui se diviseront le temps de calcul chaçun aura pour rôle de se consacrer à un seul indexes des 26 lettres tout en salant le reste des préfixes des Majuscules, minuscile, numéro, caractère spéciaux en version payante ou gratuite on vera bien pout le moment Good Ethical HashHacking. 
reçus.

========================================================================================================= BE CAREFUL ======================================================================================================================================
# Dépendances :

Si vous ne disposez pas d’OpenSSL qui est une bibliothèque à usage cryptographique :
    • sudo apt-get update
    • sudo apt-get install libssl-dev

Compilation du programme (level hard):
Server : gcc -o server serverBreaker.c designServer.c
Client : gcc -o client hashBreaker.c stringHash.c gil_design.c -lssl –lcrypto

# (level easy for compilation) : §§§§ !!!!!!!   COMPILEZ FACILEMENT EN JUSTE GIT CLONANT EN VOUS RASSURANT QUE LE MAKEFILE SOIT DANS LE REPERTOIRE COURANT AVEC LES 7 AUTRES FICHIERS ET RUN "make" pour linux !!!!!!!!!!!!!!!!!!!

# just git clone the repository for your directory else with the MakeFIle and other files programm just run "make" and linux will automatically compiled)

==========================================================================================================================================================================================================================================================

Fonctionnement de mon programme :

Le Server prend en paramètre l’adresse ip, le port et une liste de hash.
Le Client prend en paramètre l’adresse ip , le port.
Comme la plupart des architectures client-serveur, nous devons commencer par exécuter le serveur, puis le client.
Une fois l’interface en ligne de commande apparue, il suffit de saisir sur le terminal du serveur “mode hashbreaker” puis d’appuyer sur “Entrée”. Ensuite, du côté client, nous allons saisir “demande de hash”.
Le Mode “quit” de nous permet d’arrêter
Une fois ces actions effectuées, le reste du processus se fera automatiquement et de façon synchronisée. Lorsque vous saisissez “mode hashbreaker”, cela permet de mettre le serveur en mode réception et lorsque vous saisissez “demande de hash” côté client, le programme client se charge de demander le hash au serveur. Le serveur accepte la demande et le transmet automatiquement.
