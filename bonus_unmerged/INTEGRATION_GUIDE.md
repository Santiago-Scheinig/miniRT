# Render Bonus — Guía de Integración

## 1. Qué se ha implementado

Se han añadido **tres nuevas características** al renderizador:

### 1.1 Objetos de segundo grado (quádricas)
- **Cono** (`cn`) — finito, con base cerrada
- **Paraboloide** (`pb`) — finito, con boca abierta (sin tapa)
- **Hiperboloide** (`hb`) — finito, con bocas huecas (sin tapas)

Cada uno sigue el patrón existente: función de intersección en espacio local, función de normal, y función de matriz inversa para transformar el rayo de world space a local space.

### 1.2 Phong completo con Specular Reflection
Se ha reemplazado el modelo de iluminación (solo ambient + diffuse) por **Phong completo**:
- **Ambient** — igual que antes
- **Diffuse** — ahora usa el color de la luz (`light->color`) además del ratio
- **Specular** — calcula la reflexión perfecta R = 2(N·L)N - L, mide cuánto se alinea con la dirección de cámara V, eleva a `shininess`
- Todo se calcula **por luz** individualmente y solo si la luz no está en sombra

### 1.3 Texturas
- **Checkerboard pattern** — patrón de ajedrez blanco/negro mapeado via coordenadas UV. Cada primitiva tiene su propio mapeo UV (sphere, cylinder, cone, plane, paraboloid, hyperboloid).
- **Normal mapping** — carga imágenes PNG/JPG/BMP/TGA como mapas de normales. El normal map perturba la normal usada para iluminación (sin cambiar la geometría real). Usa el sistema TBN (Tangent, Bitangent, Normal) para transformar la normal del espacio tangente al world space.

### Estructuras modificadas
| Struct | Campo nuevo | Propósito |
|--------|-------------|-----------|
| `t_material` | `shininess` | Exponente del brillo especular |
| `t_material` | `is_checker` | Flag: 1 = aplica checkerboard |
| `t_material` | `normal_map*` | Puntero al normal map cargado |
| `t_object` | `c_uv_map` | Función que mapea punto local → UV |
| `t_object` | `c_tangent` | Función que calcula tangente en local space |

---

## 2. Archivos y funciones — qué hace cada uno y cómo integrarlo

Todo el código está aislado en `render_bonus_files/`. **No toca ningún archivo del proyecto base**. Para integrarlo hay que copiar los archivos y enganchar las funciones en los sitios correctos.

### 2.1 Directorio `render_bonus_files/`

| Archivo | Qué contiene |
|---------|-------------|
| `render_bonus.h` | Header con **todos los tipos** (`t_elem_cone`, `t_elem_parabole`, `t_elem_hyperboloid`, `t_normal_map`, `t_uv`, `t_material`, `t_object`) y **todas las declaraciones** de funciones |
| `get_color_at_hit_bonus.c` | Phong completo (ambient + diffuse + specular) con soporte para checkerboard y normal mapping |
| `texture_bonus.c` | Mapeo UV por primitiva + función `get_checker_color()` |
| `normal_map_bonus.c` | Carga de normal maps (stb_image), tangentes por primitiva, `get_perturbed_normal()` |
| `elems/cone_bonus.c` | `cn_inv_mat4()`, `cn_normal()`, `cn_intersection()` |
| `elems/parabole_bonus.c` | `pb_inv_mat4()`, `pb_normal()`, `pb_intersection()` |
| `elems/hyperboloid_bonus.c` | `hb_inv_mat4()`, `hb_normal()`, `hb_intersection()` |

### 2.2 `render_bonus.h` — Tipos y declaraciones

**Tipos definidos:**

```c
typedef struct s_normal_map {
    unsigned char *pixels;   // array RGB (3 bytes por pixel)
    int           width;
    int           height;
} t_normal_map;

typedef struct s_material {
    t_vector      color;
    double        shininess;       // NUEVO: exponente especular
    int           is_checker;      // NUEVO: flag de checkerboard
    t_normal_map  *normal_map;     // NUEVO: mapa de normales
} t_material;

typedef struct s_uv {
    double u;
    double v;
} t_uv;

typedef struct s_object {
    t_transform transform;
    t_material  material;
    void        *data;
    double      (*c_intersection)(t_ray local_ray);
    t_vector    (*c_normal)(t_vector point);
    t_uv        (*c_uv_map)(t_vector local_point);   // NUEVO
    t_vector    (*c_tangent)(t_vector local_point);  // NUEVO
} t_object;
```

**Qué hacer con este header:**
- Sustituye o extiende las definiciones de `t_material` y `t_object` en `libs/librt/include/rtelm.h`
- Si tu proyecto usa `#if BONUS`, puedes hacer que `rtelm_bonus.h` incluya `render_bonus.h` o copiar las definiciones

### 2.3 `get_color_at_hit_bonus.c`

**Función principal:**
```c
t_vector get_color_at_hit(t_hit hit, t_list *objs, t_rtapp *app);
```

**Sustituye a:** `src/rtapp/render/get_color_at_hit.c` (la función `get_color_at_hit`)

**Diferencias con la versión base:**
- Calcula `mat_color` resolviendo checkerboard si `is_checker` está activo
- Calcula `lighting_normal` usando `get_perturbed_normal()` si hay normal map
- Pasa `mat_color` y `lighting_normal` a diffuse y specular
- Diffuse ahora usa `color_hadamard(mat_color, light->color)` (antes solo usaba `mat_color`)
- Specular usa `mat_color` para teñir el brillo con el color del material

**Integración:**
1. Reemplazar `get_color_at_hit.c` por esta versión, o añadir `#if BONUS`
2. No requiere cambios en la firma — se llama exactamente igual

### 2.4 `texture_bonus.c`

**Funciones de mapeo UV (una por primitiva):**

| Función | Primitiva | U | V |
|---------|-----------|---|---|
| `sphere_uv()` | Esfera | `atan2(z,x)/(2π) + 0.5` | `asin(y)/π + 0.5` |
| `cylinder_uv()` | Cilindro | `atan2(z,x)/(2π) + 0.5` | `(y+1)/2` |
| `cone_uv()` | Cono | `atan2(z,x)/(2π) + 0.5` | `y` |
| `plane_uv()` | Plano | `x` | `z` |
| `paraboloid_uv()` | Paraboloide | `atan2(z,x)/(2π) + 0.5` | `y` |
| `hyperboloid_uv()` | Hiperboloide | `atan2(z,x)/(2π) + 0.5` | `(y+1)/2` |

Todas reciben un `t_vector` (punto en espacio local del objeto) y devuelven `t_uv`.

**Función checkerboard:**
```c
t_vector get_checker_color(t_uv uv);
```
Devuelve `(1,1,1)` (blanco) o `(0,0,0)` (negro) según `floor(u*SCALE) + floor(v*SCALE)` par/impar. `CHECKER_SCALE = 4.0`.

**Integración:**
- Añadir al Makefile las fuentes de este archivo
- En cada builder de objeto, asignar `obj->c_uv_map` a la función correspondiente:

```c
// En build_sp (esfera):
obj->c_uv_map = &sphere_uv;

// En build_cy (cilindro):
obj->c_uv_map = &cylinder_uv;

// En build_pl (plano):
obj->c_uv_map = &plane_uv;

// En los builders nuevos:
obj->c_uv_map = &cone_uv;        // build_cn
obj->c_uv_map = &paraboloid_uv;  // build_pb
obj->c_uv_map = &hyperboloid_uv; // build_hb
```

### 2.5 `normal_map_bonus.c`

**Carga y liberación:**
```c
t_normal_map *load_normal_map(char *filepath);  // usa stbi_load()
void          free_normal_map(t_normal_map *nmap);
```

**Tangentes por primitiva:**

| Función | Primitiva | Tangente T |
|---------|-----------|------------|
| `plane_tangent()` | Plano | `(1, 0, 0)` |
| `sphere_tangent()` | Esfera | `normalize(-z, 0, x)` |
| `cylinder_tangent()` | Cilindro | `normalize(-z, 0, x)` |
| `cone_tangent()` | Cono | `normalize(-z, 0, x)` |
| `paraboloid_tangent()` | Paraboloide | `normalize(-z, 0, x)` |
| `hyperboloid_tangent()` | Hiperboloide | `normalize(-z, 0, x)` |

**Función principal:**
```c
t_vector get_perturbed_normal(t_hit hit, t_vector local_point);
```

1. Samplea el normal map en las UV del punto → obtiene RGB
2. Convierte RGB a normal en espacio tangente: `(R/255*2-1, G/255*2-1, B/255*2-1)`
3. Calcula la tangente T del punto y la transforma a world space
4. Ortogonaliza T contra N con Gram-Schmidt
5. Calcula bitangente B = N × T
6. Combina: `perturbed = T·Nx + B·Ny + N·Nz`
7. Devuelve la normal perturbada normalizada

**Integración:**
- Añadir `stb_image.h` a `libs/stb_image/` (descargado de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h)
- Añadir `-I libs/stb_image` a `INCLUDE_DIRS` en el Makefile
- En cada builder de objeto, asignar `obj->c_tangent` a la función correspondiente (igual que con `c_uv_map`)

### 2.6 `elems/cone_bonus.c`, `parabole_bonus.c`, `hyperboloid_bonus.c`

Cada archivo contiene 3 funciones siguiendo el patrón de `cylinder.c` y `sphere.c`:

| Función | Qué hace |
|---------|----------|
| `*_inv_mat4()` | Construye la matriz inversa T·R·S y la invierte |
| `*_normal()` | Calcula la normal en un punto de espacio local |
| `*_intersection()` | Calcula la intersección rayo-objeto en espacio local |

**Ecuaciones canónicas:**
- Cono: `x² + z² - y² = 0`, rango `0 ≤ y ≤ 1`
- Paraboloide: `x² + z² - y = 0`, rango `0 ≤ y ≤ 1`
- Hiperboloide: `x² + z² - y² = 1`, rango `-1 ≤ y ≤ 1`

**Integración:**
- Crear builders `build_cn()`, `build_pb()`, `build_hb()` siguiendo el patrón de `build_cy()` y `build_sp()`
- Registrar los identifiers `cn`, `pb`, `hb` en el parser de objetos

---

## 3. Requisitos del parser — qué hay que añadir

### 3.1 Nuevos objetos a parsear

#### Cono (`cn`)
```
cn x,y,z nx,ny,z diam height R,G,B [shininess] [checker] [normal_map:ruta]
```

| Token | Índice | Ejemplo | Descripción |
|-------|--------|---------|-------------|
| `cn` | `str[0]` | `cn` | Identifier |
| Posición | `str[1]` | `50.0,0.0,20.6` | Centro del cono |
| Normal | `str[2]` | `0.0,0.0,1.0` | Vector de eje (normalizado) |
| Diámetro | `str[3]` | `14.2` | Diámetro de la base |
| Altura | `str[4]` | `21.42` | Altura del cono |
| Color | `str[5]` | `10,0,255` | RGB [0-255] |
| `shininess` | `str[6]` *(opcional)* | `50` | Exponente especular |
| `checker` | `str[7]` *(opcional)* | `checker` | Flag de checkerboard |
| `normal_map:` | `str[8]` *(opcional)* | `normal_map:brick.png` | Ruta al normal map |

**En el builder `build_cn()`:**
```c
// Aloca t_elem_cone, parsea diam/height
// Construye la matriz inversa con cn_inv_mat4()
obj->c_intersection = &cn_intersection;
obj->c_normal = &cn_normal;
obj->c_uv_map = &cone_uv;
obj->c_tangent = &cone_tangent;
// Parsea shininess, checker, normal_map (ver 3.3)
```

#### Paraboloide (`pb`)
```
pb x,y,z nx,ny,nz diam height R,G,B [shininess] [checker] [normal_map:ruta]
```

| Token | Índice | Descripción |
|-------|--------|-------------|
| `pb` | `str[0]` | Identifier |
| Posición | `str[1]` | Vértice del paraboloide |
| Normal | `str[2]` | Vector de eje (normalizado) |
| Diámetro | `str[3]` | Diámetro de la boca |
| Altura | `str[4]` | Altura (vértice a boca) |
| Color | `str[5]` | RGB [0-255] |

**En el builder `build_pb()`:**
```c
obj->c_intersection = &pb_intersection;
obj->c_normal = &pb_normal;
obj->c_uv_map = &paraboloid_uv;
obj->c_tangent = &paraboloid_tangent;
```

#### Hiperboloide (`hb`)
```
hb x,y,z nx,ny,nz diam height R,G,B [shininess] [checker] [normal_map:ruta]
```

| Token | Índice | Descripción |
|-------|--------|-------------|
| `hb` | `str[0]` | Identifier |
| Posición | `str[1]` | Centro del hiperboloide |
| Normal | `str[2]` | Vector de eje (normalizado) |
| Diámetro | `str[3]` | Diámetro de la "garganta" (punto más estrecho) |
| Altura | `str[4]` | Altura total |
| Color | `str[5]` | RGB [0-255] |

**En el builder `build_hb()`:**
```c
obj->c_intersection = &hb_intersection;
obj->c_normal = &hb_normal;
obj->c_uv_map = &hyperboloid_uv;
obj->c_tangent = &hyperboloid_tangent;
```

### 3.2 Parámetros opcionales compartidos por todos los objetos

**Todos los objetos** (esfera, cilindro, plano + los 3 nuevos) deben soportar estos parámetros opcionales al final de su línea:

#### `shininess`
- **Formato:** un número decimal
- **Default:** si no se especifica, poner `0` (sin specular) o un valor por defecto como `32`
- **Uso:** `obj->material.shininess = ft_atod(str[i])`
- **Efecto:** controla el tamaño del brillo especular. Mayor = punto más pequeño e intenso

#### `checker`
- **Formato:** la palabra literal `checker`
- **Uso:** `obj->material.is_checker = 1`
- **Efecto:** el color del objeto se reemplaza por un patrón de ajedrez blanco/negro

#### `normal_map:ruta`
- **Formato:** `normal_map:` seguido de la ruta al archivo de imagen
- **Uso:**
  ```c
  char *path = str[i] + ft_strlen("normal_map:");  // salta el prefijo
  obj->material.normal_map = load_normal_map(path);
  ```
- **Efecto:** la normal de iluminación se perturba según la textura

### 3.3 Lógica de parsing en los builders existentes

Modificar `build_sp()`, `build_cy()`, `build_pl()` para parsear los parámetros opcionales:

```c
int build_xx(char **str, t_object *obj)
{
    // ... parseo obligatorio existente ...
    
    // Inicializar campos nuevos a valores por defecto
    obj->material.shininess = 0;
    obj->material.is_checker = 0;
    obj->material.normal_map = NULL;
    
    // Parsear parámetros opcionales (empezar después del color)
    int i = 6;  // después de str[5] (color)
    while (str[i])
    {
        if (ft_strncmp(str[i], "normal_map:", 11) == 0)
        {
            char *path = str[i] + 11;
            obj->material.normal_map = load_normal_map(path);
            if (!obj->material.normal_map)
                return (1);  // error al cargar
        }
        else if (ft_strcmp(str[i], "checker") == 0)
            obj->material.is_checker = 1;
        else
            obj->material.shininess = ft_atod(str[i]);
        i++;
    }
    
    // Asignar c_uv_map y c_tangent según el tipo de objeto
    obj->c_uv_map = &xx_uv;
    obj->c_tangent = &xx_tangent;
    
    return (0);
}
```

### 3.4 Registro de nuevos identifiers en el parser

En la función que dispatcha la construcción de objetos (donde se compara `str[0]` con `"sp"`, `"cy"`, `"pl"`), añadir:

```c
if (ft_strcmp(str[0], "cn") == 0)
    return (build_cn(str, obj));
if (ft_strcmp(str[0], "pb") == 0)
    return (build_pb(str, obj));
if (ft_strcmp(str[0], "hb") == 0)
    return (build_hb(str, obj));
```

### 3.5 Colored lights (luces con color)

El struct `t_elem_light_p` ahora tiene un campo `color`:

```c
typedef struct s_elem_light_p {
    t_vector pos;
    double   ratio;
    t_vector color;   // NUEVO
} t_elem_light_p;
```

**Formato de línea de luz puntual:**
```
lp x,y,z ratio R,G,B
```

| Token | Índice | Ejemplo | Descripción |
|-------|--------|---------|-------------|
| `lp` | `str[0]` | `lp` | Identifier |
| Posición | `str[1]` | `0.0,0.0,10.0` | Posición de la luz |
| Ratio | `str[2]` | `0.8` | Intensidad [0.0-1.0] |
| Color | `str[3]` *(opcional)* | `255,100,50` | RGB [0-255] |

**En el builder `build_lp()`:**
```c
light->color = build_color(str[3]);  // si existe str[3]
// si no, default a blanco: light->color = vector_new(1, 1, 1);
```

### 3.6 Limpieza de memoria

Cuando se libera un objeto, hay que liberar el normal map si existe:

```c
void free_object(t_object *obj)
{
    if (obj->material.normal_map)
        free_normal_map(obj->material.normal_map);
    free(obj->data);  // si no es NULL (plano no tiene data)
    free(obj);
}
```

### 3.7 Makefile — qué añadir

```makefile
# Include path para stb_image
INCLUDE_DIRS += -I libs/stb_image

# Fuentes del bonus (añadir a BONUS_SRC)
BONUS_SRC += $(RENDER_BONUS_DIR)/get_color_at_hit_bonus.c \
             $(RENDER_BONUS_DIR)/texture_bonus.c \
             $(RENDER_BONUS_DIR)/normal_map_bonus.c \
             $(RENDER_BONUS_DIR)/elems/cone_bonus.c \
             $(RENDER_BONUS_DIR)/elems/parabole_bonus.c \
             $(RENDER_BONUS_DIR)/elems/hyperboloid_bonus.c
```

### 3.8 Librería stb_image

1. Descargar `stb_image.h` de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
2. Guardarlo en `libs/stb_image/stb_image.h`
3. La implementación se activa con `#define STB_IMAGE_IMPLEMENTATION` **solo en un archivo .c** (ya está en `normal_map_bonus.c`)
4. No hace falta compilar nada más — es header-only

---

## 4. Checklist de integración

- [ ] Copiar `stb_image.h` a `libs/stb_image/`
- [ ] Añadir `-I libs/stb_image` al Makefile
- [ ] Añadir los nuevos `.c` al Makefile del bonus
- [ ] Extender `t_material` con `shininess`, `is_checker`, `normal_map*`
- [ ] Extender `t_object` con `c_uv_map` y `c_tangent`
- [ ] Extender `t_elem_light_p` con `color`
- [ ] Modificar `build_sp()`, `build_cy()`, `build_pl()` para parsear shininess/checker/normal_map
- [ ] Crear `build_cn()`, `build_pb()`, `build_hb()` con sus asignaciones de funciones
- [ ] Registrar `cn`, `pb`, `hb` en el parser de objetos
- [ ] Modificar `build_lp()` para parsear color de luz
- [ ] Reemplazar `get_color_at_hit()` por la versión bonus
- [ ] Añadir `free_normal_map()` en la limpieza de objetos
- [ ] Probar con escena que incluya los 3 objetos nuevos + luces coloreadas + checker + normal map
