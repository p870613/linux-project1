//請先看過https://blog.csdn.net/Lzq_CNQF/article/details/83148013
//請加在 yourkernel/kernel/sys.c 的 #endif /* CONFIG_COMPAT */ 之前
//版本 4.17.4


void vm_table(struct task_struct *task, char* result)
{
	int no_phy_count = 0, tatol_count = 0, vma_count = 0;
    
	unsigned long vpage;
	struct vm_area_struct *vma =  0;

	for(vma = task->mm->mmap ;vma; vma = vma -> vm_next){	
		vma_count++;
		printk("VMA: %d\n",vma_count);
		
		for (vpage = vma->vm_start; vpage < vma->vm_end; vpage += PAGE_SIZE){

			tatol_count++;

			if(convert_to_phy_add(task->mm, vpage) == 0){
				no_phy_count++;

				printk(	"[VMA%d] [0x%012lx,0x%012lx] | [0x%09lx,0x%09lx] \n",
					vma_count ,
					vpage ,vpage + PAGE_SIZE,
					convert_to_phy_add(task->mm, vpage),convert_to_phy_add(task->mm, vpage)
					);


			}
			else{

				printk(	"[VMA%d] [0x%012lx,0x%012lx] | [0x%09lx,0x%09lx] \n",
						vma_count ,
						vpage ,vpage + PAGE_SIZE,
						convert_to_phy_add(task->mm, vpage),convert_to_phy_add(task->mm, vpage) + PAGE_SIZE
						);
			}


		}
	}

	printk("no_phy_count:%d\n",no_phy_count);
	printk("total_count:%d\n",tatol_count);

}




//syscall 334


SYSCALL_DEFINE1(linux_survey_TT,char*,result){

  	struct task_struct *task = get_current();
	printk("YahaRo\n");
	printk("--------Table v14--------\n");
    vm_table(task,result);
	printk("ByeBye~\n");

    return;

}
