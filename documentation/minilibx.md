# MiniLibX — Referencia Concisa para Agentes IA

MiniLibX es una librería gráfica mínima en C para renderizado básico en pantalla, sin conocimientos de X11/Cocoa. Corre sobre X11 (Linux) o AppKit/OpenGL (macOS).

---

## Flujo obligatorio

```
mlx_init() → mlx_new_window() → [crear imagen / hooks] → mlx_loop()
```

Toda aplicación sigue este orden. Sin `mlx_loop()` la ventana no se mantiene abierta.

---

## Inicialización

```c
void  *mlx_init();
// Devuelve instancia MLX. NULL si falla. DEBE llamarse primero.

void  *mlx_new_window(void *mlx, int width, int height, char *title);
// Devuelve puntero a ventana.

int    mlx_loop(void *mlx);
// Bucle infinito de eventos/render. Bloquea hasta que el programa termina.

int    mlx_destroy_window(void *mlx, void *win);
int    mlx_clear_window(void *mlx, void *win); // No recomendado; usar imagen en su lugar
```

---

## Imágenes (método recomendado para dibujar)

Nunca usar `mlx_pixel_put` directamente — es lento. El patrón correcto es escribir a una imagen en memoria y luego volcarla a la ventana.

```c
void  *mlx_new_image(void *mlx, int width, int height);
// Crea imagen en memoria. Devuelve puntero a imagen.

char  *mlx_get_data_addr(void *img, int *bits_per_pixel, int *line_length, int *endian);
// Devuelve dirección de memoria de la imagen.
// Escribe bpp, line_length y endian en los punteros dados.

int    mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y);
// Vuelca la imagen a la ventana en posición (x, y).

int    mlx_destroy_image(void *mlx, void *img);
```

### Escribir un píxel en la imagen

```c
// Struct recomendado
typedef struct s_data {
    void  *img;
    char  *addr;
    int    bits_per_pixel;
    int    line_length;
    int    endian;
} t_data;

// Fórmula del offset en memoria
int offset = y * line_length + x * (bits_per_pixel / 8);

// Función para poner un píxel
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
```

---

## Colores

Formato: `0xTTRRGGBB` (T=transparencia, R=rojo, G=verde, B=azul), cada canal 0–255.

```
Rojo   → 0x00FF0000
Verde  → 0x0000FF00
Azul   → 0x000000FF
```

### Codificar/decodificar con bit-shifting

```c
int create_trgb(int t, int r, int g, int b) {
    return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int c) { return ((c >> 24) & 0xFF); }
int get_r(int c) { return ((c >> 16) & 0xFF); }
int get_g(int c) { return ((c >> 8)  & 0xFF); }
int get_b(int c) { return  (c        & 0xFF); }
```

---

## Hooks (eventos)

Los hooks son callbacks que se invocan al ocurrir un evento. Se registran antes de llamar a `mlx_loop`.

```c
// Función genérica de hooking
void mlx_hook(void *win, int event, int mask, int (*f)(), void *param);

// Aliases de conveniencia
int mlx_key_hook  (void *win, int (*f)(int key,            void *param), void *param);
int mlx_mouse_hook(void *win, int (*f)(int btn, int x, int y, void *param), void *param);
int mlx_expose_hook(void *win, int (*f)(void *param), void *param);
int mlx_loop_hook (void *mlx, int (*f)(void *param), void *param);
```

### Eventos principales (X11 + macOS)

| Código | Nombre        | Prototipo del callback                       |
|--------|---------------|----------------------------------------------|
| 2      | KeyPress      | `int f(int keycode, void *param)`            |
| 3      | KeyRelease    | `int f(int keycode, void *param)`            |
| 4      | MouseDown     | `int f(int button, int x, int y, void *param)` |
| 5      | MouseUp       | `int f(int button, int x, int y, void *param)` |
| 6      | MouseMove     | `int f(int x, int y, void *param)`           |
| 12     | Expose        | `int f(void *param)`                         |
| 17     | Destroy       | `int f(void *param)`                         |

> En macOS el parámetro `mask` de `mlx_hook` se ignora; usar `0`.

### Botones del ratón (macOS)

| Valor | Botón         |
|-------|---------------|
| 1     | Click izquierdo |
| 2     | Click derecho |
| 3     | Click central |
| 4     | Scroll arriba |
| 5     | Scroll abajo  |

### Ejemplo: cerrar ventana al pulsar cualquier tecla

```c
typedef struct s_vars { void *mlx; void *win; } t_vars;

int close_hook(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return 0;
}

int main(void)
{
    t_vars vars;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Test");
    mlx_hook(vars.win, 2, 1L<<0, close_hook, &vars);
    mlx_loop(vars.mlx);
}
```

---

## Loop hook (animación por frames)

```c
int render_next_frame(void *data);  // Se llama cada frame

int main(void)
{
    void *mlx = mlx_init();
    mlx_loop_hook(mlx, render_next_frame, &my_data);
    mlx_loop(mlx);
}
```

---

## Carga de imágenes desde archivo

```c
void *mlx_xpm_file_to_image(void *mlx, char *file, int *w, int *h);
void *mlx_png_file_to_image(void *mlx, char *file, int *w, int *h); // tiene memory leak
void *mlx_xpm_to_image    (void *mlx, char **xpm_data, int *w, int *h);
// Devuelven NULL si falla la carga.
```

---

## Ratón: utilidades

```c
int mlx_mouse_hide();
int mlx_mouse_show();
int mlx_mouse_move   (void *win, int x, int y);
int mlx_mouse_get_pos(void *win, int *x, int *y);
```

---

## Sync (frame buffering, MLX ≥ 2020)

Alternativa moderna al doble buffering manual.

```c
#define MLX_SYNC_IMAGE_WRITABLE   1  // Inicia escritura diferida sobre imagen
#define MLX_SYNC_WIN_FLUSH_CMD    2  // Vuelca cambios a la ventana
#define MLX_SYNC_WIN_CMD_COMPLETED 3

int mlx_sync(int cmd, void *ptr);
// Uso: mlx_sync(MLX_SYNC_IMAGE_WRITABLE, img);
//      ... escribir píxeles ...
//      mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, win);
```

---

## Utilidades varias

```c
uint mlx_get_color_value(void *mlx, int color);         // Convierte color al formato nativo
int  mlx_get_screen_size(void *mlx, int *w, int *h);    // Dimensiones de pantalla
int  mlx_do_key_autorepeatoff(void *mlx);               // Desactiva repetición de teclas
int  mlx_do_key_autorepeaton (void *mlx);               // Activa repetición de teclas
int  mlx_do_sync(void *mlx);                            // Sincroniza frames de todas las ventanas
int  mlx_string_put(void *mlx, void *win, int x, int y, int color, char *str);
int  mlx_pixel_put (void *mlx, void *win, int x, int y, int color); // Lento, evitar
```

---

## Compilación

### macOS
```makefile
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# Requiere libmlx.dylib junto al ejecutable
```

### Linux
```bash
sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```
```makefile
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
```

---

## Notas importantes para el agente

- `mlx_pixel_put` es **muy lento**; siempre dibujar en imagen con `my_mlx_pixel_put` y usar `mlx_put_image_to_window`.
- `line_length` ≠ `width * bpp/8`; siempre usar el valor retornado por `mlx_get_data_addr`.
- Para evitar screen-tearing, usar dos imágenes y alternarlas (double buffering), o usar `mlx_sync`.
- `mlx_png_file_to_image` tiene un memory leak conocido; preferir `.xpm`.
- En macOS, el argumento `mask` de `mlx_hook` no tiene efecto; pasar `0`.
- Todas las funciones devuelven `int` sin valor significativo salvo las de inicialización (`void *`).