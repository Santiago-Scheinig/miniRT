Validación de extensión .rt acepta .rtx, .rts, etc.

Archivo: `src/rtapp/init/init_file.c:59`

```C
if (ft_strncmp(aux, "rt", 2))
    return (rtlog(RT_ERRLOG, 0, err, file, "invalid .rt file"));
```

Solo compara los primeros 2 caracteres de la extensión. Un archivo como `scene.rtx` o `scene.rts` pasaría la validación porque sus primeros 2 caracteres coinciden con "rt". Esto viola el enunciado que requiere que el archivo tenga extensión .rt exclusivamente.

Solución: usar `ft_strncmp(aux, "rt", 3)` para incluir la comparación con el carácter nulo terminador, garantizando que la extensión sea exactamente "rt".

Para reproducir: renombrar el archivo .rt a .rtx y ejecutar miniRT con él. El programa debería dar error pero lo acepta.