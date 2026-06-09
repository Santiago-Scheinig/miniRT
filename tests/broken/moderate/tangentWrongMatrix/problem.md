Tangente transformada con matriz incorrecta en normal maps

Archivo: `src/rtapp/render/normal_map_bonus.c:69`

```C
tangent = hit.obj->c_tangent(local_point);
tangent = vector_mult_mat4_dir(tangent, &hit.obj->transform.inv_transpose);
tangent = vector_normalize(tangent);
```

Las tangentes son vectores de dirección y deben transformarse con la matriz directa (`transform.mat`), no con la inversa-transpuesta (`transform.inv_transpose`). La matriz inversa-transpuesta es el transform correcto solo para normales, ya que estas covarían inversamente al estiramiento de la superficie. Usar `inv_transpose` en una tangente produce una dirección incorrecta para objetos con escala no-uniforme.

Consecuencia: para objetos con escala no-uniforme (por ejemplo, una esfera con radio no uniforme) que tengan un normal map, las normales perturbadas se calcularán incorrectamente, produciendo artefactos visuales.

Solución: cambiar `&hit.obj->transform.inv_transpose` por `&hit.obj->transform.mat`.

Nota: Este bug solo afecta la versión bonus (normal maps no son parte del mandatory).