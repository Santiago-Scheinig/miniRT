is_empty_or_comment_line salta líneas válidas con espacios iniciales                                                                                                            
Archivo: `src/rtapp/init/parser/parse_line.c:17-31`

```C
while (line[++i])
{
	if (line[0] == '#')        // BUG: siempre chequea line[0]
		return(TRUE);
		if (line[i] != ' ' ...)
			break ;
		return (TRUE);             // BUG: return incondicional
	}
```

El return (TRUE) en la línea 28 es incondicional, por lo que cualquier línea que empiece con espacio/tab se considera vacía. Ejemplo: "  sp 0,0,0 1 255,0,0" se ignora silenciosamente. Además, line[0] en vez de line[i] hace que solo se detecte # en posición 0.