build_texture siempre retorna 0 (silencia errores de carga de texturas)

Archivo: `libs/librt/src/rtelm/utils/build_utils_bonus.c:36-59`

```C
static int	build_texture(t_object *obj, char *str)
{
    ...
    if (!tex->img)
        return (0);   // BUG: retorna 0 (éxito) en caso de fallo
    ...
    if (!tex->pixels)
    {
        mlx_destroy_image(obj->mlx->instance, tex->img);
        tex->img = NULL;
        return (0);   // BUG: retorna 0 (éxito) en caso de fallo
    }
    return (0);       // Retorna 0 también en caso de éxito
}
```

Esta función retorna `0` tanto en caso de éxito como en caso de fallo. El llamador `build_add_att` comprueba `if (build_texture(obj, arr[i]))` para detectar errores, pero esta condición nunca se cumple porque `build_texture` siempre retorna 0.

Consecuencia: si se especifica una textura XPM inexistente o corrupta, el error se ignora silenciosamente. El objeto se renderiza sin textura sin ningún mensaje de error, lo cual puede confundir al usuario.

Solución: las rutas de error deben retornar `1` en vez de `0`.

Nota: Este bug solo afecta a la versión bonus (texturas no son parte del mandatory), por lo tanto la escena .rt requiere compilar con bonus.