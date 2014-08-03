package.cpath = string.format (
  '%s;%s/git/test_luajit_array/?.bundle',
  package.cpath, os.getenv('HOME'))

local rawarray = require ('rawarray')

local ffi = require("ffi")

local function timing (name, func)
  local bt = os.clock ()
  func ()
  local et = os.clock ()
  print (string.format ('%s elapsed %f', name, et - bt))
end

local test_size = 1024 * 1024 * 64

local function test_ffi ()
  local arr = ffi.new (ffi.typeof ("double[$]", test_size))
  for i = 0, (test_size - 1) do
    arr[i] = i
  end
  local sum = 0
  for i = 0, (test_size - 1) do
    sum = sum + arr[i]
  end
  print ('sum is ' .. sum)
end

local function test_table ()
  local arr = {}
  for i = 1, test_size do
    arr[i] = i
  end
  local sum = 0
  for i = 1, test_size do
    sum = sum + arr[i]
  end
  print ('sum is ' .. sum)
end

local function test_c ()
  local arr = rawarray.rawarray (test_size)
  for i = 0, (test_size - 1) do
    arr[i] = i
  end
  local sum = 0
  for i = 0, (test_size - 1) do
    sum = sum + arr[i]
  end
  print ('sum is ' .. sum)
end

timing ('test_ffi', test_ffi)
timing ('test_table', test_table)
timing ('test_c', test_c)
