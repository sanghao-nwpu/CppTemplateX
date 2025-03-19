cmake_minimum_required(VERSION 3.10.0)
project(TaskTemplateX VERSION 0.1.0 LANGUAGES C CXX)


## kfgins 任务模板
add_subdirectory(kfgins_task)

## 
add_subdirectory(obgins_task)

add_subdirectory(pimpl_task_template)