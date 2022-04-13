# CELESTE_PICO-8

<b>Recordar treure la AllocConsole(serveix per debugejar couts) a l'hora d'entregar</b>

<del><b> PROBLEMA VELOCIDAD: </B>Para aumentar la velocidad del jugador, hay que cambiar el valor de pos.x (de 2 a 4) cuando se comprueba si se están pulsando las flechas a la izquierda y a la derecha (en la clase Plaayer.cpp). Esto hace que el jugador entre dentro de los tiles que están a su misma altura, y por tanto hay que modificar la función collisionMoveLeft y collisionMoveRight de la clase TileMap.cpp. Así se consigue una velocidad muy parecida a la del juego original y se pueden pasar todos los niveles. El problema es que al modificar estas dos funciones, deja de funcionar la habilidad CLIMB del perosnaje.</del> <b>arreglat</b>

<del><B>PROBLEMA CLIMB: </b>El CLIMB funciona como en el juego original cuando el obstáculo se encuentra a la derecha, pero cuando el obstáculo se encuentra a la izquierda, si dejas pulsada la tecla de la flecha a la izquierda mientras el personaje está agarrado a la pared, salta hacia arriba en vez de saltar en la dirección contraria al obtáculo (en el CLIMB a la dercha si que lo hace bien).</del> <b>arreglat</b>

## Coses fetes

- Climb. 

- CollisionMoveUp i lligarlo amb Jugador.cc (que el jugador no atravessi els murs cap a dalt, i acabi de fer el salt pero cap baix)

- Modificar Jump. 

- Maduixes (voladores i no voladores). 

- Clau, tresor level 5. 

- Sprites que desapareixen. 

- Credits. 

- El boto exit. 

- Vibrar al començar nivell

- Transicions entre mapes (i sprite mestres muntanya).


## Coses que falten

- Fer sprite molles. Juan

- Sprite nubes. Juan

- <del>Sprite contador. David</del> (explicamos las funciones especiales en el info.txt)

- Tecla invulnerabilitat. Juan

- Totes altres animacions. 

- <del>Sprite punxes matar. Juan</del>

- <del>Tecla dash infinit. Juan </del>

- <del>Tecla velocitat joc. </del>

- <del>Fer sprite maduixes no voladores. David</del>

- <del>Fer sprite maduixes voladores. David</del>

- <del>Fer sprite blocs que despareixen. David</del>

- <del>Fer instruccions.         Juan</del>

- <del>Fer credits.              David</del>

- <del>Implementar boto exit. David</del>

- <del>Transicions entre mapes (i sprite mestres muntanya). David</del>

- <del>Sprite nieve. Juan</del>

- <del>Modificar jump. David</del>

- <del>Limits jugador mapa. </del>

- <del>Mort del jugador per caiguda</del>

- <del>Fer dash. Juan </del>

- <del>Vibrar al començar nivell. David</del>

- <del>Vibrar al morir. </del>

- <del>Vibrar al dash.  Juan</del>

- <del>Climb. David</del>

- <del>Sprites correr. Juan </del>

- <del>Musica.       David   </del>

- <del>Efectes especials. David </del>

- <del>Gestió de memòria (alliberar espai de memòria al cambiar de mapa).  Juan </del>
