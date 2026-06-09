Rango de brillo de luz permite valores negativos [-1, 1]

Archivo: `src/rtapp/init/parser/parse_lights.c:52`

```C
if (parse_double(arr[0], arr[2], i, build_limit(-1, 1)))
    return (rtlog(RT_ERRLOG, 0, err, i, argv[0], "invalid brightness."));
```

El rango de brillo de la luz puntual es `[-1, 1]`, permitiendo valores negativos. El enunciado especifica claramente: "the light brightness ratio in the range [0.0,1.0]".

Un brillo negativo como -0.5 causaría que la luz oscurezca en vez de iluminar, produciendo un comportamiento visualmente incorrecto y contrario a la especificación.

El mismo problema existe en la versión bonus (`parse_lights_bonus.c:52`).

Solución: cambiar `build_limit(-1, 1)` por `build_limit(0, 1)`.

Para reproducir: usar la escena de este directorio que contiene una luz con brillo negativo.

# NOTA DE ALFONSO
Me da muchisima pena quitar esta feature porque esta guapisimo tener luz negra ajkajaj. Pero hay que quitarla si, no es defendible eso la vd, pero queda guapisimo en la escena jakjak.