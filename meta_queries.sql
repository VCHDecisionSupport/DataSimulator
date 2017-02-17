


SELECT
	sch.name AS schema_name
	,tab.name AS table_name
	,col.name AS column_name
FROM sys.schemas AS sch
JOIN sys.tables AS tab
ON sch.schema_id = tab.schema_id
JOIN sys.columns as col
ON tab.object_id = col.object_id