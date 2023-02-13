int fun1(int* i) 
{ 
return (*i) * 5; 
} 
int fun2(int* i) 
{
return fun1(i) * 5; 
}