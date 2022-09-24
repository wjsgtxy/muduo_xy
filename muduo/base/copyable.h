#ifndef MUDUO_BASE_COPYABLE_H
#define MUDUO_BASE_COPYABLE_H

namespace muduo
{
// 空类，继承这个类的子类是可以复制的类，是个标签类
class copyable{
protected:
    copyable() = default;
    ~copyable() = default;
}; // 要加;才行

} // namespace muduo

#endif // MUDUO_BASE_COPYABLE_H