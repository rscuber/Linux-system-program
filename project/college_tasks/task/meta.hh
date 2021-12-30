
#define VERSION "2017-7"
#define TEST_DATA "test.data"

// These two NOT-prime numbers are randomly picked by reviewers, will be changed somehow
#define N1 123131231UL
#define N2 338371283UL

#define _M(x, y, ...) std::tie(x, y, ##__VA_ARGS__)
#define _N(x, y, ...) std::make_tuple(x, y, ##__VA_ARGS__)

#define EXG(x,y) ({ int64_t t = x; x = y; y = t; })

#ifndef DR_ERRSTR
#define DR_ERRSTR(reason) \
  std::string(__FILE__) + "(line " + std::to_string(__LINE__) + "): " + (reason)
#endif

#ifndef DR_ERROR
#define DR_ERROR(reason) \
  do{ throw std::runtime_error(DR_ERRSTR(reason)); }while(0);
#endif

class DrTask
{
public:
  DrTask(std::string your_name) : name_(your_name), version_(VERSION) {};
  ~DrTask() {};
  virtual void greeting(void){};
  virtual void run(void){};
  virtual void load(std::string filename){};
  virtual void do_the_maths(void){};
  virtual void finish_the_work(void){};
  std::tuple<uint64_t, uint64_t> get_my_numbers(void);
  uint64_t gcd(uint64_t n, uint64_t m);
  std::tuple<int64_t, int64_t, int64_t> egcd(int64_t n, int64_t m);
  void let_me_check_it(std::function<std::list<uint64_t>(uint64_t)>generator);
  std::list<uint64_t> get_check_list(uint64_t n);
  uint64_t pick(std::list<uint64_t> lst, std::function<bool(uint64_t, uint64_t)>picker);
  uint64_t max(std::list<uint64_t> lst);
  uint64_t min(std::list<uint64_t> lst);
  uint64_t get_exponent(void);
  uint64_t expt(uint64_t n, uint64_t e);
  std::list<int64_t> modular_linear_equation_solver(int64_t a, int64_t b, int64_t n);
  uint64_t multiplicative_inverse(void);
  void prepare_the_submit(void);
  void end(void);
  protected:
  std::string name_;
  std::string version_;
  uint64_t sk_;
  uint64_t pk_;
  uint64_t sn_;
  uint64_t phi_;
};
  
std::tuple<uint64_t, uint64_t> DrTask::get_my_numbers(void)
{
  return std::make_tuple(N1, N2);
}

uint64_t DrTask::gcd(uint64_t n, uint64_t m)
{
  while(m%=n) EXG(n, m);
  return n;
}

std::tuple<int64_t, int64_t, int64_t> DrTask::egcd(int64_t n, int64_t m)
{
  int64_t x0 = 1, x1 = 0, y0 = 0, y1 = 1, q = 0;

  while(m)
    {
      _M(q, n, m) = _N(n/m, m, n%m);
      _M(x0, x1) = _N(x1, x0-q*x1);
      _M(y0, y1) = _N(y1, y0-q*y1);
    }
  
  return std::make_tuple(n, x0, y0);
}

std::list<uint64_t> DrTask::get_check_list(uint64_t n)
{
  /* The reviewer will replace this function with a real generator to check your result.
   * Now we just return a prime divisors list of 10240122
   */
  return {1091, 19, 13, 2};
}

void DrTask::let_me_check_it(std::function<std::list<uint64_t>(uint64_t)>generator)
{
  if(generator(10240126) == get_check_list(10240126))
    {
      printf("Congrats! You killed a Bandersnatches!\n");
    }
  else
    {
      printf("Your get_all_prime_divisors is wrong, may be you didn't sort?\n");
      exit(42);
    }
}

uint64_t DrTask::pick(std::list<uint64_t> lst,
                      std::function<bool(uint64_t, uint64_t)>picker)
{
  try
    {
      int64_t ret = lst.front();
      lst.pop_front();
  
      for(auto i : lst)
        {
          if (1 == i)
            {
              printf("Error: I've aleady told you don't include 1!\n");
              exit(42);
            }
      
          ret = picker(ret, i)?ret:i;
        }

      return ret;
    }
  catch (std::exception &e)
    {
      DR_ERROR(e.what());
    }
}

uint64_t DrTask::max(std::list<uint64_t> lst)
{
  return pick(lst, [](uint64_t x, uint64_t y){ return x >= y; });
}

uint64_t DrTask::min(std::list<uint64_t> lst)
{
  return pick(lst, [](uint64_t x, uint64_t y){ return x <= y; });
}

uint64_t DrTask::get_exponent(void)
{
  int64_t i;
  for(i = 3; (i<=phi_) && gcd(phi_, i)!=1; i+=2);
  return i;
}

uint64_t DrTask::expt(uint64_t n, uint64_t e)
{
  uint64_t result = 1;
  for(;e;e>>=1, n*=n) result*=(e&1)?n:1;
  return result;      
}

std::list<int64_t> DrTask::modular_linear_equation_solver(int64_t a,
                                                          int64_t b,
                                                          int64_t n)
{
  int64_t d, x, y;
  _M(d, x, y) = egcd(a, n);
  std::list<int64_t> result = {};
  
  if (!(d%b))
    {
      int64_t x0 = (x*(b/d))%n;
      for (int64_t i = 0; i < d; i++)
        result.push_front((x0+(i*(n/d)))%n);
    }

  return result;
}

uint64_t DrTask::multiplicative_inverse(void)
{
  auto result =  modular_linear_equation_solver((int64_t)sk_, 1, (int64_t)phi_);
  // It's guaranteed by maths to have only one unique result
  if (result.size() != 1)
    {
      printf("Wrong expected result in multiplicative_inverse!\n");
      exit(42);
    }

  int64_t ret = result.front();
  return (uint64_t)ret<0?ret+phi_:ret;
}

void DrTask::end(void)
{
  printf("Seems you've made it, check it out again.\n");
  printf("....................\n");
  printf("Now submit all the things, thanks!\n");
}

