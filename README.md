# TP-prototipo-de-actualizacion-de-cuentas-de-un-banco
Trabajo practico realizado de manera grupal (3 personas).
Un Banco "x" desea actualizar su módulo de reportes y cuentas. Este módulo implementará las funcionalidades básicas para la actualización de saldos 
y administración de cuentas, el cual se pide el diseño de un primer prototipo.
Este prototipo es una versión “simplificada” del sistema a entregar, ya que no se tienen en cuenta datos del cliente,
rigurosidad en performance e interacción con otros sistemas de la organización.
Los tipos de datos principales que se manejan son “Cuenta” y “Operación” que presentan la siguiente
estructura:

Tarjeta:
CuentaID        99999;
FechaCreacion   AAAAMMDD;
Activa          True/False;
Saldo           999.999999;
NroCliente      9999
Registro "Cuenta"

Movimiento:
MovimientoID   9999;
FechaHora      AAAAMMDDHH:MM;
Monto          999.99999;
CuentaID       99999;
Registro "Movimiento"

Al comenzar la jornada se “levantan” todas las cuentas desde el archivo “Cuentas.BIC”. Cada vez que el usuario
requiera se procesará un “lote de movimientos”. Se desconoce cuántos movimientos puede haber en cada lote,
pero puede ser tan grande que haga difícil su manejo en un vector.
El procesamiento de un lote de movimientos implica la actualización de los saldos de aquellas cuentas que sean
afectadas. Además, cada vez que se procesa un lote, deben “transladarse” los registros procesados a un archivo
llamado “procesados.BIC”, el cual contiene todos los movimientos de todos los lotes procesados en el día.
Al finalizar el día se reescribe el archivo “Cuentas.BIC” con los saldos actualizados de las cuentas activas
únicamente.
El programa permite:
1. “Levantar” las cuentas del archivo “Cuentas.BIC”.
2. Cargar una nueva cuenta.
3. Desactivar una cuenta existente.
4. Buscar una cuenta por ID o por nro de cliente (Un cliente puede tener más de una cuenta).
5. Listar todas las cuentas activas ordenadas por saldo descendente.
6. Procesar un lote de movimientos.
7. Finalizar jornada (sobreescribir Cuentas.BIC).

averonica/TP-Prototipo-de-actualizacion-de-cuentas-de-un-banco
