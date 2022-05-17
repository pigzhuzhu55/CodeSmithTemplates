<script runat="template">

//主键类型[目前不支持联合主键]
ArrayList pkList = new ArrayList();
ArrayList allList = new ArrayList();

//页面初始化
public void Init(){
    for (int i = 0; i < SourceTable.Columns.Count; i++) { 
        ColumnSchema column = SourceTable.Columns[i];
        if(i==0){
            pkList.Add(column);
        }
       allList.Add(column);
    }
}

//查询参数字段
public void WriteQueryParamField(ColumnSchema column)
{
    string colName = column.Name;
    string colType= GetCSharpVariableType(column);
    string colDes = FilterString(column.Description);
    
    if (colType=="Date"){
        string colName1 = string.Format("{0}1",colName);
        string colDes1 = string.Format("起始 {0}",colDes);
        WriteApiModel(colName1,colType,colDes1);
        WriteDateFormat(colType);
        WritePrivateName(colName1,colType);
        Response.Write("\r\n"); 
        
        colName1 = string.Format("{0}2",colName);
        colDes1 = string.Format("结束 {0}",colDes);
        WriteApiModel(colName1,colType,colDes1);
        WriteDateFormat(colType);
        WritePrivateName(colName1,colType);
        Response.Write("\r\n"); 
    }
    else{
        WriteApiModel(colName,colType,colDes);
        WriteDateFormat(colType);
        WritePrivateName(colName,colType);
        Response.Write("\r\n"); 
    }
}
//swagger字段注解
public void WriteApiModel(string colName,string colType,string colDes){
    if (!String.IsNullOrEmpty(colDes)){
       Response.Write(string.Format("\t@ApiModelProperty(name = \"{0}\", value = \"{1}\")\r\n",GetCamelCaseName(colName),FilterString(colDes)));
    }
}
//date字段格式化注解
public void WriteDateFormat(string colType){
    if (colType=="Date"){
       Response.Write(string.Format("\t@JSONField(format=DatePattern.NORM_DATETIME_PATTERN)\r\n"));
       Response.Write(string.Format("\t@JsonFormat(shape = JsonFormat.Shape.STRING,timezone = \"GMT+8\", pattern = DatePattern.NORM_DATETIME_PATTERN,locale = \"zh_CN\")\r\n"));
    }
}
//字段名
public void WritePrivateName(string colName,string colType){
    Response.Write(string.Format("\tprivate {0} {1};\r\n", colType,GetCamelCaseName(colName)));
}
//打印换行
public void WriteWrap(int i){
    if (i < allList.Count - 1) Response.Write("\r\n"); 
}
</script>