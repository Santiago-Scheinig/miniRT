Memory leak de app.img cuando mlx_init() falla

Archivo: `src/main.c:33-38`

```C
app.img = ft_calloc(W_HEIGHT * W_WIDTH, sizeof(uint32_t));
if (!app.img)
    return (rtlog(RT_ERRLOG, 0, err, strerror(errno)), RT_FAILURE);
app.mlx.instance = mlx_init();
if (!app.mlx.instance)
    return (del_mlx(&app.mlx, 1));  // BUG: app.img no se libera
```

Si `mlx_init()` falla, se retorna `del_mlx(&app.mlx, 1)` sin liberar `app.img`, que ya fue allocado con `ft_calloc` en la línea 33. Esto causa un memory leak de `W_HEIGHT * W_WIDTH * sizeof(uint32_t)` bytes (típicamente ~8MB para 1920x1080).

`del_mlx` solo limpia los recursos internos de MiniLibX, no libera `app.img`.

Solución: agregar `free(app.img)` antes del return en la línea 38.

Nota: Este error solo se puede reproducir si mlx_init() falla (por ejemplo, en un sistema sin servidor X o sin entorno gráfico). No hay escena .rt que lo provoque directamente.
