Lógica invertida en rtapp_bonus.c: init_log retorna SUCCESS cuando falla

Archivo: `src/rtapp/rtapp_bonus.c:31-32`

```C
if (init_log(app))
    return (RT_SUCCESS);
```

Si `init_log` falla (retorna RT_FAILURE = 1), la condición se evalúa como verdadera y se retorna `RT_SUCCESS` (0). Esto es una lógica invertida: deberia retornar `RT_FAILURE`.

Adicionalmente, en `init_log_bonus.c:75-76`:
```C
if (dup2_logs(log_fd, errlog_fd, app))
    return (rtlog(RT_LOG, 0, "< Log files initialization failed >"));
```

`rtlog` retorna `fd - 1`, que para RT_LOG es `0` (RT_SUCCESS). Así que incluso si `dup2_logs` falla, `init_log` retorna RT_SUCCESS, haciendo que la comprobación en `rtapp_bonus.c` sea irrelevante.

Consecuencia: cualquier fallo en la inicialización de logs se ignora silenciosamente, y el programa puede quedar con stdout/stderr en un estado inconsistente.

Solución: cambiar `return (RT_SUCCESS)` por `return (RT_FAILURE)` en rtapp_bonus.c línea 32, y hacer que `init_log` retorne RT_FAILURE cuando `dup2_logs` falle.

Nota: Este bug solo afecta a la versión bonus. No es reproducible con una escena .rt simple, ya que requiere que `dup2` falle (condición de error del sistema).