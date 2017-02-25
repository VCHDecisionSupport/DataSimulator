:setvar server_name "PC"
:setvar database_name "WideWorldImportersDW"
:setvar schema_name "Fact"
:setvar table_name "Sale"
:setvar column_name "[Description]"

:connect $(server_name)
USE $(database_name)
GO

-- table row count is denominator
DECLARE @RowCount INT;
SELECT 
	@RowCount = COUNT(*)
FROM $(schema_name).$(table_name)

-- return this to c++
;WITH value_histogram AS (
SELECT 
	$(column_name) AS ColumnValue
	,COUNT(*) AS ValueFrequency
	,1.*COUNT(*)/@RowCount AS ValueProportion
FROM $(schema_name).$(table_name)
GROUP BY $(column_name)
)
SELECT 
	ColumnValue
	,ValueFrequency
	,ValueProportion
	,CUME_DIST() OVER(ORDER BY ValueProportion ASC) AS ValueCumulativeProportion
FROM value_histogram



--SELECT 
--	$(column_name) AS ColumnValue
--	,COUNT(*) AS ValueFrequency
--	,1.*COUNT(*)/@RowCount AS ValueProportion
--FROM $(schema_name).$(table_name)
--GROUP BY $(column_name)
--ORDER BY COUNT(*);
