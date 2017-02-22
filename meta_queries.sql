
SELECT
	DB_NAME() AS database_name
	,(sch.name) AS schema_name
	,(tab.name) AS table_name
	,(col.name) AS column_name
FROM sys.schemas AS sch
JOIN sys.tables AS tab
ON sch.schema_id = tab.schema_id
JOIN sys.columns as col
ON tab.object_id = col.object_id;


SELECT
	QUOTENAME(sch.name)+'.'+QUOTENAME(tab.name) AS table_name
	,col.name AS column_name
FROM sys.schemas AS sch
JOIN sys.tables AS tab
ON sch.schema_id = tab.schema_id
JOIN sys.columns as col
ON tab.object_id = col.object_id;


DECLARE @database_name varchar(500);
SET @database_name = 'CommunityMart';
SET @database_name = 'WideWorldImportersDW';
DECLARE @table_name varchar(500);
SET @table_name = 'Payment Method'
DECLARE @sql varchar(MAX) = '
SELECT
	sch.name AS schema_name
	,tab.name AS table_name
	,col.name AS column_name
FROM '+QUOTENAME(@database_name)+'.sys.schemas AS sch
JOIN '+QUOTENAME(@database_name)+'.sys.tables AS tab
ON sch.schema_id = tab.schema_id
JOIN '+QUOTENAME(@database_name)+'.sys.columns as col
ON tab.object_id = col.object_id
WHERE 1=1
AND tab.name = '''+@table_name+'''
';



EXEC(@sql);