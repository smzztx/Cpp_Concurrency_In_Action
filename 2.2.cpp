void f(int i, std::string const &s);
void not_oops(int some_param)
{
	char buffer[1024];
	sprintf(buffer, "%i", some_param);
	std::thread t(f, 3, std::string(buffer)); // 使用 std::string，避免悬垂指针
	t.detach();
}