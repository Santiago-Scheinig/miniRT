# **Protocolo de Trabajo Colaborativo: miniRT**

Este documento establece el estándar técnico y organizativo estricto para el desarrollo del proyecto miniRT. El objetivo es mantener trazabilidad absoluta, evitar colisiones en el código y asegurar que la rama principal siempre cumpla con los requisitos de evaluación (Norminette, cero *leaks*).

## **1\. Arquitectura de Gestión (Single Source of Truth)**

Toda la organización reside en la combinación de **GitHub Issues** (unidad de trabajo) y **GitHub Projects** (visualización del flujo).

* **Tablero Kanban:** Alojado en la cuenta del propietario del repositorio. Ambos desarrolladores deben tener permisos de escritura (Write/Admin).  
* **Columnas Estrictas:**  
  1. To Do: Tareas pendientes y priorizadas.  
  2. In Progress: Tareas en desarrollo activo (Máximo 1 por persona).  
  3. Review / Testing: Código finalizado pendiente de revisión cruzada.  
  4. Done: Integrado en dev o main.

**Regla de Oro:** Prohibido escribir una sola línea de código sin que exista un Issue real (con ID) creado y asignado previamente. No se usan "Draft Issues".

## **2\. Creación de Tareas y Metadatos**

Cada Issue debe ser atómico y contener los siguientes metadatos antes de empezar a programar:

* **Título:** Verbo imperativo \+ acción específica (Ej: Implementar producto escalar de vectores 3D).  
* **Asignación (Assignee):** Estrictamente un (1) único responsable por Issue.  
* **Etiquetado Multidimensional (Labels):** Requiere mínimo dos etiquetas por Issue:  
  * *Dominio (Dónde):* math, parser, mlx, core.  
  * *Tipo (Qué):* bug, feature, architecture, norminette, leaks.  
* **Hitos (Milestones):** Asignar el Issue a la fase correspondiente del proyecto (Ej: M1 \- Setup y Utils, M2 \- Parser).

## **3\. Estrategia de Desarrollo (Epics y Tareas)**

Evitaremos el *Big Design Up Front* (intentar prever todo el código desde el día 1). El desarrollo será iterativo.

* **Epics (Tareas Contenedoras):** Para módulos grandes (Ej: \#10 Epic: Motor Matemático), se crea un Issue padre. En su descripción, se usa una *Task List* de Markdown (- \[ \] Tarea).  
* **Child Issues:** Se utiliza el botón "Convert to issue" de la Task List para generar tareas individuales ejecutables con su propio ID (Ej: \#11 Producto Escalar).  
* **Cierre de Epics:** El Epic se cierra cuando el módulo cumple su función base requerida por el *subject*.  
* **Descubrimientos:** Si surgen nuevas necesidades menores una vez cerrado un Epic (Ej: "Falta una conversión a radianes"), **no se reabre el Epic**. Se crea un Issue nuevo, independiente y atómico.

## **4\. Arquitectura de Ramas**

Se prohíben las ramas monolíticas de larga duración (ej. lib/math). Aplicaremos Feature Branch Workflow.

* main: Producción. Código estable, evaluable y sin errores.  
* dev: Integración continua. Rama base para el desarrollo diario.  
* **Ramas Efímeras:** Se crean para un Issue, se integran y **se eliminan**.  
  * *Nomenclatura estricta:* tipo/ID-descripcion  
  * *Ejemplos:* feature/4-math-headers, bugfix/7-parser-split.

## **5\. Ciclo de Trabajo Operativo (Paso a Paso)**

Este es el bucle mecánico que debe ejecutarse para cada tarea:

### **Fase 1: Sincronización (Terminal)**

Asegurar que el entorno local tiene el código más reciente antes de ramificar.  
git checkout dev  
git pull origin dev

### **Fase 2: Aislamiento y Activación (Terminal y Web)**

Crear la rama usando el ID del Issue asignado y actualizar el Kanban.  
git checkout \-b feature/ID-descripcion

*Acción web:* Mover la tarjeta del Issue correspondiente a la columna In Progress.

### **Fase 3: Desarrollo (Local)**

Escribir código, aplicar Norminette, testear *leaks* y hacer *commits* atómicos.  
git add \<archivos\>  
git commit \-m "Descripción clara del avance"

### **Fase 4: Publicación (Terminal)**

Subir la rama efímera al repositorio remoto.  
git push \-u origin feature/ID-descripcion

### **Fase 5: Integración y Automatización (Web)**

1. Abrir un **Pull Request (PR)** apuntando la rama efímera hacia **dev** (nunca a main directamente).  
2. **ACCIÓN CRÍTICA:** Escribir Closes \#ID (Ej. Closes \#4) en el cuerpo del mensaje del PR.  
3. *Acción web:* Mover la tarjeta del Issue a Review / Testing.

### **Fase 6: Code Review (Compañero)**

El desarrollador que NO escribió el código debe revisar el PR:

1. Comprobar Norminette y compilar.  
2. Si hay errores: Solicitar cambios (la tarjeta vuelve a In Progress).  
3. Si es correcto: Aprobar y ejecutar el **Merge** a dev.  
4. El Issue se cerrará automáticamente (por el comando Closes) y pasará a Done.  
5. Eliminar la rama efímera remota y local.

## **6\. Gestión de Documentación**

Cualquier modificación exclusiva de documentación (README, comentarios, wikis) que no altere la lógica del código C debe aislarse de las features:

* **Nomenclatura de rama:** docs/ID-descripcion (Ej: docs/15-actualizar-readme).  
* **Etiquetas:** Asignar la etiqueta documentation. Se puede cruzar con el dominio (Ej: documentation \+ parser).  
* **Commits:** Aplicar prefijo estricto de Conventional Commits: docs: \[mensaje de los cambios\].