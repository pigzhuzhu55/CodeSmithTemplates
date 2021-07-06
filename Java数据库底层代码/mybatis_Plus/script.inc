<script runat="template">
private string _Prefix = "t_";
[Category("Database")]
[Description("Stroed Procedures Prefix.")]
public string Prefix
{
 	get 
	{
		return _Prefix;
	}
 	set 
	{
		_Prefix = value;
	}
}

private string _package = "com.cly.tfxgj.dbs";
[Category("Database")]
[Description("包名路径")]
public string Package
{
 	get 
	{
		return _package;
	}
 	set 
	{
		_package = value;
	}
}

public string GetClassName(TableSchema table)
{
    return TableClass(table);
}


public string TableClass(TableSchema table)
{
	string className = table.Name;
	if (className.StartsWith(Prefix))
		className = className.Substring(Prefix.Length);
	return String.Format("{0}", GetPascalCaseName(className));
}

public string GetVarName(TableSchema table)
{
	string className = table.Name.ToLower();
	if (className.StartsWith(Prefix))
		className = className.Substring(Prefix.Length);
	return String.Format("{0}", GetCamelCaseName(className));
}

public string GetPascalCaseName(string value)
{
	string result = value.Substring(0, 1).ToUpper() + value.Substring(1);
	switch(result)
	{
		case "Operator":
		case "Class":
		 result += "_p";
		 break;
	}
	return FormatCamelStr(result);
}

public string GetCamelCaseName(string value)
{
	string result = value.Substring(0, 1).ToLower() + value.Substring(1);
	switch(result)
	{
		case "Operator":
		case "Class":
		 result += "_p";
		 break;
	}
	return FormatCamelStr(result);
}

/// <summary>
/// 生成骆驼字符串
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
public string FormatCamelStr(string str){
    string retStr = String.Empty;
    bool isFit = false;
    foreach(char ar in str)
    {
        string ars = ar.ToString();
        if(ars.Equals("_"))
        {
            isFit = true;
            continue;
        }
        retStr+=isFit?ars.ToUpper():ars;
        isFit = false;
    }
    return retStr;
}

public string GetCSharpVariableType(ColumnSchema column)
{
	if (column.Name.EndsWith("TypeCode")) return column.Name;
	
    
    
	switch (column.DataType)
	{
		case DbType.AnsiString: return "String";
		case DbType.AnsiStringFixedLength: return "String";
		case DbType.Binary: return "Byte[]";
		case DbType.Boolean: return "Boolean";
		case DbType.Byte: return "Integer";
		case DbType.Currency: return "BigDecimal";
		case DbType.Date: return "Date";
		case DbType.DateTime: return "Date";
		case DbType.Decimal: return "BigDecimal";
		case DbType.Double: return "Double";
		case DbType.Guid: return "Guid";
		case DbType.Int16: return "Integer";
		case DbType.Int32: return "Integer";
		case DbType.Int64: return "Long";
		case DbType.Object: return "Object";
		case DbType.SByte: return "Integer";
		case DbType.Single: return "Double";
		case DbType.String: return "String";
		case DbType.StringFixedLength: return "String";
		case DbType.Time: return "TimeSpan";
		case DbType.UInt16: return "Integer";
		case DbType.UInt32: return "Integer";
		case DbType.UInt64: return "Long";
		case DbType.VarNumeric: return "BigDecimal";
		default:
		{
			return "__UNKNOWN__" + column.NativeType;
		}
	}
}

public string FilterString(string msg)
{
    return msg.Replace("\r", "").Replace("\n", "").Replace("\r\n", "");
}

 
</script>