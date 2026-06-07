Memory leak en build_object cuando builder() falla

Archivo: `libs/librt/src/rtelm/utils/build_utils.c:66-72`

```C
obj = ft_calloc(1, sizeof(t_object));
if (!obj)
    return (NULL);
obj->mlx = mlx;
if (builder(arr, obj))
    return (NULL);  // BUG: obj no se libera antes de retornar NULL
return (obj);
```

Si la función `builder()` (como build_sp, build_pl, build_cy) falla y retorna distinto de 0, el objeto `obj` ya fue allocado con `ft_calloc` pero nunca se libera. Se pierde la referencia al puntero, causando un memory leak.

Esto puede ocurrir cuando se proporciona un vector normal (0,0,0) en una escena, lo cual hace que build_camera o build_object falle.

Solución: agregar `free(obj)` antes del `return (NULL)` en la línea 71, o mejor aún, usar `object_del(obj)` si ya tiene recursos parciales asignados.

Para reproducir: usar una escena con un objeto que tenga normal inválida (0,0,0). El parser detectará el error, pero el objeto ya allocado se pierde.