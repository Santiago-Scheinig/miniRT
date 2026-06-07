Typos y problemas menores varios

A continuación se listan todos los typos, violaciones de Norma y problemas menores encontrados:

## Typos en mensajes de error

1. `include/g_parse_err_msgs.h:28` y `include/g_parse_err_msgs_bonus.h:23`: `"light brighness undeclared."` → debería ser **"brightness"**
2. `include/g_parse_err_msgs_bonus.h:47`: `"parabole"` → debería ser **"paraboloid"** (o al menos "parabola")
3. `src/rtapp/init/init_file.c:41`: `"successfull"` → debería ser **"successful"**
4. `src/rtapp/init/parser/parse_utils_bonus.c:69`: variable `extention` → debería ser **"extension"**
5. `src/rtapp/init/parser/parse_objects.c:57`: el mensaje dice "invalid radius" pero el enunciado usa **"diameter"**

## Inconsistencia en puntuación de mensajes

6. `include/g_parse_err_msgs.h:28`: `"light has excess arguments"` (sin punto final) mientras todos los demás mensajes terminan con punto.

## Violaciones de Norma

7. `libs/librt/include/rtmth.h:67,77-78`: Comentarios `//` inline en definiciones de structs. La Norma 42 prohibe comentarios dentro de funciones, y los comentarios tipo `//` deben usar el formato `/* */`.

## Makefile

9. `libs/librt/Makefile:26`: Usa flag `-Wno-error=incompatible-pointer-types` que silencia errores de tipo con `-Werror`. Un evaluador podría considerar esto una bandera roja.

10. `libs/librt/Makefile`: Usa `make` en vez de `$(MAKE)` en las reglas `clean` y `fclean` para sub-librerías.

## Otros

14. `libs/librt/src/rtmth/vector/vector_scalar.c:29`: Usa literales `0.0f` (float) en funciones que trabajan con `double`. Debería usar `0.0`.

15. `libs/librt/src/rterr/object_del.c`: No maneja el caso donde `content` es NULL. Si `ft_lstclear` pasa un nodo con `content = NULL`, se produce crash por dereferencia de NULL.

16. `libs/librt/src/rtelm/camera.c`: `camera->fov` es `int` pero se asigna con `ft_atod()` (double), truncando silenciosamente la parte decimal. Un FOV como 70.5 se convierte en 70.

17. `src/rtapp/debug/rtlog.c:33-35`: Timestamps muestran UTC en vez de hora local, y el PID siempre es 0 (no el PID real del proceso).