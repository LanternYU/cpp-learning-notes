#include <iostream>
#include <cstddef>
#include <cstring>
#include <cassert>

class TextDocument{
	private:
		char* content;
		size_t length;
		const char* tittle;
	public:
		TextDocument();
		~TextDocument(){delete [] content; length = 0; delete [] tittle; };
		TextDocument(const char* title,const char* initialContent);
		TextDocument(const string& content);
		TextDocument& operator = (const string& content);
		void append(const char* text); 
		char* getContent() const {return content;};
		size_t getLength() const {return length;};
		const char* getTitle() const {return tittle;};
		void clear() {delete [] content; length = 0; delete [] tittle;}
		
};
TextDocument::TextDocument()
{
	content = nullptr;
	length = 0;
	tittle = new char[9];
	const char* temp = "Untittle";
	strcpy(tittle,temp);
}
TextDocument::TextDocument(const char* title,const char* initialContent)
{
	
	length = strlen(initialContent);
	content = new char[length + 1];
	strcpy(content,initialContent);
	strcpy(this->title,title);
}
TextDocument::TextDocument(const string& content)
{
	length = content.length;
	this->content = new char[length + 1];
	strcpy(this->content,content);
}
TextDocument& TextDocument::operator =(const string& content)
{
	if(this == &content) return *this;
	delete [] this->content;
	length = content.length;
	this->content = new char[length + 1];
	strcpy(this->content,content);
}

void TextDocument::append(const char* text)
{
	char* temp = new char[length + text.length + 1];
	strcpy(temp,content);
	for(size_t i=0;i<text.length;i++){
		temp[i+length] = text[i];
	}
	temp[length + text.length] = '\0';
	delete [] content;
	content = new char[length + text.length + 1];
	strcpy(content,temp);
	delete [] temp;
}

// 测试默认构造函数
void testDefaultConstructor() {
    TextDocument doc;
    assert(strcmp(doc.getTitle(), "Untitled") == 0);
    assert(doc.getLength() == 0);
    assert(doc.getContent() == nullptr || *doc.getContent() == '\0');
    std::cout << "默认构造函数测试通过\n";
}

// 测试带参构造函数
void testParamConstructor() {
    const char* title = "Test Document";
    const char* content = "Hello, World!";
    TextDocument doc(title, content);
    
    assert(strcmp(doc.getTitle(), title) == 0);
    assert(doc.getLength() == strlen(content));
    assert(strcmp(doc.getContent(), content) == 0);
    std::cout << "带参构造函数测试通过\n";
}

// 测试拷贝构造函数（深拷贝验证）
void testCopyConstructor() {
    TextDocument doc1("Original", "Original content");
    TextDocument doc2(doc1);  // 调用拷贝构造函数
    
    // 验证内容相同
    assert(strcmp(doc1.getContent(), doc2.getContent()) == 0);
    assert(doc1.getLength() == doc2.getLength());
    
    // 修改原对象内容，验证拷贝对象不受影响（深拷贝）
    TextDocument temp("Temp", "Modified content");
    doc1 = temp;  // 利用赋值运算符修改原对象
    assert(strcmp(doc1.getContent(), "Modified content") == 0);
    assert(strcmp(doc2.getContent(), "Original content") == 0);  // 拷贝对象应保持不变
    
    std::cout << "拷贝构造函数测试通过\n";
}

// 测试赋值运算符
void testAssignmentOperator() {
    TextDocument doc1("Doc1", "Content of doc1");
    TextDocument doc2("Doc2", "Content of doc2");
    
    // 正常赋值
    doc2 = doc1;
    assert(strcmp(doc2.getContent(), "Content of doc1") == 0);
    assert(doc2.getLength() == doc1.getLength());
    
    // 自赋值测试
    doc2 = doc2;
    assert(strcmp(doc2.getContent(), "Content of doc1") == 0);  // 内容应保持不变
    
    // 赋值给空文档
    TextDocument emptyDoc;
    emptyDoc = doc1;
    assert(strcmp(emptyDoc.getContent(), "Content of doc1") == 0);
    
    std::cout << "赋值运算符测试通过\n";
}

// 测试append方法
void testAppend() {
    TextDocument doc("Append Test", "Start");
    
    // 追加正常字符串
    doc.append(" middle");
    assert(strcmp(doc.getContent(), "Start middle") == 0);
    assert(doc.getLength() == strlen("Start middle"));
    
    // 追加空字符串
    doc.append("");
    assert(strcmp(doc.getContent(), "Start middle") == 0);  // 内容应不变
    assert(doc.getLength() == strlen("Start middle"));
    
    // 追加到空文档
    TextDocument emptyDoc;
    emptyDoc.append("New content");
    assert(strcmp(emptyDoc.getContent(), "New content") == 0);
    
    std::cout << "append方法测试通过\n";
}

// 测试clear方法
void testClear() {
    TextDocument doc("Clear Test", "Content to be cleared");
    
    doc.clear();
    assert(doc.getLength() == 0);
    assert(doc.getContent() == nullptr || *doc.getContent() == '\0');
    
    // 测试清空已空文档
    doc.clear();  // 应能安全处理
    std::cout << "clear方法测试通过\n";
}

// 测试多个对象的内存管理（验证无内存泄漏和重复释放）
void testMemoryManagement() {
    // 创建多个对象并进行操作，观察是否有运行时错误
    TextDocument* doc1 = new TextDocument("Doc1", "Document 1 content");
    TextDocument* doc2 = new TextDocument(*doc1);
    
    doc2->append(" with modifications");
    *doc1 = *doc2;
    
    delete doc1;
    delete doc2;
    
    // 创建临时对象
    {
        TextDocument doc3("Temporary", "Will be destroyed");
        TextDocument doc4;
        doc4 = doc3;
    }  // 离开作用域时应正确析构
    
    std::cout << "内存管理测试通过（无明显错误）\n";
}

int main() {
    testDefaultConstructor();
    testParamConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testAppend();
    testClear();
    testMemoryManagement();
    
    std::cout << "\n所有测试均通过！\n";
    return 0;
}

