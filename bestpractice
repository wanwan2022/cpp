# Best Practice

## Rule1

- 在for循环中不允许出现`size - 1`
- `vector.size()`的数据类型为`size_t`，如果vector是空的，`size() - 1`将会是一个非常大的数，导致越界或无法跳出循环

### BadCase:

```cpp
for (size_t i = 0; i < points.size() - 1; ++i) { // 不要不信邪，core 的时候很尴尬
	...
}
```

### GoodCase:

```cpp
for (size_t i = 0; i + 1 < points.size(); ++i) { // 放心使用
	...
}
```

## Rule2

- 无论何时，使用指针都要检查有效性对输入永远保持怀疑，不要相信你的上游，甚至不要相信你自己.

  环节⼀旦多起来，函数嵌套够深的情况下，千万不要太⾃信，对任何输⼊都要抱有怀疑的⼼态，做好

  保护与检查，⼩⼼⼀点总是没错的。检查所消耗的算⼒能带来更⾼的鲁棒性，性价⽐是⾮常⾼的。

  建议将检查指针养成习惯，不要觉得上边逻辑检查过了，下边就不⽤检查了，⼀旦这段代码被复⽤，

  曾经的语境被打破就可能会 core

### 外层函数

```c++
void Function1(WorldViewPtr world_view) {
    if (!world_view) { // 这里只是一种情况，Function1 调用 Function2 的时候不检查输入是没问题的，换了 Function3 就不一定了
        return;
    }
    Function2(world_view);
}
```

### BadCase:

world_view 可能是 nullptr，world_view->chassis 也可能是 nullptr, 不要抱有侥幸⼼理，觉得既然⾛到Function2 的逻辑，⼀定有 world_view 和 world_view->chassis，这种⾃信可不兴有啊

```cpp
void Function2(WorldViewPtr world_view) {
	const double v0 = world_view->chassis()->speed_limit_mps();
}
```

### GoodCase:

```cpp
void Function2(WorldViewPtr world_view) {
    if (!world_view) { // 养成检查输入的习惯
        return;
    }
    if (world_view->chassis()) { // 不管上下文怎样，我要用一个指针，就一定要检查有效性
        const double v0 = world_view->chassis()->speed_limit_mps();
    }
}
```

## Rule3

- 不要在一个函数中返回地址

- 函数中的变都是临时变量，临时变量的指针指向的内容在函数结束的那⼀刻就变成了野指针，如果

  ⼀定要⽤指针，请使⽤智能指针

- 当然，返回指针的操作整体是不推荐的，如无必要，不要返回指针

### BadCase:

```cpp
ObstacleInfo* GetVirtualObstacle() {
    ObstacleInfo obstacle_info;
    return &obstacle_info; // 返回的瞬间，obstacle_info 的内存就被回收了
}
```

```c++
std::vector<ObstacleInfo>& GetObstacles() { // 返回引⽤也同理，会 core 的
   std::vector<ObstacleInfo> obs;
   return obs;
}
```



### GoodCase:

```cpp
std::shared_ptr<ObstacleInfo> GetVirtualObstacle() {
    std::shared_ptr<ObstacleInfo> obstacle_info = std::make_shared<ObstacleInfo>();
    return obstacle_info; // 返回的瞬间，obstacle_info 的 counter 还是 1，不会被回收
}
```

## Rule4

- **不要相信** **vector** **中元素的指针**

  vector 是会⾃动拓容的，⼀旦发⽣拓容，曾经的指针都会失效，⾮常危险，且难以排查。

### BadCase:

```c++
std::vector<ObstacleInfo> obstacles;
std::vector<const ObstacleInfo*> interested_obs;
interested_obs.reserve(obstacles.size());
for (const auto& obs : obstacles) {
   if (obs.interested()) {
     // 看似为了减少拷⻉，提⾼了效率，⼀旦obstacles 发⽣拓容操作，interested_obs 中的变量全部变成野指针
     interested_obs.push_back(&obs); 
   }
}
```

### GoodCase:

```c++
// 将对象建成 ID 的索引，存储它的智能指针
std::unordered_map<std::string, ObstacleInfoConstPtr> obs_table;
std::unordered_set<std::string> interested_obs;                 // 只取索引
for (const auto &p : obs_tacle) {
  if (p.second && p.second->interested()) {// 所有指针都要检查有效性，参考 Rule2
    interested_obs.insert(p.first);
  }
}
```

## Rule5

- 递归函数一定要加层深限制，你永远不知道，下⼀个死循环是不是出现在你的递归函数⾥

### BadCase:

```cpp
void MyFunc() {
    if (Condition()) { // 递归函数先写终止条件，养成好习惯
        return;
    }
    MyFunc(); // 常规递归，但很危险！
}
```

### GoodCase:

```cpp
const int kMaxDepth = 10000; // 用 GFlag 或 config 都可以，给一个足够大的数就可以
void MyFunc(int layer) {
    if (layer > kMaxDepth || Condition()) { // 可以增加 log，提示是由于超层深限制而退出
        return;
    }
    MyFunc(++layer); // 每多一层，layer 增加1，这种写法会多一个参数，但至少不会爆掉
}
```

## Rule6

- 在if语句中，右值放在`==`的左边
- 主要是预防手滑

### BadCase:

```cpp
ExecutorType executor_type == world_view ? world_view->executor_type() :ExecutorType::DUMMY; // 检查指针！！！
if (executor_type == ExecutorType::ICA_EXECUTOR) { // == 写成 =，executor_type 就变了，这种 bug 很难查
    ...
}
```

### GoodCase:

```c++
ExecutorType executor_type = world_view ? world_view->executor_type() : ExecutorType::DUMMY; // 检查指针！！！
if (ExecutorType::ICA_EXECUTOR == executor_type) { // == 写成 = 会编译不通过
 ...
}
```

## Rule7

- 在if语句中，即使只有一行，也要加{}

只要你的源码还在，就可能被其它⼈修改，⼀⾏的代码看似简洁，实则⾮常危险；

### BadCase:

```c++
if (Condition()) MY_MACRO(a,b,c); // 没⼈知道 MY_MACRO 这个宏是⼏⾏
```

### GoodCase:

```cpp
if (Condition()) {
    MY_MACRO(a,b,c); // 虽然不推荐用宏，但这样起码是安全的
}
```

## Rule8

**浮点数⽐较，要考虑精度**

### **BadCase**

```c++
double obs_speed_mps;

if (0.0 == obs_speed_mps) { // obs_speed 可能是 9.039581289e-27

 	...

}
```

### GoodCase:

```c++
const double kMathEpsilon = 1e-7;
double obs_speed_mps;
if (std::abs(obs_speed_mps) < kMathEpsilon) {
  ...
}
```

## Rule9

略

## **Rule10**

**默认使**  **std::abs**

fabs 和 abs 都是 C 函数，在 C++ 标准库中应使⽤ std::abs ， std::abs 可重载，适⽤⾯更⼴

**BadCase**

```c++
if (abs(1.1) > 1.0) { // abs(1.1) 等于 1，这个条件是进不去的
 // do some thing
}
```

**GoodCase**

```c++
if (std::abs(1.1) > 1.0) { // std::abs(1.1) 等于 1.1， 可以正常进⼊条件语句
 // do some thing
}
```

## Rule11

**non-void** **函数先写返回值**

gcc9 中 non-void 函数不写 return 语句是可能编译通过的，但会触发 runtime core

### **BadCase**

```c++
int BadCase() {
	std::cout << "hello core" << std::endl;
}
```

### **GoodCase**

```c++
int GoodCase() {
   std::cout << "hello world" << std::endl;
   return 0； // 刚定义的时候就可以把默认 return 写上，以防忘记
}
```

## Rule12

**不要在头⽂件⾥写** **using namespace xxx** **或** **using xxx (**别名除外);

header 可能会被多隐性包含，头⽂件中的 using namespace 可能造成命名空间污染，出现问题极其难以排查

## Rule13

- 当一个类必需持有自身类的时候，禁止使用 `std::shared_ptr`
- 如果自己持有了自己，会造成循环引用，引起内存泄漏

### BadCase

```cpp
class Lane {
protected:
    std::shared_ptr<Lane> other_lane_; // 设计初衷是想持有其它对象，但存在持有自身的风险
}
```

### GoodCase

```cpp
class Lane {
protected:
    std::weak_ptr<Lane> other_lane_; // 使用 weak_ptr，避免循环引用
    std::string other_lane_id_; // 或使用 id 索引，避免引用指针
}
```

### 

# 提升质量tips

## Recommend1

- 提前申请 vector 的空间
- 知道准确大小就用准确大小，不知道的可以估一个大概的大小，取稍大一点没关系

```c++
std::vector<ObstacleInfo> obstacles;
obstacles.reserve(perception_obstacles.size()); // 提前申请空间
for (const auto& pb_obs : perception_obstacles) {
 	obstacles.emplace_back(pb_obs);
}
```

## Recommend2

- 对于 vector，能用 `emplace_back`, 就用 `emplace_back`
- `emplace_back` 比 `push_back` 少一次拷贝，积少成多

```c++
std::vector<Vec2d> points;
points.reserve(pb_points.size()); 
for (const auto& pb_point : pb_points) {
 obstacles.emplace_back(pb_point.x(), pb_point.y()); // 尽可能使⽤emplace_back
}
```

## Recommend3

**能⽤乘法，就不要⽤除法。**

对于计算机⽽⾔，乘法是⽐除法快的；

```c++
constexpr double KMH2MPS = 0.277778 // (1.0 / 3.6) = 0.277778
double speed_mps_1 = speed_kmh * KMH2MPS;
double speed_mps_2 = speed_kmh / 3.6; // 计算量到⼀定程度时，speed_mps_1是⽐ speed_mps_2 要快的
```

## Recommend4

**类内提前开辟内存**

class 并不仅仅可以存属性，⼀些临时变量，也可以存下来，避免⼆次开辟内存（PS：效率差距超乎想象，FixedQP 的 P99 要⽐普通 QP 的 P99 低⾮常多）

### BadCase

```cpp
class Foo {
private:
    void Func() {
        std::vector<Vec2d> pionts;
        // 临时构造 points 将占用很多 CPU 资源
    }
}
```

### GoodCase

```cpp
class Foo {
private:
 void Func() {
 // 直接使⽤ points_，效率很⾼，超乎想象
 }
private:
 // For pre-malloc
 std::vector<Vec2d> points_; // 作为⼀个成员变量，虽然对业务没什么直接作⽤，但不⽤每次都开辟新的内存
};
```

## Recommend5

- 尽可能使用 math 库里的三角函数

### BadCase

```c++
const double cos_theta = std::cos(theta);
```

### GoodCase

```c++
apollo::common::math::Angle16 angle =
apollo::common::math::Angle16::from_deg(theta); // 推荐使⽤ math 库下的 angle
const double cos_theta = apollo::common::math::cos(angle); 
// 这⾥是查表计算，有兴趣可以看下源码，积少成多，⼤的三⻆函数是⽐较耗时的
```

## Recommend6

for 语句不要超过 3 层
相信函数爆炸的力量，3层 for 下数级很吓人（PS：地图实属无奈，定好的协议层级太深了）

```c++
for (const auto& road : roads) {
  for (const auto& section : road.sections()) {
    for (const auto& lane : section.lanes()) {
      for (const auto& ol : lane.overlaps()) {
        // 写到这⾥，代码已经⾮常难读了，效率也堪忧
      }
    }
  }
}
```

## Recommend7

**⼀个函数不要超出150⾏**

150 ⾏并不是⼀个硬条件，核⼼思想是不要写太⻓的函数，可读性会⾮常低，⾼可读性的代码意味着

⾼维护性，不想粘在⼿上放不掉就请把代码写的清晰易懂⼀些

### **BadCase**

```c++
void ExportWorkInfo(WorldViewPtr world_view,
	std::shared_ptr<::apollo::planning::WorkInfo> work_info) {
 	// 此处省略 500 ⾏……，太难读了，可维护性⾮常差
}
```

### GoodCase

```cpp
void ExportWorkInfo(WorldViewPtr world_view,
std::shared_ptr<::apollo::planning::WorkInfo> work_info) {
   // ⼤函数拆成⼩函数，⼀⽬了然，哪⾥ Bug 修哪⾥
   FillSpeedLimit(world_view, adc_lane_info, work_info);
   FillRoadForm(world_view, adc_lane_info, work_info);
   FillCarAhead(world_view, work_info);
   FillLaneChangeStatus(world_view, work_info);
   FillAccessACCToTJA(world_view, work_info);
   FillWTIInformation(world_view, work_info);
   FillODDReminder(world_view, work_info);
}
```

## Recommend8

**if** **没必要包太多层**

还是为了可读性，可读性与可维护性成正⽐

### BadCase

```cpp
void Func(WorldViewPtr world_view) {
   if (world_view) {
     auto loc = world_view->localization_estimate();
     if (loc) {
         // 在这样⼀个⼤括号⾥处理逻辑，可读性⽐较差
         }
     }
}
```

### GoodCase

```cpp
void Func(WorldViewPtr world_view) {
    if (!world_view) {
        AERROR << "invalid world_view";
        return;
    }
    if (!world_view->localization_estimate()) {
        AERROR << "invalid localization";
        return;
    }
    // 准入检查做完后，在这里处理逻辑会清晰很多
}
```

## Recommend9

- 控制传参的数量
- 传参太多的情况下，会极大的降低函数的可读性

### BadCase

```cpp
// 10 个参数的函数，真的非常难读！！超级难读！！！
bool do_some_thing(const bool &find_event,
                   const apollo::executor::RoadEventType &road_event_type,
                   const int &right_of_way,
                   const bool &is_left_virtual,
                   const bool &is_right_virtual,
                   const LaneInfoSegment &segment,

                   const common::math::Vec2d &segment_xy,
                   const std::string &refline_name,
                   const std::vector<ReferenceLineInfoPtr> &all_reflines,
                   ReferenceLineInfoPtr &refline);
```

## Recommend10

- 算法设计阶段切忌过渡设计，宁可设计不足后期再加接口，也不要没有需求创造需求，让算法显得很完整，往往都是实际中的需求前期没识别到，前期设计的接口实际也没人用，更重要的是，前期设计的接口如果冗余或者不合适，将很难删除

## Recommend11

- 避免 “冲击波” 式代码
- 控制语句不要嵌套太深、过深的嵌套会严重影响代码的可读性

```c++
function dosomething(params) {
    $.get(url, function(result) {
                setTimeout(function() {
                startAsyncProcess(function(){
                    S.post(url, function(response){
                if (response.good) {
                            setstateasGoodResponse(funct
                            console. log('Hooray!')
                    });
                }
            });
        });
    });
});
```

### BadCase

```c++
LeftTurnType ReferenceLineInfo::find_next_left_turn_type() const {
    if (lane_segment_left_turn_type_map_.empty()) {
        return LeftTurnType::LEFT_TURN_DEFAULT;
    }

    apollo::hdmap::LaneSegment segment;
    double distance;
    if (find_next_turn(&segment, &distance) && segment.lane_info() != nullptr) {
        const auto &lane = segment.lane_info()->lane();
        if (lane.turn() == apollo::common::hdmap::Lane::LEFT_TURN) {
            const auto &idx_map = lane_segment_idx_map_;
            const auto &segments = lane_segments_;
            const auto &left_turn_type_map = lane_segment_left_turn_type_map_;
            if (idx_map.find(lane.id().id()) != idx_map.end()) {
                const auto idx = idx_map.at(lane.id().id());
                for (int i = idx - 1; i >= 0; --i) {
                    if (segments[i].lane_info()->lane().turn() !=
                        apollo::common::hdmap::Lane::LEFT_TURN) {
                        if (left_turn_type_map.find(
                                    segments[i].lane_info()->lane().id().id()) !=
                            left_turn_type_map.end()) {
                            return left_turn_type_map.at(
                                    segments[i].lane_info()->lane().id().id());
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }

    return LeftTurnType::LEFT_TURN_DEFAULT;
}
```

### GoodCase

```c++
LeftTurnType ReferenceLineInfo::find_next_left_turn_type() const {
    if (lane_segment_left_turn_type_map_.empty()) {
        return LeftTurnType::LEFT_TURN_DEFAULT;
    }

    apollo::hdmap::LaneSegment segment;
    double distance;
    if (find_next_turn(&segment, &distance) && segment.lane_info() == nullptr) {
        return LeftTurnType::LEFT_TURN_DEFAULT;
    }
    const auto &lane = segment.lane_info()->lane();
    if (lane.turn() != apollo::common::hdmap::Lane::LEFT_TURN) {
        return LeftTurnType::LEFT_TURN_DEFAULT;
    }
    const auto &idx_map = lane_segment_idx_map_;
    const auto &segments = lane_segments_;
    const auto &left_turn_type_map = lane_segment_left_turn_type_map_;
    if (idx_map.find(lane.id().id()) == idx_map.end()) {
        return LeftTurnType::LEFT_TURN_DEFAULT;
    }
    const auto idx = idx_map.at(lane.id().id());
    for (int i = idx - 1; i >= 0; --i) {
        if (segments[i].lane_info()->lane().turn() ==
            apollo::common::hdmap::Lane::LEFT_TURN) {
            break;
        }
        if (left_turn_type_map.find(
                    segments[i].lane_info()->lane().id().id()) !=
            left_turn_type_map.end()) {
            return left_turn_type_map.at(
                    segments[i].lane_info()->lane().id().id());
        }
    }
    return LeftTurnType::LEFT_TURN_DEFAULT;
}
```

## Recommend12

- 相同的功能模块抽取成函数
- 相同的代码存在于多处，对维护成本会非常高，必须对每一处更新进行同步，bug 滋生的概率很高

### BadCase

geo.hpp 是 andes 内坐标转换的代码，andes 内起码存在 4 份！好在它比较稳定，但这是非常差劲的代码，一旦投影有变，需要四处同步，任何一处未同步都会导致严重 bug。

![img](file:////private/var/folders/9r/bcjywts115v2s_4zjj_t1mkw0000gn/T/com.kingsoft.wpsoffice.mac/wps-xiashunhan/ksohtml//wps67.jpg)

## Recommend13

- 对于状态判断函数，充分条件放最后，之前检查必要条件
- 理解起来太抽象的话可以记为 “不穿插返回”，如逻辑中穿插返回不同的值，可能会漏掉一些逻辑

### BadCase

```cpp
bool ConditionCheck() {
    if (a) { // a, b 为递进检查，很可能 a 检查完完全跳过 b、c、d 的检查，易滋生 Bug
        return true;
    } else if (b) { // 很可能由于命中 b 导致 c 未运行而提前退出
        return false;
    }
    if (c) {
        return true;
    }
    if (d) {
        return false;
    }
    return true;
}
```

### GoodCase

```cpp
bool ConditionCheck() {
    if (a) { // a、b、c都为必要检查，任一条件不满足即退出
        return false;
    }
    if (b) {
        return false; // 中途的检查都是返回 false，不穿插返回
    }

    if (c) {
        return false;
    }
    return true; // 所有必要条件检查完才，达到充分状态才可返回
}
```

## Recommend14

- 不要使用 `std::to_string` 将其它数据转化为 str 进行索引
- `std::to_string` 是非常耗时的。轻易不要把数据转成 string 进行索引

![img](file:////private/var/folders/9r/bcjywts115v2s_4zjj_t1mkw0000gn/T/com.kingsoft.wpsoffice.mac/wps-xiashunhan/ksohtml//wps66.jpg)

### BadCase

```cpp
const int N = 2000;
std::unordered_set<std::string> risk_field_str_set;
Timer t;
for (int i = 0; i < N; ++i) {
  for (int j = 0; j < N; ++j) {
    risk_field_str_set.insert(std::to_string(i) + "_" + std::to_string(j));
  }
}
t.print_elapsed("risk_field_str_set");
t.reset();
for (int i = 0; i < N; ++i) {
  for (int j = 0; j < N; ++j) {
    int c = risk_field_str_set.count(std::to_string(i) + "_" + std::to_string(j));
  }
}
t.print_elapsed("risk_field_str_set.search");
```

### GoodCase

```cpp
std::unordered_map<int, std::unordered_set<int>> risk_field_hash;
t.reset();
for (int i = 0; i < N; ++i) {
  for (int j = 0; j < N; ++j) {
    risk_field_hash[i].insert(j);
  }
}
t.print_elapsed("risk_field_hash");
t.reset();
for (int i = 0; i < N; ++i) {
  for (int j = 0; j < N; ++j) {
    int c = risk_field_hash[i].count(j);
  }
}
t.print_elapsed("risk_field_hash.search");
```

## Recommend15

- 用类似 `unordered_map` 和 `unordered_set` 这样的 hash 容器时也可以调用一下 `reserve`
- hash 容器内部撞帧后会调用 `rehash()` 函数，并重新分配内存，提前 `reserve` 一下，内部会重新分配 buckets，一定程度上减少撞帧，进而减少内存的重新分配

![img](file:////private/var/folders/9r/bcjywts115v2s_4zjj_t1mkw0000gn/T/com.kingsoft.wpsoffice.mac/wps-xiashunhan/ksohtml//wps65.jpg)

### BadCase

```cpp
std::unordered_map<int, int> M;
for (int i = 0; i < 10000; ++i) {
    M[i] = i;
}
```

### GoodCase

```cpp
std::unordered_map<int, int> M;
M.reserve(10000);
for (int i = 0; i < 10000; ++i) {
    M[i] = i;
}
```

