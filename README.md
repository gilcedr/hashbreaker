README (Just for Distribution KALI LINUX/UBUNTU/DEBIAN:

Le programme développé ici est un Hashbreaker utilisant une architecture client-serveur. Le
client se charge d’effectuer une demande de condensat et le serveur répond à cette
demande en lui transmettant le hash qu’il prend en paramètre. Le client reçoit le hash et procède à une exploration où il sera question de générer des chaînes de caractères, de calculer leur empreinte dans mon cas ici : MD5, et de comparer cette empreinte à celle reçue du serveur. Si celles-ci sont équivalentes, le client renvoie le hash au serveur et le processus se reproduit en boucle. Dans mon cas, j’ai ajouté un fichier côté serveur qui sera géré par le programme automatiquement et nous permettra de stocker les condensats
reçus. Le nom du fichier est “hashFound.txt”.

====================================================================================== BE CAREFUL ======================================================================================================================================
# Dépendances :

Si vous ne disposez pas d’OpenSSL qui est une bibliothèque à usage cryptographique :
    • sudo apt-get update
    • sudo apt-get install libssl-dev

Compilation du programme (level hard):
Server : gcc -o server serverBreaker.c designServer.c
Client : gcc -o client hashBreaker.c stringHash.c gil_design.c -lssl –lcrypto

# (level easy for compilation) : §§§§ !!!!!!!   COMPILEZ FACILEMENT EN JUSTE GIT CLONANT EN VOUS RASSURANT QUE LE MAKEFILE SOIT DANS LE REPERTOIRE COURANT AVEC LES 7 AUTRES FICHIERS ET RUN "make" pour linux !!!!!!!!!!!!!!!!!!!

# just git clone the repository four your directory with the MakeFIle and just run "make" and linux will automatically compiled)

==========================================================================================================================================================================================================================================

Fonctionnement de mon programme :
Le Server prend en paramètre l’adresse ip, le port et une liste de hash.
Le Client prend en paramètre l’adresse ip , le port.
Comme la plupart des architectures client-serveur, nous devons commencer par exécuter le serveur, puis le client.
Une fois l’interface en ligne de commande apparue, il suffit de saisir sur le terminal du serveur “mode hashbreaker” puis d’appuyer sur “Entrée”. Ensuite, du côté client, nous allons saisir “demande de hash”.
Le Mode “quit” de nous permet d’arrêter
Une fois ces actions effectuées, le reste du processus se fera automatiquement et de façon synchronisée. Lorsque vous saisissez “mode hashbreaker”, cela permet de mettre le serveur en mode réception et lorsque vous saisissez “demande de hash” côté client, le programme client se charge de demander le hash au serveur. Le serveur accepte la demande et le transmet automatiquement.
