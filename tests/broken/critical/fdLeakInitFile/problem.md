FD leak en init_file en rutas de error

Archivo: `src/rtapp/init/init_file.c:79-88`

```C
if (ft_read_file(&lines, fd) == -1)
{
    rtlog(RT_ERRLOG, 0, err, file, strerror(errno));
    return (NULL);   // BUG: fd no se cierra
}
if (!lines)
{
    rtlog(RT_ERRLOG, 0, err, file, "empty file.");
    return (NULL);   // BUG: fd no se cierra
}
close(fd);
```

Si `ft_read_file` falla o el archivo está vacío, el file descriptor `fd` no se cierra antes de retornar NULL. Solo la ruta de éxito (línea 89) cierra el descriptor. Esto causa un file descriptor leak.

Solución: agregar `close(fd)` antes de cada `return (NULL)` en las líneas 82 y 87.

Nota: Este error no se puede reproducir facilmente con una escena .rt normal, ya que requiere que ft_read_file falle o que el archivo esté vacío.