rtapp_kill en bonus siempre sale con código 0, ignorando errcode

Archivo: `src/rtapp/rtapp_bonus.c:36-54`

```C
int	rtapp_kill(t_rtapp *app, t_rterr errcode)
{
    const char	*err = "termination of miniRT app failed: %s";

    (void)errcode;
    ...
    exit(RT_SUCCESS);  // BUG: siempre sale con 0, ignora errcode
}
```

El parámetro `errcode` se ignora completamente con `(void)errcode` y siempre se llama `exit(RT_SUCCESS)`. Esto significa que errores que deberían propagarse con un código de salida no-cero siempre retornan 0, haciendo imposible detectar errores desde la línea de comandos.

En contraste, la versión obligatoria (`rtapp.c:91-101`) sí usa `exit(errcode)` correctamente.

Solución: reemplazar `exit(RT_SUCCESS)` por `exit(errcode)`.

Nota: Este bug solo afecta la versión bonus.