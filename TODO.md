* 在memory store operation增加controllability的传播。
* system setup上需要补充详细说明以及一些工作。
* ASCI上的约束是否全面与完备。
* Test case generation, 验证。
* 对Function pointer做hook
* 需要修改一下威胁模型，对全局变量指针的lazy initialization做改变，检测全局变量的异常解引用操作
* 优化lazy inilization，调用相对应的create函数来初始化kernel object
