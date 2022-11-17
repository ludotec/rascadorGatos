# Rascador de gatos
## _Proyecto Final_

[![N|Solid](https://ites.edu.ar/static/media/carreras_desarrollo.b8ce5469.png)](https://ites.edu.ar/)

## Integrantes:
- Fuentes Claudio
- Valdez Cristian

## Materias involucradas

- 	Microcontroladores 2 (Giles Alejo)
- 	Automatismos (Nicolás Gonzalez)
## Repositorio

[Github](https://github.com/ludotec/rascadorGatos) 

## Objetivo
Casa rascadora y recolectora de pelos de gatos. Rascador + Casita.
¿Qué necesidades cubre esta solución? ¿Qué soluciona?
La solución cubre, en parte, la necesidad de evitar, en este caso el felino doméstico (gato), que los pelos, que suelta de su cuerpo queden diseminados por todos los lugares por donde frecuenta dentro de la casa.
A pesar de no lograr dar solución completa a ésta necesidad, se estima que puede ser un dispositivo útil. 

## Detalle de Componentes (Partes involucradas) (BOM Listado de Materiales)
[(Artículo en Mercado Libre)](https://articulo.mercadolibre.com.ar/MLA-1117400769-kit-rueda-goma-reforzada-x-1-motor-dc-x-1-arduino-robot-_JM#position=1&search_layout=grid&type=item&tracking_id=3bcd98ec-033f-4c57-b730-e3c753356b53)

[(Artículo en Mercado Libre)](https://http2.mlstatic.com/D_NQ_NP_2X_941005-MLA48687765989_122021-F.webp)

[(Artículo en Mercado Libre)](https://articulo.mercadolibre.com.ar/MLA-796291505-mg946r-servo-motor-13kg-de-torque-analogico-peso-55g-arduino-_JM#position=21&search_layout=stack&type=item&tracking_id=41a53a0c-7dd9-496f-b07a-8047530357fb )

## Esquema de Conexiones
[Diagrama de bloques](https://viewer.diagrams.net/?tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Diagrama%20sin%20t%C3%ADtulo.drawio#Uhttps%3A%2F%2Fraw.githubusercontent.com%2Fludotec%2FrascadorGatos%2Fmain%2FDiagrama%2FDiagrama%2520sin%2520t%25C3%25ADtulo.drawio)

## Funcionalidades


El dispositivo “rascador” es un cilindro el cuál lleva adherido un tela que hará la función de recolectar los pelos del gato al rozarse sobre éste. Éste cilindro deberá empezar a girar cuando detecte un objeto cercano a él, lo hará en un sentido y en otro alternando entre cada comienzo. Cómo sensor de presencia su usa un ultrasonido que es configurado de manera tal que cuando detecte algo se centre al medio (90°) y luego de un tiempo determinado que no detecta ningún objeto cerca hará un “barrido” de 180° comenzando desde los 90° hasta el 0° y de ahí a los 180°, volviendo a su posición original. Si en el transcurso de teste “barrido” detecta el sensor ultrasonido algún objeto automáticamente se posicionará en su punto medio. Todo este movimiento el ultrasonidos lo logra gracias a estar montado sobre un servomotor.
Además de lo visto hasta ahora tendrá una señal lumínica proporcionada por un led RGB que se pondrá en rojo cuando el ultrasonido detecte un objeto cerca y alternará entre verde y azul cuando el servomotor realice el barrido de 180°. 

