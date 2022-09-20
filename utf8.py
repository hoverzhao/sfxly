# coding utf-8
import os
import chardet


def find_all_file(path: str) :
  for root, dirs, files in os.walk(path):
    for f in files:
      if f.endswith('.cpp'):
        fullname = os.path.join(root, f)
        yield fullname
      pass
    pass
  pass


def judge_coding(path: str) :
#with open('utf.txt', 'rb') as f:  # 删除就行
#    utf = chardet.detect(f.read()) # 同上

  with open(path, 'rb') as f:
    c = chardet.detect(f.read())

  if c != 'utf-8':            # 改为 c != 'utf-8'
    return c


def change_to_utf_file(path: str):
  for i in find_all_file(path):
    c = judge_coding(i)
    if c:
      change(i, c['encoding'])
      print("{} 编码方式已从{}改为 utf-8".format(i, c['encoding']))


def change(path: str, coding: str):
  with open(path, 'r', encoding=coding) as f:
    print(path)
    text = f.read()

  with open(path, 'w', encoding='utf-8') as f:
    f.write(text)


def check(path: str):
  for i in find_all_file(path):
    with open(i, 'rb') as f:
      print(chardet.detect(f.read())['encoding'], ': ', i)


def main():
  my_path = os.getcwd()
  change_to_utf_file(my_path)
  # check(my_path)


if __name__ == '__main__':
  main()
