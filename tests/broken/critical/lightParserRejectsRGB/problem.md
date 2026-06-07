El parser obligatorio de luz (L) rechaza el formato del enunciado

Archivo: `src/rtapp/init/parser/parse_lights.c:48`

```C
if (parse_arg(arr, i, g_lp_msgs, 2))
    return (RT_FAILURE);
```

El enunciado define el formato de L como: `L x,y,z brightness R,G,B`, indicando que el color RGB está presente aunque "(unused in mandatory part)". Sin embargo, el parser obligatorio solo acepta 2 argumentos (posición y brillo) y rechaza el 3er argumento (color) con el error "light has excess arguments".

El enunciado dice textualmente:
```
◦ Light:
  L -40.0,50.0,0.0 0.6 10,0,255
  ∗ identifier: L
  ∗ x, y, z coordinates of the light point: -40.0,0,0
  ∗ the light brightness ratio in the range [0.0,1.0]: 0.6
  ∗ (unused in mandatory part) R, G, B colors in the range [0-255]: 10,0,255
```

Esto significa que el formato estándar incluye 3 argumentos, y el programa solo utiliza 2 en la parte obligatoria. El parser debería aceptar los 3 argumentos e ignorar el color en mandatory, no rechazarlo.

Para reproducir: usar la escena de este directorio con una luz que tenga color RGB. El programa dará "light has excess arguments".