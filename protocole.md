# Protocole Babel

La communication entre le serveur et les clients, ainsi que celle entre les clients eux-même est segmentée en paquets.

Un paquet est composé de deux parties:
- Ses méta-données
- Ses arguments

## Méta-données
Les méta-données sont une suite de bytes qui décrivent le paquet et son contenu. Dans l'ordre:

1. Taille en bytes totale du paquet: entier non-signé 4 bytes
2. Identifiant du paquet: entier non-signé 1 byte
3. Nombre d'arguments `n`: entier non-signé 1 byte
4. Un tableau composé de `n` types d'arguments: un entier non-signé 1 byte par élément

L'identifiant du paquet est un entier qui indique le type du paquet.

### Valeurs des types d'arguments
| Type | Valeur du type |
|------|----------------|
| string | `0` |
| unsigned int | `1` |
| int | `2` |
| char | `3` |

## Arguments

Les types numériques sont représentés par leurs valeurs binaires.
Les textes sont des tableau de caractères terminés par un byte nul.

## Description des paquets
| Nom du paquet | Valeur de l'identifiant | Arguments |
|---------------|-------------------------|-----------|
| PacketCmdRegister | 1 | username: `string` password: `string` |
| PacketRespRegister | 2 | ok: `char` errorMessage: `string` |
| PacketCmdLogin | 3 | username: `string` password: `string` |
| PacketRespLogin | 4 | ok: `char` errorMessage: `string` userId: `int` |
| PacketCmdLogout | 5 | |
| PacketAudio | 6 | size: `int` samples: `sample: unsigned char [size]` |
| PacketCmdInviteFriend | 7 | username: `string` |
| PacketRespInviteFriend | 8 | ok: `char` errorMessage: `string` friendshipId: `id` username: `string` |
| PacketCmdAcceptFriend | 9 | id: `int` |
| PacketRespAcceptFriend | 10 | ok: `char` errorMessage: `string` friendshipId: `id` userId: `id` username: `string` |
| PacketCmdDenyFriend | 11 | id: `int` |
| PacketRespDenyFriend | 12 | ok: `char` errorMessage: `string` friendshipId: `id` |
| PacketInviteReceived | 13 | id: `int` username: `string` |
| PacketFriendAdded | 14 | id: `int` username: `string` friendshipId: `id` |
| PacketFriendDenied | 15 | id: `int` |
| PacketCmdListFriends | 16 | |
| PacketRespListFriends | 17 | size: `int` users: `id: int username: string [size]` |
| PacketCmdListInvites | 18 | |
| PacketRespListInvites | 19 | size: `int` users: `id: int from: int to: int fromUsername: string toUsername: string [size]` |
| PacketCall | 20 | id: `int` |
| PacketCallReceived | 21 | id: `int` username: `string` |
| PacketAcceptCall | 22 | id: `int` |
| PacketStartVoip | 23 | id: `int` ip: `string` listenPort: `int` sendPort: `int` |