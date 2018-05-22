string operator+(string x, string y); // x、y都必须非负
string operator-(string x, string y); // x、y都必须非负（结果可能为负）
string operator*(string x, string y); // x、y非负
string operator*(string s, int a); // s,a非负，且a必须小于2*10^8.
string MSDiv(string x, int y, int &res); // 多精度除以int，x非负，y为正
string operator/(string s, int a); // 调用MSDiv
int    operator%(string s, int a); // 调用MSDiv
string MMDiv(string x, string y, string &res); // 多精度除以多精度，x非负，y为正
string operator/(string x, string y); // 调用MMDiv
string    operator%(string x, string y); // 调用MMDiv
string HPower(string s, int a); // s,a必须非负！
string HSqrt(string s); // 开平方取整，s非负！
string Head_zero_remover(string num); // 除了开头可能有'0'外，num必须是非负数。
bool Less(string x, string y); // 非负数之间的“小于”
// ----------------- 以下是负数支持：f15~f19 ------------------------------------
string operator-(string s); // 取负
string SAdd(string x, string y);
string SMinus(string x, string y);
string SMul(string x, string y);
string SMul(string s, int a); // 同样，a的绝对值不能超过2*10^8
// ----------------- f1 () --------------------------
string operator+(string x, string y)
{
    if(x.size() < y.size()) // 预处理，保证x的实际长度>=y
    x.swap(y);
    y.insert(y.begin(), x.size()-y.size(), '0'); // y开头补0到和x一样长
    string sum(x.size(), -1); // 初始大小：x.size()
    int carry=0;
    for(int i=x.size()-1; i >= 0; --i)
    {
        carry += x[i]+y[i]-2*'0';
        sum[i] = carry%10+'0';
        carry /= 10;
    }

    if(carry > 0) // 还有进位1
        return string("1") += sum; // 给开头添加一个“1”
    return sum;
}

// ----------------- f2 (need: f13, f14) --------------------
string operator-(string x, string y)
{
    bool neg = false; // 结果为负标志
    if(Less(x, y))
    {
        x.swap(y); // 如果x<y，交换
        neg = true; // 结果标记为负
    }
    string diff(x.size(), -1); // 差(结果)

    y.insert(y.begin(), x.size()-y.size(), '0');
    int carry=0;
    for(int i=x.size()-1; i >= 0; --i)
        if(x[i] >= y[i]+carry) // 本位够减
        {
            diff[i] = x[i]-y[i]-carry+'0';
            carry = 0;
        }
        else // 需要借位
        {
            diff[i] = 10+x[i]-y[i]-carry+'0';
            carry=1;
        }
        if(neg)
            return string("-") += Head_zero_remover(diff);
        return Head_zero_remover(diff);
}

// ----------------- f3 (need f1, f4) --------------------------
string operator*(string x, string y)
{
    string prod="0"; //初值：0
    for(int i=y.size()-1; i >= 0; --i)
    {
        string p_sum = x * (y[i]-'0'); // p_sum：部分积
        if(p_sum != "0") // 保证后面加0后也符合UAdd的要求！
            p_sum.insert(p_sum.end(), y.size()-1-i, '0');
        prod = prod + p_sum;
    }
    return prod;
}

// ----------------- f4 () --------------------------
string operator*(string s, int a)
{
    if(s == "0" || a == 0) // 以免后面特殊处理！
        return "0";
    string prod(s.size(), -1); // 先申请s.size()位

    int carry=0;
    for(int i=s.size()-1; i >= 0; --i)
    {
        carry += (s[i]-'0')*a;
        prod[i] = carry%10+'0';
        carry /= 10;
    }
    while(carry>0)
    {
        prod.insert(prod.begin(), carry%10+'0');
        carry /= 10;
    }
    return prod;
}

// ----------------- f5 (need f13) --------------------------
string MSDiv(string x, int y, int &res)
{
    string quot(x.size(), 0);
    res=0;
    for(int i=0; i<x.size(); ++i)
    {
        res = 10*res+x[i]-'0';
        quot[i] = res/y+'0'; // 整除结果为商
        res %= y; // 取余保留
    }
    return Head_zero_remover(quot);
}

// ----------------- f6 (need f5, f13) --------------------------
string operator/(string s, int a)
{
    int res;
    return MSDiv(s, a, res);
}

// ----------------- f7 (need f5, f13) --------------------------
int operator%(string s, int a)
{
    int res;
    MSDiv(s, a, res);
    return res;
}

// ----------------- f8 (need f2, f13, f14) --------------------------
string MMDiv(string x, string y, string &res)
{
    string quot(x.size(), '0'); // 初始化成全'0'

    res = ""; // 初始为空，每次下移一个字符
    for(int i=0; i<x.size(); ++i)
    {
        res += x[i]; // 等价res = res*10+x[i];（注意：不是加）
        while( ! Less(res, y)) // 余数大于等于除数时...
        {
            res = res - y; // 余数减去除数
            ++quot[i]; // 商对应位加1
        }
    }
    return Head_zero_remover(quot);
}

// ----------------- f9 (need f2, f8, f13, f14) --------------------------
string operator/(string x, string y)
{
    string t;
    return MMDiv(x, y, t);
}

// ----------------- f10 (need f2, f8, f13, f14) --------------------------
string operator%(string x, string y)
{
    string res;
    MMDiv(x, y, res);
    return res;
}

// ----------------- f11 (need f1, f3, f4) --------------------------
string HPower(string s, int a) // 最多做2*ln(a)次大数乘法
{
    string power="1";
    while(a>0)
    {
        if(a%2 == 1)
            power = power * s;
        a /= 2;
        s = s * s;
    }
    return power;
}
// ----------------- f12 (need f2, f4, f13, f14) --------------------------
string HSqrt(string s) // 手工开平方。若要返回余数，return前的res就是！
{
    string sqroot((s.size()+1)/2, -1);
    string res = s.substr(0, 2-s.size()%2); // 奇位取前1，偶位取前2
    string div="0"; // 占一位置
    for(int i=0; i<sqroot.size(); ++i)
    {
        for(int quot=9; ; --quot)
        {
            div[div.size()-1] = quot+'0'; // 末位试商，从'9'到'0'
            string p_prod = div*quot;
            if( ! Less(res, p_prod) ) // p_prod <= res
            {
                sqroot[i] = quot+'0'; // 将结果追加！
                div = sqroot.substr(0, i+1)*20;
                res = res - p_prod;

                string next2 = s.substr((i+1)*2-s.size()%2, 2);
                if(res == "0")
                    res = next2; // 取后2位
                else
                    res += next2; // 下移2位，追加；即res = res*100+next2
                break;
            }
        }
    }
    return sqroot;
}

// ----------------- f13 () --------------------------
bool Less(string x, string y)
{
    return x.size()<y.size() || x.size() == y.size() && x < y;
}

// ----------------- f14 () --------------------------
string Head_zero_remover(string num) // 化简“003”等数
{
    if(num[0] != '0')
        return num;
    int pos=num.find_first_not_of('0');
    if(pos == string::npos) // 全0
        return "0";
    return num.substr(pos, num.size()-pos);
}

///////////////////////////////////////////////////////////////////////////////
//       以下是负数支持！
///////////////////////////////////////////////////////////////////////////////
// ----------------- f15 () --------------------------
string operator-(string s)
{
    if(s[0] == '-')
        return s.substr(1, s.size()-1);
    if(s == "0")
        return "0";
    return string("-") += s;
}

// ----------------- f16 (need f1, f2, f13, f14, f15) ----------
string SAdd(string x, string y)
{
    if(x[0] == '-' && y[0] == '-')
        return -(-x + -y);
    if(x[0] == '-')
        return y - -x;
    if(y[0] == '-')
        return x - -y;
    return x + y;
}

// ----------------- f17 (need f1, f2, f13, f14, f15) ---------
string SMinus(string x, string y)
{
    if(x[0] == '-' && y[0] == '-')
        return -y - -x;
    if(x[0] == '-')
        return -(-x + y);
    if(y[0] == '-')
        return x + -y;
    return x - y;
}

// ----------------- f18 (need f1, f3, f4, f15) --------------------------
string SMul(string x, string y)
{
    if(x[0] == '-' && y[0] == '-')
        return (-x)*(-y);
    if(x[0] == '-')
        return -((-x)*y);
    if(y[0] == '-')
        return -(x*(-y));
    return x * y;
}

// ----------------- f19 (need f4, f15)--------------------------
string SMul(string s, int a)
{
    if(s[0] == '-' && a<0)
        return (-s)*(-a);
    if(s[0] == '-')
        return -((-s)*a);
    if(a<0)
        return -(s*(-a));
    return s * a;
}
