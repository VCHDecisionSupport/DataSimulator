
DECLARE @database_name varchar(500) = 'CommunityMart';
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

';

SELECT
	sch.name AS schema_name
	,tab.name AS table_name
	,col.name AS column_name
FROM sys.schemas AS sch
JOIN sys.tables AS tab
ON sch.schema_id = tab.schema_id
JOIN sys.columns as col
ON tab.object_id = col.object_id

EXEC(@sql);