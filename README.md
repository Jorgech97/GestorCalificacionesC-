# 🎓 Sistema de Gestión de Calificaciones Estudiantiles

Este proyecto, desarrollado en **C++**, implementa un sistema completo para el registro, administración y reporte de estudiantes y sus calificaciones en diversas materias. Utiliza **archivos de texto como almacenamiento persistente** y se ejecuta en consola.

---

## 🧭 Objetivo

El propósito principal de este programa es permitir la gestión eficiente de información estudiantil mediante:

* Registro de estudiantes con datos personales.
* Ingreso de notas para distintas materias.
* Cálculo automático de promedios y estado académico.
* Edición y eliminación de registros.
* Generación de reportes detallados.

---

## 📚 Funcionalidades

### 1. Registro de Estudiantes

* Validación estricta de cédula (10 dígitos).
* Captura de nombre, provincia, cantón, distrito, edad y género.
* Almacenamiento en archivo: `estudiantes.txt`.

### 2. Ingreso de Calificaciones

* Materias personalizables por estudiante.
* Captura de:

  * Proyecto 1 (1%)
  * Proyecto 2 (2%)
  * Ensayo (3%)
  * Foro (1%)
  * Defensa (3%)
* Cálculo automático del promedio ponderado.
* Asignación de estado:

  * `Aprobó` (≥ 70)
  * `Reposición` (50–69.9)
  * `Reprobó` (< 50)
* Almacenamiento en archivo: `notas.txt`.

### 3. Modificación

* Actualización de datos de residencia y edad de los estudiantes.
* Edición completa de notas por materia.

### 4. Eliminación

* Borrado de estudiantes y todas sus notas asociadas.
* Confirmación por parte del usuario.

### 5. Reporte

* Tabla resumen con:

  * ID, Nombre, Materia, Promedio, Estado.
* Calculado directamente desde los archivos.

---

## 🧾 Estructura de Archivos

### `estudiantes.txt`

