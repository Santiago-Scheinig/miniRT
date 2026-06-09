Memory leak de new_light_p si ft_lstnew falla

Archivo: `src/rtapp/init/init_elements.c:42-44`

```C
new_light_p = build_lp(argv);
if (!new_light_p)
    return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
new_node = ft_lstnew(new_light_p);
if (!new_node)
    return (rtlog(RT_ERRLOG, 0, err, i, argv[0], strerror(errno)));
    // BUG: new_light_p no se libera antes de retornar
```

Si `ft_lstnew` falla (por malloc failure), `new_light_p` ya fue allocado exitosamente por `build_lp` pero nunca se libera. Su puntero se pierde al retornar.

La versión bonus (`init_elements_bonus.c`) tiene el mismo problema.

Solución: agregar `free(new_light_p)` antes del return en la línea 44, o usar el patrón de `build_and_add` que sí libera el objeto cuando `ft_lstnew` falla (usando `object_del(obj)` en objetos).

Nota: Este error requiere una condición de malloc failure, que es difícil de reproducir con una escena .rt normal.