#ifndef __VMLINUX_H__
#define __VMLINUX_H__

#ifndef BPF_NO_PRESERVE_ACCESS_INDEX
#pragma clang attribute push (__attribute__((preserve_access_index)), apply_to = record)
#endif

typedef signed char __s8;

typedef unsigned char __u8;

typedef short int __s16;

typedef short unsigned int __u16;

typedef int __s32;

typedef unsigned int __u32;

typedef long long int __s64;

typedef long long unsigned int __u64;

typedef __s8 s8;

typedef __u8 u8;

typedef __s16 s16;

typedef __u16 u16;

typedef __s32 s32;

typedef __u32 u32;

typedef __s64 s64;

typedef __u64 u64;

enum {
	false = 0,
	true = 1,
};

typedef long int __kernel_long_t;

typedef long unsigned int __kernel_ulong_t;

typedef int __kernel_pid_t;

typedef unsigned int __kernel_uid32_t;

typedef unsigned int __kernel_gid32_t;

typedef __kernel_ulong_t __kernel_size_t;

typedef __kernel_long_t __kernel_ssize_t;

typedef long long int __kernel_loff_t;

typedef long long int __kernel_time64_t;

typedef __kernel_long_t __kernel_clock_t;

typedef int __kernel_timer_t;

typedef int __kernel_clockid_t;

typedef unsigned int __poll_t;

typedef u32 __kernel_dev_t;

typedef __kernel_dev_t dev_t;

typedef short unsigned int umode_t;

typedef __kernel_pid_t pid_t;

typedef __kernel_clockid_t clockid_t;

typedef _Bool bool;

typedef __kernel_uid32_t uid_t;

typedef __kernel_gid32_t gid_t;

typedef __kernel_loff_t loff_t;

typedef __kernel_size_t size_t;

typedef __kernel_ssize_t ssize_t;

typedef s32 int32_t;

typedef u32 uint32_t;

typedef u64 sector_t;

typedef u64 blkcnt_t;

typedef u64 dma_addr_t;

typedef unsigned int gfp_t;

typedef unsigned int fmode_t;

typedef u64 phys_addr_t;

typedef phys_addr_t resource_size_t;

typedef struct {
	int counter;
} atomic_t;

typedef struct {
	s64 counter;
} atomic64_t;

struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

struct hlist_node;

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};

struct callback_head {
	struct callback_head *next;
	void (*func)(struct callback_head *);
};

typedef int initcall_entry_t;

struct lock_class_key {};

struct fs_context;

struct fs_parameter_spec;

struct dentry;

struct super_block;

struct module;

struct file_system_type {
	const char *name;
	int fs_flags;
	int (*init_fs_context)(struct fs_context *);
	const struct fs_parameter_spec *parameters;
	struct dentry * (*mount)(struct file_system_type *, int, const char *, void *);
	void (*kill_sb)(struct super_block *);
	struct module *owner;
	struct file_system_type *next;
	struct hlist_head fs_supers;
	struct lock_class_key s_lock_key;
	struct lock_class_key s_umount_key;
	struct lock_class_key s_vfs_rename_key;
	struct lock_class_key s_writers_key[3];
	struct lock_class_key i_lock_key;
	struct lock_class_key i_mutex_key;
	struct lock_class_key i_mutex_dir_key;
};

typedef void *fl_owner_t;

struct file;

struct kiocb;

struct iov_iter;

struct dir_context;

struct poll_table_struct;

struct vm_area_struct;

struct inode;

struct file_lock;

struct page;

struct pipe_inode_info;

struct seq_file;

struct file_operations {
	struct module *owner;
	loff_t (*llseek)(struct file *, loff_t, int);
	ssize_t (*read)(struct file *, char *, size_t, loff_t *);
	ssize_t (*write)(struct file *, const char *, size_t, loff_t *);
	ssize_t (*read_iter)(struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter)(struct kiocb *, struct iov_iter *);
	int (*iopoll)(struct kiocb *, bool);
	int (*iterate)(struct file *, struct dir_context *);
	int (*iterate_shared)(struct file *, struct dir_context *);
	__poll_t (*poll)(struct file *, struct poll_table_struct *);
	long int (*unlocked_ioctl)(struct file *, unsigned int, long unsigned int);
	long int (*compat_ioctl)(struct file *, unsigned int, long unsigned int);
	int (*mmap)(struct file *, struct vm_area_struct *);
	long unsigned int mmap_supported_flags;
	int (*open)(struct inode *, struct file *);
	int (*flush)(struct file *, fl_owner_t);
	int (*release)(struct inode *, struct file *);
	int (*fsync)(struct file *, loff_t, loff_t, int);
	int (*fasync)(int, struct file *, int);
	int (*lock)(struct file *, int, struct file_lock *);
	ssize_t (*sendpage)(struct file *, struct page *, int, size_t, loff_t *, int);
	long unsigned int (*get_unmapped_area)(struct file *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);
	int (*check_flags)(int);
	int (*flock)(struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long int, struct file_lock **, void **);
	long int (*fallocate)(struct file *, int, loff_t, loff_t);
	void (*show_fdinfo)(struct seq_file *, struct file *);
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *, loff_t, size_t, unsigned int);
	loff_t (*remap_file_range)(struct file *, loff_t, struct file *, loff_t, loff_t, unsigned int);
	int (*fadvise)(struct file *, loff_t, loff_t, int);
};

struct qspinlock {
	union {
		atomic_t val;
		struct {
			u8 locked;
			u8 pending;
		};
		struct {
			u16 locked_pending;
			u16 tail;
		};
	};
};

typedef struct qspinlock arch_spinlock_t;

struct raw_spinlock {
	arch_spinlock_t raw_lock;
};

struct spinlock {
	union {
		struct raw_spinlock rlock;
	};
};

typedef struct spinlock spinlock_t;

struct notifier_block;

struct atomic_notifier_head {
	spinlock_t lock;
	struct notifier_block *head;
};

enum system_states {
	SYSTEM_BOOTING = 0,
	SYSTEM_SCHEDULING = 1,
	SYSTEM_RUNNING = 2,
	SYSTEM_HALT = 3,
	SYSTEM_POWER_OFF = 4,
	SYSTEM_RESTART = 5,
	SYSTEM_SUSPEND = 6,
};

struct taint_flag {
	char c_true;
	char c_false;
	bool module;
};

struct jump_entry {
	s32 code;
	s32 target;
	long int key;
};

struct static_key_mod;

struct static_key {
	atomic_t enabled;
	union {
		long unsigned int type;
		struct jump_entry *entries;
		struct static_key_mod *next;
	};
};

struct static_key_true {
	struct static_key key;
};

struct static_key_false {
	struct static_key key;
};

typedef __s64 time64_t;

struct __kernel_timespec {
	__kernel_time64_t tv_sec;
	long long int tv_nsec;
};

struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

struct timespec64 {
	time64_t tv_sec;
	long int tv_nsec;
};

enum timespec_type {
	TT_NONE = 0,
	TT_NATIVE = 1,
	TT_COMPAT = 2,
};

typedef s32 old_time32_t;

struct old_timespec32 {
	old_time32_t tv_sec;
	s32 tv_nsec;
};

struct pollfd;

struct restart_block {
	long int (*fn)(struct restart_block *);
	union {
		struct {
			u32 *uaddr;
			u32 val;
			u32 flags;
			u32 bitset;
			u64 time;
			u32 *uaddr2;
		} futex;
		struct {
			clockid_t clockid;
			enum timespec_type type;
			union {
				struct __kernel_timespec *rmtp;
				struct old_timespec32 *compat_rmtp;
			};
			u64 expires;
		} nanosleep;
		struct {
			struct pollfd *ufds;
			int nfds;
			int has_timeout;
			long unsigned int tv_sec;
			long unsigned int tv_nsec;
		} poll;
	};
};

struct thread_info {
	long unsigned int flags;
	u32 status;
};

struct refcount_struct {
	atomic_t refs;
};

typedef struct refcount_struct refcount_t;

struct llist_node {
	struct llist_node *next;
};

struct __call_single_node {
	struct llist_node llist;
	union {
		unsigned int u_flags;
		atomic_t a_flags;
	};
};

struct load_weight {
	long unsigned int weight;
	u32 inv_weight;
};

struct rb_node {
	long unsigned int __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
};

struct sched_statistics {
	u64 wait_start;
	u64 wait_max;
	u64 wait_count;
	u64 wait_sum;
	u64 iowait_count;
	u64 iowait_sum;
	u64 sleep_start;
	u64 sleep_max;
	s64 sum_sleep_runtime;
	u64 block_start;
	u64 block_max;
	u64 exec_max;
	u64 slice_max;
	u64 nr_migrations_cold;
	u64 nr_failed_migrations_affine;
	u64 nr_failed_migrations_running;
	u64 nr_failed_migrations_hot;
	u64 nr_forced_migrations;
	u64 nr_wakeups;
	u64 nr_wakeups_sync;
	u64 nr_wakeups_migrate;
	u64 nr_wakeups_local;
	u64 nr_wakeups_remote;
	u64 nr_wakeups_affine;
	u64 nr_wakeups_affine_attempts;
	u64 nr_wakeups_passive;
	u64 nr_wakeups_idle;
};

struct util_est {
	unsigned int enqueued;
	unsigned int ewma;
};

struct sched_avg {
	u64 last_update_time;
	u64 load_sum;
	u64 runnable_sum;
	u32 util_sum;
	u32 period_contrib;
	long unsigned int load_avg;
	long unsigned int runnable_avg;
	long unsigned int util_avg;
	struct util_est util_est;
};

struct cfs_rq;

struct sched_entity {
	struct load_weight load;
	struct rb_node run_node;
	struct list_head group_node;
	unsigned int on_rq;
	u64 exec_start;
	u64 sum_exec_runtime;
	u64 vruntime;
	u64 prev_sum_exec_runtime;
	u64 nr_migrations;
	struct sched_statistics statistics;
	int depth;
	struct sched_entity *parent;
	struct cfs_rq *cfs_rq;
	struct cfs_rq *my_q;
	long unsigned int runnable_weight;
	long: 64;
	long: 64;
	long: 64;
	struct sched_avg avg;
};

struct sched_rt_entity {
	struct list_head run_list;
	long unsigned int timeout;
	long unsigned int watchdog_stamp;
	unsigned int time_slice;
	short unsigned int on_rq;
	short unsigned int on_list;
	struct sched_rt_entity *back;
};

typedef s64 ktime_t;

struct timerqueue_node {
	struct rb_node node;
	ktime_t expires;
};

enum hrtimer_restart {
	HRTIMER_NORESTART = 0,
	HRTIMER_RESTART = 1,
};

struct hrtimer_clock_base;

struct hrtimer {
	struct timerqueue_node node;
	ktime_t _softexpires;
	enum hrtimer_restart (*function)(struct hrtimer *);
	struct hrtimer_clock_base *base;
	u8 state;
	u8 is_rel;
	u8 is_soft;
	u8 is_hard;
};

struct sched_dl_entity {
	struct rb_node rb_node;
	u64 dl_runtime;
	u64 dl_deadline;
	u64 dl_period;
	u64 dl_bw;
	u64 dl_density;
	s64 runtime;
	u64 deadline;
	unsigned int flags;
	unsigned int dl_throttled: 1;
	unsigned int dl_boosted: 1;
	unsigned int dl_yielded: 1;
	unsigned int dl_non_contending: 1;
	unsigned int dl_overrun: 1;
	struct hrtimer dl_timer;
	struct hrtimer inactive_timer;
};

struct cpumask {
	long unsigned int bits[1];
};

typedef struct cpumask cpumask_t;

struct sched_info {
	long unsigned int pcount;
	long long unsigned int run_delay;
	long long unsigned int last_arrival;
	long long unsigned int last_queued;
};

struct plist_node {
	int prio;
	struct list_head prio_list;
	struct list_head node_list;
};

struct vmacache {
	u64 seqnum;
	struct vm_area_struct *vmas[4];
};

struct task_rss_stat {
	int events;
	int count[4];
};

typedef struct raw_spinlock raw_spinlock_t;

struct prev_cputime {
	u64 utime;
	u64 stime;
	raw_spinlock_t lock;
};

struct rb_root {
	struct rb_node *rb_node;
};

struct rb_root_cached {
	struct rb_root rb_root;
	struct rb_node *rb_leftmost;
};

struct timerqueue_head {
	struct rb_root_cached rb_root;
};

struct posix_cputimer_base {
	u64 nextevt;
	struct timerqueue_head tqhead;
};

struct posix_cputimers {
	struct posix_cputimer_base bases[3];
	unsigned int timers_active;
	unsigned int expiry_active;
};

struct sem_undo_list;

struct sysv_sem {
	struct sem_undo_list *undo_list;
};

struct sysv_shm {
	struct list_head shm_clist;
};

typedef struct {
	long unsigned int sig[1];
} sigset_t;

struct sigpending {
	struct list_head list;
	sigset_t signal;
};

typedef struct {
	uid_t val;
} kuid_t;

struct seccomp_filter;

struct seccomp {
	int mode;
	struct seccomp_filter *filter;
};

struct wake_q_node {
	struct wake_q_node *next;
};

struct task_io_accounting {
	u64 rchar;
	u64 wchar;
	u64 syscr;
	u64 syscw;
	u64 read_bytes;
	u64 write_bytes;
	u64 cancelled_write_bytes;
};

typedef struct {
	long unsigned int bits[1];
} nodemask_t;

struct seqcount {
	unsigned int sequence;
};

typedef struct seqcount seqcount_t;

typedef atomic64_t atomic_long_t;

struct optimistic_spin_queue {
	atomic_t tail;
};

struct mutex {
	atomic_long_t owner;
	spinlock_t wait_lock;
	struct optimistic_spin_queue osq;
	struct list_head wait_list;
};

struct arch_tlbflush_unmap_batch {
	struct cpumask cpumask;
};

struct tlbflush_unmap_batch {
	struct arch_tlbflush_unmap_batch arch;
	bool flush_required;
	bool writable;
};

struct page_frag {
	struct page *page;
	__u32 offset;
	__u32 size;
};

struct desc_struct {
	u16 limit0;
	u16 base0;
	u16 base1: 8;
	u16 type: 4;
	u16 s: 1;
	u16 dpl: 2;
	u16 p: 1;
	u16 limit1: 4;
	u16 avl: 1;
	u16 l: 1;
	u16 d: 1;
	u16 g: 1;
	u16 base2: 8;
};

typedef struct {
	long unsigned int seg;
} mm_segment_t;

struct fregs_state {
	u32 cwd;
	u32 swd;
	u32 twd;
	u32 fip;
	u32 fcs;
	u32 foo;
	u32 fos;
	u32 st_space[20];
	u32 status;
};

struct fxregs_state {
	u16 cwd;
	u16 swd;
	u16 twd;
	u16 fop;
	union {
		struct {
			u64 rip;
			u64 rdp;
		};
		struct {
			u32 fip;
			u32 fcs;
			u32 foo;
			u32 fos;
		};
	};
	u32 mxcsr;
	u32 mxcsr_mask;
	u32 st_space[32];
	u32 xmm_space[64];
	u32 padding[12];
	union {
		u32 padding1[12];
		u32 sw_reserved[12];
	};
};

struct math_emu_info;

struct swregs_state {
	u32 cwd;
	u32 swd;
	u32 twd;
	u32 fip;
	u32 fcs;
	u32 foo;
	u32 fos;
	u32 st_space[20];
	u8 ftop;
	u8 changed;
	u8 lookahead;
	u8 no_update;
	u8 rm;
	u8 alimit;
	struct math_emu_info *info;
	u32 entry_eip;
};

struct xstate_header {
	u64 xfeatures;
	u64 xcomp_bv;
	u64 reserved[6];
};

struct xregs_state {
	struct fxregs_state i387;
	struct xstate_header header;
	u8 extended_state_area[0];
};

union fpregs_state {
	struct fregs_state fsave;
	struct fxregs_state fxsave;
	struct swregs_state soft;
	struct xregs_state xsave;
	u8 __padding[4096];
};

struct fpu {
	unsigned int last_cpu;
	long unsigned int avx512_timestamp;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	union fpregs_state state;
};

struct perf_event;

struct io_bitmap;

struct thread_struct {
	struct desc_struct tls_array[3];
	long unsigned int sp;
	short unsigned int es;
	short unsigned int ds;
	short unsigned int fsindex;
	short unsigned int gsindex;
	long unsigned int fsbase;
	long unsigned int gsbase;
	struct perf_event *ptrace_bps[4];
	long unsigned int debugreg6;
	long unsigned int ptrace_dr7;
	long unsigned int cr2;
	long unsigned int trap_nr;
	long unsigned int error_code;
	struct io_bitmap *io_bitmap;
	long unsigned int iopl_emul;
	mm_segment_t addr_limit;
	unsigned int sig_on_uaccess_err: 1;
	long: 63;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct fpu fpu;
};

struct sched_class;

struct task_group;

struct mm_struct;

struct pid;

struct completion;

struct cred;

struct key;

struct nameidata;

struct fs_struct;

struct files_struct;

struct nsproxy;

struct signal_struct;

struct sighand_struct;

struct audit_context;

struct rt_mutex_waiter;

struct bio_list;

struct blk_plug;

struct reclaim_state;

struct backing_dev_info;

struct io_context;

struct capture_control;

struct kernel_siginfo;

typedef struct kernel_siginfo kernel_siginfo_t;

struct css_set;

struct robust_list_head;

struct compat_robust_list_head;

struct futex_pi_state;

struct perf_event_context;

struct mempolicy;

struct rseq;

struct task_delay_info;

struct uprobe_task;

struct vm_struct;

struct task_struct {
	struct thread_info thread_info;
	volatile long int state;
	void *stack;
	refcount_t usage;
	unsigned int flags;
	unsigned int ptrace;
	int on_cpu;
	struct __call_single_node wake_entry;
	unsigned int cpu;
	unsigned int wakee_flips;
	long unsigned int wakee_flip_decay_ts;
	struct task_struct *last_wakee;
	int recent_used_cpu;
	int wake_cpu;
	int on_rq;
	int prio;
	int static_prio;
	int normal_prio;
	unsigned int rt_priority;
	const struct sched_class *sched_class;
	struct sched_entity se;
	struct sched_rt_entity rt;
	struct task_group *sched_task_group;
	struct sched_dl_entity dl;
	unsigned int btrace_seq;
	unsigned int policy;
	int nr_cpus_allowed;
	const cpumask_t *cpus_ptr;
	cpumask_t cpus_mask;
	struct sched_info sched_info;
	struct list_head tasks;
	struct plist_node pushable_tasks;
	struct rb_node pushable_dl_tasks;
	struct mm_struct *mm;
	struct mm_struct *active_mm;
	struct vmacache vmacache;
	struct task_rss_stat rss_stat;
	int exit_state;
	int exit_code;
	int exit_signal;
	int pdeath_signal;
	long unsigned int jobctl;
	unsigned int personality;
	unsigned int sched_reset_on_fork: 1;
	unsigned int sched_contributes_to_load: 1;
	unsigned int sched_migrated: 1;
	unsigned int sched_remote_wakeup: 1;
	int: 28;
	unsigned int in_execve: 1;
	unsigned int in_iowait: 1;
	unsigned int restore_sigmask: 1;
	unsigned int no_cgroup_migration: 1;
	unsigned int frozen: 1;
	long unsigned int atomic_flags;
	struct restart_block restart_block;
	pid_t pid;
	pid_t tgid;
	long unsigned int stack_canary;
	struct task_struct *real_parent;
	struct task_struct *parent;
	struct list_head children;
	struct list_head sibling;
	struct task_struct *group_leader;
	struct list_head ptraced;
	struct list_head ptrace_entry;
	struct pid *thread_pid;
	struct hlist_node pid_links[4];
	struct list_head thread_group;
	struct list_head thread_node;
	struct completion *vfork_done;
	int *set_child_tid;
	int *clear_child_tid;
	u64 utime;
	u64 stime;
	u64 gtime;
	struct prev_cputime prev_cputime;
	long unsigned int nvcsw;
	long unsigned int nivcsw;
	u64 start_time;
	u64 start_boottime;
	long unsigned int min_flt;
	long unsigned int maj_flt;
	struct posix_cputimers posix_cputimers;
	const struct cred *ptracer_cred;
	const struct cred *real_cred;
	const struct cred *cred;
	struct key *cached_requested_key;
	char comm[16];
	struct nameidata *nameidata;
	struct sysv_sem sysvsem;
	struct sysv_shm sysvshm;
	struct fs_struct *fs;
	struct files_struct *files;
	struct nsproxy *nsproxy;
	struct signal_struct *signal;
	struct sighand_struct *sighand;
	sigset_t blocked;
	sigset_t real_blocked;
	sigset_t saved_sigmask;
	struct sigpending pending;
	long unsigned int sas_ss_sp;
	size_t sas_ss_size;
	unsigned int sas_ss_flags;
	struct callback_head *task_works;
	struct audit_context *audit_context;
	kuid_t loginuid;
	unsigned int sessionid;
	struct seccomp seccomp;
	u64 parent_exec_id;
	u64 self_exec_id;
	spinlock_t alloc_lock;
	raw_spinlock_t pi_lock;
	struct wake_q_node wake_q;
	struct rb_root_cached pi_waiters;
	struct task_struct *pi_top_task;
	struct rt_mutex_waiter *pi_blocked_on;
	void *journal_info;
	struct bio_list *bio_list;
	struct blk_plug *plug;
	struct reclaim_state *reclaim_state;
	struct backing_dev_info *backing_dev_info;
	struct io_context *io_context;
	struct capture_control *capture_control;
	long unsigned int ptrace_message;
	kernel_siginfo_t *last_siginfo;
	struct task_io_accounting ioac;
	u64 acct_rss_mem1;
	u64 acct_vm_mem1;
	u64 acct_timexpd;
	nodemask_t mems_allowed;
	seqcount_t mems_allowed_seq;
	int cpuset_mem_spread_rotor;
	int cpuset_slab_spread_rotor;
	struct css_set *cgroups;
	struct list_head cg_list;
	struct robust_list_head *robust_list;
	struct compat_robust_list_head *compat_robust_list;
	struct list_head pi_state_list;
	struct futex_pi_state *pi_state_cache;
	struct mutex futex_exit_mutex;
	unsigned int futex_state;
	struct perf_event_context *perf_event_ctxp[2];
	struct mutex perf_event_mutex;
	struct list_head perf_event_list;
	struct mempolicy *mempolicy;
	short int il_prev;
	short int pref_node_fork;
	struct rseq *rseq;
	u32 rseq_sig;
	long unsigned int rseq_event_mask;
	struct tlbflush_unmap_batch tlb_ubc;
	union {
		refcount_t rcu_users;
		struct callback_head rcu;
	};
	struct pipe_inode_info *splice_pipe;
	struct page_frag task_frag;
	struct task_delay_info *delays;
	int nr_dirtied;
	int nr_dirtied_pause;
	long unsigned int dirty_paused_when;
	u64 timer_slack_ns;
	u64 default_timer_slack_ns;
	long unsigned int trace;
	long unsigned int trace_recursion;
	struct uprobe_task *utask;
	int pagefault_disabled;
	struct task_struct *oom_reaper_list;
	struct vm_struct *stack_vm_area;
	refcount_t stack_refcount;
	void *security;
	u64 mce_addr;
	__u64 mce_ripv: 1;
	__u64 mce_whole_page: 1;
	__u64 __mce_reserved: 62;
	struct callback_head mce_kill_me;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct thread_struct thread;
};

struct screen_info {
	__u8 orig_x;
	__u8 orig_y;
	__u16 ext_mem_k;
	__u16 orig_video_page;
	__u8 orig_video_mode;
	__u8 orig_video_cols;
	__u8 flags;
	__u8 unused2;
	__u16 orig_video_ega_bx;
	__u16 unused3;
	__u8 orig_video_lines;
	__u8 orig_video_isVGA;
	__u16 orig_video_points;
	__u16 lfb_width;
	__u16 lfb_height;
	__u16 lfb_depth;
	__u32 lfb_base;
	__u32 lfb_size;
	__u16 cl_magic;
	__u16 cl_offset;
	__u16 lfb_linelength;
	__u8 red_size;
	__u8 red_pos;
	__u8 green_size;
	__u8 green_pos;
	__u8 blue_size;
	__u8 blue_pos;
	__u8 rsvd_size;
	__u8 rsvd_pos;
	__u16 vesapm_seg;
	__u16 vesapm_off;
	__u16 pages;
	__u16 vesa_attributes;
	__u32 capabilities;
	__u32 ext_lfb_base;
	__u8 _reserved[2];
} __attribute__((packed));

struct apm_bios_info {
	__u16 version;
	__u16 cseg;
	__u32 offset;
	__u16 cseg_16;
	__u16 dseg;
	__u16 flags;
	__u16 cseg_len;
	__u16 cseg_16_len;
	__u16 dseg_len;
};

struct apm_info {
	struct apm_bios_info bios;
	short unsigned int connection_version;
	int get_power_status_broken;
	int get_power_status_swabinminutes;
	int allow_ints;
	int forbid_idle;
	int realmode_power_off;
	int disabled;
};

struct edd_device_params {
	__u16 length;
	__u16 info_flags;
	__u32 num_default_cylinders;
	__u32 num_default_heads;
	__u32 sectors_per_track;
	__u64 number_of_sectors;
	__u16 bytes_per_sector;
	__u32 dpte_ptr;
	__u16 key;
	__u8 device_path_info_length;
	__u8 reserved2;
	__u16 reserved3;
	__u8 host_bus_type[4];
	__u8 interface_type[8];
	union {
		struct {
			__u16 base_address;
			__u16 reserved1;
			__u32 reserved2;
		} isa;
		struct {
			__u8 bus;
			__u8 slot;
			__u8 function;
			__u8 channel;
			__u32 reserved;
		} pci;
		struct {
			__u64 reserved;
		} ibnd;
		struct {
			__u64 reserved;
		} xprs;
		struct {
			__u64 reserved;
		} htpt;
		struct {
			__u64 reserved;
		} unknown;
	} interface_path;
	union {
		struct {
			__u8 device;
			__u8 reserved1;
			__u16 reserved2;
			__u32 reserved3;
			__u64 reserved4;
		} ata;
		struct {
			__u8 device;
			__u8 lun;
			__u8 reserved1;
			__u8 reserved2;
			__u32 reserved3;
			__u64 reserved4;
		} atapi;
		struct {
			__u16 id;
			__u64 lun;
			__u16 reserved1;
			__u32 reserved2;
		} __attribute__((packed)) scsi;
		struct {
			__u64 serial_number;
			__u64 reserved;
		} usb;
		struct {
			__u64 eui;
			__u64 reserved;
		} i1394;
		struct {
			__u64 wwid;
			__u64 lun;
		} fibre;
		struct {
			__u64 identity_tag;
			__u64 reserved;
		} i2o;
		struct {
			__u32 array_number;
			__u32 reserved1;
			__u64 reserved2;
		} raid;
		struct {
			__u8 device;
			__u8 reserved1;
			__u16 reserved2;
			__u32 reserved3;
			__u64 reserved4;
		} sata;
		struct {
			__u64 reserved1;
			__u64 reserved2;
		} unknown;
	} device_path;
	__u8 reserved4;
	__u8 checksum;
} __attribute__((packed));

struct edd_info {
	__u8 device;
	__u8 version;
	__u16 interface_support;
	__u16 legacy_max_cylinder;
	__u8 legacy_max_head;
	__u8 legacy_sectors_per_track;
	struct edd_device_params params;
} __attribute__((packed));

struct edd {
	unsigned int mbr_signature[16];
	struct edd_info edd_info[6];
	unsigned char mbr_signature_nr;
	unsigned char edd_info_nr;
};

struct ist_info {
	__u32 signature;
	__u32 command;
	__u32 event;
	__u32 perf_level;
};

struct edid_info {
	unsigned char dummy[128];
};

struct setup_header {
	__u8 setup_sects;
	__u16 root_flags;
	__u32 syssize;
	__u16 ram_size;
	__u16 vid_mode;
	__u16 root_dev;
	__u16 boot_flag;
	__u16 jump;
	__u32 header;
	__u16 version;
	__u32 realmode_swtch;
	__u16 start_sys_seg;
	__u16 kernel_version;
	__u8 type_of_loader;
	__u8 loadflags;
	__u16 setup_move_size;
	__u32 code32_start;
	__u32 ramdisk_image;
	__u32 ramdisk_size;
	__u32 bootsect_kludge;
	__u16 heap_end_ptr;
	__u8 ext_loader_ver;
	__u8 ext_loader_type;
	__u32 cmd_line_ptr;
	__u32 initrd_addr_max;
	__u32 kernel_alignment;
	__u8 relocatable_kernel;
	__u8 min_alignment;
	__u16 xloadflags;
	__u32 cmdline_size;
	__u32 hardware_subarch;
	__u64 hardware_subarch_data;
	__u32 payload_offset;
	__u32 payload_length;
	__u64 setup_data;
	__u64 pref_address;
	__u32 init_size;
	__u32 handover_offset;
	__u32 kernel_info_offset;
} __attribute__((packed));

struct sys_desc_table {
	__u16 length;
	__u8 table[14];
};

struct olpc_ofw_header {
	__u32 ofw_magic;
	__u32 ofw_version;
	__u32 cif_handler;
	__u32 irq_desc_table;
};

struct efi_info {
	__u32 efi_loader_signature;
	__u32 efi_systab;
	__u32 efi_memdesc_size;
	__u32 efi_memdesc_version;
	__u32 efi_memmap;
	__u32 efi_memmap_size;
	__u32 efi_systab_hi;
	__u32 efi_memmap_hi;
};

struct boot_e820_entry {
	__u64 addr;
	__u64 size;
	__u32 type;
} __attribute__((packed));

struct boot_params {
	struct screen_info screen_info;
	struct apm_bios_info apm_bios_info;
	__u8 _pad2[4];
	__u64 tboot_addr;
	struct ist_info ist_info;
	__u64 acpi_rsdp_addr;
	__u8 _pad3[8];
	__u8 hd0_info[16];
	__u8 hd1_info[16];
	struct sys_desc_table sys_desc_table;
	struct olpc_ofw_header olpc_ofw_header;
	__u32 ext_ramdisk_image;
	__u32 ext_ramdisk_size;
	__u32 ext_cmd_line_ptr;
	__u8 _pad4[116];
	struct edid_info edid_info;
	struct efi_info efi_info;
	__u32 alt_mem_k;
	__u32 scratch;
	__u8 e820_entries;
	__u8 eddbuf_entries;
	__u8 edd_mbr_sig_buf_entries;
	__u8 kbd_status;
	__u8 secure_boot;
	__u8 _pad5[2];
	__u8 sentinel;
	__u8 _pad6[1];
	struct setup_header hdr;
	__u8 _pad7[36];
	__u32 edd_mbr_sig_buffer[16];
	struct boot_e820_entry e820_table[128];
	__u8 _pad8[48];
	struct edd_info eddbuf[6];
	__u8 _pad9[276];
} __attribute__((packed));

enum x86_hardware_subarch {
	X86_SUBARCH_PC = 0,
	X86_SUBARCH_LGUEST = 1,
	X86_SUBARCH_XEN = 2,
	X86_SUBARCH_INTEL_MID = 3,
	X86_SUBARCH_CE4100 = 4,
	X86_NR_SUBARCHS = 5,
};

struct range {
	u64 start;
	u64 end;
};

struct pt_regs {
	long unsigned int r15;
	long unsigned int r14;
	long unsigned int r13;
	long unsigned int r12;
	long unsigned int bp;
	long unsigned int bx;
	long unsigned int r11;
	long unsigned int r10;
	long unsigned int r9;
	long unsigned int r8;
	long unsigned int ax;
	long unsigned int cx;
	long unsigned int dx;
	long unsigned int si;
	long unsigned int di;
	long unsigned int orig_ax;
	long unsigned int ip;
	long unsigned int cs;
	long unsigned int flags;
	long unsigned int sp;
	long unsigned int ss;
};

struct math_emu_info {
	long int ___orig_eip;
	struct pt_regs *regs;
};

typedef long unsigned int pteval_t;

typedef long unsigned int pmdval_t;

typedef long unsigned int pudval_t;

typedef long unsigned int p4dval_t;

typedef long unsigned int pgdval_t;

typedef long unsigned int pgprotval_t;

typedef struct {
	pteval_t pte;
} pte_t;

struct pgprot {
	pgprotval_t pgprot;
};

typedef struct pgprot pgprot_t;

typedef struct {
	pgdval_t pgd;
} pgd_t;

typedef struct {
	p4dval_t p4d;
} p4d_t;

typedef struct {
	pudval_t pud;
} pud_t;

typedef struct {
	pmdval_t pmd;
} pmd_t;

typedef struct page *pgtable_t;

struct address_space;

struct kmem_cache;

struct dev_pagemap;

struct page {
	long unsigned int flags;
	union {
		struct {
			struct list_head lru;
			struct address_space *mapping;
			long unsigned int index;
			long unsigned int private;
		};
		struct {
			dma_addr_t dma_addr;
		};
		struct {
			union {
				struct list_head slab_list;
				struct {
					struct page *next;
					int pages;
					int pobjects;
				};
			};
			struct kmem_cache *slab_cache;
			void *freelist;
			union {
				void *s_mem;
				long unsigned int counters;
				struct {
					unsigned int inuse: 16;
					unsigned int objects: 15;
					unsigned int frozen: 1;
				};
			};
		};
		struct {
			long unsigned int compound_head;
			unsigned char compound_dtor;
			unsigned char compound_order;
			atomic_t compound_mapcount;
		};
		struct {
			long unsigned int _compound_pad_1;
			atomic_t hpage_pinned_refcount;
			struct list_head deferred_list;
		};
		struct {
			long unsigned int _pt_pad_1;
			pgtable_t pmd_huge_pte;
			long unsigned int _pt_pad_2;
			union {
				struct mm_struct *pt_mm;
				atomic_t pt_frag_refcount;
			};
			spinlock_t ptl;
		};
		struct {
			struct dev_pagemap *pgmap;
			void *zone_device_data;
		};
		struct callback_head callback_head;
	};
	union {
		atomic_t _mapcount;
		unsigned int page_type;
		unsigned int active;
		int units;
	};
	atomic_t _refcount;
	long: 64;
};

typedef struct cpumask cpumask_var_t[1];

struct tracepoint_func {
	void *func;
	void *data;
	int prio;
};

struct tracepoint {
	const char *name;
	struct static_key key;
	int (*regfunc)();
	void (*unregfunc)();
	struct tracepoint_func *funcs;
};

struct desc_ptr {
	short unsigned int size;
	long unsigned int address;
} __attribute__((packed));

struct cpuinfo_x86 {
	__u8 x86;
	__u8 x86_vendor;
	__u8 x86_model;
	__u8 x86_stepping;
	int x86_tlbsize;
	__u32 vmx_capability[3];
	__u8 x86_virt_bits;
	__u8 x86_phys_bits;
	__u8 x86_coreid_bits;
	__u8 cu_id;
	__u32 extended_cpuid_level;
	int cpuid_level;
	union {
		__u32 x86_capability[20];
		long unsigned int x86_capability_alignment;
	};
	char x86_vendor_id[16];
	char x86_model_id[64];
	unsigned int x86_cache_size;
	int x86_cache_alignment;
	int x86_cache_max_rmid;
	int x86_cache_occ_scale;
	int x86_cache_mbm_width_offset;
	int x86_power;
	long unsigned int loops_per_jiffy;
	u16 x86_max_cores;
	u16 apicid;
	u16 initial_apicid;
	u16 x86_clflush_size;
	u16 booted_cores;
	u16 phys_proc_id;
	u16 logical_proc_id;
	u16 cpu_core_id;
	u16 cpu_die_id;
	u16 logical_die_id;
	u16 cpu_index;
	u32 microcode;
	u8 x86_cache_bits;
	unsigned int initialized: 1;
};

struct seq_operations {
	void * (*start)(struct seq_file *, loff_t *);
	void (*stop)(struct seq_file *, void *);
	void * (*next)(struct seq_file *, void *, loff_t *);
	int (*show)(struct seq_file *, void *);
};

struct x86_hw_tss {
	u32 reserved1;
	u64 sp0;
	u64 sp1;
	u64 sp2;
	u64 reserved2;
	u64 ist[7];
	u32 reserved3;
	u32 reserved4;
	u16 reserved5;
	u16 io_bitmap_base;
} __attribute__((packed));

struct entry_stack {
	char stack[4096];
};

struct entry_stack_page {
	struct entry_stack stack;
};

struct x86_io_bitmap {
	u64 prev_sequence;
	unsigned int prev_max;
	long unsigned int bitmap[1025];
	long unsigned int mapall[1025];
};

struct tss_struct {
	struct x86_hw_tss x86_tss;
	struct x86_io_bitmap io_bitmap;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct irq_stack {
	char stack[16384];
};

struct fixed_percpu_data {
	char gs_base[40];
	long unsigned int stack_canary;
};

enum l1tf_mitigations {
	L1TF_MITIGATION_OFF = 0,
	L1TF_MITIGATION_FLUSH_NOWARN = 1,
	L1TF_MITIGATION_FLUSH = 2,
	L1TF_MITIGATION_FLUSH_NOSMT = 3,
	L1TF_MITIGATION_FULL = 4,
	L1TF_MITIGATION_FULL_FORCE = 5,
};

struct mpc_table {
	char signature[4];
	short unsigned int length;
	char spec;
	char checksum;
	char oem[8];
	char productid[12];
	unsigned int oemptr;
	short unsigned int oemsize;
	short unsigned int oemcount;
	unsigned int lapic;
	unsigned int reserved;
};

struct mpc_cpu {
	unsigned char type;
	unsigned char apicid;
	unsigned char apicver;
	unsigned char cpuflag;
	unsigned int cpufeature;
	unsigned int featureflag;
	unsigned int reserved[2];
};

struct mpc_bus {
	unsigned char type;
	unsigned char busid;
	unsigned char bustype[6];
};

struct mpc_intsrc {
	unsigned char type;
	unsigned char irqtype;
	short unsigned int irqflag;
	unsigned char srcbus;
	unsigned char srcbusirq;
	unsigned char dstapic;
	unsigned char dstirq;
};

struct x86_init_mpparse {
	void (*mpc_record)(unsigned int);
	void (*setup_ioapic_ids)();
	int (*mpc_apic_id)(struct mpc_cpu *);
	void (*smp_read_mpc_oem)(struct mpc_table *);
	void (*mpc_oem_pci_bus)(struct mpc_bus *);
	void (*mpc_oem_bus_info)(struct mpc_bus *, char *);
	void (*find_smp_config)();
	void (*get_smp_config)(unsigned int);
};

struct x86_init_resources {
	void (*probe_roms)();
	void (*reserve_resources)();
	char * (*memory_setup)();
};

struct x86_init_irqs {
	void (*pre_vector_init)();
	void (*intr_init)();
	void (*intr_mode_select)();
	void (*intr_mode_init)();
};

struct x86_init_oem {
	void (*arch_setup)();
	void (*banner)();
};

struct x86_init_paging {
	void (*pagetable_init)();
};

struct x86_init_timers {
	void (*setup_percpu_clockev)();
	void (*timer_init)();
	void (*wallclock_init)();
};

struct x86_init_iommu {
	int (*iommu_init)();
};

struct x86_init_pci {
	int (*arch_init)();
	int (*init)();
	void (*init_irq)();
	void (*fixup_irqs)();
};

struct x86_hyper_init {
	void (*init_platform)();
	void (*guest_late_init)();
	bool (*x2apic_available)();
	void (*init_mem_mapping)();
	void (*init_after_bootmem)();
};

struct x86_init_acpi {
	void (*set_root_pointer)(u64);
	u64 (*get_root_pointer)();
	void (*reduced_hw_early_init)();
};

struct x86_init_ops {
	struct x86_init_resources resources;
	struct x86_init_mpparse mpparse;
	struct x86_init_irqs irqs;
	struct x86_init_oem oem;
	struct x86_init_paging paging;
	struct x86_init_timers timers;
	struct x86_init_iommu iommu;
	struct x86_init_pci pci;
	struct x86_hyper_init hyper;
	struct x86_init_acpi acpi;
};

struct x86_cpuinit_ops {
	void (*setup_percpu_clockev)();
	void (*early_percpu_clock_init)();
	void (*fixup_cpu_id)(struct cpuinfo_x86 *, int);
};

struct x86_legacy_devices {
	int pnpbios;
};

enum x86_legacy_i8042_state {
	X86_LEGACY_I8042_PLATFORM_ABSENT = 0,
	X86_LEGACY_I8042_FIRMWARE_ABSENT = 1,
	X86_LEGACY_I8042_EXPECTED_PRESENT = 2,
};

struct x86_legacy_features {
	enum x86_legacy_i8042_state i8042;
	int rtc;
	int warm_reset;
	int no_vga;
	int reserve_bios_regions;
	struct x86_legacy_devices devices;
};

struct x86_hyper_runtime {
	void (*pin_vcpu)(int);
};

struct x86_platform_ops {
	long unsigned int (*calibrate_cpu)();
	long unsigned int (*calibrate_tsc)();
	void (*get_wallclock)(struct timespec64 *);
	int (*set_wallclock)(const struct timespec64 *);
	void (*iommu_shutdown)();
	bool (*is_untracked_pat_range)(u64, u64);
	void (*nmi_init)();
	unsigned char (*get_nmi_reason)();
	void (*save_sched_clock_state)();
	void (*restore_sched_clock_state)();
	void (*apic_post_init)();
	struct x86_legacy_features legacy;
	void (*set_legacy_features)();
	struct x86_hyper_runtime hyper;
};

struct pci_dev;

struct x86_msi_ops {
	int (*setup_msi_irqs)(struct pci_dev *, int, int);
	void (*teardown_msi_irq)(unsigned int);
	void (*teardown_msi_irqs)(struct pci_dev *);
	void (*restore_msi_irqs)(struct pci_dev *);
};

struct x86_apic_ops {
	unsigned int (*io_apic_read)(unsigned int, unsigned int);
	void (*restore)();
};

struct physid_mask {
	long unsigned int mask[512];
};

typedef struct physid_mask physid_mask_t;

struct qrwlock {
	union {
		atomic_t cnts;
		struct {
			u8 wlocked;
			u8 __lstate[3];
		};
	};
	arch_spinlock_t wait_lock;
};

typedef struct qrwlock arch_rwlock_t;

typedef struct {
	arch_rwlock_t raw_lock;
} rwlock_t;

struct rw_semaphore {
	atomic_long_t count;
	atomic_long_t owner;
	struct optimistic_spin_queue osq;
	raw_spinlock_t wait_lock;
	struct list_head wait_list;
};

struct vdso_image {
	void *data;
	long unsigned int size;
	long unsigned int alt;
	long unsigned int alt_len;
	long int sym_vvar_start;
	long int sym_vvar_page;
	long int sym_pvclock_page;
	long int sym_hvclock_page;
	long int sym_timens_page;
	long int sym_VDSO32_NOTE_MASK;
	long int sym___kernel_sigreturn;
	long int sym___kernel_rt_sigreturn;
	long int sym___kernel_vsyscall;
	long int sym_int80_landing_pad;
};

struct ldt_struct;

typedef struct {
	u64 ctx_id;
	atomic64_t tlb_gen;
	struct rw_semaphore ldt_usr_sem;
	struct ldt_struct *ldt;
	short unsigned int ia32_compat;
	struct mutex lock;
	void *vdso;
	const struct vdso_image *vdso_image;
	atomic_t perf_rdpmc_allowed;
	u16 pkey_allocation_map;
	s16 execute_only_pkey;
} mm_context_t;

struct kref {
	refcount_t refcount;
};

struct kset;

struct kobj_type;

struct kernfs_node;

struct kobject {
	const char *name;
	struct list_head entry;
	struct kobject *parent;
	struct kset *kset;
	struct kobj_type *ktype;
	struct kernfs_node *sd;
	struct kref kref;
	unsigned int state_initialized: 1;
	unsigned int state_in_sysfs: 1;
	unsigned int state_add_uevent_sent: 1;
	unsigned int state_remove_uevent_sent: 1;
	unsigned int uevent_suppress: 1;
};

enum dl_dev_state {
	DL_DEV_NO_DRIVER = 0,
	DL_DEV_PROBING = 1,
	DL_DEV_DRIVER_BOUND = 2,
	DL_DEV_UNBINDING = 3,
};

struct dev_links_info {
	struct list_head suppliers;
	struct list_head consumers;
	struct list_head needs_suppliers;
	struct list_head defer_hook;
	bool need_for_probe;
	enum dl_dev_state status;
};

struct pm_message {
	int event;
};

typedef struct pm_message pm_message_t;

struct swait_queue_head {
	raw_spinlock_t lock;
	struct list_head task_list;
};

struct completion {
	unsigned int done;
	struct swait_queue_head wait;
};

struct work_struct;

typedef void (*work_func_t)(struct work_struct *);

struct work_struct {
	atomic_long_t data;
	struct list_head entry;
	work_func_t func;
};

struct wait_queue_head {
	spinlock_t lock;
	struct list_head head;
};

typedef struct wait_queue_head wait_queue_head_t;

enum rpm_request {
	RPM_REQ_NONE = 0,
	RPM_REQ_IDLE = 1,
	RPM_REQ_SUSPEND = 2,
	RPM_REQ_AUTOSUSPEND = 3,
	RPM_REQ_RESUME = 4,
};

enum rpm_status {
	RPM_ACTIVE = 0,
	RPM_RESUMING = 1,
	RPM_SUSPENDED = 2,
	RPM_SUSPENDING = 3,
};

struct wakeup_source;

struct wake_irq;

struct pm_subsys_data;

struct device;

struct dev_pm_qos;

struct dev_pm_info {
	pm_message_t power_state;
	unsigned int can_wakeup: 1;
	unsigned int async_suspend: 1;
	bool in_dpm_list: 1;
	bool is_prepared: 1;
	bool is_suspended: 1;
	bool is_noirq_suspended: 1;
	bool is_late_suspended: 1;
	bool no_pm: 1;
	bool early_init: 1;
	bool direct_complete: 1;
	u32 driver_flags;
	spinlock_t lock;
	struct list_head entry;
	struct completion completion;
	struct wakeup_source *wakeup;
	bool wakeup_path: 1;
	bool syscore: 1;
	bool no_pm_callbacks: 1;
	unsigned int must_resume: 1;
	unsigned int may_skip_resume: 1;
	struct hrtimer suspend_timer;
	long unsigned int timer_expires;
	struct work_struct work;
	wait_queue_head_t wait_queue;
	struct wake_irq *wakeirq;
	atomic_t usage_count;
	atomic_t child_count;
	unsigned int disable_depth: 3;
	unsigned int idle_notification: 1;
	unsigned int request_pending: 1;
	unsigned int deferred_resume: 1;
	unsigned int runtime_auto: 1;
	bool ignore_children: 1;
	unsigned int no_callbacks: 1;
	unsigned int irq_safe: 1;
	unsigned int use_autosuspend: 1;
	unsigned int timer_autosuspends: 1;
	unsigned int memalloc_noio: 1;
	unsigned int links_count;
	enum rpm_request request;
	enum rpm_status runtime_status;
	int runtime_error;
	int autosuspend_delay;
	u64 last_busy;
	u64 active_time;
	u64 suspended_time;
	u64 accounting_timestamp;
	struct pm_subsys_data *subsys_data;
	void (*set_latency_tolerance)(struct device *, s32);
	struct dev_pm_qos *qos;
};

struct dev_archdata {
	void *iommu;
};

struct device_private;

struct device_type;

struct bus_type;

struct device_driver;

struct dev_pm_domain;

struct irq_domain;

struct dma_map_ops;

struct device_dma_parameters;

struct device_node;

struct fwnode_handle;

struct class;

struct attribute_group;

struct iommu_group;

struct dev_iommu;

struct device {
	struct kobject kobj;
	struct device *parent;
	struct device_private *p;
	const char *init_name;
	const struct device_type *type;
	struct bus_type *bus;
	struct device_driver *driver;
	void *platform_data;
	void *driver_data;
	struct mutex mutex;
	struct dev_links_info links;
	struct dev_pm_info power;
	struct dev_pm_domain *pm_domain;
	struct irq_domain *msi_domain;
	struct list_head msi_list;
	const struct dma_map_ops *dma_ops;
	u64 *dma_mask;
	u64 coherent_dma_mask;
	u64 bus_dma_limit;
	long unsigned int dma_pfn_offset;
	struct device_dma_parameters *dma_parms;
	struct list_head dma_pools;
	struct dev_archdata archdata;
	struct device_node *of_node;
	struct fwnode_handle *fwnode;
	int numa_node;
	dev_t devt;
	u32 id;
	spinlock_t devres_lock;
	struct list_head devres_head;
	struct class *class;
	const struct attribute_group **groups;
	void (*release)(struct device *);
	struct iommu_group *iommu_group;
	struct dev_iommu *iommu;
	bool offline_disabled: 1;
	bool offline: 1;
	bool of_node_reused: 1;
	bool state_synced: 1;
};

enum fixed_addresses {
	VSYSCALL_PAGE = 511,
	FIX_DBGP_BASE = 512,
	FIX_EARLYCON_MEM_BASE = 513,
	FIX_OHCI1394_BASE = 514,
	FIX_APIC_BASE = 515,
	FIX_IO_APIC_BASE_0 = 516,
	FIX_IO_APIC_BASE_END = 643,
	__end_of_permanent_fixed_addresses = 644,
	FIX_BTMAP_END = 1024,
	FIX_BTMAP_BEGIN = 1535,
	__end_of_fixed_addresses = 1536,
};

struct vm_userfaultfd_ctx {};

struct anon_vma;

struct vm_operations_struct;

struct vm_area_struct {
	long unsigned int vm_start;
	long unsigned int vm_end;
	struct vm_area_struct *vm_next;
	struct vm_area_struct *vm_prev;
	struct rb_node vm_rb;
	long unsigned int rb_subtree_gap;
	struct mm_struct *vm_mm;
	pgprot_t vm_page_prot;
	long unsigned int vm_flags;
	struct {
		struct rb_node rb;
		long unsigned int rb_subtree_last;
	} shared;
	struct list_head anon_vma_chain;
	struct anon_vma *anon_vma;
	const struct vm_operations_struct *vm_ops;
	long unsigned int vm_pgoff;
	struct file *vm_file;
	void *vm_private_data;
	atomic_long_t swap_readahead_info;
	struct mempolicy *vm_policy;
	struct vm_userfaultfd_ctx vm_userfaultfd_ctx;
};

struct mm_rss_stat {
	atomic_long_t count[4];
};

struct xol_area;

struct uprobes_state {
	struct xol_area *xol_area;
};

struct linux_binfmt;

struct core_state;

struct kioctx_table;

struct user_namespace;

struct mmu_notifier_subscriptions;

struct mm_struct {
	struct {
		struct vm_area_struct *mmap;
		struct rb_root mm_rb;
		u64 vmacache_seqnum;
		long unsigned int (*get_unmapped_area)(struct file *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);
		long unsigned int mmap_base;
		long unsigned int mmap_legacy_base;
		long unsigned int mmap_compat_base;
		long unsigned int mmap_compat_legacy_base;
		long unsigned int task_size;
		long unsigned int highest_vm_end;
		pgd_t *pgd;
		atomic_t membarrier_state;
		atomic_t mm_users;
		atomic_t mm_count;
		atomic_long_t pgtables_bytes;
		int map_count;
		spinlock_t page_table_lock;
		struct rw_semaphore mmap_lock;
		struct list_head mmlist;
		long unsigned int hiwater_rss;
		long unsigned int hiwater_vm;
		long unsigned int total_vm;
		long unsigned int locked_vm;
		atomic64_t pinned_vm;
		long unsigned int data_vm;
		long unsigned int exec_vm;
		long unsigned int stack_vm;
		long unsigned int def_flags;
		spinlock_t arg_lock;
		long unsigned int start_code;
		long unsigned int end_code;
		long unsigned int start_data;
		long unsigned int end_data;
		long unsigned int start_brk;
		long unsigned int brk;
		long unsigned int start_stack;
		long unsigned int arg_start;
		long unsigned int arg_end;
		long unsigned int env_start;
		long unsigned int env_end;
		long unsigned int saved_auxv[46];
		struct mm_rss_stat rss_stat;
		struct linux_binfmt *binfmt;
		mm_context_t context;
		long unsigned int flags;
		struct core_state *core_state;
		spinlock_t ioctx_lock;
		struct kioctx_table *ioctx_table;
		struct user_namespace *user_ns;
		struct file *exe_file;
		struct mmu_notifier_subscriptions *notifier_subscriptions;
		atomic_t tlb_flush_pending;
		bool tlb_flush_batched;
		struct uprobes_state uprobes_state;
		atomic_long_t hugetlb_usage;
		struct work_struct async_put_work;
	};
	long unsigned int cpu_bitmap[0];
};

typedef struct {
	struct seqcount seqcount;
	spinlock_t lock;
} seqlock_t;

struct timer_list {
	struct hlist_node entry;
	long unsigned int expires;
	void (*function)(struct timer_list *);
	u32 flags;
};

typedef int (*notifier_fn_t)(struct notifier_block *, long unsigned int, void *);

struct notifier_block {
	notifier_fn_t notifier_call;
	struct notifier_block *next;
	int priority;
};

struct blocking_notifier_head {
	struct rw_semaphore rwsem;
	struct notifier_block *head;
};

struct arch_uprobe_task {
	long unsigned int saved_scratch_register;
	unsigned int saved_trap_nr;
	unsigned int saved_tf;
};

enum uprobe_task_state {
	UTASK_RUNNING = 0,
	UTASK_SSTEP = 1,
	UTASK_SSTEP_ACK = 2,
	UTASK_SSTEP_TRAPPED = 3,
};

struct uprobe;

struct return_instance;

struct uprobe_task {
	enum uprobe_task_state state;
	union {
		struct {
			struct arch_uprobe_task autask;
			long unsigned int vaddr;
		};
		struct {
			struct callback_head dup_xol_work;
			long unsigned int dup_xol_addr;
		};
	};
	struct uprobe *active_uprobe;
	long unsigned int xol_vaddr;
	struct return_instance *return_instances;
	unsigned int depth;
};

struct return_instance {
	struct uprobe *uprobe;
	long unsigned int func;
	long unsigned int stack;
	long unsigned int orig_ret_vaddr;
	bool chained;
	struct return_instance *next;
};

struct xarray {
	spinlock_t xa_lock;
	gfp_t xa_flags;
	void *xa_head;
};

typedef u32 errseq_t;

struct address_space_operations;

struct address_space {
	struct inode *host;
	struct xarray i_pages;
	gfp_t gfp_mask;
	atomic_t i_mmap_writable;
	struct rb_root_cached i_mmap;
	struct rw_semaphore i_mmap_rwsem;
	long unsigned int nrpages;
	long unsigned int nrexceptional;
	long unsigned int writeback_index;
	const struct address_space_operations *a_ops;
	long unsigned int flags;
	errseq_t wb_err;
	spinlock_t private_lock;
	struct list_head private_list;
	void *private_data;
};

struct vmem_altmap {
	const long unsigned int base_pfn;
	const long unsigned int end_pfn;
	const long unsigned int reserve;
	long unsigned int free;
	long unsigned int align;
	long unsigned int alloc;
};

struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	long unsigned int flags;
	long unsigned int desc;
	struct resource *parent;
	struct resource *sibling;
	struct resource *child;
};

struct percpu_ref;

typedef void percpu_ref_func_t(struct percpu_ref *);

struct percpu_ref {
	atomic_long_t count;
	long unsigned int percpu_count_ptr;
	percpu_ref_func_t *release;
	percpu_ref_func_t *confirm_switch;
	bool force_atomic: 1;
	bool allow_reinit: 1;
	struct callback_head rcu;
};

enum memory_type {
	MEMORY_DEVICE_PRIVATE = 1,
	MEMORY_DEVICE_FS_DAX = 2,
	MEMORY_DEVICE_DEVDAX = 3,
	MEMORY_DEVICE_PCI_P2PDMA = 4,
};

struct dev_pagemap_ops;

struct dev_pagemap {
	struct vmem_altmap altmap;
	struct resource res;
	struct percpu_ref *ref;
	struct percpu_ref internal_ref;
	struct completion done;
	enum memory_type type;
	unsigned int flags;
	const struct dev_pagemap_ops *ops;
	void *owner;
};

struct vfsmount;

struct path {
	struct vfsmount *mnt;
	struct dentry *dentry;
};

enum rw_hint {
	WRITE_LIFE_NOT_SET = 0,
	WRITE_LIFE_NONE = 1,
	WRITE_LIFE_SHORT = 2,
	WRITE_LIFE_MEDIUM = 3,
	WRITE_LIFE_LONG = 4,
	WRITE_LIFE_EXTREME = 5,
};

enum pid_type {
	PIDTYPE_PID = 0,
	PIDTYPE_TGID = 1,
	PIDTYPE_PGID = 2,
	PIDTYPE_SID = 3,
	PIDTYPE_MAX = 4,
};

struct fown_struct {
	rwlock_t lock;
	struct pid *pid;
	enum pid_type pid_type;
	kuid_t uid;
	kuid_t euid;
	int signum;
};

struct file_ra_state {
	long unsigned int start;
	unsigned int size;
	unsigned int async_size;
	unsigned int ra_pages;
	unsigned int mmap_miss;
	loff_t prev_pos;
};

struct file {
	union {
		struct llist_node fu_llist;
		struct callback_head fu_rcuhead;
	} f_u;
	struct path f_path;
	struct inode *f_inode;
	const struct file_operations *f_op;
	spinlock_t f_lock;
	enum rw_hint f_write_hint;
	atomic_long_t f_count;
	unsigned int f_flags;
	fmode_t f_mode;
	struct mutex f_pos_lock;
	loff_t f_pos;
	struct fown_struct f_owner;
	const struct cred *f_cred;
	struct file_ra_state f_ra;
	u64 f_version;
	void *f_security;
	void *private_data;
	struct list_head f_ep_links;
	struct list_head f_tfile_llink;
	struct address_space *f_mapping;
	errseq_t f_wb_err;
	errseq_t f_sb_err;
};

typedef unsigned int vm_fault_t;

enum page_entry_size {
	PE_SIZE_PTE = 0,
	PE_SIZE_PMD = 1,
	PE_SIZE_PUD = 2,
};

struct vm_fault;

struct vm_operations_struct {
	void (*open)(struct vm_area_struct *);
	void (*close)(struct vm_area_struct *);
	int (*split)(struct vm_area_struct *, long unsigned int);
	int (*mremap)(struct vm_area_struct *);
	vm_fault_t (*fault)(struct vm_fault *);
	vm_fault_t (*huge_fault)(struct vm_fault *, enum page_entry_size);
	void (*map_pages)(struct vm_fault *, long unsigned int, long unsigned int);
	long unsigned int (*pagesize)(struct vm_area_struct *);
	vm_fault_t (*page_mkwrite)(struct vm_fault *);
	vm_fault_t (*pfn_mkwrite)(struct vm_fault *);
	int (*access)(struct vm_area_struct *, long unsigned int, void *, int, int);
	const char * (*name)(struct vm_area_struct *);
	int (*set_policy)(struct vm_area_struct *, struct mempolicy *);
	struct mempolicy * (*get_policy)(struct vm_area_struct *, long unsigned int);
	struct page * (*find_special_page)(struct vm_area_struct *, long unsigned int);
};

struct core_thread {
	struct task_struct *task;
	struct core_thread *next;
};

struct core_state {
	atomic_t nr_threads;
	struct core_thread dumper;
	struct completion startup;
};

struct vm_fault {
	struct vm_area_struct *vma;
	unsigned int flags;
	gfp_t gfp_mask;
	long unsigned int pgoff;
	long unsigned int address;
	pmd_t *pmd;
	pud_t *pud;
	pte_t orig_pte;
	struct page *cow_page;
	struct page *page;
	pte_t *pte;
	spinlock_t *ptl;
	pgtable_t prealloc_pte;
};

typedef struct {
	u16 __softirq_pending;
	unsigned int __nmi_count;
	unsigned int apic_timer_irqs;
	unsigned int irq_spurious_count;
	unsigned int icr_read_retry_count;
	unsigned int kvm_posted_intr_ipis;
	unsigned int kvm_posted_intr_wakeup_ipis;
	unsigned int kvm_posted_intr_nested_ipis;
	unsigned int x86_platform_ipis;
	unsigned int apic_perf_irqs;
	unsigned int apic_irq_work_irqs;
	unsigned int irq_resched_count;
	unsigned int irq_call_count;
	unsigned int irq_tlb_count;
	unsigned int irq_thermal_count;
	unsigned int irq_threshold_count;
	unsigned int irq_deferred_error_count;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
} irq_cpustat_t;

enum apic_intr_mode_id {
	APIC_PIC = 0,
	APIC_VIRTUAL_WIRE = 1,
	APIC_VIRTUAL_WIRE_NO_CONFIG = 2,
	APIC_SYMMETRIC_IO = 3,
	APIC_SYMMETRIC_IO_NO_ROUTING = 4,
};

struct apic {
	void (*eoi_write)(u32, u32);
	void (*native_eoi_write)(u32, u32);
	void (*write)(u32, u32);
	u32 (*read)(u32);
	void (*wait_icr_idle)();
	u32 (*safe_wait_icr_idle)();
	void (*send_IPI)(int, int);
	void (*send_IPI_mask)(const struct cpumask *, int);
	void (*send_IPI_mask_allbutself)(const struct cpumask *, int);
	void (*send_IPI_allbutself)(int);
	void (*send_IPI_all)(int);
	void (*send_IPI_self)(int);
	u32 dest_logical;
	u32 disable_esr;
	u32 irq_delivery_mode;
	u32 irq_dest_mode;
	u32 (*calc_dest_apicid)(unsigned int);
	u64 (*icr_read)();
	void (*icr_write)(u32, u32);
	int (*probe)();
	int (*acpi_madt_oem_check)(char *, char *);
	int (*apic_id_valid)(u32);
	int (*apic_id_registered)();
	bool (*check_apicid_used)(physid_mask_t *, int);
	void (*init_apic_ldr)();
	void (*ioapic_phys_id_map)(physid_mask_t *, physid_mask_t *);
	void (*setup_apic_routing)();
	int (*cpu_present_to_apicid)(int);
	void (*apicid_to_cpu_present)(int, physid_mask_t *);
	int (*check_phys_apicid_present)(int);
	int (*phys_pkg_id)(int, int);
	u32 (*get_apic_id)(long unsigned int);
	u32 (*set_apic_id)(unsigned int);
	int (*wakeup_secondary_cpu)(int, long unsigned int);
	void (*inquire_remote_apic)(int);
	char *name;
};

struct smp_ops {
	void (*smp_prepare_boot_cpu)();
	void (*smp_prepare_cpus)(unsigned int);
	void (*smp_cpus_done)(unsigned int);
	void (*stop_other_cpus)(int);
	void (*crash_stop_other_cpus)();
	void (*smp_send_reschedule)(int);
	int (*cpu_up)(unsigned int, struct task_struct *);
	int (*cpu_disable)();
	void (*cpu_die)(unsigned int);
	void (*play_dead)();
	void (*send_call_func_ipi)(const struct cpumask *);
	void (*send_call_func_single_ipi)(int);
};

enum pcpu_fc {
	PCPU_FC_AUTO = 0,
	PCPU_FC_EMBED = 1,
	PCPU_FC_PAGE = 2,
	PCPU_FC_NR = 3,
};

struct fwnode_operations;

struct fwnode_handle {
	struct fwnode_handle *secondary;
	const struct fwnode_operations *ops;
	struct device *dev;
};

struct fwnode_reference_args;

struct fwnode_endpoint;

struct fwnode_operations {
	struct fwnode_handle * (*get)(struct fwnode_handle *);
	void (*put)(struct fwnode_handle *);
	bool (*device_is_available)(const struct fwnode_handle *);
	const void * (*device_get_match_data)(const struct fwnode_handle *, const struct device *);
	bool (*property_present)(const struct fwnode_handle *, const char *);
	int (*property_read_int_array)(const struct fwnode_handle *, const char *, unsigned int, void *, size_t);
	int (*property_read_string_array)(const struct fwnode_handle *, const char *, const char **, size_t);
	const char * (*get_name)(const struct fwnode_handle *);
	const char * (*get_name_prefix)(const struct fwnode_handle *);
	struct fwnode_handle * (*get_parent)(const struct fwnode_handle *);
	struct fwnode_handle * (*get_next_child_node)(const struct fwnode_handle *, struct fwnode_handle *);
	struct fwnode_handle * (*get_named_child_node)(const struct fwnode_handle *, const char *);
	int (*get_reference_args)(const struct fwnode_handle *, const char *, const char *, unsigned int, unsigned int, struct fwnode_reference_args *);
	struct fwnode_handle * (*graph_get_next_endpoint)(const struct fwnode_handle *, struct fwnode_handle *);
	struct fwnode_handle * (*graph_get_remote_endpoint)(const struct fwnode_handle *);
	struct fwnode_handle * (*graph_get_port_parent)(struct fwnode_handle *);
	int (*graph_parse_endpoint)(const struct fwnode_handle *, struct fwnode_endpoint *);
	int (*add_links)(const struct fwnode_handle *, struct device *);
};

struct fwnode_endpoint {
	unsigned int port;
	unsigned int id;
	const struct fwnode_handle *local_fwnode;
};

struct fwnode_reference_args {
	struct fwnode_handle *fwnode;
	unsigned int nargs;
	u64 args[8];
};

struct vm_struct {
	struct vm_struct *next;
	void *addr;
	long unsigned int size;
	long unsigned int flags;
	struct page **pages;
	unsigned int nr_pages;
	phys_addr_t phys_addr;
	const void *caller;
};

struct free_area {
	struct list_head free_list[4];
	long unsigned int nr_free;
};

struct zone_padding {
	char x[0];
};

enum numa_stat_item {
	NUMA_HIT = 0,
	NUMA_MISS = 1,
	NUMA_FOREIGN = 2,
	NUMA_INTERLEAVE_HIT = 3,
	NUMA_LOCAL = 4,
	NUMA_OTHER = 5,
	NR_VM_NUMA_STAT_ITEMS = 6,
};

enum zone_stat_item {
	NR_FREE_PAGES = 0,
	NR_ZONE_LRU_BASE = 1,
	NR_ZONE_INACTIVE_ANON = 1,
	NR_ZONE_ACTIVE_ANON = 2,
	NR_ZONE_INACTIVE_FILE = 3,
	NR_ZONE_ACTIVE_FILE = 4,
	NR_ZONE_UNEVICTABLE = 5,
	NR_ZONE_WRITE_PENDING = 6,
	NR_MLOCK = 7,
	NR_PAGETABLE = 8,
	NR_KERNEL_STACK_KB = 9,
	NR_BOUNCE = 10,
	NR_FREE_CMA_PAGES = 11,
	NR_VM_ZONE_STAT_ITEMS = 12,
};

enum node_stat_item {
	NR_LRU_BASE = 0,
	NR_INACTIVE_ANON = 0,
	NR_ACTIVE_ANON = 1,
	NR_INACTIVE_FILE = 2,
	NR_ACTIVE_FILE = 3,
	NR_UNEVICTABLE = 4,
	NR_SLAB_RECLAIMABLE = 5,
	NR_SLAB_UNRECLAIMABLE = 6,
	NR_ISOLATED_ANON = 7,
	NR_ISOLATED_FILE = 8,
	WORKINGSET_NODES = 9,
	WORKINGSET_REFAULT = 10,
	WORKINGSET_ACTIVATE = 11,
	WORKINGSET_RESTORE = 12,
	WORKINGSET_NODERECLAIM = 13,
	NR_ANON_MAPPED = 14,
	NR_FILE_MAPPED = 15,
	NR_FILE_PAGES = 16,
	NR_FILE_DIRTY = 17,
	NR_WRITEBACK = 18,
	NR_WRITEBACK_TEMP = 19,
	NR_SHMEM = 20,
	NR_SHMEM_THPS = 21,
	NR_SHMEM_PMDMAPPED = 22,
	NR_FILE_THPS = 23,
	NR_FILE_PMDMAPPED = 24,
	NR_ANON_THPS = 25,
	NR_VMSCAN_WRITE = 26,
	NR_VMSCAN_IMMEDIATE = 27,
	NR_DIRTIED = 28,
	NR_WRITTEN = 29,
	NR_KERNEL_MISC_RECLAIMABLE = 30,
	NR_FOLL_PIN_ACQUIRED = 31,
	NR_FOLL_PIN_RELEASED = 32,
	NR_VM_NODE_STAT_ITEMS = 33,
};

struct lruvec {
	struct list_head lists[5];
	long unsigned int anon_cost;
	long unsigned int file_cost;
	atomic_long_t nonresident_age;
	long unsigned int refaults;
	long unsigned int flags;
};

typedef unsigned int isolate_mode_t;

struct per_cpu_pages {
	int count;
	int high;
	int batch;
	struct list_head lists[3];
};

struct per_cpu_pageset {
	struct per_cpu_pages pcp;
	s8 expire;
	u16 vm_numa_stat_diff[6];
	s8 stat_threshold;
	s8 vm_stat_diff[12];
};

struct per_cpu_nodestat {
	s8 stat_threshold;
	s8 vm_node_stat_diff[33];
};

enum zone_type {
	ZONE_DMA = 0,
	ZONE_DMA32 = 1,
	ZONE_NORMAL = 2,
	ZONE_MOVABLE = 3,
	__MAX_NR_ZONES = 4,
};

struct pglist_data;

struct zone {
	long unsigned int _watermark[3];
	long unsigned int watermark_boost;
	long unsigned int nr_reserved_highatomic;
	long int lowmem_reserve[4];
	int node;
	struct pglist_data *zone_pgdat;
	struct per_cpu_pageset *pageset;
	long unsigned int zone_start_pfn;
	atomic_long_t managed_pages;
	long unsigned int spanned_pages;
	long unsigned int present_pages;
	const char *name;
	int initialized;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct zone_padding _pad1_;
	struct free_area free_area[11];
	long unsigned int flags;
	spinlock_t lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	struct zone_padding _pad2_;
	long unsigned int percpu_drift_mark;
	long unsigned int compact_cached_free_pfn;
	long unsigned int compact_cached_migrate_pfn[2];
	long unsigned int compact_init_migrate_pfn;
	long unsigned int compact_init_free_pfn;
	unsigned int compact_considered;
	unsigned int compact_defer_shift;
	int compact_order_failed;
	bool compact_blockskip_flush;
	bool contiguous;
	short: 16;
	struct zone_padding _pad3_;
	atomic_long_t vm_stat[12];
	atomic_long_t vm_numa_stat[6];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct zoneref {
	struct zone *zone;
	int zone_idx;
};

struct zonelist {
	struct zoneref _zonerefs[257];
};

struct pglist_data {
	struct zone node_zones[4];
	struct zonelist node_zonelists[2];
	int nr_zones;
	long unsigned int node_start_pfn;
	long unsigned int node_present_pages;
	long unsigned int node_spanned_pages;
	int node_id;
	wait_queue_head_t kswapd_wait;
	wait_queue_head_t pfmemalloc_wait;
	struct task_struct *kswapd;
	int kswapd_order;
	enum zone_type kswapd_highest_zoneidx;
	int kswapd_failures;
	int kcompactd_max_order;
	enum zone_type kcompactd_highest_zoneidx;
	wait_queue_head_t kcompactd_wait;
	struct task_struct *kcompactd;
	long unsigned int totalreserve_pages;
	long unsigned int min_unmapped_pages;
	long unsigned int min_slab_pages;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct zone_padding _pad1_;
	spinlock_t lru_lock;
	struct lruvec __lruvec;
	long unsigned int flags;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct zone_padding _pad2_;
	struct per_cpu_nodestat *per_cpu_nodestats;
	atomic_long_t vm_stat[33];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct mem_section_usage {
	long unsigned int subsection_map[1];
	long unsigned int pageblock_flags[0];
};

struct mem_section {
	long unsigned int section_mem_map;
	struct mem_section_usage *usage;
};

struct mem_cgroup;

struct shrink_control {
	gfp_t gfp_mask;
	int nid;
	long unsigned int nr_to_scan;
	long unsigned int nr_scanned;
	struct mem_cgroup *memcg;
};

struct shrinker {
	long unsigned int (*count_objects)(struct shrinker *, struct shrink_control *);
	long unsigned int (*scan_objects)(struct shrinker *, struct shrink_control *);
	long int batch;
	int seeks;
	unsigned int flags;
	struct list_head list;
	atomic_long_t *nr_deferred;
};

struct rlimit {
	__kernel_ulong_t rlim_cur;
	__kernel_ulong_t rlim_max;
};

struct dev_pagemap_ops {
	void (*page_free)(struct page *);
	void (*kill)(struct dev_pagemap *);
	void (*cleanup)(struct dev_pagemap *);
	vm_fault_t (*migrate_to_ram)(struct vm_fault *);
};

struct pid_namespace;

struct upid {
	int nr;
	struct pid_namespace *ns;
};

struct pid {
	refcount_t count;
	unsigned int level;
	spinlock_t lock;
	struct hlist_head tasks[4];
	struct hlist_head inodes;
	wait_queue_head_t wait_pidfd;
	struct callback_head rcu;
	struct upid numbers[1];
};

typedef struct {
	gid_t val;
} kgid_t;

struct hrtimer_cpu_base;

struct hrtimer_clock_base {
	struct hrtimer_cpu_base *cpu_base;
	unsigned int index;
	clockid_t clockid;
	seqcount_t seq;
	struct hrtimer *running;
	struct timerqueue_head active;
	ktime_t (*get_time)();
	ktime_t offset;
};

struct hrtimer_cpu_base {
	raw_spinlock_t lock;
	unsigned int cpu;
	unsigned int active_bases;
	unsigned int clock_was_set_seq;
	unsigned int hres_active: 1;
	unsigned int in_hrtirq: 1;
	unsigned int hang_detected: 1;
	unsigned int softirq_activated: 1;
	unsigned int nr_events;
	short unsigned int nr_retries;
	short unsigned int nr_hangs;
	unsigned int max_hang_time;
	ktime_t expires_next;
	struct hrtimer *next_timer;
	ktime_t softirq_expires_next;
	struct hrtimer *softirq_next_timer;
	struct hrtimer_clock_base clock_base[8];
};

struct tick_device;

typedef void __signalfn_t(int);

typedef __signalfn_t *__sighandler_t;

typedef void __restorefn_t();

typedef __restorefn_t *__sigrestore_t;

union sigval {
	int sival_int;
	void *sival_ptr;
};

typedef union sigval sigval_t;

union __sifields {
	struct {
		__kernel_pid_t _pid;
		__kernel_uid32_t _uid;
	} _kill;
	struct {
		__kernel_timer_t _tid;
		int _overrun;
		sigval_t _sigval;
		int _sys_private;
	} _timer;
	struct {
		__kernel_pid_t _pid;
		__kernel_uid32_t _uid;
		sigval_t _sigval;
	} _rt;
	struct {
		__kernel_pid_t _pid;
		__kernel_uid32_t _uid;
		int _status;
		__kernel_clock_t _utime;
		__kernel_clock_t _stime;
	} _sigchld;
	struct {
		void *_addr;
		union {
			short int _addr_lsb;
			struct {
				char _dummy_bnd[8];
				void *_lower;
				void *_upper;
			} _addr_bnd;
			struct {
				char _dummy_pkey[8];
				__u32 _pkey;
			} _addr_pkey;
		};
	} _sigfault;
	struct {
		long int _band;
		int _fd;
	} _sigpoll;
	struct {
		void *_call_addr;
		int _syscall;
		unsigned int _arch;
	} _sigsys;
};

struct kernel_siginfo {
	struct {
		int si_signo;
		int si_errno;
		int si_code;
		union __sifields _sifields;
	};
};

struct ratelimit_state {
	raw_spinlock_t lock;
	int interval;
	int burst;
	int printed;
	int missed;
	long unsigned int begin;
	long unsigned int flags;
};

struct user_struct {
	refcount_t __count;
	atomic_t processes;
	atomic_t sigpending;
	atomic_long_t epoll_watches;
	long unsigned int mq_bytes;
	long unsigned int locked_shm;
	long unsigned int unix_inflight;
	atomic_long_t pipe_bufs;
	struct hlist_node uidhash_node;
	kuid_t uid;
	atomic_long_t locked_vm;
	struct ratelimit_state ratelimit;
};

struct sigaction {
	__sighandler_t sa_handler;
	long unsigned int sa_flags;
	__sigrestore_t sa_restorer;
	sigset_t sa_mask;
};

struct k_sigaction {
	struct sigaction sa;
};

struct cpu_itimer {
	u64 expires;
	u64 incr;
};

struct task_cputime_atomic {
	atomic64_t utime;
	atomic64_t stime;
	atomic64_t sum_exec_runtime;
};

struct thread_group_cputimer {
	struct task_cputime_atomic cputime_atomic;
};

struct pacct_struct {
	int ac_flag;
	long int ac_exitcode;
	long unsigned int ac_mem;
	u64 ac_utime;
	u64 ac_stime;
	long unsigned int ac_minflt;
	long unsigned int ac_majflt;
};

struct tty_struct;

struct taskstats;

struct tty_audit_buf;

struct signal_struct {
	refcount_t sigcnt;
	atomic_t live;
	int nr_threads;
	struct list_head thread_head;
	wait_queue_head_t wait_chldexit;
	struct task_struct *curr_target;
	struct sigpending shared_pending;
	struct hlist_head multiprocess;
	int group_exit_code;
	int notify_count;
	struct task_struct *group_exit_task;
	int group_stop_count;
	unsigned int flags;
	unsigned int is_child_subreaper: 1;
	unsigned int has_child_subreaper: 1;
	int posix_timer_id;
	struct list_head posix_timers;
	struct hrtimer real_timer;
	ktime_t it_real_incr;
	struct cpu_itimer it[2];
	struct thread_group_cputimer cputimer;
	struct posix_cputimers posix_cputimers;
	struct pid *pids[4];
	struct pid *tty_old_pgrp;
	int leader;
	struct tty_struct *tty;
	seqlock_t stats_lock;
	u64 utime;
	u64 stime;
	u64 cutime;
	u64 cstime;
	u64 gtime;
	u64 cgtime;
	struct prev_cputime prev_cputime;
	long unsigned int nvcsw;
	long unsigned int nivcsw;
	long unsigned int cnvcsw;
	long unsigned int cnivcsw;
	long unsigned int min_flt;
	long unsigned int maj_flt;
	long unsigned int cmin_flt;
	long unsigned int cmaj_flt;
	long unsigned int inblock;
	long unsigned int oublock;
	long unsigned int cinblock;
	long unsigned int coublock;
	long unsigned int maxrss;
	long unsigned int cmaxrss;
	struct task_io_accounting ioac;
	long long unsigned int sum_sched_runtime;
	struct rlimit rlim[16];
	struct pacct_struct pacct;
	struct taskstats *stats;
	unsigned int audit_tty;
	struct tty_audit_buf *tty_audit_buf;
	bool oom_flag_origin;
	short int oom_score_adj;
	short int oom_score_adj_min;
	struct mm_struct *oom_mm;
	struct mutex cred_guard_mutex;
	struct mutex exec_update_mutex;
};

struct rseq {
	__u32 cpu_id_start;
	__u32 cpu_id;
	union {
		__u64 ptr64;
		__u64 ptr;
	} rseq_cs;
	__u32 flags;
	long: 32;
	long: 64;
};

struct root_domain;

struct rq;

struct rq_flags;

struct sched_class {
	const struct sched_class *next;
	void (*enqueue_task)(struct rq *, struct task_struct *, int);
	void (*dequeue_task)(struct rq *, struct task_struct *, int);
	void (*yield_task)(struct rq *);
	bool (*yield_to_task)(struct rq *, struct task_struct *, bool);
	void (*check_preempt_curr)(struct rq *, struct task_struct *, int);
	struct task_struct * (*pick_next_task)(struct rq *);
	void (*put_prev_task)(struct rq *, struct task_struct *);
	void (*set_next_task)(struct rq *, struct task_struct *, bool);
	int (*balance)(struct rq *, struct task_struct *, struct rq_flags *);
	int (*select_task_rq)(struct task_struct *, int, int, int);
	void (*migrate_task_rq)(struct task_struct *, int);
	void (*task_woken)(struct rq *, struct task_struct *);
	void (*set_cpus_allowed)(struct task_struct *, const struct cpumask *);
	void (*rq_online)(struct rq *);
	void (*rq_offline)(struct rq *);
	void (*task_tick)(struct rq *, struct task_struct *, int);
	void (*task_fork)(struct task_struct *);
	void (*task_dead)(struct task_struct *);
	void (*switched_from)(struct rq *, struct task_struct *);
	void (*switched_to)(struct rq *, struct task_struct *);
	void (*prio_changed)(struct rq *, struct task_struct *, int);
	unsigned int (*get_rr_interval)(struct rq *, struct task_struct *);
	void (*update_curr)(struct rq *);
	void (*task_change_group)(struct task_struct *, int);
};

struct kernel_cap_struct {
	__u32 cap[2];
};

typedef struct kernel_cap_struct kernel_cap_t;

struct group_info;

struct cred {
	atomic_t usage;
	kuid_t uid;
	kgid_t gid;
	kuid_t suid;
	kgid_t sgid;
	kuid_t euid;
	kgid_t egid;
	kuid_t fsuid;
	kgid_t fsgid;
	unsigned int securebits;
	kernel_cap_t cap_inheritable;
	kernel_cap_t cap_permitted;
	kernel_cap_t cap_effective;
	kernel_cap_t cap_bset;
	kernel_cap_t cap_ambient;
	unsigned char jit_keyring;
	struct key *session_keyring;
	struct key *process_keyring;
	struct key *thread_keyring;
	struct key *request_key_auth;
	void *security;
	struct user_struct *user;
	struct user_namespace *user_ns;
	struct group_info *group_info;
	union {
		int non_rcu;
		struct callback_head rcu;
	};
};

typedef int32_t key_serial_t;

typedef uint32_t key_perm_t;

struct key_type;

struct key_tag;

struct keyring_index_key {
	long unsigned int hash;
	union {
		struct {
			u16 desc_len;
			char desc[6];
		};
		long unsigned int x;
	};
	struct key_type *type;
	struct key_tag *domain_tag;
	const char *description;
};

union key_payload {
	void *rcu_data0;
	void *data[4];
};

struct assoc_array_ptr;

struct assoc_array {
	struct assoc_array_ptr *root;
	long unsigned int nr_leaves_on_tree;
};

struct key_user;

struct key_restriction;

struct key {
	refcount_t usage;
	key_serial_t serial;
	union {
		struct list_head graveyard_link;
		struct rb_node serial_node;
	};
	struct rw_semaphore sem;
	struct key_user *user;
	void *security;
	union {
		time64_t expiry;
		time64_t revoked_at;
	};
	time64_t last_used_at;
	kuid_t uid;
	kgid_t gid;
	key_perm_t perm;
	short unsigned int quotalen;
	short unsigned int datalen;
	short int state;
	long unsigned int flags;
	union {
		struct keyring_index_key index_key;
		struct {
			long unsigned int hash;
			long unsigned int len_desc;
			struct key_type *type;
			struct key_tag *domain_tag;
			char *description;
		};
	};
	union {
		union key_payload payload;
		struct {
			struct list_head name_link;
			struct assoc_array keys;
		};
	};
	struct key_restriction *restrict_link;
};

struct sighand_struct {
	spinlock_t siglock;
	refcount_t count;
	wait_queue_head_t signalfd_wqh;
	struct k_sigaction action[64];
};

struct io_cq;

struct io_context {
	atomic_long_t refcount;
	atomic_t active_ref;
	atomic_t nr_tasks;
	spinlock_t lock;
	short unsigned int ioprio;
	int nr_batch_requests;
	long unsigned int last_waited;
	struct xarray icq_tree;
	struct io_cq *icq_hint;
	struct hlist_head icq_list;
	struct work_struct release_work;
};

union thread_union {
	struct task_struct task;
	long unsigned int stack[2048];
};

struct hlist_bl_node;

struct hlist_bl_head {
	struct hlist_bl_node *first;
};

struct hlist_bl_node {
	struct hlist_bl_node *next;
	struct hlist_bl_node **pprev;
};

struct lockref {
	union {
		__u64 lock_count;
		struct {
			spinlock_t lock;
			int count;
		};
	};
};

struct qstr {
	union {
		struct {
			u32 hash;
			u32 len;
		};
		u64 hash_len;
	};
	const unsigned char *name;
};

struct dentry_stat_t {
	long int nr_dentry;
	long int nr_unused;
	long int age_limit;
	long int want_pages;
	long int nr_negative;
	long int dummy;
};

struct dentry_operations;

struct dentry {
	unsigned int d_flags;
	seqcount_t d_seq;
	struct hlist_bl_node d_hash;
	struct dentry *d_parent;
	struct qstr d_name;
	struct inode *d_inode;
	unsigned char d_iname[32];
	struct lockref d_lockref;
	const struct dentry_operations *d_op;
	struct super_block *d_sb;
	long unsigned int d_time;
	void *d_fsdata;
	union {
		struct list_head d_lru;
		wait_queue_head_t *d_wait;
	};
	struct list_head d_child;
	struct list_head d_subdirs;
	union {
		struct hlist_node d_alias;
		struct hlist_bl_node d_in_lookup_hash;
		struct callback_head d_rcu;
	} d_u;
};

struct posix_acl;

struct inode_operations;

struct file_lock_context;

struct block_device;

struct cdev;

struct fsnotify_mark_connector;

struct inode {
	umode_t i_mode;
	short unsigned int i_opflags;
	kuid_t i_uid;
	kgid_t i_gid;
	unsigned int i_flags;
	struct posix_acl *i_acl;
	struct posix_acl *i_default_acl;
	const struct inode_operations *i_op;
	struct super_block *i_sb;
	struct address_space *i_mapping;
	void *i_security;
	long unsigned int i_ino;
	union {
		const unsigned int i_nlink;
		unsigned int __i_nlink;
	};
	dev_t i_rdev;
	loff_t i_size;
	struct timespec64 i_atime;
	struct timespec64 i_mtime;
	struct timespec64 i_ctime;
	spinlock_t i_lock;
	short unsigned int i_bytes;
	u8 i_blkbits;
	u8 i_write_hint;
	blkcnt_t i_blocks;
	long unsigned int i_state;
	struct rw_semaphore i_rwsem;
	long unsigned int dirtied_when;
	long unsigned int dirtied_time_when;
	struct hlist_node i_hash;
	struct list_head i_io_list;
	struct list_head i_lru;
	struct list_head i_sb_list;
	struct list_head i_wb_list;
	union {
		struct hlist_head i_dentry;
		struct callback_head i_rcu;
	};
	atomic64_t i_version;
	atomic64_t i_sequence;
	atomic_t i_count;
	atomic_t i_dio_count;
	atomic_t i_writecount;
	atomic_t i_readcount;
	union {
		const struct file_operations *i_fop;
		void (*free_inode)(struct inode *);
	};
	struct file_lock_context *i_flctx;
	struct address_space i_data;
	struct list_head i_devices;
	union {
		struct pipe_inode_info *i_pipe;
		struct block_device *i_bdev;
		struct cdev *i_cdev;
		char *i_link;
		unsigned int i_dir_seq;
	};
	__u32 i_generation;
	__u32 i_fsnotify_mask;
	struct fsnotify_mark_connector *i_fsnotify_marks;
	void *i_private;
};

struct dentry_operations {
	int (*d_revalidate)(struct dentry *, unsigned int);
	int (*d_weak_revalidate)(struct dentry *, unsigned int);
	int (*d_hash)(const struct dentry *, struct qstr *);
	int (*d_compare)(const struct dentry *, unsigned int, const char *, const struct qstr *);
	int (*d_delete)(const struct dentry *);
	int (*d_init)(struct dentry *);
	void (*d_release)(struct dentry *);
	void (*d_prune)(struct dentry *);
	void (*d_iput)(struct dentry *, struct inode *);
	char * (*d_dname)(struct dentry *, char *, int);
	struct vfsmount * (*d_automount)(struct path *);
	int (*d_manage)(const struct path *, bool);
	struct dentry * (*d_real)(struct dentry *, const struct inode *);
	long: 64;
	long: 64;
	long: 64;
};

struct mtd_info;

typedef long long int qsize_t;

struct quota_format_type;

struct mem_dqinfo {
	struct quota_format_type *dqi_format;
	int dqi_fmt_id;
	struct list_head dqi_dirty_list;
	long unsigned int dqi_flags;
	unsigned int dqi_bgrace;
	unsigned int dqi_igrace;
	qsize_t dqi_max_spc_limit;
	qsize_t dqi_max_ino_limit;
	void *dqi_priv;
};

struct quota_format_ops;

struct quota_info {
	unsigned int flags;
	struct rw_semaphore dqio_sem;
	struct inode *files[3];
	struct mem_dqinfo info[3];
	const struct quota_format_ops *ops[3];
};

struct rcu_sync {
	int gp_state;
	int gp_count;
	wait_queue_head_t gp_wait;
	struct callback_head cb_head;
};

struct rcuwait {
	struct task_struct *task;
};

struct percpu_rw_semaphore {
	struct rcu_sync rss;
	unsigned int *read_count;
	struct rcuwait writer;
	wait_queue_head_t waiters;
	atomic_t block;
};

struct sb_writers {
	int frozen;
	wait_queue_head_t wait_unfrozen;
	struct percpu_rw_semaphore rw_sem[3];
};

typedef struct {
	__u8 b[16];
} uuid_t;

struct list_lru_node;

struct list_lru {
	struct list_lru_node *node;
};

struct super_operations;

struct dquot_operations;

struct quotactl_ops;

struct export_operations;

struct xattr_handler;

struct workqueue_struct;

struct super_block {
	struct list_head s_list;
	dev_t s_dev;
	unsigned char s_blocksize_bits;
	long unsigned int s_blocksize;
	loff_t s_maxbytes;
	struct file_system_type *s_type;
	const struct super_operations *s_op;
	const struct dquot_operations *dq_op;
	const struct quotactl_ops *s_qcop;
	const struct export_operations *s_export_op;
	long unsigned int s_flags;
	long unsigned int s_iflags;
	long unsigned int s_magic;
	struct dentry *s_root;
	struct rw_semaphore s_umount;
	int s_count;
	atomic_t s_active;
	void *s_security;
	const struct xattr_handler **s_xattr;
	struct hlist_bl_head s_roots;
	struct list_head s_mounts;
	struct block_device *s_bdev;
	struct backing_dev_info *s_bdi;
	struct mtd_info *s_mtd;
	struct hlist_node s_instances;
	unsigned int s_quota_types;
	struct quota_info s_dquot;
	struct sb_writers s_writers;
	void *s_fs_info;
	u32 s_time_gran;
	time64_t s_time_min;
	time64_t s_time_max;
	__u32 s_fsnotify_mask;
	struct fsnotify_mark_connector *s_fsnotify_marks;
	char s_id[32];
	uuid_t s_uuid;
	unsigned int s_max_links;
	fmode_t s_mode;
	struct mutex s_vfs_rename_mutex;
	const char *s_subtype;
	const struct dentry_operations *s_d_op;
	int cleancache_poolid;
	struct shrinker s_shrink;
	atomic_long_t s_remove_count;
	atomic_long_t s_fsnotify_inode_refs;
	int s_readonly_remount;
	errseq_t s_wb_err;
	struct workqueue_struct *s_dio_done_wq;
	struct hlist_head s_pins;
	struct user_namespace *s_user_ns;
	struct list_lru s_dentry_lru;
	struct list_lru s_inode_lru;
	struct callback_head rcu;
	struct work_struct destroy_work;
	struct mutex s_sync_lock;
	int s_stack_depth;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t s_inode_list_lock;
	struct list_head s_inodes;
	spinlock_t s_inode_wblist_lock;
	struct list_head s_inodes_wb;
	long: 64;
	long: 64;
};

struct kstat {
	u32 result_mask;
	umode_t mode;
	unsigned int nlink;
	uint32_t blksize;
	u64 attributes;
	u64 attributes_mask;
	u64 ino;
	dev_t dev;
	dev_t rdev;
	kuid_t uid;
	kgid_t gid;
	loff_t size;
	struct timespec64 atime;
	struct timespec64 mtime;
	struct timespec64 ctime;
	struct timespec64 btime;
	u64 blocks;
	u64 mnt_id;
};

struct list_lru_one {
	struct list_head list;
	long int nr_items;
};

struct list_lru_node {
	spinlock_t lock;
	struct list_lru_one lru;
	long int nr_items;
	long: 64;
	long: 64;
	long: 64;
};

struct xa_node {
	unsigned char shift;
	unsigned char offset;
	unsigned char count;
	unsigned char nr_values;
	struct xa_node *parent;
	struct xarray *array;
	union {
		struct list_head private_list;
		struct callback_head callback_head;
	};
	void *slots[64];
	union {
		long unsigned int tags[3];
		long unsigned int marks[3];
	};
};

typedef struct {} local_lock_t;

struct radix_tree_preload {
	local_lock_t lock;
	unsigned int nr;
	struct xa_node *nodes;
};

enum migrate_mode {
	MIGRATE_ASYNC = 0,
	MIGRATE_SYNC_LIGHT = 1,
	MIGRATE_SYNC = 2,
	MIGRATE_SYNC_NO_COPY = 3,
};

struct ctl_table;

typedef int proc_handler(struct ctl_table *, int, void *, size_t *, loff_t *);

struct ctl_table_poll;

struct ctl_table {
	const char *procname;
	void *data;
	int maxlen;
	umode_t mode;
	struct ctl_table *child;
	proc_handler *proc_handler;
	struct ctl_table_poll *poll;
	void *extra1;
	void *extra2;
};

struct ctl_table_poll {
	atomic_t event;
	wait_queue_head_t wait;
};

struct key_tag {
	struct callback_head rcu;
	refcount_t usage;
	bool removed;
};

typedef int (*request_key_actor_t)(struct key *, void *);

struct key_preparsed_payload;

struct key_match_data;

struct kernel_pkey_params;

struct kernel_pkey_query;

struct key_type {
	const char *name;
	size_t def_datalen;
	unsigned int flags;
	int (*vet_description)(const char *);
	int (*preparse)(struct key_preparsed_payload *);
	void (*free_preparse)(struct key_preparsed_payload *);
	int (*instantiate)(struct key *, struct key_preparsed_payload *);
	int (*update)(struct key *, struct key_preparsed_payload *);
	int (*match_preparse)(struct key_match_data *);
	void (*match_free)(struct key_match_data *);
	void (*revoke)(struct key *);
	void (*destroy)(struct key *);
	void (*describe)(const struct key *, struct seq_file *);
	long int (*read)(const struct key *, char *, size_t);
	request_key_actor_t request_key;
	struct key_restriction * (*lookup_restriction)(const char *);
	int (*asym_query)(const struct kernel_pkey_params *, struct kernel_pkey_query *);
	int (*asym_eds_op)(struct kernel_pkey_params *, const void *, void *);
	int (*asym_verify_signature)(struct kernel_pkey_params *, const void *, const void *);
	struct list_head link;
	struct lock_class_key lock_class;
};

typedef int (*key_restrict_link_func_t)(struct key *, const struct key_type *, const union key_payload *, struct key *);

struct key_restriction {
	key_restrict_link_func_t check;
	struct key *key;
	struct key_type *keytype;
};

struct group_info {
	atomic_t usage;
	int ngroups;
	kgid_t gid[0];
};

struct delayed_call {
	void (*fn)(void *);
	void *arg;
};

typedef struct {
	__u8 b[16];
} guid_t;

struct request_queue;

struct io_cq {
	struct request_queue *q;
	struct io_context *ioc;
	union {
		struct list_head q_node;
		struct kmem_cache *__rcu_icq_cache;
	};
	union {
		struct hlist_node ioc_node;
		struct callback_head __rcu_head;
	};
	unsigned int flags;
};

struct files_stat_struct {
	long unsigned int nr_files;
	long unsigned int nr_free_files;
	long unsigned int max_files;
};

struct inodes_stat_t {
	long int nr_inodes;
	long int nr_unused;
	long int dummy[5];
};

struct kiocb {
	struct file *ki_filp;
	loff_t ki_pos;
	void (*ki_complete)(struct kiocb *, long int, long int);
	void *private;
	int ki_flags;
	u16 ki_hint;
	u16 ki_ioprio;
	unsigned int ki_cookie;
};

struct iattr {
	unsigned int ia_valid;
	umode_t ia_mode;
	kuid_t ia_uid;
	kgid_t ia_gid;
	loff_t ia_size;
	struct timespec64 ia_atime;
	struct timespec64 ia_mtime;
	struct timespec64 ia_ctime;
	struct file *ia_file;
};

struct percpu_counter {
	raw_spinlock_t lock;
	s64 count;
	struct list_head list;
	s32 *counters;
};

typedef __kernel_uid32_t projid_t;

typedef struct {
	projid_t val;
} kprojid_t;

enum quota_type {
	USRQUOTA = 0,
	GRPQUOTA = 1,
	PRJQUOTA = 2,
};

struct kqid {
	union {
		kuid_t uid;
		kgid_t gid;
		kprojid_t projid;
	};
	enum quota_type type;
};

struct mem_dqblk {
	qsize_t dqb_bhardlimit;
	qsize_t dqb_bsoftlimit;
	qsize_t dqb_curspace;
	qsize_t dqb_rsvspace;
	qsize_t dqb_ihardlimit;
	qsize_t dqb_isoftlimit;
	qsize_t dqb_curinodes;
	time64_t dqb_btime;
	time64_t dqb_itime;
};

struct dquot {
	struct hlist_node dq_hash;
	struct list_head dq_inuse;
	struct list_head dq_free;
	struct list_head dq_dirty;
	struct mutex dq_lock;
	spinlock_t dq_dqb_lock;
	atomic_t dq_count;
	struct super_block *dq_sb;
	struct kqid dq_id;
	loff_t dq_off;
	long unsigned int dq_flags;
	struct mem_dqblk dq_dqb;
};

struct quota_format_type {
	int qf_fmt_id;
	const struct quota_format_ops *qf_ops;
	struct module *qf_owner;
	struct quota_format_type *qf_next;
};

struct dqstats {
	long unsigned int stat[8];
	struct percpu_counter counter[8];
};

struct quota_format_ops {
	int (*check_quota_file)(struct super_block *, int);
	int (*read_file_info)(struct super_block *, int);
	int (*write_file_info)(struct super_block *, int);
	int (*free_file_info)(struct super_block *, int);
	int (*read_dqblk)(struct dquot *);
	int (*commit_dqblk)(struct dquot *);
	int (*release_dqblk)(struct dquot *);
	int (*get_next_id)(struct super_block *, struct kqid *);
};

struct dquot_operations {
	int (*write_dquot)(struct dquot *);
	struct dquot * (*alloc_dquot)(struct super_block *, int);
	void (*destroy_dquot)(struct dquot *);
	int (*acquire_dquot)(struct dquot *);
	int (*release_dquot)(struct dquot *);
	int (*mark_dirty)(struct dquot *);
	int (*write_info)(struct super_block *, int);
	qsize_t * (*get_reserved_space)(struct inode *);
	int (*get_projid)(struct inode *, kprojid_t *);
	int (*get_inode_usage)(struct inode *, qsize_t *);
	int (*get_next_id)(struct super_block *, struct kqid *);
};

struct qc_dqblk {
	int d_fieldmask;
	u64 d_spc_hardlimit;
	u64 d_spc_softlimit;
	u64 d_ino_hardlimit;
	u64 d_ino_softlimit;
	u64 d_space;
	u64 d_ino_count;
	s64 d_ino_timer;
	s64 d_spc_timer;
	int d_ino_warns;
	int d_spc_warns;
	u64 d_rt_spc_hardlimit;
	u64 d_rt_spc_softlimit;
	u64 d_rt_space;
	s64 d_rt_spc_timer;
	int d_rt_spc_warns;
};

struct qc_type_state {
	unsigned int flags;
	unsigned int spc_timelimit;
	unsigned int ino_timelimit;
	unsigned int rt_spc_timelimit;
	unsigned int spc_warnlimit;
	unsigned int ino_warnlimit;
	unsigned int rt_spc_warnlimit;
	long long unsigned int ino;
	blkcnt_t blocks;
	blkcnt_t nextents;
};

struct qc_state {
	unsigned int s_incoredqs;
	struct qc_type_state s_state[3];
};

struct qc_info {
	int i_fieldmask;
	unsigned int i_flags;
	unsigned int i_spc_timelimit;
	unsigned int i_ino_timelimit;
	unsigned int i_rt_spc_timelimit;
	unsigned int i_spc_warnlimit;
	unsigned int i_ino_warnlimit;
	unsigned int i_rt_spc_warnlimit;
};

struct quotactl_ops {
	int (*quota_on)(struct super_block *, int, int, const struct path *);
	int (*quota_off)(struct super_block *, int);
	int (*quota_enable)(struct super_block *, unsigned int);
	int (*quota_disable)(struct super_block *, unsigned int);
	int (*quota_sync)(struct super_block *, int);
	int (*set_info)(struct super_block *, int, struct qc_info *);
	int (*get_dqblk)(struct super_block *, struct kqid, struct qc_dqblk *);
	int (*get_nextdqblk)(struct super_block *, struct kqid *, struct qc_dqblk *);
	int (*set_dqblk)(struct super_block *, struct kqid, struct qc_dqblk *);
	int (*get_state)(struct super_block *, struct qc_state *);
	int (*rm_xquota)(struct super_block *, unsigned int);
};

struct writeback_control;

struct readahead_control;

struct swap_info_struct;

struct address_space_operations {
	int (*writepage)(struct page *, struct writeback_control *);
	int (*readpage)(struct file *, struct page *);
	int (*writepages)(struct address_space *, struct writeback_control *);
	int (*set_page_dirty)(struct page *);
	int (*readpages)(struct file *, struct address_space *, struct list_head *, unsigned int);
	void (*readahead)(struct readahead_control *);
	int (*write_begin)(struct file *, struct address_space *, loff_t, unsigned int, unsigned int, struct page **, void **);
	int (*write_end)(struct file *, struct address_space *, loff_t, unsigned int, unsigned int, struct page *, void *);
	sector_t (*bmap)(struct address_space *, sector_t);
	void (*invalidatepage)(struct page *, unsigned int, unsigned int);
	int (*releasepage)(struct page *, gfp_t);
	void (*freepage)(struct page *);
	ssize_t (*direct_IO)(struct kiocb *, struct iov_iter *);
	int (*migratepage)(struct address_space *, struct page *, struct page *, enum migrate_mode);
	bool (*isolate_page)(struct page *, isolate_mode_t);
	void (*putback_page)(struct page *);
	int (*launder_page)(struct page *);
	int (*is_partially_uptodate)(struct page *, long unsigned int, long unsigned int);
	void (*is_dirty_writeback)(struct page *, bool *, bool *);
	int (*error_remove_page)(struct address_space *, struct page *);
	int (*swap_activate)(struct swap_info_struct *, struct file *, sector_t *);
	void (*swap_deactivate)(struct file *);
};

struct hd_struct;

struct gendisk;

struct block_device {
	dev_t bd_dev;
	int bd_openers;
	struct inode *bd_inode;
	struct super_block *bd_super;
	struct mutex bd_mutex;
	void *bd_claiming;
	void *bd_holder;
	int bd_holders;
	bool bd_write_holder;
	struct list_head bd_holder_disks;
	struct block_device *bd_contains;
	unsigned int bd_block_size;
	u8 bd_partno;
	struct hd_struct *bd_part;
	unsigned int bd_part_count;
	int bd_invalidated;
	struct gendisk *bd_disk;
	struct request_queue *bd_queue;
	struct backing_dev_info *bd_bdi;
	struct list_head bd_list;
	long unsigned int bd_private;
	int bd_fsfreeze_count;
	struct mutex bd_fsfreeze_mutex;
};

struct fiemap_extent_info;

struct inode_operations {
	struct dentry * (*lookup)(struct inode *, struct dentry *, unsigned int);
	const char * (*get_link)(struct dentry *, struct inode *, struct delayed_call *);
	int (*permission)(struct inode *, int);
	struct posix_acl * (*get_acl)(struct inode *, int);
	int (*readlink)(struct dentry *, char *, int);
	int (*create)(struct inode *, struct dentry *, umode_t, bool);
	int (*link)(struct dentry *, struct inode *, struct dentry *);
	int (*unlink)(struct inode *, struct dentry *);
	int (*symlink)(struct inode *, struct dentry *, const char *);
	int (*mkdir)(struct inode *, struct dentry *, umode_t);
	int (*rmdir)(struct inode *, struct dentry *);
	int (*mknod)(struct inode *, struct dentry *, umode_t, dev_t);
	int (*rename)(struct inode *, struct dentry *, struct inode *, struct dentry *, unsigned int);
	int (*setattr)(struct dentry *, struct iattr *);
	int (*getattr)(const struct path *, struct kstat *, u32, unsigned int);
	ssize_t (*listxattr)(struct dentry *, char *, size_t);
	int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64, u64);
	int (*update_time)(struct inode *, struct timespec64 *, int);
	int (*atomic_open)(struct inode *, struct dentry *, struct file *, unsigned int, umode_t);
	int (*tmpfile)(struct inode *, struct dentry *, umode_t);
	int (*set_acl)(struct inode *, struct posix_acl *, int);
	long: 64;
	long: 64;
	long: 64;
};

struct file_lock_context {
	spinlock_t flc_lock;
	struct list_head flc_flock;
	struct list_head flc_posix;
	struct list_head flc_lease;
};

struct file_lock_operations {
	void (*fl_copy_lock)(struct file_lock *, struct file_lock *);
	void (*fl_release_private)(struct file_lock *);
};

struct nlm_lockowner;

struct nfs_lock_info {
	u32 state;
	struct nlm_lockowner *owner;
	struct list_head list;
};

struct nfs4_lock_state;

struct nfs4_lock_info {
	struct nfs4_lock_state *owner;
};

struct fasync_struct;

struct lock_manager_operations;

struct file_lock {
	struct file_lock *fl_blocker;
	struct list_head fl_list;
	struct hlist_node fl_link;
	struct list_head fl_blocked_requests;
	struct list_head fl_blocked_member;
	fl_owner_t fl_owner;
	unsigned int fl_flags;
	unsigned char fl_type;
	unsigned int fl_pid;
	int fl_link_cpu;
	wait_queue_head_t fl_wait;
	struct file *fl_file;
	loff_t fl_start;
	loff_t fl_end;
	struct fasync_struct *fl_fasync;
	long unsigned int fl_break_time;
	long unsigned int fl_downgrade_time;
	const struct file_lock_operations *fl_ops;
	const struct lock_manager_operations *fl_lmops;
	union {
		struct nfs_lock_info nfs_fl;
		struct nfs4_lock_info nfs4_fl;
		struct {
			struct list_head link;
			int state;
			unsigned int debug_id;
		} afs;
	} fl_u;
};

struct lock_manager_operations {
	fl_owner_t (*lm_get_owner)(fl_owner_t);
	void (*lm_put_owner)(fl_owner_t);
	void (*lm_notify)(struct file_lock *);
	int (*lm_grant)(struct file_lock *, int);
	bool (*lm_break)(struct file_lock *);
	int (*lm_change)(struct file_lock *, int, struct list_head *);
	void (*lm_setup)(struct file_lock *, void **);
	bool (*lm_breaker_owns_lease)(struct file_lock *);
};

struct fasync_struct {
	rwlock_t fa_lock;
	int magic;
	int fa_fd;
	struct fasync_struct *fa_next;
	struct file *fa_file;
	struct callback_head fa_rcu;
};

struct kstatfs;

struct super_operations {
	struct inode * (*alloc_inode)(struct super_block *);
	void (*destroy_inode)(struct inode *);
	void (*free_inode)(struct inode *);
	void (*dirty_inode)(struct inode *, int);
	int (*write_inode)(struct inode *, struct writeback_control *);
	int (*drop_inode)(struct inode *);
	void (*evict_inode)(struct inode *);
	void (*put_super)(struct super_block *);
	int (*sync_fs)(struct super_block *, int);
	int (*freeze_super)(struct super_block *);
	int (*freeze_fs)(struct super_block *);
	int (*thaw_super)(struct super_block *);
	int (*unfreeze_fs)(struct super_block *);
	int (*statfs)(struct dentry *, struct kstatfs *);
	int (*remount_fs)(struct super_block *, int *, char *);
	void (*umount_begin)(struct super_block *);
	int (*show_options)(struct seq_file *, struct dentry *);
	int (*show_devname)(struct seq_file *, struct dentry *);
	int (*show_path)(struct seq_file *, struct dentry *);
	int (*show_stats)(struct seq_file *, struct dentry *);
	ssize_t (*quota_read)(struct super_block *, int, char *, size_t, loff_t);
	ssize_t (*quota_write)(struct super_block *, int, const char *, size_t, loff_t);
	struct dquot ** (*get_dquots)(struct inode *);
	int (*bdev_try_to_free_page)(struct super_block *, struct page *, gfp_t);
	long int (*nr_cached_objects)(struct super_block *, struct shrink_control *);
	long int (*free_cached_objects)(struct super_block *, struct shrink_control *);
};

struct iomap;

struct fid;

struct export_operations {
	int (*encode_fh)(struct inode *, __u32 *, int *, struct inode *);
	struct dentry * (*fh_to_dentry)(struct super_block *, struct fid *, int, int);
	struct dentry * (*fh_to_parent)(struct super_block *, struct fid *, int, int);
	int (*get_name)(struct dentry *, char *, struct dentry *);
	struct dentry * (*get_parent)(struct dentry *);
	int (*commit_metadata)(struct inode *);
	int (*get_uuid)(struct super_block *, u8 *, u32 *, u64 *);
	int (*map_blocks)(struct inode *, loff_t, u64, struct iomap *, bool, u32 *);
	int (*commit_blocks)(struct inode *, struct iomap *, int, struct iattr *);
};

struct xattr_handler {
	const char *name;
	const char *prefix;
	int flags;
	bool (*list)(struct dentry *);
	int (*get)(const struct xattr_handler *, struct dentry *, struct inode *, const char *, void *, size_t);
	int (*set)(const struct xattr_handler *, struct dentry *, struct inode *, const char *, const void *, size_t, int);
};

typedef int (*filldir_t)(struct dir_context *, const char *, int, loff_t, u64, unsigned int);

struct dir_context {
	filldir_t actor;
	loff_t pos;
};

struct p_log;

struct fs_parameter;

struct fs_parse_result;

typedef int fs_param_type(struct p_log *, const struct fs_parameter_spec *, struct fs_parameter *, struct fs_parse_result *);

struct fs_parameter_spec {
	const char *name;
	fs_param_type *type;
	u8 opt;
	short unsigned int flags;
	const void *data;
};

struct attribute {
	const char *name;
	umode_t mode;
};

struct kobj_attribute {
	struct attribute attr;
	ssize_t (*show)(struct kobject *, struct kobj_attribute *, char *);
	ssize_t (*store)(struct kobject *, struct kobj_attribute *, const char *, size_t);
};

typedef void compound_page_dtor(struct page *);

enum compound_dtor_id {
	NULL_COMPOUND_DTOR = 0,
	COMPOUND_PAGE_DTOR = 1,
	HUGETLB_PAGE_DTOR = 2,
	NR_COMPOUND_DTORS = 3,
};

enum vm_event_item {
	PGPGIN = 0,
	PGPGOUT = 1,
	PSWPIN = 2,
	PSWPOUT = 3,
	PGALLOC_DMA = 4,
	PGALLOC_DMA32 = 5,
	PGALLOC_NORMAL = 6,
	PGALLOC_MOVABLE = 7,
	ALLOCSTALL_DMA = 8,
	ALLOCSTALL_DMA32 = 9,
	ALLOCSTALL_NORMAL = 10,
	ALLOCSTALL_MOVABLE = 11,
	PGSCAN_SKIP_DMA = 12,
	PGSCAN_SKIP_DMA32 = 13,
	PGSCAN_SKIP_NORMAL = 14,
	PGSCAN_SKIP_MOVABLE = 15,
	PGFREE = 16,
	PGACTIVATE = 17,
	PGDEACTIVATE = 18,
	PGLAZYFREE = 19,
	PGFAULT = 20,
	PGMAJFAULT = 21,
	PGLAZYFREED = 22,
	PGREFILL = 23,
	PGSTEAL_KSWAPD = 24,
	PGSTEAL_DIRECT = 25,
	PGSCAN_KSWAPD = 26,
	PGSCAN_DIRECT = 27,
	PGSCAN_DIRECT_THROTTLE = 28,
	PGSCAN_ANON = 29,
	PGSCAN_FILE = 30,
	PGSTEAL_ANON = 31,
	PGSTEAL_FILE = 32,
	PGSCAN_ZONE_RECLAIM_FAILED = 33,
	PGINODESTEAL = 34,
	SLABS_SCANNED = 35,
	KSWAPD_INODESTEAL = 36,
	KSWAPD_LOW_WMARK_HIT_QUICKLY = 37,
	KSWAPD_HIGH_WMARK_HIT_QUICKLY = 38,
	PAGEOUTRUN = 39,
	PGROTATED = 40,
	DROP_PAGECACHE = 41,
	DROP_SLAB = 42,
	OOM_KILL = 43,
	PGMIGRATE_SUCCESS = 44,
	PGMIGRATE_FAIL = 45,
	COMPACTMIGRATE_SCANNED = 46,
	COMPACTFREE_SCANNED = 47,
	COMPACTISOLATED = 48,
	COMPACTSTALL = 49,
	COMPACTFAIL = 50,
	COMPACTSUCCESS = 51,
	KCOMPACTD_WAKE = 52,
	KCOMPACTD_MIGRATE_SCANNED = 53,
	KCOMPACTD_FREE_SCANNED = 54,
	HTLB_BUDDY_PGALLOC = 55,
	HTLB_BUDDY_PGALLOC_FAIL = 56,
	UNEVICTABLE_PGCULLED = 57,
	UNEVICTABLE_PGSCANNED = 58,
	UNEVICTABLE_PGRESCUED = 59,
	UNEVICTABLE_PGMLOCKED = 60,
	UNEVICTABLE_PGMUNLOCKED = 61,
	UNEVICTABLE_PGCLEARED = 62,
	UNEVICTABLE_PGSTRANDED = 63,
	SWAP_RA = 64,
	SWAP_RA_HIT = 65,
	NR_VM_EVENT_ITEMS = 66,
};

struct vm_event_state {
	long unsigned int event[66];
};

enum memblock_flags {
	MEMBLOCK_NONE = 0,
	MEMBLOCK_HOTPLUG = 1,
	MEMBLOCK_MIRROR = 2,
	MEMBLOCK_NOMAP = 4,
};

struct memblock_region {
	phys_addr_t base;
	phys_addr_t size;
	enum memblock_flags flags;
	int nid;
};

struct memblock_type {
	long unsigned int cnt;
	long unsigned int max;
	phys_addr_t total_size;
	struct memblock_region *regions;
	char *name;
};

struct memblock {
	bool bottom_up;
	phys_addr_t current_limit;
	struct memblock_type memory;
	struct memblock_type reserved;
};

struct debug_store {
	u64 bts_buffer_base;
	u64 bts_index;
	u64 bts_absolute_maximum;
	u64 bts_interrupt_threshold;
	u64 pebs_buffer_base;
	u64 pebs_index;
	u64 pebs_absolute_maximum;
	u64 pebs_interrupt_threshold;
	u64 pebs_event_reset[12];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct debug_store_buffers {
	char bts_buffer[65536];
	char pebs_buffer[65536];
};

struct cea_exception_stacks {
	char DF_stack_guard[4096];
	char DF_stack[4096];
	char NMI_stack_guard[4096];
	char NMI_stack[4096];
	char DB_stack_guard[4096];
	char DB_stack[4096];
	char MCE_stack_guard[4096];
	char MCE_stack[4096];
	char IST_top_guard[4096];
};

struct cpu_entry_area {
	char gdt[4096];
	struct entry_stack_page entry_stack_page;
	struct tss_struct tss;
	struct cea_exception_stacks estacks;
	struct debug_store cpu_debug_store;
	struct debug_store_buffers cpu_debug_buffers;
};

struct gdt_page {
	struct desc_struct gdt[16];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct tlb_context {
	u64 ctx_id;
	u64 tlb_gen;
};

struct tlb_state {
	struct mm_struct *loaded_mm;
	union {
		struct mm_struct *last_user_mm;
		long unsigned int last_user_mm_ibpb;
	};
	u16 loaded_mm_asid;
	u16 next_asid;
	bool is_lazy;
	bool invalidate_other;
	short unsigned int user_pcid_flush_mask;
	long unsigned int cr4;
	struct tlb_context ctxs[6];
};

enum e820_type {
	E820_TYPE_RAM = 1,
	E820_TYPE_RESERVED = 2,
	E820_TYPE_ACPI = 3,
	E820_TYPE_NVS = 4,
	E820_TYPE_UNUSABLE = 5,
	E820_TYPE_PMEM = 7,
	E820_TYPE_PRAM = 12,
	E820_TYPE_SOFT_RESERVED = 4026531839,
	E820_TYPE_RESERVED_KERN = 128,
};

struct e820_entry {
	u64 addr;
	u64 size;
	enum e820_type type;
} __attribute__((packed));

struct e820_table {
	__u32 nr_entries;
	struct e820_entry entries[320];
} __attribute__((packed));

struct boot_params_to_save {
	unsigned int start;
	unsigned int len;
};

struct idr {
	struct xarray idr_rt;
	unsigned int idr_base;
	unsigned int idr_next;
};

struct kernfs_root;

struct kernfs_elem_dir {
	long unsigned int subdirs;
	struct rb_root children;
	struct kernfs_root *root;
};

struct kernfs_syscall_ops;

struct kernfs_root {
	struct kernfs_node *kn;
	unsigned int flags;
	struct idr ino_idr;
	u32 last_id_lowbits;
	u32 id_highbits;
	struct kernfs_syscall_ops *syscall_ops;
	struct list_head supers;
	wait_queue_head_t deactivate_waitq;
};

struct kernfs_elem_symlink {
	struct kernfs_node *target_kn;
};

struct kernfs_ops;

struct kernfs_open_node;

struct kernfs_elem_attr {
	const struct kernfs_ops *ops;
	struct kernfs_open_node *open;
	loff_t size;
	struct kernfs_node *notify_next;
};

struct kernfs_iattrs;

struct kernfs_node {
	atomic_t count;
	atomic_t active;
	struct kernfs_node *parent;
	const char *name;
	struct rb_node rb;
	const void *ns;
	unsigned int hash;
	union {
		struct kernfs_elem_dir dir;
		struct kernfs_elem_symlink symlink;
		struct kernfs_elem_attr attr;
	};
	void *priv;
	u64 id;
	short unsigned int flags;
	umode_t mode;
	struct kernfs_iattrs *iattr;
};

struct kernfs_open_file;

struct kernfs_ops {
	int (*open)(struct kernfs_open_file *);
	void (*release)(struct kernfs_open_file *);
	int (*seq_show)(struct seq_file *, void *);
	void * (*seq_start)(struct seq_file *, loff_t *);
	void * (*seq_next)(struct seq_file *, void *, loff_t *);
	void (*seq_stop)(struct seq_file *, void *);
	ssize_t (*read)(struct kernfs_open_file *, char *, size_t, loff_t);
	size_t atomic_write_len;
	bool prealloc;
	ssize_t (*write)(struct kernfs_open_file *, char *, size_t, loff_t);
	__poll_t (*poll)(struct kernfs_open_file *, struct poll_table_struct *);
	int (*mmap)(struct kernfs_open_file *, struct vm_area_struct *);
};

struct kernfs_syscall_ops {
	int (*show_options)(struct seq_file *, struct kernfs_root *);
	int (*mkdir)(struct kernfs_node *, const char *, umode_t);
	int (*rmdir)(struct kernfs_node *);
	int (*rename)(struct kernfs_node *, struct kernfs_node *, const char *);
	int (*show_path)(struct seq_file *, struct kernfs_node *, struct kernfs_root *);
};

struct kernfs_open_file {
	struct kernfs_node *kn;
	struct file *file;
	struct seq_file *seq_file;
	void *priv;
	struct mutex mutex;
	struct mutex prealloc_mutex;
	int event;
	struct list_head list;
	char *prealloc_buf;
	size_t atomic_write_len;
	bool mmapped: 1;
	bool released: 1;
	const struct vm_operations_struct *vm_ops;
};

enum kobj_ns_type {
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET = 1,
	KOBJ_NS_TYPES = 2,
};

struct sock;

struct kobj_ns_type_operations {
	enum kobj_ns_type type;
	bool (*current_may_mount)();
	void * (*grab_current_ns)();
	const void * (*netlink_ns)(struct sock *);
	const void * (*initial_ns)();
	void (*drop_ns)(void *);
};

struct bin_attribute;

struct attribute_group {
	const char *name;
	umode_t (*is_visible)(struct kobject *, struct attribute *, int);
	umode_t (*is_bin_visible)(struct kobject *, struct bin_attribute *, int);
	struct attribute **attrs;
	struct bin_attribute **bin_attrs;
};

struct bin_attribute {
	struct attribute attr;
	size_t size;
	void *private;
	ssize_t (*read)(struct file *, struct kobject *, struct bin_attribute *, char *, loff_t, size_t);
	ssize_t (*write)(struct file *, struct kobject *, struct bin_attribute *, char *, loff_t, size_t);
	int (*mmap)(struct file *, struct kobject *, struct bin_attribute *, struct vm_area_struct *);
};

struct sysfs_ops {
	ssize_t (*show)(struct kobject *, struct attribute *, char *);
	ssize_t (*store)(struct kobject *, struct attribute *, const char *, size_t);
};

struct kset_uevent_ops;

struct kset {
	struct list_head list;
	spinlock_t list_lock;
	struct kobject kobj;
	const struct kset_uevent_ops *uevent_ops;
};

struct kobj_type {
	void (*release)(struct kobject *);
	const struct sysfs_ops *sysfs_ops;
	struct attribute **default_attrs;
	const struct attribute_group **default_groups;
	const struct kobj_ns_type_operations * (*child_ns_type)(struct kobject *);
	const void * (*namespace)(struct kobject *);
	void (*get_ownership)(struct kobject *, kuid_t *, kgid_t *);
};

struct kobj_uevent_env {
	char *argv[3];
	char *envp[64];
	int envp_idx;
	char buf[2048];
	int buflen;
};

struct kset_uevent_ops {
	int (* const filter)(struct kset *, struct kobject *);
	const char * (* const name)(struct kset *, struct kobject *);
	int (* const uevent)(struct kset *, struct kobject *, struct kobj_uevent_env *);
};

struct dev_pm_ops {
	int (*prepare)(struct device *);
	void (*complete)(struct device *);
	int (*suspend)(struct device *);
	int (*resume)(struct device *);
	int (*freeze)(struct device *);
	int (*thaw)(struct device *);
	int (*poweroff)(struct device *);
	int (*restore)(struct device *);
	int (*suspend_late)(struct device *);
	int (*resume_early)(struct device *);
	int (*freeze_late)(struct device *);
	int (*thaw_early)(struct device *);
	int (*poweroff_late)(struct device *);
	int (*restore_early)(struct device *);
	int (*suspend_noirq)(struct device *);
	int (*resume_noirq)(struct device *);
	int (*freeze_noirq)(struct device *);
	int (*thaw_noirq)(struct device *);
	int (*poweroff_noirq)(struct device *);
	int (*restore_noirq)(struct device *);
	int (*runtime_suspend)(struct device *);
	int (*runtime_resume)(struct device *);
	int (*runtime_idle)(struct device *);
};

struct pm_subsys_data {
	spinlock_t lock;
	unsigned int refcount;
	struct list_head clock_list;
};

struct wakeup_source {
	const char *name;
	int id;
	struct list_head entry;
	spinlock_t lock;
	struct wake_irq *wakeirq;
	struct timer_list timer;
	long unsigned int timer_expires;
	ktime_t total_time;
	ktime_t max_time;
	ktime_t last_time;
	ktime_t start_prevent_time;
	ktime_t prevent_sleep_time;
	long unsigned int event_count;
	long unsigned int active_count;
	long unsigned int relax_count;
	long unsigned int expire_count;
	long unsigned int wakeup_count;
	struct device *dev;
	bool active: 1;
	bool autosleep_enabled: 1;
};

struct dev_pm_domain {
	struct dev_pm_ops ops;
	int (*start)(struct device *);
	void (*detach)(struct device *, bool);
	int (*activate)(struct device *);
	void (*sync)(struct device *);
	void (*dismiss)(struct device *);
};

struct iommu_ops;

struct subsys_private;

struct bus_type {
	const char *name;
	const char *dev_name;
	struct device *dev_root;
	const struct attribute_group **bus_groups;
	const struct attribute_group **dev_groups;
	const struct attribute_group **drv_groups;
	int (*match)(struct device *, struct device_driver *);
	int (*uevent)(struct device *, struct kobj_uevent_env *);
	int (*probe)(struct device *);
	void (*sync_state)(struct device *);
	int (*remove)(struct device *);
	void (*shutdown)(struct device *);
	int (*online)(struct device *);
	int (*offline)(struct device *);
	int (*suspend)(struct device *, pm_message_t);
	int (*resume)(struct device *);
	int (*num_vf)(struct device *);
	int (*dma_configure)(struct device *);
	const struct dev_pm_ops *pm;
	const struct iommu_ops *iommu_ops;
	struct subsys_private *p;
	struct lock_class_key lock_key;
	bool need_parent_lock;
};

enum probe_type {
	PROBE_DEFAULT_STRATEGY = 0,
	PROBE_PREFER_ASYNCHRONOUS = 1,
	PROBE_FORCE_SYNCHRONOUS = 2,
};

struct of_device_id;

struct acpi_device_id;

struct driver_private;

struct device_driver {
	const char *name;
	struct bus_type *bus;
	struct module *owner;
	const char *mod_name;
	bool suppress_bind_attrs;
	enum probe_type probe_type;
	const struct of_device_id *of_match_table;
	const struct acpi_device_id *acpi_match_table;
	int (*probe)(struct device *);
	void (*sync_state)(struct device *);
	int (*remove)(struct device *);
	void (*shutdown)(struct device *);
	int (*suspend)(struct device *, pm_message_t);
	int (*resume)(struct device *);
	const struct attribute_group **groups;
	const struct attribute_group **dev_groups;
	const struct dev_pm_ops *pm;
	void (*coredump)(struct device *);
	struct driver_private *p;
};

enum iommu_cap {
	IOMMU_CAP_CACHE_COHERENCY = 0,
	IOMMU_CAP_INTR_REMAP = 1,
	IOMMU_CAP_NOEXEC = 2,
};

enum iommu_attr {
	DOMAIN_ATTR_GEOMETRY = 0,
	DOMAIN_ATTR_PAGING = 1,
	DOMAIN_ATTR_WINDOWS = 2,
	DOMAIN_ATTR_FSL_PAMU_STASH = 3,
	DOMAIN_ATTR_FSL_PAMU_ENABLE = 4,
	DOMAIN_ATTR_FSL_PAMUV1 = 5,
	DOMAIN_ATTR_NESTING = 6,
	DOMAIN_ATTR_DMA_USE_FLUSH_QUEUE = 7,
	DOMAIN_ATTR_MAX = 8,
};

enum iommu_dev_features {
	IOMMU_DEV_FEAT_AUX = 0,
	IOMMU_DEV_FEAT_SVA = 1,
};

struct iommu_domain;

struct iommu_iotlb_gather;

struct iommu_device;

struct iommu_resv_region;

struct of_phandle_args;

struct iommu_sva;

struct iommu_fault_event;

struct iommu_page_response;

struct iommu_cache_invalidate_info;

struct iommu_gpasid_bind_data;

struct iommu_ops {
	bool (*capable)(enum iommu_cap);
	struct iommu_domain * (*domain_alloc)(unsigned int);
	void (*domain_free)(struct iommu_domain *);
	int (*attach_dev)(struct iommu_domain *, struct device *);
	void (*detach_dev)(struct iommu_domain *, struct device *);
	int (*map)(struct iommu_domain *, long unsigned int, phys_addr_t, size_t, int, gfp_t);
	size_t (*unmap)(struct iommu_domain *, long unsigned int, size_t, struct iommu_iotlb_gather *);
	void (*flush_iotlb_all)(struct iommu_domain *);
	void (*iotlb_sync_map)(struct iommu_domain *);
	void (*iotlb_sync)(struct iommu_domain *, struct iommu_iotlb_gather *);
	phys_addr_t (*iova_to_phys)(struct iommu_domain *, dma_addr_t);
	struct iommu_device * (*probe_device)(struct device *);
	void (*release_device)(struct device *);
	void (*probe_finalize)(struct device *);
	struct iommu_group * (*device_group)(struct device *);
	int (*domain_get_attr)(struct iommu_domain *, enum iommu_attr, void *);
	int (*domain_set_attr)(struct iommu_domain *, enum iommu_attr, void *);
	void (*get_resv_regions)(struct device *, struct list_head *);
	void (*put_resv_regions)(struct device *, struct list_head *);
	void (*apply_resv_region)(struct device *, struct iommu_domain *, struct iommu_resv_region *);
	int (*domain_window_enable)(struct iommu_domain *, u32, phys_addr_t, u64, int);
	void (*domain_window_disable)(struct iommu_domain *, u32);
	int (*of_xlate)(struct device *, struct of_phandle_args *);
	bool (*is_attach_deferred)(struct iommu_domain *, struct device *);
	bool (*dev_has_feat)(struct device *, enum iommu_dev_features);
	bool (*dev_feat_enabled)(struct device *, enum iommu_dev_features);
	int (*dev_enable_feat)(struct device *, enum iommu_dev_features);
	int (*dev_disable_feat)(struct device *, enum iommu_dev_features);
	int (*aux_attach_dev)(struct iommu_domain *, struct device *);
	void (*aux_detach_dev)(struct iommu_domain *, struct device *);
	int (*aux_get_pasid)(struct iommu_domain *, struct device *);
	struct iommu_sva * (*sva_bind)(struct device *, struct mm_struct *, void *);
	void (*sva_unbind)(struct iommu_sva *);
	int (*sva_get_pasid)(struct iommu_sva *);
	int (*page_response)(struct device *, struct iommu_fault_event *, struct iommu_page_response *);
	int (*cache_invalidate)(struct iommu_domain *, struct device *, struct iommu_cache_invalidate_info *);
	int (*sva_bind_gpasid)(struct iommu_domain *, struct device *, struct iommu_gpasid_bind_data *);
	int (*sva_unbind_gpasid)(struct device *, int);
	int (*def_domain_type)(struct device *);
	long unsigned int pgsize_bitmap;
	struct module *owner;
};

struct device_type {
	const char *name;
	const struct attribute_group **groups;
	int (*uevent)(struct device *, struct kobj_uevent_env *);
	char * (*devnode)(struct device *, umode_t *, kuid_t *, kgid_t *);
	void (*release)(struct device *);
	const struct dev_pm_ops *pm;
};

struct class {
	const char *name;
	struct module *owner;
	const struct attribute_group **class_groups;
	const struct attribute_group **dev_groups;
	struct kobject *dev_kobj;
	int (*dev_uevent)(struct device *, struct kobj_uevent_env *);
	char * (*devnode)(struct device *, umode_t *);
	void (*class_release)(struct class *);
	void (*dev_release)(struct device *);
	int (*shutdown_pre)(struct device *);
	const struct kobj_ns_type_operations *ns_type;
	const void * (*namespace)(struct device *);
	void (*get_ownership)(struct device *, kuid_t *, kgid_t *);
	const struct dev_pm_ops *pm;
	struct subsys_private *p;
};

struct of_device_id {
	char name[32];
	char type[32];
	char compatible[128];
	const void *data;
};

typedef long unsigned int kernel_ulong_t;

struct acpi_device_id {
	__u8 id[9];
	kernel_ulong_t driver_data;
	__u32 cls;
	__u32 cls_msk;
};

struct device_dma_parameters {
	unsigned int max_segment_size;
	long unsigned int segment_boundary_mask;
};

enum dma_data_direction {
	DMA_BIDIRECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
};

struct sg_table;

struct scatterlist;

struct dma_map_ops {
	void * (*alloc)(struct device *, size_t, dma_addr_t *, gfp_t, long unsigned int);
	void (*free)(struct device *, size_t, void *, dma_addr_t, long unsigned int);
	int (*mmap)(struct device *, struct vm_area_struct *, void *, dma_addr_t, size_t, long unsigned int);
	int (*get_sgtable)(struct device *, struct sg_table *, void *, dma_addr_t, size_t, long unsigned int);
	dma_addr_t (*map_page)(struct device *, struct page *, long unsigned int, size_t, enum dma_data_direction, long unsigned int);
	void (*unmap_page)(struct device *, dma_addr_t, size_t, enum dma_data_direction, long unsigned int);
	int (*map_sg)(struct device *, struct scatterlist *, int, enum dma_data_direction, long unsigned int);
	void (*unmap_sg)(struct device *, struct scatterlist *, int, enum dma_data_direction, long unsigned int);
	dma_addr_t (*map_resource)(struct device *, phys_addr_t, size_t, enum dma_data_direction, long unsigned int);
	void (*unmap_resource)(struct device *, dma_addr_t, size_t, enum dma_data_direction, long unsigned int);
	void (*sync_single_for_cpu)(struct device *, dma_addr_t, size_t, enum dma_data_direction);
	void (*sync_single_for_device)(struct device *, dma_addr_t, size_t, enum dma_data_direction);
	void (*sync_sg_for_cpu)(struct device *, struct scatterlist *, int, enum dma_data_direction);
	void (*sync_sg_for_device)(struct device *, struct scatterlist *, int, enum dma_data_direction);
	void (*cache_sync)(struct device *, void *, size_t, enum dma_data_direction);
	int (*dma_supported)(struct device *, u64);
	u64 (*get_required_mask)(struct device *);
	size_t (*max_mapping_size)(struct device *);
	long unsigned int (*get_merge_boundary)(struct device *);
};

struct node {
	struct device dev;
	struct list_head access_list;
};

enum cpuhp_smt_control {
	CPU_SMT_ENABLED = 0,
	CPU_SMT_DISABLED = 1,
	CPU_SMT_FORCE_DISABLED = 2,
	CPU_SMT_NOT_SUPPORTED = 3,
	CPU_SMT_NOT_IMPLEMENTED = 4,
};

struct cpu_signature {
	unsigned int sig;
	unsigned int pf;
	unsigned int rev;
};

struct ucode_cpu_info {
	struct cpu_signature cpu_sig;
	int valid;
	void *mc;
};

typedef long unsigned int pto_T__;

struct kobj_attribute___2;

struct file_system_type___2;

struct atomic_notifier_head___2;

typedef long unsigned int irq_hw_number_t;

struct kernel_symbol {
	int value_offset;
	int name_offset;
	int namespace_offset;
};

typedef int (*initcall_t)();

struct obs_kernel_param {
	const char *str;
	int (*setup_func)(char *);
	int early;
};

enum ftrace_dump_mode {
	DUMP_NONE = 0,
	DUMP_ALL = 1,
	DUMP_ORIG = 2,
};

struct bug_entry {
	int bug_addr_disp;
	int file_disp;
	short unsigned int line;
	short unsigned int flags;
};

struct pollfd {
	int fd;
	short int events;
	short int revents;
};

typedef const int tracepoint_ptr_t;

struct bpf_raw_event_map {
	struct tracepoint *tp;
	void *bpf_func;
	u32 num_args;
	u32 writable_size;
	long: 64;
};

struct orc_entry {
	s16 sp_offset;
	s16 bp_offset;
	unsigned int sp_reg: 4;
	unsigned int bp_reg: 4;
	unsigned int type: 2;
	unsigned int end: 1;
} __attribute__((packed));

enum perf_event_state {
	PERF_EVENT_STATE_DEAD = 4294967292,
	PERF_EVENT_STATE_EXIT = 4294967293,
	PERF_EVENT_STATE_ERROR = 4294967294,
	PERF_EVENT_STATE_OFF = 4294967295,
	PERF_EVENT_STATE_INACTIVE = 0,
	PERF_EVENT_STATE_ACTIVE = 1,
};

typedef struct {
	atomic_long_t a;
} local_t;

typedef struct {
	local_t a;
} local64_t;

struct perf_event_attr {
	__u32 type;
	__u32 size;
	__u64 config;
	union {
		__u64 sample_period;
		__u64 sample_freq;
	};
	__u64 sample_type;
	__u64 read_format;
	__u64 disabled: 1;
	__u64 inherit: 1;
	__u64 pinned: 1;
	__u64 exclusive: 1;
	__u64 exclude_user: 1;
	__u64 exclude_kernel: 1;
	__u64 exclude_hv: 1;
	__u64 exclude_idle: 1;
	__u64 mmap: 1;
	__u64 comm: 1;
	__u64 freq: 1;
	__u64 inherit_stat: 1;
	__u64 enable_on_exec: 1;
	__u64 task: 1;
	__u64 watermark: 1;
	__u64 precise_ip: 2;
	__u64 mmap_data: 1;
	__u64 sample_id_all: 1;
	__u64 exclude_host: 1;
	__u64 exclude_guest: 1;
	__u64 exclude_callchain_kernel: 1;
	__u64 exclude_callchain_user: 1;
	__u64 mmap2: 1;
	__u64 comm_exec: 1;
	__u64 use_clockid: 1;
	__u64 context_switch: 1;
	__u64 write_backward: 1;
	__u64 namespaces: 1;
	__u64 ksymbol: 1;
	__u64 bpf_event: 1;
	__u64 aux_output: 1;
	__u64 cgroup: 1;
	__u64 __reserved_1: 31;
	union {
		__u32 wakeup_events;
		__u32 wakeup_watermark;
	};
	__u32 bp_type;
	union {
		__u64 bp_addr;
		__u64 kprobe_func;
		__u64 uprobe_path;
		__u64 config1;
	};
	union {
		__u64 bp_len;
		__u64 kprobe_addr;
		__u64 probe_offset;
		__u64 config2;
	};
	__u64 branch_sample_type;
	__u64 sample_regs_user;
	__u32 sample_stack_user;
	__s32 clockid;
	__u64 sample_regs_intr;
	__u32 aux_watermark;
	__u16 sample_max_stack;
	__u16 __reserved_2;
	__u32 aux_sample_size;
	__u32 __reserved_3;
};

struct hw_perf_event_extra {
	u64 config;
	unsigned int reg;
	int alloc;
	int idx;
};

struct arch_hw_breakpoint {
	long unsigned int address;
	long unsigned int mask;
	u8 len;
	u8 type;
};

struct hw_perf_event {
	union {
		struct {
			u64 config;
			u64 last_tag;
			long unsigned int config_base;
			long unsigned int event_base;
			int event_base_rdpmc;
			int idx;
			int last_cpu;
			int flags;
			struct hw_perf_event_extra extra_reg;
			struct hw_perf_event_extra branch_reg;
		};
		struct {
			struct hrtimer hrtimer;
		};
		struct {
			struct list_head tp_list;
		};
		struct {
			u64 pwr_acc;
			u64 ptsc;
		};
		struct {
			struct arch_hw_breakpoint info;
			struct list_head bp_list;
		};
		struct {
			u8 iommu_bank;
			u8 iommu_cntr;
			u16 padding;
			u64 conf;
			u64 conf1;
		};
	};
	struct task_struct *target;
	void *addr_filters;
	long unsigned int addr_filters_gen;
	int state;
	local64_t prev_count;
	u64 sample_period;
	u64 last_period;
	local64_t period_left;
	u64 interrupts_seq;
	u64 interrupts;
	u64 freq_time_stamp;
	u64 freq_count_stamp;
};

struct irq_work {
	union {
		struct __call_single_node node;
		struct {
			struct llist_node llnode;
			atomic_t flags;
		};
	};
	void (*func)(struct irq_work *);
};

struct perf_addr_filters_head {
	struct list_head list;
	raw_spinlock_t lock;
	unsigned int nr_file_filters;
};

struct perf_sample_data;

typedef void (*perf_overflow_handler_t)(struct perf_event *, struct perf_sample_data *, struct pt_regs *);

struct pmu;

struct perf_buffer;

struct perf_addr_filter_range;

struct bpf_prog;

struct trace_event_call;

struct event_filter;

struct perf_event {
	struct list_head event_entry;
	struct list_head sibling_list;
	struct list_head active_list;
	struct rb_node group_node;
	u64 group_index;
	struct list_head migrate_entry;
	struct hlist_node hlist_entry;
	struct list_head active_entry;
	int nr_siblings;
	int event_caps;
	int group_caps;
	struct perf_event *group_leader;
	struct pmu *pmu;
	void *pmu_private;
	enum perf_event_state state;
	unsigned int attach_state;
	local64_t count;
	atomic64_t child_count;
	u64 total_time_enabled;
	u64 total_time_running;
	u64 tstamp;
	u64 shadow_ctx_time;
	struct perf_event_attr attr;
	u16 header_size;
	u16 id_header_size;
	u16 read_size;
	struct hw_perf_event hw;
	struct perf_event_context *ctx;
	atomic_long_t refcount;
	atomic64_t child_total_time_enabled;
	atomic64_t child_total_time_running;
	struct mutex child_mutex;
	struct list_head child_list;
	struct perf_event *parent;
	int oncpu;
	int cpu;
	struct list_head owner_entry;
	struct task_struct *owner;
	struct mutex mmap_mutex;
	atomic_t mmap_count;
	struct perf_buffer *rb;
	struct list_head rb_entry;
	long unsigned int rcu_batches;
	int rcu_pending;
	wait_queue_head_t waitq;
	struct fasync_struct *fasync;
	int pending_wakeup;
	int pending_kill;
	int pending_disable;
	struct irq_work pending;
	atomic_t event_limit;
	struct perf_addr_filters_head addr_filters;
	struct perf_addr_filter_range *addr_filter_ranges;
	long unsigned int addr_filters_gen;
	struct perf_event *aux_event;
	void (*destroy)(struct perf_event *);
	struct callback_head callback_head;
	struct pid_namespace *ns;
	u64 id;
	u64 (*clock)();
	perf_overflow_handler_t overflow_handler;
	void *overflow_handler_context;
	perf_overflow_handler_t orig_overflow_handler;
	struct bpf_prog *prog;
	struct trace_event_call *tp_event;
	struct event_filter *filter;
	void *security;
	struct list_head sb_list;
};

struct lockdep_map {};

struct uid_gid_extent {
	u32 first;
	u32 lower_first;
	u32 count;
};

struct uid_gid_map {
	u32 nr_extents;
	union {
		struct uid_gid_extent extent[5];
		struct {
			struct uid_gid_extent *forward;
			struct uid_gid_extent *reverse;
		};
	};
};

struct proc_ns_operations;

struct ns_common {
	atomic_long_t stashed;
	const struct proc_ns_operations *ops;
	unsigned int inum;
};

struct ctl_table_root;

struct ctl_table_set;

struct ctl_dir;

struct ctl_node;

struct ctl_table_header {
	union {
		struct {
			struct ctl_table *ctl_table;
			int used;
			int count;
			int nreg;
		};
		struct callback_head rcu;
	};
	struct completion *unregistering;
	struct ctl_table *ctl_table_arg;
	struct ctl_table_root *root;
	struct ctl_table_set *set;
	struct ctl_dir *parent;
	struct ctl_node *node;
	struct hlist_head inodes;
};

struct ctl_dir {
	struct ctl_table_header header;
	struct rb_root root;
};

struct ctl_table_set {
	int (*is_seen)(struct ctl_table_set *);
	struct ctl_dir dir;
};

struct ucounts;

struct user_namespace {
	struct uid_gid_map uid_map;
	struct uid_gid_map gid_map;
	struct uid_gid_map projid_map;
	atomic_t count;
	struct user_namespace *parent;
	int level;
	kuid_t owner;
	kgid_t group;
	struct ns_common ns;
	long unsigned int flags;
	struct list_head keyring_name_list;
	struct key *user_keyring_register;
	struct rw_semaphore keyring_sem;
	struct work_struct work;
	struct ctl_table_set set;
	struct ctl_table_header *sysctls;
	struct ucounts *ucounts;
	int ucount_max[10];
};

enum node_states {
	N_POSSIBLE = 0,
	N_ONLINE = 1,
	N_NORMAL_MEMORY = 2,
	N_HIGH_MEMORY = 2,
	N_MEMORY = 3,
	N_CPU = 4,
	NR_NODE_STATES = 5,
};

struct delayed_work {
	struct work_struct work;
	struct timer_list timer;
	struct workqueue_struct *wq;
	int cpu;
};

struct rcu_work {
	struct work_struct work;
	struct callback_head rcu;
	struct workqueue_struct *wq;
};

struct rcu_segcblist {
	struct callback_head *head;
	struct callback_head **tails[4];
	long unsigned int gp_seq[4];
	long int len;
	u8 enabled;
	u8 offloaded;
};

struct srcu_node;

struct srcu_struct;

struct srcu_data {
	long unsigned int srcu_lock_count[2];
	long unsigned int srcu_unlock_count[2];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t lock;
	struct rcu_segcblist srcu_cblist;
	long unsigned int srcu_gp_seq_needed;
	long unsigned int srcu_gp_seq_needed_exp;
	bool srcu_cblist_invoking;
	struct timer_list delay_work;
	struct work_struct work;
	struct callback_head srcu_barrier_head;
	struct srcu_node *mynode;
	long unsigned int grpmask;
	int cpu;
	struct srcu_struct *ssp;
	long: 64;
	long: 64;
};

struct srcu_node {
	spinlock_t lock;
	long unsigned int srcu_have_cbs[4];
	long unsigned int srcu_data_have_cbs[4];
	long unsigned int srcu_gp_seq_needed_exp;
	struct srcu_node *srcu_parent;
	int grplo;
	int grphi;
};

struct srcu_struct {
	struct srcu_node node[5];
	struct srcu_node *level[3];
	struct mutex srcu_cb_mutex;
	spinlock_t lock;
	struct mutex srcu_gp_mutex;
	unsigned int srcu_idx;
	long unsigned int srcu_gp_seq;
	long unsigned int srcu_gp_seq_needed;
	long unsigned int srcu_gp_seq_needed_exp;
	long unsigned int srcu_last_gp_end;
	struct srcu_data *sda;
	long unsigned int srcu_barrier_seq;
	struct mutex srcu_barrier_mutex;
	struct completion srcu_barrier_completion;
	atomic_t srcu_barrier_cpu_cnt;
	struct delayed_work work;
};

struct anon_vma {
	struct anon_vma *root;
	struct rw_semaphore rwsem;
	atomic_t refcount;
	unsigned int degree;
	struct anon_vma *parent;
	struct rb_root_cached rb_root;
};

struct mempolicy {
	atomic_t refcnt;
	short unsigned int mode;
	short unsigned int flags;
	union {
		short int preferred_node;
		nodemask_t nodes;
	} v;
	union {
		nodemask_t cpuset_mems_allowed;
		nodemask_t user_nodemask;
	} w;
};

struct linux_binprm;

struct coredump_params;

struct linux_binfmt {
	struct list_head lh;
	struct module *module;
	int (*load_binary)(struct linux_binprm *);
	int (*load_shlib)(struct file *);
	int (*core_dump)(struct coredump_params *);
	long unsigned int min_coredump;
};

typedef void (*smp_call_func_t)(void *);

struct __call_single_data {
	union {
		struct __call_single_node node;
		struct {
			struct llist_node llist;
			unsigned int flags;
		};
	};
	smp_call_func_t func;
	void *info;
};

struct ctl_node {
	struct rb_node node;
	struct ctl_table_header *header;
};

struct ctl_table_root {
	struct ctl_table_set default_set;
	struct ctl_table_set * (*lookup)(struct ctl_table_root *);
	void (*set_ownership)(struct ctl_table_header *, struct ctl_table *, kuid_t *, kgid_t *);
	int (*permissions)(struct ctl_table_header *, struct ctl_table *);
};

enum umh_disable_depth {
	UMH_ENABLED = 0,
	UMH_FREEZING = 1,
	UMH_DISABLED = 2,
};

struct va_alignment {
	int flags;
	long unsigned int mask;
	long unsigned int bits;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

typedef __u64 Elf64_Addr;

typedef __u16 Elf64_Half;

typedef __u32 Elf64_Word;

typedef __u64 Elf64_Xword;

typedef __s64 Elf64_Sxword;

typedef struct {
	Elf64_Sxword d_tag;
	union {
		Elf64_Xword d_val;
		Elf64_Addr d_ptr;
	} d_un;
} Elf64_Dyn;

struct elf64_sym {
	Elf64_Word st_name;
	unsigned char st_info;
	unsigned char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_Xword st_size;
};

typedef struct elf64_sym Elf64_Sym;

struct seq_file {
	char *buf;
	size_t size;
	size_t from;
	size_t count;
	size_t pad_until;
	loff_t index;
	loff_t read_pos;
	struct mutex lock;
	const struct seq_operations *op;
	int poll_event;
	const struct file *file;
	void *private;
};

typedef void (*poll_queue_proc)(struct file *, wait_queue_head_t *, struct poll_table_struct *);

struct poll_table_struct {
	poll_queue_proc _qproc;
	__poll_t _key;
};

struct kernel_param;

struct kernel_param_ops {
	unsigned int flags;
	int (*set)(const char *, const struct kernel_param *);
	int (*get)(char *, const struct kernel_param *);
	void (*free)(void *);
};

struct kparam_string;

struct kparam_array;

struct kernel_param {
	const char *name;
	struct module *mod;
	const struct kernel_param_ops *ops;
	const u16 perm;
	s8 level;
	u8 flags;
	union {
		void *arg;
		const struct kparam_string *str;
		const struct kparam_array *arr;
	};
};

struct kparam_string {
	unsigned int maxlen;
	char *string;
};

struct kparam_array {
	unsigned int max;
	unsigned int elemsize;
	unsigned int *num;
	const struct kernel_param_ops *ops;
	void *elem;
};

enum module_state {
	MODULE_STATE_LIVE = 0,
	MODULE_STATE_COMING = 1,
	MODULE_STATE_GOING = 2,
	MODULE_STATE_UNFORMED = 3,
};

struct module_param_attrs;

struct module_kobject {
	struct kobject kobj;
	struct module *mod;
	struct kobject *drivers_dir;
	struct module_param_attrs *mp;
	struct completion *kobj_completion;
};

struct latch_tree_node {
	struct rb_node node[2];
};

struct mod_tree_node {
	struct module *mod;
	struct latch_tree_node node;
};

struct module_layout {
	void *base;
	unsigned int size;
	unsigned int text_size;
	unsigned int ro_size;
	unsigned int ro_after_init_size;
	struct mod_tree_node mtn;
};

struct mod_arch_specific {
	unsigned int num_orcs;
	int *orc_unwind_ip;
	struct orc_entry *orc_unwind;
};

struct mod_kallsyms {
	Elf64_Sym *symtab;
	unsigned int num_symtab;
	char *strtab;
	char *typetab;
};

struct module_attribute;

struct exception_table_entry;

struct module_sect_attrs;

struct module_notes_attrs;

struct trace_eval_map;

struct error_injection_entry;

struct module {
	enum module_state state;
	struct list_head list;
	char name[56];
	struct module_kobject mkobj;
	struct module_attribute *modinfo_attrs;
	const char *version;
	const char *srcversion;
	struct kobject *holders_dir;
	const struct kernel_symbol *syms;
	const s32 *crcs;
	unsigned int num_syms;
	struct mutex param_lock;
	struct kernel_param *kp;
	unsigned int num_kp;
	unsigned int num_gpl_syms;
	const struct kernel_symbol *gpl_syms;
	const s32 *gpl_crcs;
	bool async_probe_requested;
	const struct kernel_symbol *gpl_future_syms;
	const s32 *gpl_future_crcs;
	unsigned int num_gpl_future_syms;
	unsigned int num_exentries;
	struct exception_table_entry *extable;
	int (*init)();
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct module_layout core_layout;
	struct module_layout init_layout;
	struct mod_arch_specific arch;
	long unsigned int taints;
	unsigned int num_bugs;
	struct list_head bug_list;
	struct bug_entry *bug_table;
	struct mod_kallsyms *kallsyms;
	struct mod_kallsyms core_kallsyms;
	struct module_sect_attrs *sect_attrs;
	struct module_notes_attrs *notes_attrs;
	char *args;
	void *percpu;
	unsigned int percpu_size;
	void *noinstr_text_start;
	unsigned int noinstr_text_size;
	unsigned int num_tracepoints;
	tracepoint_ptr_t *tracepoints_ptrs;
	unsigned int num_srcu_structs;
	struct srcu_struct **srcu_struct_ptrs;
	unsigned int num_bpf_raw_events;
	struct bpf_raw_event_map *bpf_raw_events;
	struct jump_entry *jump_entries;
	unsigned int num_jump_entries;
	unsigned int num_trace_bprintk_fmt;
	const char **trace_bprintk_fmt_start;
	struct trace_event_call **trace_events;
	unsigned int num_trace_events;
	struct trace_eval_map **trace_evals;
	unsigned int num_trace_evals;
	void *kprobes_text_start;
	unsigned int kprobes_text_size;
	long unsigned int *kprobe_blacklist;
	unsigned int num_kprobe_blacklist;
	struct list_head source_list;
	struct list_head target_list;
	void (*exit)();
	atomic_t refcnt;
	struct error_injection_entry *ei_funcs;
	unsigned int num_ei_funcs;
};

struct error_injection_entry {
	long unsigned int addr;
	int etype;
};

struct module_attribute {
	struct attribute attr;
	ssize_t (*show)(struct module_attribute *, struct module_kobject *, char *);
	ssize_t (*store)(struct module_attribute *, struct module_kobject *, const char *, size_t);
	void (*setup)(struct module *, const char *);
	int (*test)(struct module *);
	void (*free)(struct module *);
};

struct exception_table_entry {
	int insn;
	int fixup;
	int handler;
};

struct trace_event_functions;

struct trace_event {
	struct hlist_node node;
	struct list_head list;
	int type;
	struct trace_event_functions *funcs;
};

struct trace_event_class;

struct bpf_prog_array;

struct trace_event_call {
	struct list_head list;
	struct trace_event_class *class;
	union {
		char *name;
		struct tracepoint *tp;
	};
	struct trace_event event;
	char *print_fmt;
	struct event_filter *filter;
	void *mod;
	void *data;
	int flags;
	int perf_refcount;
	struct hlist_head *perf_events;
	struct bpf_prog_array *prog_array;
	int (*perf_perm)(struct trace_event_call *, struct perf_event *);
};

struct trace_eval_map {
	const char *system;
	const char *eval_string;
	long unsigned int eval_value;
};

struct fs_pin;

struct pid_namespace {
	struct kref kref;
	struct idr idr;
	struct callback_head rcu;
	unsigned int pid_allocated;
	struct task_struct *child_reaper;
	struct kmem_cache *pid_cachep;
	unsigned int level;
	struct pid_namespace *parent;
	struct fs_pin *bacct;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	int reboot;
	struct ns_common ns;
};

struct task_cputime {
	u64 stime;
	u64 utime;
	long long unsigned int sum_exec_runtime;
};

struct uts_namespace;

struct ipc_namespace;

struct mnt_namespace;

struct net;

struct time_namespace;

struct cgroup_namespace;

struct nsproxy {
	atomic_t count;
	struct uts_namespace *uts_ns;
	struct ipc_namespace *ipc_ns;
	struct mnt_namespace *mnt_ns;
	struct pid_namespace *pid_ns_for_children;
	struct net *net_ns;
	struct time_namespace *time_ns;
	struct time_namespace *time_ns_for_children;
	struct cgroup_namespace *cgroup_ns;
};

struct bio;

struct bio_list {
	struct bio *head;
	struct bio *tail;
};

struct blk_plug {
	struct list_head mq_list;
	struct list_head cb_list;
	short unsigned int rq_count;
	bool multiple_queues;
};

struct reclaim_state {
	long unsigned int reclaimed_slab;
};

typedef int congested_fn(void *, int);

struct fprop_local_percpu {
	struct percpu_counter events;
	unsigned int period;
	raw_spinlock_t lock;
};

enum wb_reason {
	WB_REASON_BACKGROUND = 0,
	WB_REASON_VMSCAN = 1,
	WB_REASON_SYNC = 2,
	WB_REASON_PERIODIC = 3,
	WB_REASON_LAPTOP_TIMER = 4,
	WB_REASON_FS_FREE_SPACE = 5,
	WB_REASON_FORKER_THREAD = 6,
	WB_REASON_FOREIGN_FLUSH = 7,
	WB_REASON_MAX = 8,
};

struct bdi_writeback_congested;

struct bdi_writeback {
	struct backing_dev_info *bdi;
	long unsigned int state;
	long unsigned int last_old_flush;
	struct list_head b_dirty;
	struct list_head b_io;
	struct list_head b_more_io;
	struct list_head b_dirty_time;
	spinlock_t list_lock;
	struct percpu_counter stat[4];
	struct bdi_writeback_congested *congested;
	long unsigned int bw_time_stamp;
	long unsigned int dirtied_stamp;
	long unsigned int written_stamp;
	long unsigned int write_bandwidth;
	long unsigned int avg_write_bandwidth;
	long unsigned int dirty_ratelimit;
	long unsigned int balanced_dirty_ratelimit;
	struct fprop_local_percpu completions;
	int dirty_exceeded;
	enum wb_reason start_all_reason;
	spinlock_t work_lock;
	struct list_head work_list;
	struct delayed_work dwork;
	long unsigned int dirty_sleep;
	struct list_head bdi_node;
};

struct backing_dev_info {
	u64 id;
	struct rb_node rb_node;
	struct list_head bdi_list;
	long unsigned int ra_pages;
	long unsigned int io_pages;
	congested_fn *congested_fn;
	void *congested_data;
	struct kref refcnt;
	unsigned int capabilities;
	unsigned int min_ratio;
	unsigned int max_ratio;
	unsigned int max_prop_frac;
	atomic_long_t tot_write_bandwidth;
	struct bdi_writeback wb;
	struct list_head wb_list;
	struct bdi_writeback_congested *wb_congested;
	wait_queue_head_t wb_waitq;
	struct device *dev;
	char dev_name[64];
	struct device *owner;
	struct timer_list laptop_mode_wb_timer;
	struct dentry *debug_dir;
};

struct cgroup_subsys_state;

struct cgroup;

struct css_set {
	struct cgroup_subsys_state *subsys[4];
	refcount_t refcount;
	struct css_set *dom_cset;
	struct cgroup *dfl_cgrp;
	int nr_tasks;
	struct list_head tasks;
	struct list_head mg_tasks;
	struct list_head dying_tasks;
	struct list_head task_iters;
	struct list_head e_cset_node[4];
	struct list_head threaded_csets;
	struct list_head threaded_csets_node;
	struct hlist_node hlist;
	struct list_head cgrp_links;
	struct list_head mg_preload_node;
	struct list_head mg_node;
	struct cgroup *mg_src_cgrp;
	struct cgroup *mg_dst_cgrp;
	struct css_set *mg_dst_cset;
	bool dead;
	struct callback_head callback_head;
};

struct perf_event_groups {
	struct rb_root tree;
	u64 index;
};

struct perf_event_context {
	struct pmu *pmu;
	raw_spinlock_t lock;
	struct mutex mutex;
	struct list_head active_ctx_list;
	struct perf_event_groups pinned_groups;
	struct perf_event_groups flexible_groups;
	struct list_head event_list;
	struct list_head pinned_active;
	struct list_head flexible_active;
	int nr_events;
	int nr_active;
	int is_active;
	int nr_stat;
	int nr_freq;
	int rotate_disable;
	int rotate_necessary;
	refcount_t refcount;
	struct task_struct *task;
	u64 time;
	u64 timestamp;
	struct perf_event_context *parent_ctx;
	u64 parent_gen;
	u64 generation;
	int pin_count;
	void *task_ctx_data;
	struct callback_head callback_head;
};

struct task_delay_info {
	raw_spinlock_t lock;
	unsigned int flags;
	u64 blkio_start;
	u64 blkio_delay;
	u64 swapin_delay;
	u32 blkio_count;
	u32 swapin_count;
	u64 freepages_start;
	u64 freepages_delay;
	u64 thrashing_start;
	u64 thrashing_delay;
	u32 freepages_count;
	u32 thrashing_count;
};

struct cgroup_subsys;

struct cgroup_subsys_state {
	struct cgroup *cgroup;
	struct cgroup_subsys *ss;
	struct percpu_ref refcnt;
	struct list_head sibling;
	struct list_head children;
	struct list_head rstat_css_node;
	int id;
	unsigned int flags;
	u64 serial_nr;
	atomic_t online_cnt;
	struct work_struct destroy_work;
	struct rcu_work destroy_rwork;
	struct cgroup_subsys_state *parent;
};

struct cgroup_file {
	struct kernfs_node *kn;
	long unsigned int notified_at;
	struct timer_list notify_timer;
};

struct cgroup_base_stat {
	struct task_cputime cputime;
};

struct psi_group {};

struct cgroup_bpf {
	struct bpf_prog_array *effective[34];
	struct list_head progs[34];
	u32 flags[34];
	struct bpf_prog_array *inactive;
	struct percpu_ref refcnt;
	struct work_struct release_work;
};

struct cgroup_freezer_state {
	bool freeze;
	int e_freeze;
	int nr_frozen_descendants;
	int nr_frozen_tasks;
};

struct cgroup_root;

struct cgroup_rstat_cpu;

struct cgroup {
	struct cgroup_subsys_state self;
	long unsigned int flags;
	int level;
	int max_depth;
	int nr_descendants;
	int nr_dying_descendants;
	int max_descendants;
	int nr_populated_csets;
	int nr_populated_domain_children;
	int nr_populated_threaded_children;
	int nr_threaded_children;
	struct kernfs_node *kn;
	struct cgroup_file procs_file;
	struct cgroup_file events_file;
	u16 subtree_control;
	u16 subtree_ss_mask;
	u16 old_subtree_control;
	u16 old_subtree_ss_mask;
	struct cgroup_subsys_state *subsys[4];
	struct cgroup_root *root;
	struct list_head cset_links;
	struct list_head e_csets[4];
	struct cgroup *dom_cgrp;
	struct cgroup *old_dom_cgrp;
	struct cgroup_rstat_cpu *rstat_cpu;
	struct list_head rstat_css_list;
	struct cgroup_base_stat last_bstat;
	struct cgroup_base_stat bstat;
	struct prev_cputime prev_cputime;
	struct list_head pidlists;
	struct mutex pidlist_mutex;
	wait_queue_head_t offline_waitq;
	struct work_struct release_agent_work;
	struct psi_group psi;
	struct cgroup_bpf bpf;
	atomic_t congestion_count;
	struct cgroup_freezer_state freezer;
	u64 ancestor_ids[0];
};

struct taskstats {
	__u16 version;
	__u32 ac_exitcode;
	__u8 ac_flag;
	__u8 ac_nice;
	__u64 cpu_count;
	__u64 cpu_delay_total;
	__u64 blkio_count;
	__u64 blkio_delay_total;
	__u64 swapin_count;
	__u64 swapin_delay_total;
	__u64 cpu_run_real_total;
	__u64 cpu_run_virtual_total;
	char ac_comm[32];
	__u8 ac_sched;
	__u8 ac_pad[3];
	int: 32;
	__u32 ac_uid;
	__u32 ac_gid;
	__u32 ac_pid;
	__u32 ac_ppid;
	__u32 ac_btime;
	__u64 ac_etime;
	__u64 ac_utime;
	__u64 ac_stime;
	__u64 ac_minflt;
	__u64 ac_majflt;
	__u64 coremem;
	__u64 virtmem;
	__u64 hiwater_rss;
	__u64 hiwater_vm;
	__u64 read_char;
	__u64 write_char;
	__u64 read_syscalls;
	__u64 write_syscalls;
	__u64 read_bytes;
	__u64 write_bytes;
	__u64 cancelled_write_bytes;
	__u64 nvcsw;
	__u64 nivcsw;
	__u64 ac_utimescaled;
	__u64 ac_stimescaled;
	__u64 cpu_scaled_run_real_total;
	__u64 freepages_count;
	__u64 freepages_delay_total;
	__u64 thrashing_count;
	__u64 thrashing_delay_total;
	__u64 ac_btime64;
};

typedef unsigned int blk_qc_t;

typedef blk_qc_t make_request_fn(struct request_queue *, struct bio *);

struct blk_rq_stat {
	u64 mean;
	u64 min;
	u64 max;
	u32 nr_samples;
	u64 batch;
};

enum blk_zoned_model {
	BLK_ZONED_NONE = 0,
	BLK_ZONED_HA = 1,
	BLK_ZONED_HM = 2,
};

struct queue_limits {
	long unsigned int bounce_pfn;
	long unsigned int seg_boundary_mask;
	long unsigned int virt_boundary_mask;
	unsigned int max_hw_sectors;
	unsigned int max_dev_sectors;
	unsigned int chunk_sectors;
	unsigned int max_sectors;
	unsigned int max_segment_size;
	unsigned int physical_block_size;
	unsigned int logical_block_size;
	unsigned int alignment_offset;
	unsigned int io_min;
	unsigned int io_opt;
	unsigned int max_discard_sectors;
	unsigned int max_hw_discard_sectors;
	unsigned int max_write_same_sectors;
	unsigned int max_write_zeroes_sectors;
	unsigned int max_zone_append_sectors;
	unsigned int discard_granularity;
	unsigned int discard_alignment;
	short unsigned int max_segments;
	short unsigned int max_integrity_segments;
	short unsigned int max_discard_segments;
	unsigned char misaligned;
	unsigned char discard_misaligned;
	unsigned char raid_partial_stripes_expensive;
	enum blk_zoned_model zoned;
};

struct bsg_ops;

struct bsg_class_device {
	struct device *class_dev;
	int minor;
	struct request_queue *queue;
	const struct bsg_ops *ops;
};

typedef void *mempool_alloc_t(gfp_t, void *);

typedef void mempool_free_t(void *, void *);

struct mempool_s {
	spinlock_t lock;
	int min_nr;
	int curr_nr;
	void **elements;
	void *pool_data;
	mempool_alloc_t *alloc;
	mempool_free_t *free;
	wait_queue_head_t wait;
};

typedef struct mempool_s mempool_t;

struct bio_set {
	struct kmem_cache *bio_slab;
	unsigned int front_pad;
	mempool_t bio_pool;
	mempool_t bvec_pool;
	spinlock_t rescue_lock;
	struct bio_list rescue_list;
	struct work_struct rescue_work;
	struct workqueue_struct *rescue_workqueue;
};

struct request;

struct elevator_queue;

struct blk_queue_stats;

struct rq_qos;

struct blk_mq_ops;

struct blk_mq_ctx;

struct blk_mq_hw_ctx;

struct blk_stat_callback;

struct blk_trace;

struct blk_flush_queue;

struct blk_mq_tag_set;

struct request_queue {
	struct request *last_merge;
	struct elevator_queue *elevator;
	struct blk_queue_stats *stats;
	struct rq_qos *rq_qos;
	make_request_fn *make_request_fn;
	const struct blk_mq_ops *mq_ops;
	struct blk_mq_ctx *queue_ctx;
	unsigned int queue_depth;
	struct blk_mq_hw_ctx **queue_hw_ctx;
	unsigned int nr_hw_queues;
	struct backing_dev_info *backing_dev_info;
	void *queuedata;
	long unsigned int queue_flags;
	atomic_t pm_only;
	int id;
	gfp_t bounce_gfp;
	spinlock_t queue_lock;
	struct kobject kobj;
	struct kobject *mq_kobj;
	struct device *dev;
	int rpm_status;
	unsigned int nr_pending;
	long unsigned int nr_requests;
	unsigned int dma_pad_mask;
	unsigned int dma_alignment;
	unsigned int rq_timeout;
	int poll_nsec;
	struct blk_stat_callback *poll_cb;
	struct blk_rq_stat poll_stat[16];
	struct timer_list timeout;
	struct work_struct timeout_work;
	struct list_head icq_list;
	struct queue_limits limits;
	unsigned int required_elevator_features;
	unsigned int sg_timeout;
	unsigned int sg_reserved_size;
	int node;
	struct blk_trace *blk_trace;
	struct mutex blk_trace_mutex;
	struct blk_flush_queue *fq;
	struct list_head requeue_list;
	spinlock_t requeue_lock;
	struct delayed_work requeue_work;
	struct mutex sysfs_lock;
	struct mutex sysfs_dir_lock;
	struct list_head unused_hctx_list;
	spinlock_t unused_hctx_lock;
	int mq_freeze_depth;
	struct bsg_class_device bsg_dev;
	struct callback_head callback_head;
	wait_queue_head_t mq_freeze_wq;
	struct mutex mq_freeze_lock;
	struct percpu_ref q_usage_counter;
	struct blk_mq_tag_set *tag_set;
	struct list_head tag_set_list;
	struct bio_set bio_split;
	struct dentry *debugfs_dir;
	struct dentry *sched_debugfs_dir;
	struct dentry *rqos_debugfs_dir;
	bool mq_sysfs_init_done;
	size_t cmd_size;
	struct work_struct release_work;
	u64 write_hints[5];
};

enum writeback_sync_modes {
	WB_SYNC_NONE = 0,
	WB_SYNC_ALL = 1,
};

struct writeback_control {
	long int nr_to_write;
	long int pages_skipped;
	loff_t range_start;
	loff_t range_end;
	enum writeback_sync_modes sync_mode;
	unsigned int for_kupdate: 1;
	unsigned int for_background: 1;
	unsigned int tagged_writepages: 1;
	unsigned int for_reclaim: 1;
	unsigned int range_cyclic: 1;
	unsigned int for_sync: 1;
	unsigned int no_cgroup_owner: 1;
	unsigned int punt_to_cgroup: 1;
};

struct readahead_control {
	struct file *file;
	struct address_space *mapping;
	long unsigned int _index;
	unsigned int _nr_pages;
	unsigned int _batch_count;
};

struct swap_cluster_info {
	spinlock_t lock;
	unsigned int data: 24;
	unsigned int flags: 8;
};

struct swap_cluster_list {
	struct swap_cluster_info head;
	struct swap_cluster_info tail;
};

struct percpu_cluster;

struct swap_info_struct {
	long unsigned int flags;
	short int prio;
	struct plist_node list;
	signed char type;
	unsigned int max;
	unsigned char *swap_map;
	struct swap_cluster_info *cluster_info;
	struct swap_cluster_list free_clusters;
	unsigned int lowest_bit;
	unsigned int highest_bit;
	unsigned int pages;
	unsigned int inuse_pages;
	unsigned int cluster_next;
	unsigned int cluster_nr;
	unsigned int *cluster_next_cpu;
	struct percpu_cluster *percpu_cluster;
	struct rb_root swap_extent_root;
	struct block_device *bdev;
	struct file *swap_file;
	unsigned int old_block_size;
	spinlock_t lock;
	spinlock_t cont_lock;
	struct work_struct discard_work;
	struct swap_cluster_list discard_clusters;
	struct plist_node avail_lists[0];
};

struct disk_stats;

struct partition_meta_info;

struct hd_struct {
	sector_t start_sect;
	sector_t nr_sects;
	long unsigned int stamp;
	struct disk_stats *dkstats;
	struct percpu_ref ref;
	sector_t alignment_offset;
	unsigned int discard_alignment;
	struct device __dev;
	struct kobject *holder_dir;
	int policy;
	int partno;
	struct partition_meta_info *info;
	struct rcu_work rcu_work;
};

struct disk_part_tbl;

struct block_device_operations;

struct timer_rand_state;

struct disk_events;

struct cdrom_device_info;

struct badblocks;

struct gendisk {
	int major;
	int first_minor;
	int minors;
	char disk_name[32];
	short unsigned int events;
	short unsigned int event_flags;
	struct disk_part_tbl *part_tbl;
	struct hd_struct part0;
	const struct block_device_operations *fops;
	struct request_queue *queue;
	void *private_data;
	int flags;
	struct rw_semaphore lookup_sem;
	struct kobject *slave_dir;
	struct timer_rand_state *random;
	atomic_t sync_io;
	struct disk_events *ev;
	struct cdrom_device_info *cdi;
	int node_id;
	struct badblocks *bb;
	struct lockdep_map lockdep_map;
};

struct cdev {
	struct kobject kobj;
	struct module *owner;
	const struct file_operations *ops;
	struct list_head list;
	dev_t dev;
	unsigned int count;
};

struct fc_log;

struct p_log {
	const char *prefix;
	struct fc_log *log;
};

enum fs_context_purpose {
	FS_CONTEXT_FOR_MOUNT = 0,
	FS_CONTEXT_FOR_SUBMOUNT = 1,
	FS_CONTEXT_FOR_RECONFIGURE = 2,
};

enum fs_context_phase {
	FS_CONTEXT_CREATE_PARAMS = 0,
	FS_CONTEXT_CREATING = 1,
	FS_CONTEXT_AWAITING_MOUNT = 2,
	FS_CONTEXT_AWAITING_RECONF = 3,
	FS_CONTEXT_RECONF_PARAMS = 4,
	FS_CONTEXT_RECONFIGURING = 5,
	FS_CONTEXT_FAILED = 6,
};

struct fs_context_operations;

struct fs_context {
	const struct fs_context_operations *ops;
	struct mutex uapi_mutex;
	struct file_system_type *fs_type;
	void *fs_private;
	void *sget_key;
	struct dentry *root;
	struct user_namespace *user_ns;
	struct net *net_ns;
	const struct cred *cred;
	struct p_log log;
	const char *source;
	void *security;
	void *s_fs_info;
	unsigned int sb_flags;
	unsigned int sb_flags_mask;
	unsigned int s_iflags;
	unsigned int lsm_flags;
	enum fs_context_purpose purpose: 8;
	enum fs_context_phase phase: 8;
	bool need_free: 1;
	bool global: 1;
	bool oldapi: 1;
};

struct audit_names;

struct filename {
	const char *name;
	const char *uptr;
	int refcnt;
	struct audit_names *aname;
	const char iname[0];
};

typedef u8 blk_status_t;

struct bvec_iter {
	sector_t bi_sector;
	unsigned int bi_size;
	unsigned int bi_idx;
	unsigned int bi_bvec_done;
};

typedef void bio_end_io_t(struct bio *);

struct bio_vec {
	struct page *bv_page;
	unsigned int bv_len;
	unsigned int bv_offset;
};

struct bio {
	struct bio *bi_next;
	struct gendisk *bi_disk;
	unsigned int bi_opf;
	short unsigned int bi_flags;
	short unsigned int bi_ioprio;
	short unsigned int bi_write_hint;
	blk_status_t bi_status;
	u8 bi_partno;
	atomic_t __bi_remaining;
	struct bvec_iter bi_iter;
	bio_end_io_t *bi_end_io;
	void *bi_private;
	union {	};
	short unsigned int bi_vcnt;
	short unsigned int bi_max_vecs;
	atomic_t __bi_cnt;
	struct bio_vec *bi_io_vec;
	struct bio_set *bi_pool;
	struct bio_vec bi_inline_vecs[0];
};

struct linux_binprm {
	struct vm_area_struct *vma;
	long unsigned int vma_pages;
	struct mm_struct *mm;
	long unsigned int p;
	long unsigned int argmin;
	unsigned int have_execfd: 1;
	unsigned int execfd_creds: 1;
	unsigned int secureexec: 1;
	unsigned int point_of_no_return: 1;
	struct file *executable;
	struct file *interpreter;
	struct file *file;
	struct cred *cred;
	int unsafe;
	unsigned int per_clear;
	int argc;
	int envc;
	const char *filename;
	const char *interp;
	unsigned int interp_flags;
	int execfd;
	long unsigned int loader;
	long unsigned int exec;
	struct rlimit rlim_stack;
	char buf[256];
};

struct coredump_params {
	const kernel_siginfo_t *siginfo;
	struct pt_regs *regs;
	struct file *file;
	long unsigned int limit;
	long unsigned int mm_flags;
	loff_t written;
	loff_t pos;
};

struct ring_buffer_event {
	u32 type_len: 5;
	u32 time_delta: 27;
	u32 array[0];
};

struct seq_buf {
	char *buffer;
	size_t size;
	size_t len;
	loff_t readpos;
};

struct trace_seq {
	unsigned char buffer[4096];
	struct seq_buf seq;
	int full;
};

enum perf_sw_ids {
	PERF_COUNT_SW_CPU_CLOCK = 0,
	PERF_COUNT_SW_TASK_CLOCK = 1,
	PERF_COUNT_SW_PAGE_FAULTS = 2,
	PERF_COUNT_SW_CONTEXT_SWITCHES = 3,
	PERF_COUNT_SW_CPU_MIGRATIONS = 4,
	PERF_COUNT_SW_PAGE_FAULTS_MIN = 5,
	PERF_COUNT_SW_PAGE_FAULTS_MAJ = 6,
	PERF_COUNT_SW_ALIGNMENT_FAULTS = 7,
	PERF_COUNT_SW_EMULATION_FAULTS = 8,
	PERF_COUNT_SW_DUMMY = 9,
	PERF_COUNT_SW_BPF_OUTPUT = 10,
	PERF_COUNT_SW_MAX = 11,
};

union perf_mem_data_src {
	__u64 val;
	struct {
		__u64 mem_op: 5;
		__u64 mem_lvl: 14;
		__u64 mem_snoop: 5;
		__u64 mem_lock: 2;
		__u64 mem_dtlb: 7;
		__u64 mem_lvl_num: 4;
		__u64 mem_remote: 1;
		__u64 mem_snoopx: 2;
		__u64 mem_rsvd: 24;
	};
};

struct perf_branch_entry {
	__u64 from;
	__u64 to;
	__u64 mispred: 1;
	__u64 predicted: 1;
	__u64 in_tx: 1;
	__u64 abort: 1;
	__u64 cycles: 16;
	__u64 type: 4;
	__u64 reserved: 40;
};

struct new_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
	char domainname[65];
};

struct uts_namespace {
	struct kref kref;
	struct new_utsname name;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct ns_common ns;
};

struct cgroup_namespace {
	refcount_t count;
	struct ns_common ns;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct css_set *root_cset;
};

struct nsset {
	unsigned int flags;
	struct nsproxy *nsproxy;
	struct fs_struct *fs;
	const struct cred *cred;
};

struct proc_ns_operations {
	const char *name;
	const char *real_ns_name;
	int type;
	struct ns_common * (*get)(struct task_struct *);
	void (*put)(struct ns_common *);
	int (*install)(struct nsset *, struct ns_common *);
	struct user_namespace * (*owner)(struct ns_common *);
	struct ns_common * (*get_parent)(struct ns_common *);
};

struct ucounts {
	struct hlist_node node;
	struct user_namespace *ns;
	kuid_t uid;
	int count;
	atomic_t ucount[10];
};

struct perf_guest_info_callbacks {
	int (*is_in_guest)();
	int (*is_user_mode)();
	long unsigned int (*get_guest_ip)();
	void (*handle_intel_pt_intr)();
};

struct perf_cpu_context;

struct perf_output_handle;

struct pmu {
	struct list_head entry;
	struct module *module;
	struct device *dev;
	const struct attribute_group **attr_groups;
	const struct attribute_group **attr_update;
	const char *name;
	int type;
	int capabilities;
	int *pmu_disable_count;
	struct perf_cpu_context *pmu_cpu_context;
	atomic_t exclusive_cnt;
	int task_ctx_nr;
	int hrtimer_interval_ms;
	unsigned int nr_addr_filters;
	void (*pmu_enable)(struct pmu *);
	void (*pmu_disable)(struct pmu *);
	int (*event_init)(struct perf_event *);
	void (*event_mapped)(struct perf_event *, struct mm_struct *);
	void (*event_unmapped)(struct perf_event *, struct mm_struct *);
	int (*add)(struct perf_event *, int);
	void (*del)(struct perf_event *, int);
	void (*start)(struct perf_event *, int);
	void (*stop)(struct perf_event *, int);
	void (*read)(struct perf_event *);
	void (*start_txn)(struct pmu *, unsigned int);
	int (*commit_txn)(struct pmu *);
	void (*cancel_txn)(struct pmu *);
	int (*event_idx)(struct perf_event *);
	void (*sched_task)(struct perf_event_context *, bool);
	size_t task_ctx_size;
	void (*swap_task_ctx)(struct perf_event_context *, struct perf_event_context *);
	void * (*setup_aux)(struct perf_event *, void **, int, bool);
	void (*free_aux)(void *);
	long int (*snapshot_aux)(struct perf_event *, struct perf_output_handle *, long unsigned int);
	int (*addr_filters_validate)(struct list_head *);
	void (*addr_filters_sync)(struct perf_event *);
	int (*aux_output_match)(struct perf_event *);
	int (*filter_match)(struct perf_event *);
	int (*check_period)(struct perf_event *, u64);
};

enum irq_domain_bus_token {
	DOMAIN_BUS_ANY = 0,
	DOMAIN_BUS_WIRED = 1,
	DOMAIN_BUS_GENERIC_MSI = 2,
	DOMAIN_BUS_PCI_MSI = 3,
	DOMAIN_BUS_PLATFORM_MSI = 4,
	DOMAIN_BUS_NEXUS = 5,
	DOMAIN_BUS_IPI = 6,
	DOMAIN_BUS_FSL_MC_MSI = 7,
	DOMAIN_BUS_TI_SCI_INTA_MSI = 8,
	DOMAIN_BUS_WAKEUP = 9,
};

struct irq_domain_ops;

struct irq_domain_chip_generic;

struct irq_domain {
	struct list_head link;
	const char *name;
	const struct irq_domain_ops *ops;
	void *host_data;
	unsigned int flags;
	unsigned int mapcount;
	struct fwnode_handle *fwnode;
	enum irq_domain_bus_token bus_token;
	struct irq_domain_chip_generic *gc;
	struct irq_domain *parent;
	irq_hw_number_t hwirq_max;
	unsigned int revmap_direct_max_irq;
	unsigned int revmap_size;
	struct xarray revmap_tree;
	struct mutex revmap_tree_mutex;
	unsigned int linear_revmap[0];
};

typedef u32 phandle;

struct property;

struct device_node {
	const char *name;
	phandle phandle;
	const char *full_name;
	struct fwnode_handle fwnode;
	struct property *properties;
	struct property *deadprops;
	struct device_node *parent;
	struct device_node *child;
	struct device_node *sibling;
	long unsigned int _flags;
	void *data;
};

enum cpuhp_state {
	CPUHP_INVALID = 4294967295,
	CPUHP_OFFLINE = 0,
	CPUHP_CREATE_THREADS = 1,
	CPUHP_PERF_PREPARE = 2,
	CPUHP_PERF_X86_PREPARE = 3,
	CPUHP_PERF_X86_AMD_UNCORE_PREP = 4,
	CPUHP_PERF_POWER = 5,
	CPUHP_PERF_SUPERH = 6,
	CPUHP_X86_HPET_DEAD = 7,
	CPUHP_X86_APB_DEAD = 8,
	CPUHP_X86_MCE_DEAD = 9,
	CPUHP_VIRT_NET_DEAD = 10,
	CPUHP_SLUB_DEAD = 11,
	CPUHP_MM_WRITEBACK_DEAD = 12,
	CPUHP_MM_VMSTAT_DEAD = 13,
	CPUHP_SOFTIRQ_DEAD = 14,
	CPUHP_NET_MVNETA_DEAD = 15,
	CPUHP_CPUIDLE_DEAD = 16,
	CPUHP_ARM64_FPSIMD_DEAD = 17,
	CPUHP_ARM_OMAP_WAKE_DEAD = 18,
	CPUHP_IRQ_POLL_DEAD = 19,
	CPUHP_BLOCK_SOFTIRQ_DEAD = 20,
	CPUHP_ACPI_CPUDRV_DEAD = 21,
	CPUHP_S390_PFAULT_DEAD = 22,
	CPUHP_BLK_MQ_DEAD = 23,
	CPUHP_FS_BUFF_DEAD = 24,
	CPUHP_PRINTK_DEAD = 25,
	CPUHP_MM_MEMCQ_DEAD = 26,
	CPUHP_PERCPU_CNT_DEAD = 27,
	CPUHP_RADIX_DEAD = 28,
	CPUHP_PAGE_ALLOC_DEAD = 29,
	CPUHP_NET_DEV_DEAD = 30,
	CPUHP_PCI_XGENE_DEAD = 31,
	CPUHP_IOMMU_INTEL_DEAD = 32,
	CPUHP_LUSTRE_CFS_DEAD = 33,
	CPUHP_AP_ARM_CACHE_B15_RAC_DEAD = 34,
	CPUHP_PADATA_DEAD = 35,
	CPUHP_WORKQUEUE_PREP = 36,
	CPUHP_POWER_NUMA_PREPARE = 37,
	CPUHP_HRTIMERS_PREPARE = 38,
	CPUHP_PROFILE_PREPARE = 39,
	CPUHP_X2APIC_PREPARE = 40,
	CPUHP_SMPCFD_PREPARE = 41,
	CPUHP_RELAY_PREPARE = 42,
	CPUHP_SLAB_PREPARE = 43,
	CPUHP_MD_RAID5_PREPARE = 44,
	CPUHP_RCUTREE_PREP = 45,
	CPUHP_CPUIDLE_COUPLED_PREPARE = 46,
	CPUHP_POWERPC_PMAC_PREPARE = 47,
	CPUHP_POWERPC_MMU_CTX_PREPARE = 48,
	CPUHP_XEN_PREPARE = 49,
	CPUHP_XEN_EVTCHN_PREPARE = 50,
	CPUHP_ARM_SHMOBILE_SCU_PREPARE = 51,
	CPUHP_SH_SH3X_PREPARE = 52,
	CPUHP_NET_FLOW_PREPARE = 53,
	CPUHP_TOPOLOGY_PREPARE = 54,
	CPUHP_NET_IUCV_PREPARE = 55,
	CPUHP_ARM_BL_PREPARE = 56,
	CPUHP_TRACE_RB_PREPARE = 57,
	CPUHP_MM_ZS_PREPARE = 58,
	CPUHP_MM_ZSWP_MEM_PREPARE = 59,
	CPUHP_MM_ZSWP_POOL_PREPARE = 60,
	CPUHP_KVM_PPC_BOOK3S_PREPARE = 61,
	CPUHP_ZCOMP_PREPARE = 62,
	CPUHP_TIMERS_PREPARE = 63,
	CPUHP_MIPS_SOC_PREPARE = 64,
	CPUHP_BP_PREPARE_DYN = 65,
	CPUHP_BP_PREPARE_DYN_END = 85,
	CPUHP_BRINGUP_CPU = 86,
	CPUHP_AP_IDLE_DEAD = 87,
	CPUHP_AP_OFFLINE = 88,
	CPUHP_AP_SCHED_STARTING = 89,
	CPUHP_AP_RCUTREE_DYING = 90,
	CPUHP_AP_CPU_PM_STARTING = 91,
	CPUHP_AP_IRQ_GIC_STARTING = 92,
	CPUHP_AP_IRQ_HIP04_STARTING = 93,
	CPUHP_AP_IRQ_ARMADA_XP_STARTING = 94,
	CPUHP_AP_IRQ_BCM2836_STARTING = 95,
	CPUHP_AP_IRQ_MIPS_GIC_STARTING = 96,
	CPUHP_AP_IRQ_RISCV_STARTING = 97,
	CPUHP_AP_IRQ_SIFIVE_PLIC_STARTING = 98,
	CPUHP_AP_ARM_MVEBU_COHERENCY = 99,
	CPUHP_AP_MICROCODE_LOADER = 100,
	CPUHP_AP_PERF_X86_AMD_UNCORE_STARTING = 101,
	CPUHP_AP_PERF_X86_STARTING = 102,
	CPUHP_AP_PERF_X86_AMD_IBS_STARTING = 103,
	CPUHP_AP_PERF_X86_CQM_STARTING = 104,
	CPUHP_AP_PERF_X86_CSTATE_STARTING = 105,
	CPUHP_AP_PERF_XTENSA_STARTING = 106,
	CPUHP_AP_MIPS_OP_LOONGSON3_STARTING = 107,
	CPUHP_AP_ARM_SDEI_STARTING = 108,
	CPUHP_AP_ARM_VFP_STARTING = 109,
	CPUHP_AP_ARM64_DEBUG_MONITORS_STARTING = 110,
	CPUHP_AP_PERF_ARM_HW_BREAKPOINT_STARTING = 111,
	CPUHP_AP_PERF_ARM_ACPI_STARTING = 112,
	CPUHP_AP_PERF_ARM_STARTING = 113,
	CPUHP_AP_ARM_L2X0_STARTING = 114,
	CPUHP_AP_EXYNOS4_MCT_TIMER_STARTING = 115,
	CPUHP_AP_ARM_ARCH_TIMER_STARTING = 116,
	CPUHP_AP_ARM_GLOBAL_TIMER_STARTING = 117,
	CPUHP_AP_JCORE_TIMER_STARTING = 118,
	CPUHP_AP_ARM_TWD_STARTING = 119,
	CPUHP_AP_QCOM_TIMER_STARTING = 120,
	CPUHP_AP_TEGRA_TIMER_STARTING = 121,
	CPUHP_AP_ARMADA_TIMER_STARTING = 122,
	CPUHP_AP_MARCO_TIMER_STARTING = 123,
	CPUHP_AP_MIPS_GIC_TIMER_STARTING = 124,
	CPUHP_AP_ARC_TIMER_STARTING = 125,
	CPUHP_AP_RISCV_TIMER_STARTING = 126,
	CPUHP_AP_CSKY_TIMER_STARTING = 127,
	CPUHP_AP_HYPERV_TIMER_STARTING = 128,
	CPUHP_AP_KVM_STARTING = 129,
	CPUHP_AP_KVM_ARM_VGIC_INIT_STARTING = 130,
	CPUHP_AP_KVM_ARM_VGIC_STARTING = 131,
	CPUHP_AP_KVM_ARM_TIMER_STARTING = 132,
	CPUHP_AP_DUMMY_TIMER_STARTING = 133,
	CPUHP_AP_ARM_XEN_STARTING = 134,
	CPUHP_AP_ARM_KVMPV_STARTING = 135,
	CPUHP_AP_ARM_CORESIGHT_STARTING = 136,
	CPUHP_AP_ARM_CORESIGHT_CTI_STARTING = 137,
	CPUHP_AP_ARM64_ISNDEP_STARTING = 138,
	CPUHP_AP_SMPCFD_DYING = 139,
	CPUHP_AP_X86_TBOOT_DYING = 140,
	CPUHP_AP_ARM_CACHE_B15_RAC_DYING = 141,
	CPUHP_AP_ONLINE = 142,
	CPUHP_TEARDOWN_CPU = 143,
	CPUHP_AP_ONLINE_IDLE = 144,
	CPUHP_AP_SMPBOOT_THREADS = 145,
	CPUHP_AP_X86_VDSO_VMA_ONLINE = 146,
	CPUHP_AP_IRQ_AFFINITY_ONLINE = 147,
	CPUHP_AP_BLK_MQ_ONLINE = 148,
	CPUHP_AP_ARM_MVEBU_SYNC_CLOCKS = 149,
	CPUHP_AP_X86_INTEL_EPB_ONLINE = 150,
	CPUHP_AP_PERF_ONLINE = 151,
	CPUHP_AP_PERF_X86_ONLINE = 152,
	CPUHP_AP_PERF_X86_UNCORE_ONLINE = 153,
	CPUHP_AP_PERF_X86_AMD_UNCORE_ONLINE = 154,
	CPUHP_AP_PERF_X86_AMD_POWER_ONLINE = 155,
	CPUHP_AP_PERF_X86_RAPL_ONLINE = 156,
	CPUHP_AP_PERF_X86_CQM_ONLINE = 157,
	CPUHP_AP_PERF_X86_CSTATE_ONLINE = 158,
	CPUHP_AP_PERF_S390_CF_ONLINE = 159,
	CPUHP_AP_PERF_S390_SF_ONLINE = 160,
	CPUHP_AP_PERF_ARM_CCI_ONLINE = 161,
	CPUHP_AP_PERF_ARM_CCN_ONLINE = 162,
	CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE = 163,
	CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE = 164,
	CPUHP_AP_PERF_ARM_HISI_L3_ONLINE = 165,
	CPUHP_AP_PERF_ARM_L2X0_ONLINE = 166,
	CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE = 167,
	CPUHP_AP_PERF_ARM_QCOM_L3_ONLINE = 168,
	CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE = 169,
	CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE = 170,
	CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE = 171,
	CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE = 172,
	CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE = 173,
	CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE = 174,
	CPUHP_AP_WATCHDOG_ONLINE = 175,
	CPUHP_AP_WORKQUEUE_ONLINE = 176,
	CPUHP_AP_RCUTREE_ONLINE = 177,
	CPUHP_AP_BASE_CACHEINFO_ONLINE = 178,
	CPUHP_AP_ONLINE_DYN = 179,
	CPUHP_AP_ONLINE_DYN_END = 209,
	CPUHP_AP_X86_HPET_ONLINE = 210,
	CPUHP_AP_X86_KVM_CLK_ONLINE = 211,
	CPUHP_AP_ACTIVE = 212,
	CPUHP_ONLINE = 213,
};

struct perf_regs {
	__u64 abi;
	struct pt_regs *regs;
};

struct kernel_cpustat {
	u64 cpustat[10];
};

struct kernel_stat {
	long unsigned int irqs_sum;
	unsigned int softirqs[10];
};

struct u64_stats_sync {};

struct bpf_insn {
	__u8 code;
	__u8 dst_reg: 4;
	__u8 src_reg: 4;
	__s16 off;
	__s32 imm;
};

struct bpf_cgroup_storage_key {
	__u64 cgroup_inode_id;
	__u32 attach_type;
};

enum bpf_map_type {
	BPF_MAP_TYPE_UNSPEC = 0,
	BPF_MAP_TYPE_HASH = 1,
	BPF_MAP_TYPE_ARRAY = 2,
	BPF_MAP_TYPE_PROG_ARRAY = 3,
	BPF_MAP_TYPE_PERF_EVENT_ARRAY = 4,
	BPF_MAP_TYPE_PERCPU_HASH = 5,
	BPF_MAP_TYPE_PERCPU_ARRAY = 6,
	BPF_MAP_TYPE_STACK_TRACE = 7,
	BPF_MAP_TYPE_CGROUP_ARRAY = 8,
	BPF_MAP_TYPE_LRU_HASH = 9,
	BPF_MAP_TYPE_LRU_PERCPU_HASH = 10,
	BPF_MAP_TYPE_LPM_TRIE = 11,
	BPF_MAP_TYPE_ARRAY_OF_MAPS = 12,
	BPF_MAP_TYPE_HASH_OF_MAPS = 13,
	BPF_MAP_TYPE_DEVMAP = 14,
	BPF_MAP_TYPE_SOCKMAP = 15,
	BPF_MAP_TYPE_CPUMAP = 16,
	BPF_MAP_TYPE_XSKMAP = 17,
	BPF_MAP_TYPE_SOCKHASH = 18,
	BPF_MAP_TYPE_CGROUP_STORAGE = 19,
	BPF_MAP_TYPE_REUSEPORT_SOCKARRAY = 20,
	BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE = 21,
	BPF_MAP_TYPE_QUEUE = 22,
	BPF_MAP_TYPE_STACK = 23,
	BPF_MAP_TYPE_SK_STORAGE = 24,
	BPF_MAP_TYPE_DEVMAP_HASH = 25,
	BPF_MAP_TYPE_STRUCT_OPS = 26,
	BPF_MAP_TYPE_RINGBUF = 27,
};

union bpf_attr {
	struct {
		__u32 map_type;
		__u32 key_size;
		__u32 value_size;
		__u32 max_entries;
		__u32 map_flags;
		__u32 inner_map_fd;
		__u32 numa_node;
		char map_name[16];
		__u32 map_ifindex;
		__u32 btf_fd;
		__u32 btf_key_type_id;
		__u32 btf_value_type_id;
		__u32 btf_vmlinux_value_type_id;
	};
	struct {
		__u32 map_fd;
		__u64 key;
		union {
			__u64 value;
			__u64 next_key;
		};
		__u64 flags;
	};
	struct {
		__u64 in_batch;
		__u64 out_batch;
		__u64 keys;
		__u64 values;
		__u32 count;
		__u32 map_fd;
		__u64 elem_flags;
		__u64 flags;
	} batch;
	struct {
		__u32 prog_type;
		__u32 insn_cnt;
		__u64 insns;
		__u64 license;
		__u32 log_level;
		__u32 log_size;
		__u64 log_buf;
		__u32 kern_version;
		__u32 prog_flags;
		char prog_name[16];
		__u32 prog_ifindex;
		__u32 expected_attach_type;
		__u32 prog_btf_fd;
		__u32 func_info_rec_size;
		__u64 func_info;
		__u32 func_info_cnt;
		__u32 line_info_rec_size;
		__u64 line_info;
		__u32 line_info_cnt;
		__u32 attach_btf_id;
		__u32 attach_prog_fd;
	};
	struct {
		__u64 pathname;
		__u32 bpf_fd;
		__u32 file_flags;
	};
	struct {
		__u32 target_fd;
		__u32 attach_bpf_fd;
		__u32 attach_type;
		__u32 attach_flags;
		__u32 replace_bpf_fd;
	};
	struct {
		__u32 prog_fd;
		__u32 retval;
		__u32 data_size_in;
		__u32 data_size_out;
		__u64 data_in;
		__u64 data_out;
		__u32 repeat;
		__u32 duration;
		__u32 ctx_size_in;
		__u32 ctx_size_out;
		__u64 ctx_in;
		__u64 ctx_out;
	} test;
	struct {
		union {
			__u32 start_id;
			__u32 prog_id;
			__u32 map_id;
			__u32 btf_id;
			__u32 link_id;
		};
		__u32 next_id;
		__u32 open_flags;
	};
	struct {
		__u32 bpf_fd;
		__u32 info_len;
		__u64 info;
	} info;
	struct {
		__u32 target_fd;
		__u32 attach_type;
		__u32 query_flags;
		__u32 attach_flags;
		__u64 prog_ids;
		__u32 prog_cnt;
	} query;
	struct {
		__u64 name;
		__u32 prog_fd;
	} raw_tracepoint;
	struct {
		__u64 btf;
		__u64 btf_log_buf;
		__u32 btf_size;
		__u32 btf_log_size;
		__u32 btf_log_level;
	};
	struct {
		__u32 pid;
		__u32 fd;
		__u32 flags;
		__u32 buf_len;
		__u64 buf;
		__u32 prog_id;
		__u32 fd_type;
		__u64 probe_offset;
		__u64 probe_addr;
	} task_fd_query;
	struct {
		__u32 prog_fd;
		__u32 target_fd;
		__u32 attach_type;
		__u32 flags;
	} link_create;
	struct {
		__u32 link_fd;
		__u32 new_prog_fd;
		__u32 flags;
		__u32 old_prog_fd;
	} link_update;
	struct {
		__u32 type;
	} enable_stats;
	struct {
		__u32 link_fd;
		__u32 flags;
	} iter_create;
};

enum bpf_func_id {
	BPF_FUNC_unspec = 0,
	BPF_FUNC_map_lookup_elem = 1,
	BPF_FUNC_map_update_elem = 2,
	BPF_FUNC_map_delete_elem = 3,
	BPF_FUNC_probe_read = 4,
	BPF_FUNC_ktime_get_ns = 5,
	BPF_FUNC_trace_printk = 6,
	BPF_FUNC_get_prandom_u32 = 7,
	BPF_FUNC_get_smp_processor_id = 8,
	BPF_FUNC_skb_store_bytes = 9,
	BPF_FUNC_l3_csum_replace = 10,
	BPF_FUNC_l4_csum_replace = 11,
	BPF_FUNC_tail_call = 12,
	BPF_FUNC_clone_redirect = 13,
	BPF_FUNC_get_current_pid_tgid = 14,
	BPF_FUNC_get_current_uid_gid = 15,
	BPF_FUNC_get_current_comm = 16,
	BPF_FUNC_get_cgroup_classid = 17,
	BPF_FUNC_skb_vlan_push = 18,
	BPF_FUNC_skb_vlan_pop = 19,
	BPF_FUNC_skb_get_tunnel_key = 20,
	BPF_FUNC_skb_set_tunnel_key = 21,
	BPF_FUNC_perf_event_read = 22,
	BPF_FUNC_redirect = 23,
	BPF_FUNC_get_route_realm = 24,
	BPF_FUNC_perf_event_output = 25,
	BPF_FUNC_skb_load_bytes = 26,
	BPF_FUNC_get_stackid = 27,
	BPF_FUNC_csum_diff = 28,
	BPF_FUNC_skb_get_tunnel_opt = 29,
	BPF_FUNC_skb_set_tunnel_opt = 30,
	BPF_FUNC_skb_change_proto = 31,
	BPF_FUNC_skb_change_type = 32,
	BPF_FUNC_skb_under_cgroup = 33,
	BPF_FUNC_get_hash_recalc = 34,
	BPF_FUNC_get_current_task = 35,
	BPF_FUNC_probe_write_user = 36,
	BPF_FUNC_current_task_under_cgroup = 37,
	BPF_FUNC_skb_change_tail = 38,
	BPF_FUNC_skb_pull_data = 39,
	BPF_FUNC_csum_update = 40,
	BPF_FUNC_set_hash_invalid = 41,
	BPF_FUNC_get_numa_node_id = 42,
	BPF_FUNC_skb_change_head = 43,
	BPF_FUNC_xdp_adjust_head = 44,
	BPF_FUNC_probe_read_str = 45,
	BPF_FUNC_get_socket_cookie = 46,
	BPF_FUNC_get_socket_uid = 47,
	BPF_FUNC_set_hash = 48,
	BPF_FUNC_setsockopt = 49,
	BPF_FUNC_skb_adjust_room = 50,
	BPF_FUNC_redirect_map = 51,
	BPF_FUNC_sk_redirect_map = 52,
	BPF_FUNC_sock_map_update = 53,
	BPF_FUNC_xdp_adjust_meta = 54,
	BPF_FUNC_perf_event_read_value = 55,
	BPF_FUNC_perf_prog_read_value = 56,
	BPF_FUNC_getsockopt = 57,
	BPF_FUNC_override_return = 58,
	BPF_FUNC_sock_ops_cb_flags_set = 59,
	BPF_FUNC_msg_redirect_map = 60,
	BPF_FUNC_msg_apply_bytes = 61,
	BPF_FUNC_msg_cork_bytes = 62,
	BPF_FUNC_msg_pull_data = 63,
	BPF_FUNC_bind = 64,
	BPF_FUNC_xdp_adjust_tail = 65,
	BPF_FUNC_skb_get_xfrm_state = 66,
	BPF_FUNC_get_stack = 67,
	BPF_FUNC_skb_load_bytes_relative = 68,
	BPF_FUNC_fib_lookup = 69,
	BPF_FUNC_sock_hash_update = 70,
	BPF_FUNC_msg_redirect_hash = 71,
	BPF_FUNC_sk_redirect_hash = 72,
	BPF_FUNC_lwt_push_encap = 73,
	BPF_FUNC_lwt_seg6_store_bytes = 74,
	BPF_FUNC_lwt_seg6_adjust_srh = 75,
	BPF_FUNC_lwt_seg6_action = 76,
	BPF_FUNC_rc_repeat = 77,
	BPF_FUNC_rc_keydown = 78,
	BPF_FUNC_skb_cgroup_id = 79,
	BPF_FUNC_get_current_cgroup_id = 80,
	BPF_FUNC_get_local_storage = 81,
	BPF_FUNC_sk_select_reuseport = 82,
	BPF_FUNC_skb_ancestor_cgroup_id = 83,
	BPF_FUNC_sk_lookup_tcp = 84,
	BPF_FUNC_sk_lookup_udp = 85,
	BPF_FUNC_sk_release = 86,
	BPF_FUNC_map_push_elem = 87,
	BPF_FUNC_map_pop_elem = 88,
	BPF_FUNC_map_peek_elem = 89,
	BPF_FUNC_msg_push_data = 90,
	BPF_FUNC_msg_pop_data = 91,
	BPF_FUNC_rc_pointer_rel = 92,
	BPF_FUNC_spin_lock = 93,
	BPF_FUNC_spin_unlock = 94,
	BPF_FUNC_sk_fullsock = 95,
	BPF_FUNC_tcp_sock = 96,
	BPF_FUNC_skb_ecn_set_ce = 97,
	BPF_FUNC_get_listener_sock = 98,
	BPF_FUNC_skc_lookup_tcp = 99,
	BPF_FUNC_tcp_check_syncookie = 100,
	BPF_FUNC_sysctl_get_name = 101,
	BPF_FUNC_sysctl_get_current_value = 102,
	BPF_FUNC_sysctl_get_new_value = 103,
	BPF_FUNC_sysctl_set_new_value = 104,
	BPF_FUNC_strtol = 105,
	BPF_FUNC_strtoul = 106,
	BPF_FUNC_sk_storage_get = 107,
	BPF_FUNC_sk_storage_delete = 108,
	BPF_FUNC_send_signal = 109,
	BPF_FUNC_tcp_gen_syncookie = 110,
	BPF_FUNC_skb_output = 111,
	BPF_FUNC_probe_read_user = 112,
	BPF_FUNC_probe_read_kernel = 113,
	BPF_FUNC_probe_read_user_str = 114,
	BPF_FUNC_probe_read_kernel_str = 115,
	BPF_FUNC_tcp_send_ack = 116,
	BPF_FUNC_send_signal_thread = 117,
	BPF_FUNC_jiffies64 = 118,
	BPF_FUNC_read_branch_records = 119,
	BPF_FUNC_get_ns_current_pid_tgid = 120,
	BPF_FUNC_xdp_output = 121,
	BPF_FUNC_get_netns_cookie = 122,
	BPF_FUNC_get_current_ancestor_cgroup_id = 123,
	BPF_FUNC_sk_assign = 124,
	BPF_FUNC_ktime_get_boot_ns = 125,
	BPF_FUNC_seq_printf = 126,
	BPF_FUNC_seq_write = 127,
	BPF_FUNC_sk_cgroup_id = 128,
	BPF_FUNC_sk_ancestor_cgroup_id = 129,
	BPF_FUNC_ringbuf_output = 130,
	BPF_FUNC_ringbuf_reserve = 131,
	BPF_FUNC_ringbuf_submit = 132,
	BPF_FUNC_ringbuf_discard = 133,
	BPF_FUNC_ringbuf_query = 134,
	BPF_FUNC_csum_level = 135,
	__BPF_FUNC_MAX_ID = 136,
};

struct bpf_func_info {
	__u32 insn_off;
	__u32 type_id;
};

struct bpf_line_info {
	__u32 insn_off;
	__u32 file_name_off;
	__u32 line_off;
	__u32 line_col;
};

struct bpf_map;

struct btf;

struct btf_type;

struct bpf_prog_aux;

struct bpf_map_ops {
	int (*map_alloc_check)(union bpf_attr *);
	struct bpf_map * (*map_alloc)(union bpf_attr *);
	void (*map_release)(struct bpf_map *, struct file *);
	void (*map_free)(struct bpf_map *);
	int (*map_get_next_key)(struct bpf_map *, void *, void *);
	void (*map_release_uref)(struct bpf_map *);
	void * (*map_lookup_elem_sys_only)(struct bpf_map *, void *);
	int (*map_lookup_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	int (*map_lookup_and_delete_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	int (*map_update_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	int (*map_delete_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	void * (*map_lookup_elem)(struct bpf_map *, void *);
	int (*map_update_elem)(struct bpf_map *, void *, void *, u64);
	int (*map_delete_elem)(struct bpf_map *, void *);
	int (*map_push_elem)(struct bpf_map *, void *, u64);
	int (*map_pop_elem)(struct bpf_map *, void *);
	int (*map_peek_elem)(struct bpf_map *, void *);
	void * (*map_fd_get_ptr)(struct bpf_map *, struct file *, int);
	void (*map_fd_put_ptr)(void *);
	u32 (*map_gen_lookup)(struct bpf_map *, struct bpf_insn *);
	u32 (*map_fd_sys_lookup_elem)(void *);
	void (*map_seq_show_elem)(struct bpf_map *, void *, struct seq_file *);
	int (*map_check_btf)(const struct bpf_map *, const struct btf *, const struct btf_type *, const struct btf_type *);
	int (*map_poke_track)(struct bpf_map *, struct bpf_prog_aux *);
	void (*map_poke_untrack)(struct bpf_map *, struct bpf_prog_aux *);
	void (*map_poke_run)(struct bpf_map *, u32, struct bpf_prog *, struct bpf_prog *);
	int (*map_direct_value_addr)(const struct bpf_map *, u64 *, u32);
	int (*map_direct_value_meta)(const struct bpf_map *, u64, u32 *);
	int (*map_mmap)(struct bpf_map *, struct vm_area_struct *);
	__poll_t (*map_poll)(struct bpf_map *, struct file *, struct poll_table_struct *);
};

struct bpf_map_memory {
	u32 pages;
	struct user_struct *user;
};

struct bpf_map {
	const struct bpf_map_ops *ops;
	struct bpf_map *inner_map_meta;
	void *security;
	enum bpf_map_type map_type;
	u32 key_size;
	u32 value_size;
	u32 max_entries;
	u32 map_flags;
	int spin_lock_off;
	u32 id;
	int numa_node;
	u32 btf_key_type_id;
	u32 btf_value_type_id;
	struct btf *btf;
	struct bpf_map_memory memory;
	char name[16];
	u32 btf_vmlinux_value_type_id;
	bool bypass_spec_v1;
	bool frozen;
	long: 16;
	long: 64;
	long: 64;
	atomic64_t refcnt;
	atomic64_t usercnt;
	struct work_struct work;
	struct mutex freeze_mutex;
	u64 writecnt;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct btf_header {
	__u16 magic;
	__u8 version;
	__u8 flags;
	__u32 hdr_len;
	__u32 type_off;
	__u32 type_len;
	__u32 str_off;
	__u32 str_len;
};

struct btf {
	void *data;
	struct btf_type **types;
	u32 *resolved_ids;
	u32 *resolved_sizes;
	const char *strings;
	void *nohdr_data;
	struct btf_header hdr;
	u32 nr_types;
	u32 types_size;
	u32 data_size;
	refcount_t refcnt;
	u32 id;
	struct callback_head rcu;
};

struct btf_type {
	__u32 name_off;
	__u32 info;
	union {
		__u32 size;
		__u32 type;
	};
};

enum bpf_tramp_prog_type {
	BPF_TRAMP_FENTRY = 0,
	BPF_TRAMP_FEXIT = 1,
	BPF_TRAMP_MODIFY_RETURN = 2,
	BPF_TRAMP_MAX = 3,
	BPF_TRAMP_REPLACE = 4,
};

struct bpf_ksym {
	long unsigned int start;
	long unsigned int end;
	char name[128];
	struct list_head lnode;
	struct latch_tree_node tnode;
	bool prog;
};

struct bpf_ctx_arg_aux;

struct bpf_trampoline;

struct bpf_jit_poke_descriptor;

struct bpf_prog_ops;

struct bpf_prog_offload;

struct bpf_func_info_aux;

struct bpf_prog_stats;

struct bpf_prog_aux {
	atomic64_t refcnt;
	u32 used_map_cnt;
	u32 max_ctx_offset;
	u32 max_pkt_offset;
	u32 max_tp_access;
	u32 stack_depth;
	u32 id;
	u32 func_cnt;
	u32 func_idx;
	u32 attach_btf_id;
	u32 ctx_arg_info_size;
	const struct bpf_ctx_arg_aux *ctx_arg_info;
	struct bpf_prog *linked_prog;
	bool verifier_zext;
	bool offload_requested;
	bool attach_btf_trace;
	bool func_proto_unreliable;
	enum bpf_tramp_prog_type trampoline_prog_type;
	struct bpf_trampoline *trampoline;
	struct hlist_node tramp_hlist;
	const struct btf_type *attach_func_proto;
	const char *attach_func_name;
	struct bpf_prog **func;
	void *jit_data;
	struct bpf_jit_poke_descriptor *poke_tab;
	u32 size_poke_tab;
	struct bpf_ksym ksym;
	const struct bpf_prog_ops *ops;
	struct bpf_map **used_maps;
	struct bpf_prog *prog;
	struct user_struct *user;
	u64 load_time;
	struct bpf_map *cgroup_storage[2];
	char name[16];
	void *security;
	struct bpf_prog_offload *offload;
	struct btf *btf;
	struct bpf_func_info *func_info;
	struct bpf_func_info_aux *func_info_aux;
	struct bpf_line_info *linfo;
	void **jited_linfo;
	u32 func_info_cnt;
	u32 nr_linfo;
	u32 linfo_idx;
	u32 num_exentries;
	struct exception_table_entry *extable;
	struct bpf_prog_stats *stats;
	union {
		struct work_struct work;
		struct callback_head rcu;
	};
};

enum bpf_prog_type {
	BPF_PROG_TYPE_UNSPEC = 0,
	BPF_PROG_TYPE_SOCKET_FILTER = 1,
	BPF_PROG_TYPE_KPROBE = 2,
	BPF_PROG_TYPE_SCHED_CLS = 3,
	BPF_PROG_TYPE_SCHED_ACT = 4,
	BPF_PROG_TYPE_TRACEPOINT = 5,
	BPF_PROG_TYPE_XDP = 6,
	BPF_PROG_TYPE_PERF_EVENT = 7,
	BPF_PROG_TYPE_CGROUP_SKB = 8,
	BPF_PROG_TYPE_CGROUP_SOCK = 9,
	BPF_PROG_TYPE_LWT_IN = 10,
	BPF_PROG_TYPE_LWT_OUT = 11,
	BPF_PROG_TYPE_LWT_XMIT = 12,
	BPF_PROG_TYPE_SOCK_OPS = 13,
	BPF_PROG_TYPE_SK_SKB = 14,
	BPF_PROG_TYPE_CGROUP_DEVICE = 15,
	BPF_PROG_TYPE_SK_MSG = 16,
	BPF_PROG_TYPE_RAW_TRACEPOINT = 17,
	BPF_PROG_TYPE_CGROUP_SOCK_ADDR = 18,
	BPF_PROG_TYPE_LWT_SEG6LOCAL = 19,
	BPF_PROG_TYPE_LIRC_MODE2 = 20,
	BPF_PROG_TYPE_SK_REUSEPORT = 21,
	BPF_PROG_TYPE_FLOW_DISSECTOR = 22,
	BPF_PROG_TYPE_CGROUP_SYSCTL = 23,
	BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE = 24,
	BPF_PROG_TYPE_CGROUP_SOCKOPT = 25,
	BPF_PROG_TYPE_TRACING = 26,
	BPF_PROG_TYPE_STRUCT_OPS = 27,
	BPF_PROG_TYPE_EXT = 28,
	BPF_PROG_TYPE_LSM = 29,
};

enum bpf_attach_type {
	BPF_CGROUP_INET_INGRESS = 0,
	BPF_CGROUP_INET_EGRESS = 1,
	BPF_CGROUP_INET_SOCK_CREATE = 2,
	BPF_CGROUP_SOCK_OPS = 3,
	BPF_SK_SKB_STREAM_PARSER = 4,
	BPF_SK_SKB_STREAM_VERDICT = 5,
	BPF_CGROUP_DEVICE = 6,
	BPF_SK_MSG_VERDICT = 7,
	BPF_CGROUP_INET4_BIND = 8,
	BPF_CGROUP_INET6_BIND = 9,
	BPF_CGROUP_INET4_CONNECT = 10,
	BPF_CGROUP_INET6_CONNECT = 11,
	BPF_CGROUP_INET4_POST_BIND = 12,
	BPF_CGROUP_INET6_POST_BIND = 13,
	BPF_CGROUP_UDP4_SENDMSG = 14,
	BPF_CGROUP_UDP6_SENDMSG = 15,
	BPF_LIRC_MODE2 = 16,
	BPF_FLOW_DISSECTOR = 17,
	BPF_CGROUP_SYSCTL = 18,
	BPF_CGROUP_UDP4_RECVMSG = 19,
	BPF_CGROUP_UDP6_RECVMSG = 20,
	BPF_CGROUP_GETSOCKOPT = 21,
	BPF_CGROUP_SETSOCKOPT = 22,
	BPF_TRACE_RAW_TP = 23,
	BPF_TRACE_FENTRY = 24,
	BPF_TRACE_FEXIT = 25,
	BPF_MODIFY_RETURN = 26,
	BPF_LSM_MAC = 27,
	BPF_TRACE_ITER = 28,
	BPF_CGROUP_INET4_GETPEERNAME = 29,
	BPF_CGROUP_INET6_GETPEERNAME = 30,
	BPF_CGROUP_INET4_GETSOCKNAME = 31,
	BPF_CGROUP_INET6_GETSOCKNAME = 32,
	BPF_XDP_DEVMAP = 33,
	__MAX_BPF_ATTACH_TYPE = 34,
};

struct sock_filter {
	__u16 code;
	__u8 jt;
	__u8 jf;
	__u32 k;
};

struct sock_fprog_kern;

struct bpf_prog {
	u16 pages;
	u16 jited: 1;
	u16 jit_requested: 1;
	u16 gpl_compatible: 1;
	u16 cb_access: 1;
	u16 dst_needed: 1;
	u16 blinded: 1;
	u16 is_func: 1;
	u16 kprobe_override: 1;
	u16 has_callchain_buf: 1;
	u16 enforce_expected_attach_type: 1;
	enum bpf_prog_type type;
	enum bpf_attach_type expected_attach_type;
	u32 len;
	u32 jited_len;
	u8 tag[8];
	struct bpf_prog_aux *aux;
	struct sock_fprog_kern *orig_prog;
	unsigned int (*bpf_func)(const void *, const struct bpf_insn *);
	struct sock_filter insns[0];
	struct bpf_insn insnsi[0];
};

enum bpf_arg_type {
	ARG_DONTCARE = 0,
	ARG_CONST_MAP_PTR = 1,
	ARG_PTR_TO_MAP_KEY = 2,
	ARG_PTR_TO_MAP_VALUE = 3,
	ARG_PTR_TO_UNINIT_MAP_VALUE = 4,
	ARG_PTR_TO_MAP_VALUE_OR_NULL = 5,
	ARG_PTR_TO_MEM = 6,
	ARG_PTR_TO_MEM_OR_NULL = 7,
	ARG_PTR_TO_UNINIT_MEM = 8,
	ARG_CONST_SIZE = 9,
	ARG_CONST_SIZE_OR_ZERO = 10,
	ARG_PTR_TO_CTX = 11,
	ARG_PTR_TO_CTX_OR_NULL = 12,
	ARG_ANYTHING = 13,
	ARG_PTR_TO_SPIN_LOCK = 14,
	ARG_PTR_TO_SOCK_COMMON = 15,
	ARG_PTR_TO_INT = 16,
	ARG_PTR_TO_LONG = 17,
	ARG_PTR_TO_SOCKET = 18,
	ARG_PTR_TO_BTF_ID = 19,
	ARG_PTR_TO_ALLOC_MEM = 20,
	ARG_PTR_TO_ALLOC_MEM_OR_NULL = 21,
	ARG_CONST_ALLOC_SIZE_OR_ZERO = 22,
};

enum bpf_return_type {
	RET_INTEGER = 0,
	RET_VOID = 1,
	RET_PTR_TO_MAP_VALUE = 2,
	RET_PTR_TO_MAP_VALUE_OR_NULL = 3,
	RET_PTR_TO_SOCKET_OR_NULL = 4,
	RET_PTR_TO_TCP_SOCK_OR_NULL = 5,
	RET_PTR_TO_SOCK_COMMON_OR_NULL = 6,
	RET_PTR_TO_ALLOC_MEM_OR_NULL = 7,
};

struct bpf_func_proto {
	u64 (*func)(u64, u64, u64, u64, u64);
	bool gpl_only;
	bool pkt_access;
	enum bpf_return_type ret_type;
	union {
		struct {
			enum bpf_arg_type arg1_type;
			enum bpf_arg_type arg2_type;
			enum bpf_arg_type arg3_type;
			enum bpf_arg_type arg4_type;
			enum bpf_arg_type arg5_type;
		};
		enum bpf_arg_type arg_type[5];
	};
	int *btf_id;
};

enum bpf_access_type {
	BPF_READ = 1,
	BPF_WRITE = 2,
};

enum bpf_reg_type {
	NOT_INIT = 0,
	SCALAR_VALUE = 1,
	PTR_TO_CTX = 2,
	CONST_PTR_TO_MAP = 3,
	PTR_TO_MAP_VALUE = 4,
	PTR_TO_MAP_VALUE_OR_NULL = 5,
	PTR_TO_STACK = 6,
	PTR_TO_PACKET_META = 7,
	PTR_TO_PACKET = 8,
	PTR_TO_PACKET_END = 9,
	PTR_TO_FLOW_KEYS = 10,
	PTR_TO_SOCKET = 11,
	PTR_TO_SOCKET_OR_NULL = 12,
	PTR_TO_SOCK_COMMON = 13,
	PTR_TO_SOCK_COMMON_OR_NULL = 14,
	PTR_TO_TCP_SOCK = 15,
	PTR_TO_TCP_SOCK_OR_NULL = 16,
	PTR_TO_TP_BUFFER = 17,
	PTR_TO_XDP_SOCK = 18,
	PTR_TO_BTF_ID = 19,
	PTR_TO_BTF_ID_OR_NULL = 20,
	PTR_TO_MEM = 21,
	PTR_TO_MEM_OR_NULL = 22,
};

struct bpf_verifier_log;

struct bpf_insn_access_aux {
	enum bpf_reg_type reg_type;
	union {
		int ctx_field_size;
		u32 btf_id;
	};
	struct bpf_verifier_log *log;
};

struct bpf_prog_ops {
	int (*test_run)(struct bpf_prog *, const union bpf_attr *, union bpf_attr *);
};

struct bpf_verifier_ops {
	const struct bpf_func_proto * (*get_func_proto)(enum bpf_func_id, const struct bpf_prog *);
	bool (*is_valid_access)(int, int, enum bpf_access_type, const struct bpf_prog *, struct bpf_insn_access_aux *);
	int (*gen_prologue)(struct bpf_insn *, bool, const struct bpf_prog *);
	int (*gen_ld_abs)(const struct bpf_insn *, struct bpf_insn *);
	u32 (*convert_ctx_access)(enum bpf_access_type, const struct bpf_insn *, struct bpf_insn *, struct bpf_prog *, u32 *);
	int (*btf_struct_access)(struct bpf_verifier_log *, const struct btf_type *, int, int, enum bpf_access_type, u32 *);
};

struct net_device;

struct bpf_offload_dev;

struct bpf_prog_offload {
	struct bpf_prog *prog;
	struct net_device *netdev;
	struct bpf_offload_dev *offdev;
	void *dev_priv;
	struct list_head offloads;
	bool dev_state;
	bool opt_failed;
	void *jited_image;
	u32 jited_len;
};

struct bpf_prog_stats {
	u64 cnt;
	u64 nsecs;
	struct u64_stats_sync syncp;
};

struct btf_func_model {
	u8 ret_size;
	u8 nr_args;
	u8 arg_size[12];
};

struct bpf_trampoline {
	struct hlist_node hlist;
	struct mutex mutex;
	refcount_t refcnt;
	u64 key;
	struct {
		struct btf_func_model model;
		void *addr;
		bool ftrace_managed;
	} func;
	struct bpf_prog *extension_prog;
	struct hlist_head progs_hlist[3];
	int progs_cnt[3];
	void *image;
	u64 selector;
	struct bpf_ksym ksym;
};

struct bpf_func_info_aux {
	u16 linkage;
	bool unreliable;
};

struct bpf_jit_poke_descriptor {
	void *ip;
	union {
		struct {
			struct bpf_map *map;
			u32 key;
		} tail_call;
	};
	bool ip_stable;
	u8 adj_off;
	u16 reason;
};

struct bpf_ctx_arg_aux {
	u32 offset;
	enum bpf_reg_type reg_type;
};

struct bpf_cgroup_storage;

struct bpf_prog_array_item {
	struct bpf_prog *prog;
	struct bpf_cgroup_storage *cgroup_storage[2];
};

struct bpf_storage_buffer;

struct bpf_cgroup_storage_map;

struct bpf_cgroup_storage {
	union {
		struct bpf_storage_buffer *buf;
		void *percpu_buf;
	};
	struct bpf_cgroup_storage_map *map;
	struct bpf_cgroup_storage_key key;
	struct list_head list;
	struct rb_node node;
	struct callback_head rcu;
};

struct bpf_prog_array {
	struct callback_head rcu;
	struct bpf_prog_array_item items[0];
};

struct bpf_storage_buffer {
	struct callback_head rcu;
	char data[0];
};

struct cgroup_taskset;

struct cftype;

struct cgroup_subsys {
	struct cgroup_subsys_state * (*css_alloc)(struct cgroup_subsys_state *);
	int (*css_online)(struct cgroup_subsys_state *);
	void (*css_offline)(struct cgroup_subsys_state *);
	void (*css_released)(struct cgroup_subsys_state *);
	void (*css_free)(struct cgroup_subsys_state *);
	void (*css_reset)(struct cgroup_subsys_state *);
	void (*css_rstat_flush)(struct cgroup_subsys_state *, int);
	int (*css_extra_stat_show)(struct seq_file *, struct cgroup_subsys_state *);
	int (*can_attach)(struct cgroup_taskset *);
	void (*cancel_attach)(struct cgroup_taskset *);
	void (*attach)(struct cgroup_taskset *);
	void (*post_attach)();
	int (*can_fork)(struct task_struct *, struct css_set *);
	void (*cancel_fork)(struct task_struct *, struct css_set *);
	void (*fork)(struct task_struct *);
	void (*exit)(struct task_struct *);
	void (*release)(struct task_struct *);
	void (*bind)(struct cgroup_subsys_state *);
	bool early_init: 1;
	bool implicit_on_dfl: 1;
	bool threaded: 1;
	bool broken_hierarchy: 1;
	bool warned_broken_hierarchy: 1;
	int id;
	const char *name;
	const char *legacy_name;
	struct cgroup_root *root;
	struct idr css_idr;
	struct list_head cfts;
	struct cftype *dfl_cftypes;
	struct cftype *legacy_cftypes;
	unsigned int depends_on;
};

struct cgroup_rstat_cpu {
	struct u64_stats_sync bsync;
	struct cgroup_base_stat bstat;
	struct cgroup_base_stat last_bstat;
	struct cgroup *updated_children;
	struct cgroup *updated_next;
};

struct cgroup_root {
	struct kernfs_root *kf_root;
	unsigned int subsys_mask;
	int hierarchy_id;
	struct cgroup cgrp;
	u64 cgrp_ancestor_id_storage;
	atomic_t nr_cgrps;
	struct list_head root_list;
	unsigned int flags;
	char release_agent_path[4096];
	char name[64];
};

struct cftype {
	char name[64];
	long unsigned int private;
	size_t max_write_len;
	unsigned int flags;
	unsigned int file_offset;
	struct cgroup_subsys *ss;
	struct list_head node;
	struct kernfs_ops *kf_ops;
	int (*open)(struct kernfs_open_file *);
	void (*release)(struct kernfs_open_file *);
	u64 (*read_u64)(struct cgroup_subsys_state *, struct cftype *);
	s64 (*read_s64)(struct cgroup_subsys_state *, struct cftype *);
	int (*seq_show)(struct seq_file *, void *);
	void * (*seq_start)(struct seq_file *, loff_t *);
	void * (*seq_next)(struct seq_file *, void *, loff_t *);
	void (*seq_stop)(struct seq_file *, void *);
	int (*write_u64)(struct cgroup_subsys_state *, struct cftype *, u64);
	int (*write_s64)(struct cgroup_subsys_state *, struct cftype *, s64);
	ssize_t (*write)(struct kernfs_open_file *, char *, size_t, loff_t);
	__poll_t (*poll)(struct kernfs_open_file *, struct poll_table_struct *);
};

enum kmalloc_cache_type {
	KMALLOC_NORMAL = 0,
	KMALLOC_RECLAIM = 1,
	KMALLOC_DMA = 2,
	NR_KMALLOC_TYPES = 3,
};

struct perf_callchain_entry {
	__u64 nr;
	__u64 ip[0];
};

typedef long unsigned int (*perf_copy_f)(void *, const void *, long unsigned int, long unsigned int);

struct perf_raw_frag {
	union {
		struct perf_raw_frag *next;
		long unsigned int pad;
	};
	perf_copy_f copy;
	void *data;
	u32 size;
} __attribute__((packed));

struct perf_raw_record {
	struct perf_raw_frag frag;
	u32 size;
};

struct perf_branch_stack {
	__u64 nr;
	__u64 hw_idx;
	struct perf_branch_entry entries[0];
};

struct perf_cpu_context {
	struct perf_event_context ctx;
	struct perf_event_context *task_ctx;
	int active_oncpu;
	int exclusive;
	raw_spinlock_t hrtimer_lock;
	struct hrtimer hrtimer;
	ktime_t hrtimer_interval;
	unsigned int hrtimer_active;
	struct list_head sched_cb_entry;
	int sched_cb_usage;
	int online;
	int heap_size;
	struct perf_event **heap;
	struct perf_event *heap_default[2];
};

struct perf_output_handle {
	struct perf_event *event;
	struct perf_buffer *rb;
	long unsigned int wakeup;
	long unsigned int size;
	u64 aux_flags;
	union {
		void *addr;
		long unsigned int head;
	};
	int page;
};

struct perf_addr_filter_range {
	long unsigned int start;
	long unsigned int size;
};

struct perf_sample_data {
	u64 addr;
	struct perf_raw_record *raw;
	struct perf_branch_stack *br_stack;
	u64 period;
	u64 weight;
	u64 txn;
	union perf_mem_data_src data_src;
	u64 type;
	u64 ip;
	struct {
		u32 pid;
		u32 tid;
	} tid_entry;
	u64 time;
	u64 id;
	u64 stream_id;
	struct {
		u32 cpu;
		u32 reserved;
	} cpu_entry;
	struct perf_callchain_entry *callchain;
	u64 aux_size;
	struct perf_regs regs_user;
	struct pt_regs regs_user_copy;
	struct perf_regs regs_intr;
	u64 stack_user_size;
	u64 phys_addr;
	u64 cgroup;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct trace_entry {
	short unsigned int type;
	unsigned char flags;
	unsigned char preempt_count;
	int pid;
};

struct trace_array;

struct tracer;

struct array_buffer;

struct ring_buffer_iter;

struct trace_iterator {
	struct trace_array *tr;
	struct tracer *trace;
	struct array_buffer *array_buffer;
	void *private;
	int cpu_file;
	struct mutex mutex;
	struct ring_buffer_iter **buffer_iter;
	long unsigned int iter_flags;
	void *temp;
	unsigned int temp_size;
	struct trace_seq tmp_seq;
	cpumask_var_t started;
	bool snapshot;
	struct trace_seq seq;
	struct trace_entry *ent;
	long unsigned int lost_events;
	int leftover;
	int ent_size;
	int cpu;
	u64 ts;
	loff_t pos;
	long int idx;
};

enum print_line_t {
	TRACE_TYPE_PARTIAL_LINE = 0,
	TRACE_TYPE_HANDLED = 1,
	TRACE_TYPE_UNHANDLED = 2,
	TRACE_TYPE_NO_CONSUME = 3,
};

typedef enum print_line_t (*trace_print_func)(struct trace_iterator *, int, struct trace_event *);

struct trace_event_functions {
	trace_print_func trace;
	trace_print_func raw;
	trace_print_func hex;
	trace_print_func binary;
};

enum trace_reg {
	TRACE_REG_REGISTER = 0,
	TRACE_REG_UNREGISTER = 1,
	TRACE_REG_PERF_REGISTER = 2,
	TRACE_REG_PERF_UNREGISTER = 3,
	TRACE_REG_PERF_OPEN = 4,
	TRACE_REG_PERF_CLOSE = 5,
	TRACE_REG_PERF_ADD = 6,
	TRACE_REG_PERF_DEL = 7,
};

struct trace_event_fields {
	const char *type;
	union {
		struct {
			const char *name;
			const int size;
			const int align;
			const int is_signed;
			const int filter_type;
		};
		int (*define_fields)(struct trace_event_call *);
	};
};

struct trace_event_class {
	const char *system;
	void *probe;
	void *perf_probe;
	int (*reg)(struct trace_event_call *, enum trace_reg, void *);
	struct trace_event_fields *fields_array;
	struct list_head * (*get_fields)(struct trace_event_call *);
	struct list_head fields;
	int (*raw_init)(struct trace_event_call *);
};

struct trace_buffer;

struct trace_event_file;

struct trace_event_buffer {
	struct trace_buffer *buffer;
	struct ring_buffer_event *event;
	struct trace_event_file *trace_file;
	void *entry;
	long unsigned int flags;
	int pc;
	struct pt_regs *regs;
};

struct trace_subsystem_dir;

struct trace_event_file {
	struct list_head list;
	struct trace_event_call *event_call;
	struct event_filter *filter;
	struct dentry *dir;
	struct trace_array *tr;
	struct trace_subsystem_dir *system;
	struct list_head triggers;
	long unsigned int flags;
	atomic_t sm_ref;
	atomic_t tm_ref;
};

enum {
	TRACE_EVENT_FL_FILTERED_BIT = 0,
	TRACE_EVENT_FL_CAP_ANY_BIT = 1,
	TRACE_EVENT_FL_NO_SET_FILTER_BIT = 2,
	TRACE_EVENT_FL_IGNORE_ENABLE_BIT = 3,
	TRACE_EVENT_FL_TRACEPOINT_BIT = 4,
	TRACE_EVENT_FL_KPROBE_BIT = 5,
	TRACE_EVENT_FL_UPROBE_BIT = 6,
};

enum {
	TRACE_EVENT_FL_FILTERED = 1,
	TRACE_EVENT_FL_CAP_ANY = 2,
	TRACE_EVENT_FL_NO_SET_FILTER = 4,
	TRACE_EVENT_FL_IGNORE_ENABLE = 8,
	TRACE_EVENT_FL_TRACEPOINT = 16,
	TRACE_EVENT_FL_KPROBE = 32,
	TRACE_EVENT_FL_UPROBE = 64,
};

enum {
	EVENT_FILE_FL_ENABLED_BIT = 0,
	EVENT_FILE_FL_RECORDED_CMD_BIT = 1,
	EVENT_FILE_FL_RECORDED_TGID_BIT = 2,
	EVENT_FILE_FL_FILTERED_BIT = 3,
	EVENT_FILE_FL_NO_SET_FILTER_BIT = 4,
	EVENT_FILE_FL_SOFT_MODE_BIT = 5,
	EVENT_FILE_FL_SOFT_DISABLED_BIT = 6,
	EVENT_FILE_FL_TRIGGER_MODE_BIT = 7,
	EVENT_FILE_FL_TRIGGER_COND_BIT = 8,
	EVENT_FILE_FL_PID_FILTER_BIT = 9,
	EVENT_FILE_FL_WAS_ENABLED_BIT = 10,
};

enum {
	EVENT_FILE_FL_ENABLED = 1,
	EVENT_FILE_FL_RECORDED_CMD = 2,
	EVENT_FILE_FL_RECORDED_TGID = 4,
	EVENT_FILE_FL_FILTERED = 8,
	EVENT_FILE_FL_NO_SET_FILTER = 16,
	EVENT_FILE_FL_SOFT_MODE = 32,
	EVENT_FILE_FL_SOFT_DISABLED = 64,
	EVENT_FILE_FL_TRIGGER_MODE = 128,
	EVENT_FILE_FL_TRIGGER_COND = 256,
	EVENT_FILE_FL_PID_FILTER = 512,
	EVENT_FILE_FL_WAS_ENABLED = 1024,
};

enum {
	FILTER_OTHER = 0,
	FILTER_STATIC_STRING = 1,
	FILTER_DYN_STRING = 2,
	FILTER_PTR_STRING = 3,
	FILTER_TRACE_FN = 4,
	FILTER_COMM = 5,
	FILTER_CPU = 6,
};

struct rnd_state {
	__u32 s1;
	__u32 s2;
	__u32 s3;
	__u32 s4;
};

struct property {
	char *name;
	int length;
	void *value;
	struct property *next;
};

struct irq_fwspec {
	struct fwnode_handle *fwnode;
	int param_count;
	u32 param[16];
};

struct irq_data;

struct irq_domain_ops {
	int (*match)(struct irq_domain *, struct device_node *, enum irq_domain_bus_token);
	int (*select)(struct irq_domain *, struct irq_fwspec *, enum irq_domain_bus_token);
	int (*map)(struct irq_domain *, unsigned int, irq_hw_number_t);
	void (*unmap)(struct irq_domain *, unsigned int);
	int (*xlate)(struct irq_domain *, struct device_node *, const u32 *, unsigned int, long unsigned int *, unsigned int *);
	int (*alloc)(struct irq_domain *, unsigned int, unsigned int, void *);
	void (*free)(struct irq_domain *, unsigned int, unsigned int);
	int (*activate)(struct irq_domain *, struct irq_data *, bool);
	void (*deactivate)(struct irq_domain *, struct irq_data *);
	int (*translate)(struct irq_domain *, struct irq_fwspec *, long unsigned int *, unsigned int *);
};

struct acpi_table_header {
	char signature[4];
	u32 length;
	u8 revision;
	u8 checksum;
	char oem_id[6];
	char oem_table_id[8];
	u32 oem_revision;
	char asl_compiler_id[4];
	u32 asl_compiler_revision;
};

struct acpi_generic_address {
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_width;
	u64 address;
} __attribute__((packed));

struct acpi_table_fadt {
	struct acpi_table_header header;
	u32 facs;
	u32 dsdt;
	u8 model;
	u8 preferred_profile;
	u16 sci_interrupt;
	u32 smi_command;
	u8 acpi_enable;
	u8 acpi_disable;
	u8 s4_bios_request;
	u8 pstate_control;
	u32 pm1a_event_block;
	u32 pm1b_event_block;
	u32 pm1a_control_block;
	u32 pm1b_control_block;
	u32 pm2_control_block;
	u32 pm_timer_block;
	u32 gpe0_block;
	u32 gpe1_block;
	u8 pm1_event_length;
	u8 pm1_control_length;
	u8 pm2_control_length;
	u8 pm_timer_length;
	u8 gpe0_block_length;
	u8 gpe1_block_length;
	u8 gpe1_base;
	u8 cst_control;
	u16 c2_latency;
	u16 c3_latency;
	u16 flush_size;
	u16 flush_stride;
	u8 duty_offset;
	u8 duty_width;
	u8 day_alarm;
	u8 month_alarm;
	u8 century;
	u16 boot_flags;
	u8 reserved;
	u32 flags;
	struct acpi_generic_address reset_register;
	u8 reset_value;
	u16 arm_boot_flags;
	u8 minor_revision;
	u64 Xfacs;
	u64 Xdsdt;
	struct acpi_generic_address xpm1a_event_block;
	struct acpi_generic_address xpm1b_event_block;
	struct acpi_generic_address xpm1a_control_block;
	struct acpi_generic_address xpm1b_control_block;
	struct acpi_generic_address xpm2_control_block;
	struct acpi_generic_address xpm_timer_block;
	struct acpi_generic_address xgpe0_block;
	struct acpi_generic_address xgpe1_block;
	struct acpi_generic_address sleep_control;
	struct acpi_generic_address sleep_status;
	u64 hypervisor_id;
} __attribute__((packed));

enum acpi_irq_model_id {
	ACPI_IRQ_MODEL_PIC = 0,
	ACPI_IRQ_MODEL_IOAPIC = 1,
	ACPI_IRQ_MODEL_IOSAPIC = 2,
	ACPI_IRQ_MODEL_PLATFORM = 3,
	ACPI_IRQ_MODEL_GIC = 4,
	ACPI_IRQ_MODEL_COUNT = 5,
};

enum con_scroll {
	SM_UP = 0,
	SM_DOWN = 1,
};

struct vc_data;

struct console_font;

struct consw {
	struct module *owner;
	const char * (*con_startup)();
	void (*con_init)(struct vc_data *, int);
	void (*con_deinit)(struct vc_data *);
	void (*con_clear)(struct vc_data *, int, int, int, int);
	void (*con_putc)(struct vc_data *, int, int, int);
	void (*con_putcs)(struct vc_data *, const short unsigned int *, int, int, int);
	void (*con_cursor)(struct vc_data *, int);
	bool (*con_scroll)(struct vc_data *, unsigned int, unsigned int, enum con_scroll, unsigned int);
	int (*con_switch)(struct vc_data *);
	int (*con_blank)(struct vc_data *, int, int);
	int (*con_font_set)(struct vc_data *, struct console_font *, unsigned int);
	int (*con_font_get)(struct vc_data *, struct console_font *);
	int (*con_font_default)(struct vc_data *, struct console_font *, char *);
	int (*con_font_copy)(struct vc_data *, int);
	int (*con_resize)(struct vc_data *, unsigned int, unsigned int, unsigned int);
	void (*con_set_palette)(struct vc_data *, const unsigned char *);
	void (*con_scrolldelta)(struct vc_data *, int);
	int (*con_set_origin)(struct vc_data *);
	void (*con_save_screen)(struct vc_data *);
	u8 (*con_build_attr)(struct vc_data *, u8, u8, u8, u8, u8, u8);
	void (*con_invert_region)(struct vc_data *, u16 *, int);
	u16 * (*con_screen_pos)(struct vc_data *, int);
	long unsigned int (*con_getxy)(struct vc_data *, long unsigned int, int *, int *);
	void (*con_flush_scrollback)(struct vc_data *);
	int (*con_debug_enter)(struct vc_data *);
	int (*con_debug_leave)(struct vc_data *);
};

struct tty_driver;

struct console {
	char name[16];
	void (*write)(struct console *, const char *, unsigned int);
	int (*read)(struct console *, char *, unsigned int);
	struct tty_driver * (*device)(struct console *, int *);
	void (*unblank)();
	int (*setup)(struct console *, char *);
	int (*exit)(struct console *);
	int (*match)(struct console *, char *, int, char *);
	short int flags;
	short int index;
	int cflag;
	void *data;
	struct console *next;
};

struct fprop_global {
	struct percpu_counter events;
	unsigned int period;
	seqcount_t sequence;
};

enum wb_stat_item {
	WB_RECLAIMABLE = 0,
	WB_WRITEBACK = 1,
	WB_DIRTIED = 2,
	WB_WRITTEN = 3,
	NR_WB_STAT_ITEMS = 4,
};

struct bdi_writeback_congested {
	long unsigned int state;
	refcount_t refcnt;
};

struct partition_meta_info {
	char uuid[37];
	u8 volname[64];
};

struct disk_part_tbl {
	struct callback_head callback_head;
	int len;
	struct hd_struct *last_lookup;
	struct hd_struct *part[0];
};

struct blk_zone;

typedef int (*report_zones_cb)(struct blk_zone *, unsigned int, void *);

struct hd_geometry;

struct pr_ops;

struct block_device_operations {
	int (*open)(struct block_device *, fmode_t);
	void (*release)(struct gendisk *, fmode_t);
	int (*rw_page)(struct block_device *, sector_t, struct page *, unsigned int);
	int (*ioctl)(struct block_device *, fmode_t, unsigned int, long unsigned int);
	int (*compat_ioctl)(struct block_device *, fmode_t, unsigned int, long unsigned int);
	unsigned int (*check_events)(struct gendisk *, unsigned int);
	int (*media_changed)(struct gendisk *);
	void (*unlock_native_capacity)(struct gendisk *);
	int (*revalidate_disk)(struct gendisk *);
	int (*getgeo)(struct block_device *, struct hd_geometry *);
	void (*swap_slot_free_notify)(struct block_device *, long unsigned int);
	int (*report_zones)(struct gendisk *, sector_t, unsigned int, report_zones_cb, void *);
	char * (*devnode)(struct gendisk *, umode_t *);
	struct module *owner;
	const struct pr_ops *pr_ops;
};

struct sg_io_v4 {
	__s32 guard;
	__u32 protocol;
	__u32 subprotocol;
	__u32 request_len;
	__u64 request;
	__u64 request_tag;
	__u32 request_attr;
	__u32 request_priority;
	__u32 request_extra;
	__u32 max_response_len;
	__u64 response;
	__u32 dout_iovec_count;
	__u32 dout_xfer_len;
	__u32 din_iovec_count;
	__u32 din_xfer_len;
	__u64 dout_xferp;
	__u64 din_xferp;
	__u32 timeout;
	__u32 flags;
	__u64 usr_ptr;
	__u32 spare_in;
	__u32 driver_status;
	__u32 transport_status;
	__u32 device_status;
	__u32 retry_delay;
	__u32 info;
	__u32 duration;
	__u32 response_len;
	__s32 din_resid;
	__s32 dout_resid;
	__u64 generated_tag;
	__u32 spare_out;
	__u32 padding;
};

struct bsg_ops {
	int (*check_proto)(struct sg_io_v4 *);
	int (*fill_hdr)(struct request *, struct sg_io_v4 *, fmode_t);
	int (*complete_rq)(struct request *, struct sg_io_v4 *);
	void (*free_rq)(struct request *);
};

typedef __u32 req_flags_t;

typedef void rq_end_io_fn(struct request *, blk_status_t);

enum mq_rq_state {
	MQ_RQ_IDLE = 0,
	MQ_RQ_IN_FLIGHT = 1,
	MQ_RQ_COMPLETE = 2,
};

struct request {
	struct request_queue *q;
	struct blk_mq_ctx *mq_ctx;
	struct blk_mq_hw_ctx *mq_hctx;
	unsigned int cmd_flags;
	req_flags_t rq_flags;
	int tag;
	int internal_tag;
	unsigned int __data_len;
	sector_t __sector;
	struct bio *bio;
	struct bio *biotail;
	struct list_head queuelist;
	union {
		struct hlist_node hash;
		struct list_head ipi_list;
	};
	union {
		struct rb_node rb_node;
		struct bio_vec special_vec;
		void *completion_data;
		int error_count;
	};
	union {
		struct {
			struct io_cq *icq;
			void *priv[2];
		} elv;
		struct {
			unsigned int seq;
			struct list_head list;
			rq_end_io_fn *saved_end_io;
		} flush;
	};
	struct gendisk *rq_disk;
	struct hd_struct *part;
	u64 start_time_ns;
	u64 io_start_time_ns;
	short unsigned int stats_sectors;
	short unsigned int nr_phys_segments;
	short unsigned int write_hint;
	short unsigned int ioprio;
	enum mq_rq_state state;
	refcount_t ref;
	unsigned int timeout;
	long unsigned int deadline;
	union {
		struct __call_single_data csd;
		u64 fifo_time;
	};
	rq_end_io_fn *end_io;
	void *end_io_data;
};

struct blk_zone {
	__u64 start;
	__u64 len;
	__u64 wp;
	__u8 type;
	__u8 cond;
	__u8 non_seq;
	__u8 reset;
	__u8 reserved[36];
};

enum elv_merge {
	ELEVATOR_NO_MERGE = 0,
	ELEVATOR_FRONT_MERGE = 1,
	ELEVATOR_BACK_MERGE = 2,
	ELEVATOR_DISCARD_MERGE = 3,
};

struct elevator_type;

struct blk_mq_alloc_data;

struct elevator_mq_ops {
	int (*init_sched)(struct request_queue *, struct elevator_type *);
	void (*exit_sched)(struct elevator_queue *);
	int (*init_hctx)(struct blk_mq_hw_ctx *, unsigned int);
	void (*exit_hctx)(struct blk_mq_hw_ctx *, unsigned int);
	void (*depth_updated)(struct blk_mq_hw_ctx *);
	bool (*allow_merge)(struct request_queue *, struct request *, struct bio *);
	bool (*bio_merge)(struct blk_mq_hw_ctx *, struct bio *, unsigned int);
	int (*request_merge)(struct request_queue *, struct request **, struct bio *);
	void (*request_merged)(struct request_queue *, struct request *, enum elv_merge);
	void (*requests_merged)(struct request_queue *, struct request *, struct request *);
	void (*limit_depth)(unsigned int, struct blk_mq_alloc_data *);
	void (*prepare_request)(struct request *);
	void (*finish_request)(struct request *);
	void (*insert_requests)(struct blk_mq_hw_ctx *, struct list_head *, bool);
	struct request * (*dispatch_request)(struct blk_mq_hw_ctx *);
	bool (*has_work)(struct blk_mq_hw_ctx *);
	void (*completed_request)(struct request *, u64);
	void (*requeue_request)(struct request *);
	struct request * (*former_request)(struct request_queue *, struct request *);
	struct request * (*next_request)(struct request_queue *, struct request *);
	void (*init_icq)(struct io_cq *);
	void (*exit_icq)(struct io_cq *);
};

struct elv_fs_entry;

struct blk_mq_debugfs_attr;

struct elevator_type {
	struct kmem_cache *icq_cache;
	struct elevator_mq_ops ops;
	size_t icq_size;
	size_t icq_align;
	struct elv_fs_entry *elevator_attrs;
	const char *elevator_name;
	const char *elevator_alias;
	const unsigned int elevator_features;
	struct module *elevator_owner;
	const struct blk_mq_debugfs_attr *queue_debugfs_attrs;
	const struct blk_mq_debugfs_attr *hctx_debugfs_attrs;
	char icq_cache_name[22];
	struct list_head list;
};

struct elevator_queue {
	struct elevator_type *type;
	void *elevator_data;
	struct kobject kobj;
	struct mutex sysfs_lock;
	unsigned int registered: 1;
	struct hlist_head hash[64];
};

struct elv_fs_entry {
	struct attribute attr;
	ssize_t (*show)(struct elevator_queue *, char *);
	ssize_t (*store)(struct elevator_queue *, const char *, size_t);
};

struct blk_mq_debugfs_attr {
	const char *name;
	umode_t mode;
	int (*show)(void *, struct seq_file *);
	ssize_t (*write)(void *, const char *, size_t, loff_t *);
	const struct seq_operations *seq_ops;
};

struct blk_mq_queue_data;

typedef blk_status_t queue_rq_fn(struct blk_mq_hw_ctx *, const struct blk_mq_queue_data *);

typedef void commit_rqs_fn(struct blk_mq_hw_ctx *);

typedef bool get_budget_fn(struct blk_mq_hw_ctx *);

typedef void put_budget_fn(struct blk_mq_hw_ctx *);

enum blk_eh_timer_return {
	BLK_EH_DONE = 0,
	BLK_EH_RESET_TIMER = 1,
};

typedef enum blk_eh_timer_return timeout_fn(struct request *, bool);

typedef int poll_fn(struct blk_mq_hw_ctx *);

typedef void complete_fn(struct request *);

typedef int init_hctx_fn(struct blk_mq_hw_ctx *, void *, unsigned int);

typedef void exit_hctx_fn(struct blk_mq_hw_ctx *, unsigned int);

typedef int init_request_fn(struct blk_mq_tag_set *, struct request *, unsigned int, unsigned int);

typedef void exit_request_fn(struct blk_mq_tag_set *, struct request *, unsigned int);

typedef void cleanup_rq_fn(struct request *);

typedef bool busy_fn(struct request_queue *);

typedef int map_queues_fn(struct blk_mq_tag_set *);

struct blk_mq_ops {
	queue_rq_fn *queue_rq;
	commit_rqs_fn *commit_rqs;
	get_budget_fn *get_budget;
	put_budget_fn *put_budget;
	timeout_fn *timeout;
	poll_fn *poll;
	complete_fn *complete;
	init_hctx_fn *init_hctx;
	exit_hctx_fn *exit_hctx;
	init_request_fn *init_request;
	exit_request_fn *exit_request;
	void (*initialize_rq_fn)(struct request *);
	cleanup_rq_fn *cleanup_rq;
	busy_fn *busy;
	map_queues_fn *map_queues;
	void (*show_rq)(struct seq_file *, struct request *);
};

enum pr_type {
	PR_WRITE_EXCLUSIVE = 1,
	PR_EXCLUSIVE_ACCESS = 2,
	PR_WRITE_EXCLUSIVE_REG_ONLY = 3,
	PR_EXCLUSIVE_ACCESS_REG_ONLY = 4,
	PR_WRITE_EXCLUSIVE_ALL_REGS = 5,
	PR_EXCLUSIVE_ACCESS_ALL_REGS = 6,
};

struct pr_ops {
	int (*pr_register)(struct block_device *, u64, u64, u32);
	int (*pr_reserve)(struct block_device *, u64, enum pr_type, u32);
	int (*pr_release)(struct block_device *, u64, enum pr_type);
	int (*pr_preempt)(struct block_device *, u64, u64, enum pr_type, bool);
	int (*pr_clear)(struct block_device *, u64);
};

struct wb_domain {
	spinlock_t lock;
	struct fprop_global completions;
	struct timer_list period_timer;
	long unsigned int period_time;
	long unsigned int dirty_limit_tstamp;
	long unsigned int dirty_limit;
};

enum cpu_idle_type {
	CPU_IDLE = 0,
	CPU_NOT_IDLE = 1,
	CPU_NEWLY_IDLE = 2,
	CPU_MAX_IDLE_TYPES = 3,
};

enum reboot_mode {
	REBOOT_UNDEFINED = 4294967295,
	REBOOT_COLD = 0,
	REBOOT_WARM = 1,
	REBOOT_HARD = 2,
	REBOOT_SOFT = 3,
	REBOOT_GPIO = 4,
};

enum reboot_type {
	BOOT_TRIPLE = 116,
	BOOT_KBD = 107,
	BOOT_BIOS = 98,
	BOOT_ACPI = 97,
	BOOT_EFI = 101,
	BOOT_CF9_FORCE = 112,
	BOOT_CF9_SAFE = 113,
};

typedef long unsigned int efi_status_t;

typedef u8 efi_bool_t;

typedef u16 efi_char16_t;

typedef guid_t efi_guid_t;

typedef struct {
	u64 signature;
	u32 revision;
	u32 headersize;
	u32 crc32;
	u32 reserved;
} efi_table_hdr_t;

typedef struct {
	u32 type;
	u32 pad;
	u64 phys_addr;
	u64 virt_addr;
	u64 num_pages;
	u64 attribute;
} efi_memory_desc_t;

typedef struct {
	efi_guid_t guid;
	u32 headersize;
	u32 flags;
	u32 imagesize;
} efi_capsule_header_t;

typedef struct {
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
	u8 pad1;
	u32 nanosecond;
	s16 timezone;
	u8 daylight;
	u8 pad2;
} efi_time_t;

typedef struct {
	u32 resolution;
	u32 accuracy;
	u8 sets_to_zero;
} efi_time_cap_t;

typedef struct {
	efi_table_hdr_t hdr;
	u32 get_time;
	u32 set_time;
	u32 get_wakeup_time;
	u32 set_wakeup_time;
	u32 set_virtual_address_map;
	u32 convert_pointer;
	u32 get_variable;
	u32 get_next_variable;
	u32 set_variable;
	u32 get_next_high_mono_count;
	u32 reset_system;
	u32 update_capsule;
	u32 query_capsule_caps;
	u32 query_variable_info;
} efi_runtime_services_32_t;

typedef efi_status_t efi_get_time_t(efi_time_t *, efi_time_cap_t *);

typedef efi_status_t efi_set_time_t(efi_time_t *);

typedef efi_status_t efi_get_wakeup_time_t(efi_bool_t *, efi_bool_t *, efi_time_t *);

typedef efi_status_t efi_set_wakeup_time_t(efi_bool_t, efi_time_t *);

typedef efi_status_t efi_get_variable_t(efi_char16_t *, efi_guid_t *, u32 *, long unsigned int *, void *);

typedef efi_status_t efi_get_next_variable_t(long unsigned int *, efi_char16_t *, efi_guid_t *);

typedef efi_status_t efi_set_variable_t(efi_char16_t *, efi_guid_t *, u32, long unsigned int, void *);

typedef efi_status_t efi_get_next_high_mono_count_t(u32 *);

typedef void efi_reset_system_t(int, efi_status_t, long unsigned int, efi_char16_t *);

typedef efi_status_t efi_query_variable_info_t(u32, u64 *, u64 *, u64 *);

typedef efi_status_t efi_update_capsule_t(efi_capsule_header_t **, long unsigned int, long unsigned int);

typedef efi_status_t efi_query_capsule_caps_t(efi_capsule_header_t **, long unsigned int, u64 *, int *);

typedef union {
	struct {
		efi_table_hdr_t hdr;
		efi_status_t (*get_time)(efi_time_t *, efi_time_cap_t *);
		efi_status_t (*set_time)(efi_time_t *);
		efi_status_t (*get_wakeup_time)(efi_bool_t *, efi_bool_t *, efi_time_t *);
		efi_status_t (*set_wakeup_time)(efi_bool_t, efi_time_t *);
		efi_status_t (*set_virtual_address_map)(long unsigned int, long unsigned int, u32, efi_memory_desc_t *);
		void *convert_pointer;
		efi_status_t (*get_variable)(efi_char16_t *, efi_guid_t *, u32 *, long unsigned int *, void *);
		efi_status_t (*get_next_variable)(long unsigned int *, efi_char16_t *, efi_guid_t *);
		efi_status_t (*set_variable)(efi_char16_t *, efi_guid_t *, u32, long unsigned int, void *);
		efi_status_t (*get_next_high_mono_count)(u32 *);
		void (*reset_system)(int, efi_status_t, long unsigned int, efi_char16_t *);
		efi_status_t (*update_capsule)(efi_capsule_header_t **, long unsigned int, long unsigned int);
		efi_status_t (*query_capsule_caps)(efi_capsule_header_t **, long unsigned int, u64 *, int *);
		efi_status_t (*query_variable_info)(u32, u64 *, u64 *, u64 *);
	};
	efi_runtime_services_32_t mixed_mode;
} efi_runtime_services_t;

struct efi_memory_map {
	phys_addr_t phys_map;
	void *map;
	void *map_end;
	int nr_map;
	long unsigned int desc_version;
	long unsigned int desc_size;
	long unsigned int flags;
};

struct efi {
	const efi_runtime_services_t *runtime;
	unsigned int runtime_version;
	unsigned int runtime_supported_mask;
	long unsigned int acpi;
	long unsigned int acpi20;
	long unsigned int smbios;
	long unsigned int smbios3;
	long unsigned int esrt;
	long unsigned int tpm_log;
	long unsigned int tpm_final_log;
	efi_get_time_t *get_time;
	efi_set_time_t *set_time;
	efi_get_wakeup_time_t *get_wakeup_time;
	efi_set_wakeup_time_t *set_wakeup_time;
	efi_get_variable_t *get_variable;
	efi_get_next_variable_t *get_next_variable;
	efi_set_variable_t *set_variable;
	efi_set_variable_t *set_variable_nonblocking;
	efi_query_variable_info_t *query_variable_info;
	efi_query_variable_info_t *query_variable_info_nonblocking;
	efi_update_capsule_t *update_capsule;
	efi_query_capsule_caps_t *query_capsule_caps;
	efi_get_next_high_mono_count_t *get_next_high_mono_count;
	efi_reset_system_t *reset_system;
	struct efi_memory_map memmap;
	long unsigned int flags;
};

enum efi_rts_ids {
	EFI_NONE = 0,
	EFI_GET_TIME = 1,
	EFI_SET_TIME = 2,
	EFI_GET_WAKEUP_TIME = 3,
	EFI_SET_WAKEUP_TIME = 4,
	EFI_GET_VARIABLE = 5,
	EFI_GET_NEXT_VARIABLE = 6,
	EFI_SET_VARIABLE = 7,
	EFI_QUERY_VARIABLE_INFO = 8,
	EFI_GET_NEXT_HIGH_MONO_COUNT = 9,
	EFI_RESET_SYSTEM = 10,
	EFI_UPDATE_CAPSULE = 11,
	EFI_QUERY_CAPSULE_CAPS = 12,
};

struct efi_runtime_work {
	void *arg1;
	void *arg2;
	void *arg3;
	void *arg4;
	void *arg5;
	efi_status_t status;
	struct work_struct work;
	enum efi_rts_ids efi_rts_id;
	struct completion efi_rts_comp;
};

struct percpu_cluster {
	struct swap_cluster_info index;
	unsigned int next;
};

enum fs_value_type {
	fs_value_is_undefined = 0,
	fs_value_is_flag = 1,
	fs_value_is_string = 2,
	fs_value_is_blob = 3,
	fs_value_is_filename = 4,
	fs_value_is_file = 5,
};

struct fs_parameter {
	const char *key;
	enum fs_value_type type: 8;
	union {
		char *string;
		void *blob;
		struct filename *name;
		struct file *file;
	};
	size_t size;
	int dirfd;
};

struct fc_log {
	refcount_t usage;
	u8 head;
	u8 tail;
	u8 need_free;
	struct module *owner;
	char *buffer[8];
};

struct fs_context_operations {
	void (*free)(struct fs_context *);
	int (*dup)(struct fs_context *, struct fs_context *);
	int (*parse_param)(struct fs_context *, struct fs_parameter *);
	int (*parse_monolithic)(struct fs_context *, void *);
	int (*get_tree)(struct fs_context *);
	int (*reconfigure)(struct fs_context *);
};

struct fs_parse_result {
	bool negated;
	union {
		bool boolean;
		int int_32;
		unsigned int uint_32;
		u64 uint_64;
	};
};

struct trace_event_raw_initcall_level {
	struct trace_entry ent;
	u32 __data_loc_level;
	char __data[0];
};

struct trace_event_raw_initcall_start {
	struct trace_entry ent;
	initcall_t func;
	char __data[0];
};

struct trace_event_raw_initcall_finish {
	struct trace_entry ent;
	initcall_t func;
	int ret;
	char __data[0];
};

struct trace_event_data_offsets_initcall_level {
	u32 level;
};

struct trace_event_data_offsets_initcall_start {};

struct trace_event_data_offsets_initcall_finish {};

typedef void (*btf_trace_initcall_level)(void *, const char *);

typedef void (*btf_trace_initcall_start)(void *, initcall_t);

typedef void (*btf_trace_initcall_finish)(void *, initcall_t, int);

struct blacklist_entry {
	struct list_head next;
	char *buf;
};

typedef __u32 Elf32_Word;

struct elf32_note {
	Elf32_Word n_namesz;
	Elf32_Word n_descsz;
	Elf32_Word n_type;
};

enum {
	UNAME26 = 131072,
	ADDR_NO_RANDOMIZE = 262144,
	FDPIC_FUNCPTRS = 524288,
	MMAP_PAGE_ZERO = 1048576,
	ADDR_COMPAT_LAYOUT = 2097152,
	READ_IMPLIES_EXEC = 4194304,
	ADDR_LIMIT_32BIT = 8388608,
	SHORT_INODE = 16777216,
	WHOLE_SECONDS = 33554432,
	STICKY_TIMEOUTS = 67108864,
	ADDR_LIMIT_3GB = 134217728,
};

enum tlb_infos {
	ENTRIES = 0,
	NR_INFO = 1,
};

enum {
	MM_FILEPAGES = 0,
	MM_ANONPAGES = 1,
	MM_SWAPENTS = 2,
	MM_SHMEMPAGES = 3,
	NR_MM_COUNTERS = 4,
};

enum hrtimer_base_type {
	HRTIMER_BASE_MONOTONIC = 0,
	HRTIMER_BASE_REALTIME = 1,
	HRTIMER_BASE_BOOTTIME = 2,
	HRTIMER_BASE_TAI = 3,
	HRTIMER_BASE_MONOTONIC_SOFT = 4,
	HRTIMER_BASE_REALTIME_SOFT = 5,
	HRTIMER_BASE_BOOTTIME_SOFT = 6,
	HRTIMER_BASE_TAI_SOFT = 7,
	HRTIMER_MAX_CLOCK_BASES = 8,
};

enum rseq_cs_flags_bit {
	RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT_BIT = 0,
	RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL_BIT = 1,
	RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE_BIT = 2,
};

enum perf_event_task_context {
	perf_invalid_context = 4294967295,
	perf_hw_context = 0,
	perf_sw_context = 1,
	perf_nr_task_contexts = 2,
};

enum rseq_event_mask_bits {
	RSEQ_EVENT_PREEMPT_BIT = 0,
	RSEQ_EVENT_SIGNAL_BIT = 1,
	RSEQ_EVENT_MIGRATE_BIT = 2,
};

enum {
	PROC_ROOT_INO = 1,
	PROC_IPC_INIT_INO = 4026531839,
	PROC_UTS_INIT_INO = 4026531838,
	PROC_USER_INIT_INO = 4026531837,
	PROC_PID_INIT_INO = 4026531836,
	PROC_CGROUP_INIT_INO = 4026531835,
	PROC_TIME_INIT_INO = 4026531834,
};

typedef __u16 __le16;

typedef __u16 __be16;

typedef __u32 __be32;

typedef __u64 __be64;

typedef __u32 __wsum;

typedef u64 uint64_t;

typedef unsigned int slab_flags_t;

struct raw_notifier_head {
	struct notifier_block *head;
};

struct llist_head {
	struct llist_node *first;
};

typedef struct __call_single_data call_single_data_t;

struct ida {
	struct xarray xa;
};

typedef __u64 __addrpair;

typedef __u32 __portpair;

typedef struct {
	struct net *net;
} possible_net_t;

struct in6_addr {
	union {
		__u8 u6_addr8[16];
		__be16 u6_addr16[8];
		__be32 u6_addr32[4];
	} in6_u;
};

struct hlist_nulls_node {
	struct hlist_nulls_node *next;
	struct hlist_nulls_node **pprev;
};

struct proto;

struct inet_timewait_death_row;

struct sock_common {
	union {
		__addrpair skc_addrpair;
		struct {
			__be32 skc_daddr;
			__be32 skc_rcv_saddr;
		};
	};
	union {
		unsigned int skc_hash;
		__u16 skc_u16hashes[2];
	};
	union {
		__portpair skc_portpair;
		struct {
			__be16 skc_dport;
			__u16 skc_num;
		};
	};
	short unsigned int skc_family;
	volatile unsigned char skc_state;
	unsigned char skc_reuse: 4;
	unsigned char skc_reuseport: 1;
	unsigned char skc_ipv6only: 1;
	unsigned char skc_net_refcnt: 1;
	int skc_bound_dev_if;
	union {
		struct hlist_node skc_bind_node;
		struct hlist_node skc_portaddr_node;
	};
	struct proto *skc_prot;
	possible_net_t skc_net;
	struct in6_addr skc_v6_daddr;
	struct in6_addr skc_v6_rcv_saddr;
	atomic64_t skc_cookie;
	union {
		long unsigned int skc_flags;
		struct sock *skc_listener;
		struct inet_timewait_death_row *skc_tw_dr;
	};
	int skc_dontcopy_begin[0];
	union {
		struct hlist_node skc_node;
		struct hlist_nulls_node skc_nulls_node;
	};
	short unsigned int skc_tx_queue_mapping;
	short unsigned int skc_rx_queue_mapping;
	union {
		int skc_incoming_cpu;
		u32 skc_rcv_wnd;
		u32 skc_tw_rcv_nxt;
	};
	refcount_t skc_refcnt;
	int skc_dontcopy_end[0];
	union {
		u32 skc_rxhash;
		u32 skc_window_clamp;
		u32 skc_tw_snd_nxt;
	};
};

typedef struct {
	spinlock_t slock;
	int owned;
	wait_queue_head_t wq;
} socket_lock_t;

struct sk_buff;

struct sk_buff_head {
	struct sk_buff *next;
	struct sk_buff *prev;
	__u32 qlen;
	spinlock_t lock;
};

typedef u64 netdev_features_t;

struct sock_cgroup_data {
	union {
		struct {
			u8 is_data: 1;
			u8 no_refcnt: 1;
			u8 unused: 6;
			u8 padding;
			u16 prioidx;
			u32 classid;
		};
		u64 val;
	};
};

struct sk_filter;

struct socket_wq;

struct xfrm_policy;

struct dst_entry;

struct socket;

struct sock_reuseport;

struct bpf_sk_storage;

struct sock {
	struct sock_common __sk_common;
	socket_lock_t sk_lock;
	atomic_t sk_drops;
	int sk_rcvlowat;
	struct sk_buff_head sk_error_queue;
	struct sk_buff *sk_rx_skb_cache;
	struct sk_buff_head sk_receive_queue;
	struct {
		atomic_t rmem_alloc;
		int len;
		struct sk_buff *head;
		struct sk_buff *tail;
	} sk_backlog;
	int sk_forward_alloc;
	unsigned int sk_ll_usec;
	unsigned int sk_napi_id;
	int sk_rcvbuf;
	struct sk_filter *sk_filter;
	union {
		struct socket_wq *sk_wq;
		struct socket_wq *sk_wq_raw;
	};
	struct xfrm_policy *sk_policy[2];
	struct dst_entry *sk_rx_dst;
	struct dst_entry *sk_dst_cache;
	atomic_t sk_omem_alloc;
	int sk_sndbuf;
	int sk_wmem_queued;
	refcount_t sk_wmem_alloc;
	long unsigned int sk_tsq_flags;
	union {
		struct sk_buff *sk_send_head;
		struct rb_root tcp_rtx_queue;
	};
	struct sk_buff *sk_tx_skb_cache;
	struct sk_buff_head sk_write_queue;
	__s32 sk_peek_off;
	int sk_write_pending;
	__u32 sk_dst_pending_confirm;
	u32 sk_pacing_status;
	long int sk_sndtimeo;
	struct timer_list sk_timer;
	__u32 sk_priority;
	__u32 sk_mark;
	long unsigned int sk_pacing_rate;
	long unsigned int sk_max_pacing_rate;
	struct page_frag sk_frag;
	netdev_features_t sk_route_caps;
	netdev_features_t sk_route_nocaps;
	netdev_features_t sk_route_forced_caps;
	int sk_gso_type;
	unsigned int sk_gso_max_size;
	gfp_t sk_allocation;
	__u32 sk_txhash;
	u8 sk_padding: 1;
	u8 sk_kern_sock: 1;
	u8 sk_no_check_tx: 1;
	u8 sk_no_check_rx: 1;
	u8 sk_userlocks: 4;
	u8 sk_pacing_shift;
	u16 sk_type;
	u16 sk_protocol;
	u16 sk_gso_max_segs;
	long unsigned int sk_lingertime;
	struct proto *sk_prot_creator;
	rwlock_t sk_callback_lock;
	int sk_err;
	int sk_err_soft;
	u32 sk_ack_backlog;
	u32 sk_max_ack_backlog;
	kuid_t sk_uid;
	struct pid *sk_peer_pid;
	const struct cred *sk_peer_cred;
	long int sk_rcvtimeo;
	ktime_t sk_stamp;
	u16 sk_tsflags;
	u8 sk_shutdown;
	u32 sk_tskey;
	atomic_t sk_zckey;
	u8 sk_clockid;
	u8 sk_txtime_deadline_mode: 1;
	u8 sk_txtime_report_errors: 1;
	u8 sk_txtime_unused: 6;
	struct socket *sk_socket;
	void *sk_user_data;
	void *sk_security;
	struct sock_cgroup_data sk_cgrp_data;
	struct mem_cgroup *sk_memcg;
	void (*sk_state_change)(struct sock *);
	void (*sk_data_ready)(struct sock *);
	void (*sk_write_space)(struct sock *);
	void (*sk_error_report)(struct sock *);
	int (*sk_backlog_rcv)(struct sock *, struct sk_buff *);
	void (*sk_destruct)(struct sock *);
	struct sock_reuseport *sk_reuseport_cb;
	struct bpf_sk_storage *sk_bpf_storage;
	struct callback_head sk_rcu;
};

struct rhash_head {
	struct rhash_head *next;
};

struct rhashtable;

struct rhashtable_compare_arg {
	struct rhashtable *ht;
	const void *key;
};

typedef u32 (*rht_hashfn_t)(const void *, u32, u32);

typedef u32 (*rht_obj_hashfn_t)(const void *, u32, u32);

typedef int (*rht_obj_cmpfn_t)(struct rhashtable_compare_arg *, const void *);

struct rhashtable_params {
	u16 nelem_hint;
	u16 key_len;
	u16 key_offset;
	u16 head_offset;
	unsigned int max_size;
	u16 min_size;
	bool automatic_shrinking;
	rht_hashfn_t hashfn;
	rht_obj_hashfn_t obj_hashfn;
	rht_obj_cmpfn_t obj_cmpfn;
};

struct bucket_table;

struct rhashtable {
	struct bucket_table *tbl;
	unsigned int key_len;
	unsigned int max_elems;
	struct rhashtable_params p;
	bool rhlist;
	struct work_struct run_work;
	struct mutex mutex;
	spinlock_t lock;
	atomic_t nelems;
};

struct fs_struct {
	int users;
	spinlock_t lock;
	seqcount_t seq;
	int umask;
	int in_exec;
	struct path root;
	struct path pwd;
};

typedef u32 compat_uptr_t;

struct compat_robust_list {
	compat_uptr_t next;
};

typedef s32 compat_long_t;

struct compat_robust_list_head {
	struct compat_robust_list list;
	compat_long_t futex_offset;
	compat_uptr_t list_op_pending;
};

struct pipe_buffer;

struct pipe_inode_info {
	struct mutex mutex;
	wait_queue_head_t rd_wait;
	wait_queue_head_t wr_wait;
	unsigned int head;
	unsigned int tail;
	unsigned int max_usage;
	unsigned int ring_size;
	unsigned int nr_accounted;
	unsigned int readers;
	unsigned int writers;
	unsigned int files;
	unsigned int r_counter;
	unsigned int w_counter;
	struct page *tmp_page;
	struct fasync_struct *fasync_readers;
	struct fasync_struct *fasync_writers;
	struct pipe_buffer *bufs;
	struct user_struct *user;
};

struct scatterlist {
	long unsigned int page_link;
	unsigned int offset;
	unsigned int length;
	dma_addr_t dma_address;
	unsigned int dma_length;
};

struct iovec {
	void *iov_base;
	__kernel_size_t iov_len;
};

struct kvec {
	void *iov_base;
	size_t iov_len;
};

struct iov_iter {
	unsigned int type;
	size_t iov_offset;
	size_t count;
	union {
		const struct iovec *iov;
		const struct kvec *kvec;
		const struct bio_vec *bvec;
		struct pipe_inode_info *pipe;
	};
	union {
		long unsigned int nr_segs;
		struct {
			unsigned int head;
			unsigned int start_head;
		};
	};
};

typedef short unsigned int __kernel_sa_family_t;

struct __kernel_sockaddr_storage {
	union {
		struct {
			__kernel_sa_family_t ss_family;
			char __data[126];
		};
		void *__align;
	};
};

typedef __kernel_sa_family_t sa_family_t;

struct sockaddr {
	sa_family_t sa_family;
	char sa_data[14];
};

struct msghdr {
	void *msg_name;
	int msg_namelen;
	struct iov_iter msg_iter;
	union {
		void *msg_control;
		void *msg_control_user;
	};
	bool msg_control_is_user: 1;
	__kernel_size_t msg_controllen;
	unsigned int msg_flags;
	struct kiocb *msg_iocb;
};

typedef struct {
	unsigned int clock_rate;
	unsigned int clock_type;
	short unsigned int loopback;
} sync_serial_settings;

typedef struct {
	unsigned int clock_rate;
	unsigned int clock_type;
	short unsigned int loopback;
	unsigned int slot_map;
} te1_settings;

typedef struct {
	short unsigned int encoding;
	short unsigned int parity;
} raw_hdlc_proto;

typedef struct {
	unsigned int t391;
	unsigned int t392;
	unsigned int n391;
	unsigned int n392;
	unsigned int n393;
	short unsigned int lmi;
	short unsigned int dce;
} fr_proto;

typedef struct {
	unsigned int dlci;
} fr_proto_pvc;

typedef struct {
	unsigned int dlci;
	char master[16];
} fr_proto_pvc_info;

typedef struct {
	unsigned int interval;
	unsigned int timeout;
} cisco_proto;

typedef struct {
	short unsigned int dce;
	unsigned int modulo;
	unsigned int window;
	unsigned int t1;
	unsigned int t2;
	unsigned int n2;
} x25_hdlc_proto;

struct ifmap {
	long unsigned int mem_start;
	long unsigned int mem_end;
	short unsigned int base_addr;
	unsigned char irq;
	unsigned char dma;
	unsigned char port;
};

struct if_settings {
	unsigned int type;
	unsigned int size;
	union {
		raw_hdlc_proto *raw_hdlc;
		cisco_proto *cisco;
		fr_proto *fr;
		fr_proto_pvc *fr_pvc;
		fr_proto_pvc_info *fr_pvc_info;
		x25_hdlc_proto *x25;
		sync_serial_settings *sync;
		te1_settings *te1;
	} ifs_ifsu;
};

struct ifreq {
	union {
		char ifrn_name[16];
	} ifr_ifrn;
	union {
		struct sockaddr ifru_addr;
		struct sockaddr ifru_dstaddr;
		struct sockaddr ifru_broadaddr;
		struct sockaddr ifru_netmask;
		struct sockaddr ifru_hwaddr;
		short int ifru_flags;
		int ifru_ivalue;
		int ifru_mtu;
		struct ifmap ifru_map;
		char ifru_slave[16];
		char ifru_newname[16];
		void *ifru_data;
		struct if_settings ifru_settings;
	} ifr_ifru;
};

struct vfsmount {
	struct dentry *mnt_root;
	struct super_block *mnt_sb;
	int mnt_flags;
};

struct ld_semaphore {
	atomic_long_t count;
	raw_spinlock_t wait_lock;
	unsigned int wait_readers;
	struct list_head read_wait;
	struct list_head write_wait;
};

typedef unsigned int tcflag_t;

typedef unsigned char cc_t;

typedef unsigned int speed_t;

struct ktermios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_line;
	cc_t c_cc[19];
	speed_t c_ispeed;
	speed_t c_ospeed;
};

struct winsize {
	short unsigned int ws_row;
	short unsigned int ws_col;
	short unsigned int ws_xpixel;
	short unsigned int ws_ypixel;
};

struct tty_operations;

struct tty_ldisc;

struct termiox;

struct tty_port;

struct tty_struct {
	int magic;
	struct kref kref;
	struct device *dev;
	struct tty_driver *driver;
	const struct tty_operations *ops;
	int index;
	struct ld_semaphore ldisc_sem;
	struct tty_ldisc *ldisc;
	struct mutex atomic_write_lock;
	struct mutex legacy_mutex;
	struct mutex throttle_mutex;
	struct rw_semaphore termios_rwsem;
	struct mutex winsize_mutex;
	spinlock_t ctrl_lock;
	spinlock_t flow_lock;
	struct ktermios termios;
	struct ktermios termios_locked;
	struct termiox *termiox;
	char name[64];
	struct pid *pgrp;
	struct pid *session;
	long unsigned int flags;
	int count;
	struct winsize winsize;
	long unsigned int stopped: 1;
	long unsigned int flow_stopped: 1;
	int: 30;
	long unsigned int unused: 62;
	int hw_stopped;
	long unsigned int ctrl_status: 8;
	long unsigned int packet: 1;
	int: 23;
	long unsigned int unused_ctrl: 55;
	unsigned int receive_room;
	int flow_change;
	struct tty_struct *link;
	struct fasync_struct *fasync;
	wait_queue_head_t write_wait;
	wait_queue_head_t read_wait;
	struct work_struct hangup_work;
	void *disc_data;
	void *driver_data;
	spinlock_t files_lock;
	struct list_head tty_files;
	int closing;
	unsigned char *write_buf;
	int write_cnt;
	struct work_struct SAK_work;
	struct tty_port *port;
};

typedef struct {
	size_t written;
	size_t count;
	union {
		char *buf;
		void *data;
	} arg;
	int error;
} read_descriptor_t;

struct posix_acl_entry {
	short int e_tag;
	short unsigned int e_perm;
	union {
		kuid_t e_uid;
		kgid_t e_gid;
	};
};

struct posix_acl {
	refcount_t a_refcount;
	struct callback_head a_rcu;
	unsigned int a_count;
	struct posix_acl_entry a_entries[0];
};

struct termiox {
	__u16 x_hflag;
	__u16 x_cflag;
	__u16 x_rflag[5];
	__u16 x_sflag;
};

struct serial_icounter_struct;

struct serial_struct;

struct tty_operations {
	struct tty_struct * (*lookup)(struct tty_driver *, struct file *, int);
	int (*install)(struct tty_driver *, struct tty_struct *);
	void (*remove)(struct tty_driver *, struct tty_struct *);
	int (*open)(struct tty_struct *, struct file *);
	void (*close)(struct tty_struct *, struct file *);
	void (*shutdown)(struct tty_struct *);
	void (*cleanup)(struct tty_struct *);
	int (*write)(struct tty_struct *, const unsigned char *, int);
	int (*put_char)(struct tty_struct *, unsigned char);
	void (*flush_chars)(struct tty_struct *);
	int (*write_room)(struct tty_struct *);
	int (*chars_in_buffer)(struct tty_struct *);
	int (*ioctl)(struct tty_struct *, unsigned int, long unsigned int);
	long int (*compat_ioctl)(struct tty_struct *, unsigned int, long unsigned int);
	void (*set_termios)(struct tty_struct *, struct ktermios *);
	void (*throttle)(struct tty_struct *);
	void (*unthrottle)(struct tty_struct *);
	void (*stop)(struct tty_struct *);
	void (*start)(struct tty_struct *);
	void (*hangup)(struct tty_struct *);
	int (*break_ctl)(struct tty_struct *, int);
	void (*flush_buffer)(struct tty_struct *);
	void (*set_ldisc)(struct tty_struct *);
	void (*wait_until_sent)(struct tty_struct *, int);
	void (*send_xchar)(struct tty_struct *, char);
	int (*tiocmget)(struct tty_struct *);
	int (*tiocmset)(struct tty_struct *, unsigned int, unsigned int);
	int (*resize)(struct tty_struct *, struct winsize *);
	int (*set_termiox)(struct tty_struct *, struct termiox *);
	int (*get_icount)(struct tty_struct *, struct serial_icounter_struct *);
	int (*get_serial)(struct tty_struct *, struct serial_struct *);
	int (*set_serial)(struct tty_struct *, struct serial_struct *);
	void (*show_fdinfo)(struct tty_struct *, struct seq_file *);
	int (*proc_show)(struct seq_file *, void *);
};

struct proc_dir_entry;

struct tty_driver {
	int magic;
	struct kref kref;
	struct cdev **cdevs;
	struct module *owner;
	const char *driver_name;
	const char *name;
	int name_base;
	int major;
	int minor_start;
	unsigned int num;
	short int type;
	short int subtype;
	struct ktermios init_termios;
	long unsigned int flags;
	struct proc_dir_entry *proc_entry;
	struct tty_driver *other;
	struct tty_struct **ttys;
	struct tty_port **ports;
	struct ktermios **termios;
	void *driver_state;
	const struct tty_operations *ops;
	struct list_head tty_drivers;
};

struct tty_buffer {
	union {
		struct tty_buffer *next;
		struct llist_node free;
	};
	int used;
	int size;
	int commit;
	int read;
	int flags;
	long unsigned int data[0];
};

struct tty_bufhead {
	struct tty_buffer *head;
	struct work_struct work;
	struct mutex lock;
	atomic_t priority;
	struct tty_buffer sentinel;
	struct llist_head free;
	atomic_t mem_used;
	int mem_limit;
	struct tty_buffer *tail;
};

struct tty_port_operations;

struct tty_port_client_operations;

struct tty_port {
	struct tty_bufhead buf;
	struct tty_struct *tty;
	struct tty_struct *itty;
	const struct tty_port_operations *ops;
	const struct tty_port_client_operations *client_ops;
	spinlock_t lock;
	int blocked_open;
	int count;
	wait_queue_head_t open_wait;
	wait_queue_head_t delta_msr_wait;
	long unsigned int flags;
	long unsigned int iflags;
	unsigned char console: 1;
	unsigned char low_latency: 1;
	struct mutex mutex;
	struct mutex buf_mutex;
	unsigned char *xmit_buf;
	unsigned int close_delay;
	unsigned int closing_wait;
	int drain_delay;
	struct kref kref;
	void *client_data;
};

struct tty_ldisc_ops {
	int magic;
	char *name;
	int num;
	int flags;
	int (*open)(struct tty_struct *);
	void (*close)(struct tty_struct *);
	void (*flush_buffer)(struct tty_struct *);
	ssize_t (*read)(struct tty_struct *, struct file *, unsigned char *, size_t);
	ssize_t (*write)(struct tty_struct *, struct file *, const unsigned char *, size_t);
	int (*ioctl)(struct tty_struct *, struct file *, unsigned int, long unsigned int);
	int (*compat_ioctl)(struct tty_struct *, struct file *, unsigned int, long unsigned int);
	void (*set_termios)(struct tty_struct *, struct ktermios *);
	__poll_t (*poll)(struct tty_struct *, struct file *, struct poll_table_struct *);
	int (*hangup)(struct tty_struct *);
	void (*receive_buf)(struct tty_struct *, const unsigned char *, char *, int);
	void (*write_wakeup)(struct tty_struct *);
	void (*dcd_change)(struct tty_struct *, unsigned int);
	int (*receive_buf2)(struct tty_struct *, const unsigned char *, char *, int);
	struct module *owner;
	int refcount;
};

struct tty_ldisc {
	struct tty_ldisc_ops *ops;
	struct tty_struct *tty;
};

struct tty_port_operations {
	int (*carrier_raised)(struct tty_port *);
	void (*dtr_rts)(struct tty_port *, int);
	void (*shutdown)(struct tty_port *);
	int (*activate)(struct tty_port *, struct tty_struct *);
	void (*destruct)(struct tty_port *);
};

struct tty_port_client_operations {
	int (*receive_buf)(struct tty_port *, const unsigned char *, const unsigned char *, size_t);
	void (*write_wakeup)(struct tty_port *);
};

struct prot_inuse;

struct netns_core {
	struct ctl_table_header *sysctl_hdr;
	int sysctl_somaxconn;
	int *sock_inuse;
	struct prot_inuse *prot_inuse;
};

struct tcp_mib;

struct ipstats_mib;

struct linux_mib;

struct udp_mib;

struct icmp_mib;

struct icmpmsg_mib;

struct icmpv6_mib;

struct icmpv6msg_mib;

struct netns_mib {
	struct tcp_mib *tcp_statistics;
	struct ipstats_mib *ip_statistics;
	struct linux_mib *net_statistics;
	struct udp_mib *udp_statistics;
	struct udp_mib *udplite_statistics;
	struct icmp_mib *icmp_statistics;
	struct icmpmsg_mib *icmpmsg_statistics;
	struct proc_dir_entry *proc_net_devsnmp6;
	struct udp_mib *udp_stats_in6;
	struct udp_mib *udplite_stats_in6;
	struct ipstats_mib *ipv6_statistics;
	struct icmpv6_mib *icmpv6_statistics;
	struct icmpv6msg_mib *icmpv6msg_statistics;
};

struct netns_packet {
	struct mutex sklist_lock;
	struct hlist_head sklist;
};

struct netns_unix {
	int sysctl_max_dgram_qlen;
	struct ctl_table_header *ctl;
};

struct netns_nexthop {
	struct rb_root rb_root;
	struct hlist_head *devhash;
	unsigned int seq;
	u32 last_id_allocated;
	struct atomic_notifier_head notifier_chain;
};

struct local_ports {
	seqlock_t lock;
	int range[2];
	bool warned;
};

struct inet_hashinfo;

struct inet_timewait_death_row {
	atomic_t tw_count;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct inet_hashinfo *hashinfo;
	int sysctl_max_tw_buckets;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct ping_group_range {
	seqlock_t lock;
	kgid_t range[2];
};

typedef struct {
	u64 key[2];
} siphash_key_t;

struct ipv4_devconf;

struct ip_ra_chain;

struct fib_rules_ops;

struct fib_table;

struct inet_peer_base;

struct fqdir;

struct xt_table;

struct tcp_congestion_ops;

struct tcp_fastopen_context;

struct mr_table;

struct fib_notifier_ops;

struct netns_ipv4 {
	struct ctl_table_header *forw_hdr;
	struct ctl_table_header *frags_hdr;
	struct ctl_table_header *ipv4_hdr;
	struct ctl_table_header *route_hdr;
	struct ctl_table_header *xfrm4_hdr;
	struct ipv4_devconf *devconf_all;
	struct ipv4_devconf *devconf_dflt;
	struct ip_ra_chain *ra_chain;
	struct mutex ra_mutex;
	struct fib_rules_ops *rules_ops;
	bool fib_has_custom_rules;
	unsigned int fib_rules_require_fldissect;
	struct fib_table *fib_main;
	struct fib_table *fib_default;
	bool fib_has_custom_local_routes;
	struct hlist_head *fib_table_hash;
	bool fib_offload_disabled;
	struct sock *fibnl;
	struct sock **icmp_sk;
	struct sock *mc_autojoin_sk;
	struct inet_peer_base *peers;
	struct sock **tcp_sk;
	struct fqdir *fqdir;
	struct xt_table *iptable_filter;
	struct xt_table *iptable_mangle;
	struct xt_table *iptable_raw;
	struct xt_table *arptable_filter;
	struct xt_table *iptable_security;
	struct xt_table *nat_table;
	int sysctl_icmp_echo_ignore_all;
	int sysctl_icmp_echo_ignore_broadcasts;
	int sysctl_icmp_ignore_bogus_error_responses;
	int sysctl_icmp_ratelimit;
	int sysctl_icmp_ratemask;
	int sysctl_icmp_errors_use_inbound_ifaddr;
	struct local_ports ip_local_ports;
	int sysctl_tcp_ecn;
	int sysctl_tcp_ecn_fallback;
	int sysctl_ip_default_ttl;
	int sysctl_ip_no_pmtu_disc;
	int sysctl_ip_fwd_use_pmtu;
	int sysctl_ip_fwd_update_priority;
	int sysctl_ip_nonlocal_bind;
	int sysctl_ip_autobind_reuse;
	int sysctl_ip_dynaddr;
	int sysctl_ip_early_demux;
	int sysctl_tcp_early_demux;
	int sysctl_udp_early_demux;
	int sysctl_nexthop_compat_mode;
	int sysctl_fwmark_reflect;
	int sysctl_tcp_fwmark_accept;
	int sysctl_tcp_mtu_probing;
	int sysctl_tcp_mtu_probe_floor;
	int sysctl_tcp_base_mss;
	int sysctl_tcp_min_snd_mss;
	int sysctl_tcp_probe_threshold;
	u32 sysctl_tcp_probe_interval;
	int sysctl_tcp_keepalive_time;
	int sysctl_tcp_keepalive_probes;
	int sysctl_tcp_keepalive_intvl;
	int sysctl_tcp_syn_retries;
	int sysctl_tcp_synack_retries;
	int sysctl_tcp_syncookies;
	int sysctl_tcp_reordering;
	int sysctl_tcp_retries1;
	int sysctl_tcp_retries2;
	int sysctl_tcp_orphan_retries;
	int sysctl_tcp_fin_timeout;
	unsigned int sysctl_tcp_notsent_lowat;
	int sysctl_tcp_tw_reuse;
	int sysctl_tcp_sack;
	int sysctl_tcp_window_scaling;
	int sysctl_tcp_timestamps;
	int sysctl_tcp_early_retrans;
	int sysctl_tcp_recovery;
	int sysctl_tcp_thin_linear_timeouts;
	int sysctl_tcp_slow_start_after_idle;
	int sysctl_tcp_retrans_collapse;
	int sysctl_tcp_stdurg;
	int sysctl_tcp_rfc1337;
	int sysctl_tcp_abort_on_overflow;
	int sysctl_tcp_fack;
	int sysctl_tcp_max_reordering;
	int sysctl_tcp_dsack;
	int sysctl_tcp_app_win;
	int sysctl_tcp_adv_win_scale;
	int sysctl_tcp_frto;
	int sysctl_tcp_nometrics_save;
	int sysctl_tcp_no_ssthresh_metrics_save;
	int sysctl_tcp_moderate_rcvbuf;
	int sysctl_tcp_tso_win_divisor;
	int sysctl_tcp_workaround_signed_windows;
	int sysctl_tcp_limit_output_bytes;
	int sysctl_tcp_challenge_ack_limit;
	int sysctl_tcp_min_tso_segs;
	int sysctl_tcp_min_rtt_wlen;
	int sysctl_tcp_autocorking;
	int sysctl_tcp_invalid_ratelimit;
	int sysctl_tcp_pacing_ss_ratio;
	int sysctl_tcp_pacing_ca_ratio;
	int sysctl_tcp_wmem[3];
	int sysctl_tcp_rmem[3];
	int sysctl_tcp_comp_sack_nr;
	long unsigned int sysctl_tcp_comp_sack_delay_ns;
	long unsigned int sysctl_tcp_comp_sack_slack_ns;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct inet_timewait_death_row tcp_death_row;
	int sysctl_max_syn_backlog;
	int sysctl_tcp_fastopen;
	const struct tcp_congestion_ops *tcp_congestion_control;
	struct tcp_fastopen_context *tcp_fastopen_ctx;
	spinlock_t tcp_fastopen_ctx_lock;
	unsigned int sysctl_tcp_fastopen_blackhole_timeout;
	atomic_t tfo_active_disable_times;
	long unsigned int tfo_active_disable_stamp;
	int sysctl_udp_wmem_min;
	int sysctl_udp_rmem_min;
	int sysctl_igmp_max_memberships;
	int sysctl_igmp_max_msf;
	int sysctl_igmp_llm_reports;
	int sysctl_igmp_qrv;
	struct ping_group_range ping_group_range;
	atomic_t dev_addr_genid;
	long unsigned int *sysctl_local_reserved_ports;
	int sysctl_ip_prot_sock;
	struct mr_table *mrt;
	int sysctl_fib_multipath_use_neigh;
	int sysctl_fib_multipath_hash_policy;
	struct fib_notifier_ops *notifier_ops;
	unsigned int fib_seq;
	struct fib_notifier_ops *ipmr_notifier_ops;
	unsigned int ipmr_seq;
	atomic_t rt_genid;
	siphash_key_t ip_id_key;
	long: 64;
	long: 64;
};

struct netns_sysctl_ipv6 {
	struct ctl_table_header *hdr;
	struct ctl_table_header *route_hdr;
	struct ctl_table_header *icmp_hdr;
	struct ctl_table_header *frags_hdr;
	struct ctl_table_header *xfrm6_hdr;
	int bindv6only;
	int flush_delay;
	int ip6_rt_max_size;
	int ip6_rt_gc_min_interval;
	int ip6_rt_gc_timeout;
	int ip6_rt_gc_interval;
	int ip6_rt_gc_elasticity;
	int ip6_rt_mtu_expires;
	int ip6_rt_min_advmss;
	int multipath_hash_policy;
	int flowlabel_consistency;
	int auto_flowlabels;
	int icmpv6_time;
	int icmpv6_echo_ignore_all;
	int icmpv6_echo_ignore_multicast;
	int icmpv6_echo_ignore_anycast;
	long unsigned int icmpv6_ratemask[4];
	long unsigned int *icmpv6_ratemask_ptr;
	int anycast_src_echo_reply;
	int ip_nonlocal_bind;
	int fwmark_reflect;
	int idgen_retries;
	int idgen_delay;
	int flowlabel_state_ranges;
	int flowlabel_reflect;
	int max_dst_opts_cnt;
	int max_hbh_opts_cnt;
	int max_dst_opts_len;
	int max_hbh_opts_len;
	int seg6_flowlabel;
	bool skip_notify_on_dev_down;
};

struct neighbour;

struct dst_ops {
	short unsigned int family;
	unsigned int gc_thresh;
	int (*gc)(struct dst_ops *);
	struct dst_entry * (*check)(struct dst_entry *, __u32);
	unsigned int (*default_advmss)(const struct dst_entry *);
	unsigned int (*mtu)(const struct dst_entry *);
	u32 * (*cow_metrics)(struct dst_entry *, long unsigned int);
	void (*destroy)(struct dst_entry *);
	void (*ifdown)(struct dst_entry *, struct net_device *, int);
	struct dst_entry * (*negative_advice)(struct dst_entry *);
	void (*link_failure)(struct sk_buff *);
	void (*update_pmtu)(struct dst_entry *, struct sock *, struct sk_buff *, u32, bool);
	void (*redirect)(struct dst_entry *, struct sock *, struct sk_buff *);
	int (*local_out)(struct net *, struct sock *, struct sk_buff *);
	struct neighbour * (*neigh_lookup)(const struct dst_entry *, struct sk_buff *, const void *);
	void (*confirm_neigh)(const struct dst_entry *, const void *);
	struct kmem_cache *kmem_cachep;
	struct percpu_counter pcpuc_entries;
	long: 64;
	long: 64;
	long: 64;
};

struct ipv6_devconf;

struct fib6_info;

struct rt6_info;

struct rt6_statistics;

struct fib6_table;

struct seg6_pernet_data;

struct netns_ipv6 {
	struct netns_sysctl_ipv6 sysctl;
	struct ipv6_devconf *devconf_all;
	struct ipv6_devconf *devconf_dflt;
	struct inet_peer_base *peers;
	struct fqdir *fqdir;
	struct xt_table *ip6table_filter;
	struct xt_table *ip6table_mangle;
	struct xt_table *ip6table_raw;
	struct xt_table *ip6table_security;
	struct xt_table *ip6table_nat;
	struct fib6_info *fib6_null_entry;
	struct rt6_info *ip6_null_entry;
	struct rt6_statistics *rt6_stats;
	struct timer_list ip6_fib_timer;
	struct hlist_head *fib_table_hash;
	struct fib6_table *fib6_main_tbl;
	struct list_head fib6_walkers;
	long: 64;
	long: 64;
	struct dst_ops ip6_dst_ops;
	rwlock_t fib6_walker_lock;
	spinlock_t fib6_gc_lock;
	unsigned int ip6_rt_gc_expire;
	long unsigned int ip6_rt_last_gc;
	unsigned int fib6_rules_require_fldissect;
	bool fib6_has_custom_rules;
	struct rt6_info *ip6_prohibit_entry;
	struct rt6_info *ip6_blk_hole_entry;
	struct fib6_table *fib6_local_tbl;
	struct fib_rules_ops *fib6_rules_ops;
	struct sock **icmp_sk;
	struct sock *ndisc_sk;
	struct sock *tcp_sk;
	struct sock *igmp_sk;
	struct sock *mc_autojoin_sk;
	atomic_t dev_addr_genid;
	atomic_t fib6_sernum;
	struct seg6_pernet_data *seg6_data;
	struct fib_notifier_ops *notifier_ops;
	struct fib_notifier_ops *ip6mr_notifier_ops;
	unsigned int ipmr_seq;
	struct {
		struct hlist_head head;
		spinlock_t lock;
		u32 seq;
	} ip6addrlbl_table;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct nf_queue_handler;

struct nf_logger;

struct nf_hook_entries;

struct netns_nf {
	struct proc_dir_entry *proc_netfilter;
	const struct nf_queue_handler *queue_handler;
	const struct nf_logger *nf_loggers[13];
	struct ctl_table_header *nf_log_dir_header;
	struct nf_hook_entries *hooks_ipv4[5];
	struct nf_hook_entries *hooks_ipv6[5];
	bool defrag_ipv4;
	bool defrag_ipv6;
};

struct netns_xt {
	struct list_head tables[13];
	bool notrack_deprecated_warning;
	bool clusterip_deprecated_warning;
};

struct nf_ct_event_notifier;

struct nf_exp_event_notifier;

struct nf_generic_net {
	unsigned int timeout;
};

struct nf_tcp_net {
	unsigned int timeouts[14];
	int tcp_loose;
	int tcp_be_liberal;
	int tcp_max_retrans;
};

struct nf_udp_net {
	unsigned int timeouts[2];
};

struct nf_icmp_net {
	unsigned int timeout;
};

struct nf_dccp_net {
	int dccp_loose;
	unsigned int dccp_timeout[10];
};

struct nf_sctp_net {
	unsigned int timeouts[10];
};

struct nf_ip_net {
	struct nf_generic_net generic;
	struct nf_tcp_net tcp;
	struct nf_udp_net udp;
	struct nf_icmp_net icmp;
	struct nf_icmp_net icmpv6;
	struct nf_dccp_net dccp;
	struct nf_sctp_net sctp;
};

struct ct_pcpu;

struct ip_conntrack_stat;

struct netns_ct {
	atomic_t count;
	unsigned int expect_count;
	bool auto_assign_helper_warned;
	struct ctl_table_header *sysctl_header;
	unsigned int sysctl_log_invalid;
	int sysctl_events;
	int sysctl_acct;
	int sysctl_auto_assign_helper;
	int sysctl_tstamp;
	int sysctl_checksum;
	struct ct_pcpu *pcpu_lists;
	struct ip_conntrack_stat *stat;
	struct nf_ct_event_notifier *nf_conntrack_event_cb;
	struct nf_exp_event_notifier *nf_expect_event_cb;
	struct nf_ip_net nf_ct_proto;
};

struct netns_nf_frag {
	struct fqdir *fqdir;
};

struct netns_bpf {
	struct bpf_prog_array *run_array[1];
	struct bpf_prog *progs[1];
	struct list_head links[1];
};

struct xfrm_policy_hash {
	struct hlist_head *table;
	unsigned int hmask;
	u8 dbits4;
	u8 sbits4;
	u8 dbits6;
	u8 sbits6;
};

struct xfrm_policy_hthresh {
	struct work_struct work;
	seqlock_t lock;
	u8 lbits4;
	u8 rbits4;
	u8 lbits6;
	u8 rbits6;
};

struct netns_xfrm {
	struct list_head state_all;
	struct hlist_head *state_bydst;
	struct hlist_head *state_bysrc;
	struct hlist_head *state_byspi;
	unsigned int state_hmask;
	unsigned int state_num;
	struct work_struct state_hash_work;
	struct list_head policy_all;
	struct hlist_head *policy_byidx;
	unsigned int policy_idx_hmask;
	struct hlist_head policy_inexact[3];
	struct xfrm_policy_hash policy_bydst[3];
	unsigned int policy_count[6];
	struct work_struct policy_hash_work;
	struct xfrm_policy_hthresh policy_hthresh;
	struct list_head inexact_bins;
	struct sock *nlsk;
	struct sock *nlsk_stash;
	u32 sysctl_aevent_etime;
	u32 sysctl_aevent_rseqth;
	int sysctl_larval_drop;
	u32 sysctl_acq_expires;
	struct ctl_table_header *sysctl_hdr;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct dst_ops xfrm4_dst_ops;
	struct dst_ops xfrm6_dst_ops;
	spinlock_t xfrm_state_lock;
	spinlock_t xfrm_policy_lock;
	struct mutex xfrm_cfg_mutex;
	long: 64;
	long: 64;
	long: 64;
};

struct netns_xdp {
	struct mutex lock;
	struct hlist_head list;
};

struct uevent_sock;

struct net_generic;

struct net {
	refcount_t passive;
	refcount_t count;
	spinlock_t rules_mod_lock;
	unsigned int dev_unreg_count;
	unsigned int dev_base_seq;
	int ifindex;
	spinlock_t nsid_lock;
	atomic_t fnhe_genid;
	struct list_head list;
	struct list_head exit_list;
	struct llist_node cleanup_list;
	struct key_tag *key_domain;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct idr netns_ids;
	struct ns_common ns;
	struct list_head dev_base_head;
	struct proc_dir_entry *proc_net;
	struct proc_dir_entry *proc_net_stat;
	struct ctl_table_set sysctls;
	struct sock *rtnl;
	struct sock *genl_sock;
	struct uevent_sock *uevent_sock;
	struct hlist_head *dev_name_head;
	struct hlist_head *dev_index_head;
	struct raw_notifier_head netdev_chain;
	u32 hash_mix;
	struct net_device *loopback_dev;
	struct list_head rules_ops;
	struct netns_core core;
	struct netns_mib mib;
	struct netns_packet packet;
	struct netns_unix unx;
	struct netns_nexthop nexthop;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct netns_ipv4 ipv4;
	struct netns_ipv6 ipv6;
	struct netns_nf nf;
	struct netns_xt xt;
	struct netns_ct ct;
	struct netns_nf_frag nf_frag;
	struct ctl_table_header *nf_frag_frags_hdr;
	struct sock *nfnl;
	struct sock *nfnl_stash;
	struct net_generic *gen;
	struct netns_bpf bpf;
	long: 64;
	struct netns_xfrm xfrm;
	atomic64_t net_cookie;
	struct netns_xdp xdp;
	struct sock *diag_nlsk;
	long: 64;
};

typedef struct {
	local64_t v;
} u64_stats_t;

struct bpf_offloaded_map;

struct bpf_map_dev_ops {
	int (*map_get_next_key)(struct bpf_offloaded_map *, void *, void *);
	int (*map_lookup_elem)(struct bpf_offloaded_map *, void *, void *);
	int (*map_update_elem)(struct bpf_offloaded_map *, void *, void *, u64);
	int (*map_delete_elem)(struct bpf_offloaded_map *, void *);
};

struct bpf_offloaded_map {
	struct bpf_map map;
	struct net_device *netdev;
	const struct bpf_map_dev_ops *dev_ops;
	void *dev_priv;
	struct list_head offloads;
	long: 64;
	long: 64;
	long: 64;
};

struct net_device_stats {
	long unsigned int rx_packets;
	long unsigned int tx_packets;
	long unsigned int rx_bytes;
	long unsigned int tx_bytes;
	long unsigned int rx_errors;
	long unsigned int tx_errors;
	long unsigned int rx_dropped;
	long unsigned int tx_dropped;
	long unsigned int multicast;
	long unsigned int collisions;
	long unsigned int rx_length_errors;
	long unsigned int rx_over_errors;
	long unsigned int rx_crc_errors;
	long unsigned int rx_frame_errors;
	long unsigned int rx_fifo_errors;
	long unsigned int rx_missed_errors;
	long unsigned int tx_aborted_errors;
	long unsigned int tx_carrier_errors;
	long unsigned int tx_fifo_errors;
	long unsigned int tx_heartbeat_errors;
	long unsigned int tx_window_errors;
	long unsigned int rx_compressed;
	long unsigned int tx_compressed;
};

struct netdev_hw_addr_list {
	struct list_head list;
	int count;
};

enum rx_handler_result {
	RX_HANDLER_CONSUMED = 0,
	RX_HANDLER_ANOTHER = 1,
	RX_HANDLER_EXACT = 2,
	RX_HANDLER_PASS = 3,
};

typedef enum rx_handler_result rx_handler_result_t;

typedef rx_handler_result_t rx_handler_func_t(struct sk_buff **);

struct pcpu_dstats;

struct netdev_tc_txq {
	u16 count;
	u16 offset;
};

struct sfp_bus;

struct netdev_name_node;

struct dev_ifalias;

struct net_device_ops;

struct ethtool_ops;

struct ndisc_ops;

struct header_ops;

struct in_device;

struct inet6_dev;

struct wireless_dev;

struct wpan_dev;

struct netdev_rx_queue;

struct mini_Qdisc;

struct netdev_queue;

struct cpu_rmap;

struct Qdisc;

struct xdp_dev_bulk_queue;

struct xps_dev_maps;

struct netpoll_info;

struct pcpu_lstats;

struct pcpu_sw_netstats;

struct rtnl_link_ops;

struct phy_device;

struct net_device {
	char name[16];
	struct netdev_name_node *name_node;
	struct dev_ifalias *ifalias;
	long unsigned int mem_end;
	long unsigned int mem_start;
	long unsigned int base_addr;
	int irq;
	long unsigned int state;
	struct list_head dev_list;
	struct list_head napi_list;
	struct list_head unreg_list;
	struct list_head close_list;
	struct list_head ptype_all;
	struct list_head ptype_specific;
	struct {
		struct list_head upper;
		struct list_head lower;
	} adj_list;
	netdev_features_t features;
	netdev_features_t hw_features;
	netdev_features_t wanted_features;
	netdev_features_t vlan_features;
	netdev_features_t hw_enc_features;
	netdev_features_t mpls_features;
	netdev_features_t gso_partial_features;
	int ifindex;
	int group;
	struct net_device_stats stats;
	atomic_long_t rx_dropped;
	atomic_long_t tx_dropped;
	atomic_long_t rx_nohandler;
	atomic_t carrier_up_count;
	atomic_t carrier_down_count;
	const struct net_device_ops *netdev_ops;
	const struct ethtool_ops *ethtool_ops;
	const struct ndisc_ops *ndisc_ops;
	const struct header_ops *header_ops;
	unsigned int flags;
	unsigned int priv_flags;
	short unsigned int gflags;
	short unsigned int padded;
	unsigned char operstate;
	unsigned char link_mode;
	unsigned char if_port;
	unsigned char dma;
	unsigned int mtu;
	unsigned int min_mtu;
	unsigned int max_mtu;
	short unsigned int type;
	short unsigned int hard_header_len;
	unsigned char min_header_len;
	short unsigned int needed_headroom;
	short unsigned int needed_tailroom;
	unsigned char perm_addr[32];
	unsigned char addr_assign_type;
	unsigned char addr_len;
	unsigned char upper_level;
	unsigned char lower_level;
	short unsigned int neigh_priv_len;
	short unsigned int dev_id;
	short unsigned int dev_port;
	spinlock_t addr_list_lock;
	unsigned char name_assign_type;
	bool uc_promisc;
	struct netdev_hw_addr_list uc;
	struct netdev_hw_addr_list mc;
	struct netdev_hw_addr_list dev_addrs;
	struct kset *queues_kset;
	unsigned int promiscuity;
	unsigned int allmulti;
	struct in_device *ip_ptr;
	struct inet6_dev *ip6_ptr;
	struct wireless_dev *ieee80211_ptr;
	struct wpan_dev *ieee802154_ptr;
	unsigned char *dev_addr;
	struct netdev_rx_queue *_rx;
	unsigned int num_rx_queues;
	unsigned int real_num_rx_queues;
	struct bpf_prog *xdp_prog;
	long unsigned int gro_flush_timeout;
	int napi_defer_hard_irqs;
	rx_handler_func_t *rx_handler;
	void *rx_handler_data;
	struct mini_Qdisc *miniq_ingress;
	struct netdev_queue *ingress_queue;
	struct nf_hook_entries *nf_hooks_ingress;
	unsigned char broadcast[32];
	struct cpu_rmap *rx_cpu_rmap;
	struct hlist_node index_hlist;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct netdev_queue *_tx;
	unsigned int num_tx_queues;
	unsigned int real_num_tx_queues;
	struct Qdisc *qdisc;
	unsigned int tx_queue_len;
	spinlock_t tx_global_lock;
	struct xdp_dev_bulk_queue *xdp_bulkq;
	struct xps_dev_maps *xps_cpus_map;
	struct xps_dev_maps *xps_rxqs_map;
	struct mini_Qdisc *miniq_egress;
	struct hlist_head qdisc_hash[16];
	struct timer_list watchdog_timer;
	int watchdog_timeo;
	struct list_head todo_list;
	int *pcpu_refcnt;
	struct list_head link_watch_list;
	enum {
		NETREG_UNINITIALIZED = 0,
		NETREG_REGISTERED = 1,
		NETREG_UNREGISTERING = 2,
		NETREG_UNREGISTERED = 3,
		NETREG_RELEASED = 4,
		NETREG_DUMMY = 5,
	} reg_state: 8;
	bool dismantle;
	enum {
		RTNL_LINK_INITIALIZED = 0,
		RTNL_LINK_INITIALIZING = 1,
	} rtnl_link_state: 16;
	bool needs_free_netdev;
	void (*priv_destructor)(struct net_device *);
	struct netpoll_info *npinfo;
	possible_net_t nd_net;
	union {
		void *ml_priv;
		struct pcpu_lstats *lstats;
		struct pcpu_sw_netstats *tstats;
		struct pcpu_dstats *dstats;
	};
	struct device dev;
	const struct attribute_group *sysfs_groups[4];
	const struct attribute_group *sysfs_rx_queue_group;
	const struct rtnl_link_ops *rtnl_link_ops;
	unsigned int gso_max_size;
	u16 gso_max_segs;
	s16 num_tc;
	struct netdev_tc_txq tc_to_txq[16];
	u8 prio_tc_map[16];
	struct phy_device *phydev;
	struct sfp_bus *sfp_bus;
	struct lock_class_key *qdisc_tx_busylock;
	struct lock_class_key *qdisc_running_key;
	bool proto_down;
	unsigned int wol_enabled: 1;
	struct list_head net_notifier_list;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_dispatcher_prog {
	struct bpf_prog *prog;
	refcount_t users;
};

struct bpf_dispatcher {
	struct mutex mutex;
	void *func;
	struct bpf_dispatcher_prog progs[48];
	int num_progs;
	void *image;
	u32 image_off;
	struct bpf_ksym ksym;
};

typedef unsigned int sk_buff_data_t;

struct skb_ext;

struct sk_buff {
	union {
		struct {
			struct sk_buff *next;
			struct sk_buff *prev;
			union {
				struct net_device *dev;
				long unsigned int dev_scratch;
			};
		};
		struct rb_node rbnode;
		struct list_head list;
	};
	union {
		struct sock *sk;
		int ip_defrag_offset;
	};
	union {
		ktime_t tstamp;
		u64 skb_mstamp_ns;
	};
	char cb[48];
	union {
		struct {
			long unsigned int _skb_refdst;
			void (*destructor)(struct sk_buff *);
		};
		struct list_head tcp_tsorted_anchor;
	};
	long unsigned int _nfct;
	unsigned int len;
	unsigned int data_len;
	__u16 mac_len;
	__u16 hdr_len;
	__u16 queue_mapping;
	__u8 __cloned_offset[0];
	__u8 cloned: 1;
	__u8 nohdr: 1;
	__u8 fclone: 2;
	__u8 peeked: 1;
	__u8 head_frag: 1;
	__u8 pfmemalloc: 1;
	__u8 active_extensions;
	__u32 headers_start[0];
	__u8 __pkt_type_offset[0];
	__u8 pkt_type: 3;
	__u8 ignore_df: 1;
	__u8 nf_trace: 1;
	__u8 ip_summed: 2;
	__u8 ooo_okay: 1;
	__u8 l4_hash: 1;
	__u8 sw_hash: 1;
	__u8 wifi_acked_valid: 1;
	__u8 wifi_acked: 1;
	__u8 no_fcs: 1;
	__u8 encapsulation: 1;
	__u8 encap_hdr_csum: 1;
	__u8 csum_valid: 1;
	__u8 __pkt_vlan_present_offset[0];
	__u8 vlan_present: 1;
	__u8 csum_complete_sw: 1;
	__u8 csum_level: 2;
	__u8 csum_not_inet: 1;
	__u8 dst_pending_confirm: 1;
	__u8 ndisc_nodetype: 2;
	__u8 ipvs_property: 1;
	__u8 inner_protocol_type: 1;
	__u8 remcsum_offload: 1;
	__u8 tc_skip_classify: 1;
	__u8 tc_at_ingress: 1;
	__u16 tc_index;
	union {
		__wsum csum;
		struct {
			__u16 csum_start;
			__u16 csum_offset;
		};
	};
	__u32 priority;
	int skb_iif;
	__u32 hash;
	__be16 vlan_proto;
	__u16 vlan_tci;
	union {
		unsigned int napi_id;
		unsigned int sender_cpu;
	};
	__u32 secmark;
	union {
		__u32 mark;
		__u32 reserved_tailroom;
	};
	union {
		__be16 inner_protocol;
		__u8 inner_ipproto;
	};
	__u16 inner_transport_header;
	__u16 inner_network_header;
	__u16 inner_mac_header;
	__be16 protocol;
	__u16 transport_header;
	__u16 network_header;
	__u16 mac_header;
	__u32 headers_end[0];
	sk_buff_data_t tail;
	sk_buff_data_t end;
	unsigned char *head;
	unsigned char *data;
	unsigned int truesize;
	refcount_t users;
	struct skb_ext *extensions;
};

struct sg_table {
	struct scatterlist *sgl;
	unsigned int nents;
	unsigned int orig_nents;
};

typedef int suspend_state_t;

enum suspend_stat_step {
	SUSPEND_FREEZE = 1,
	SUSPEND_PREPARE = 2,
	SUSPEND_SUSPEND = 3,
	SUSPEND_SUSPEND_LATE = 4,
	SUSPEND_SUSPEND_NOIRQ = 5,
	SUSPEND_RESUME_NOIRQ = 6,
	SUSPEND_RESUME_EARLY = 7,
	SUSPEND_RESUME = 8,
};

struct suspend_stats {
	int success;
	int fail;
	int failed_freeze;
	int failed_prepare;
	int failed_suspend;
	int failed_suspend_late;
	int failed_suspend_noirq;
	int failed_resume;
	int failed_resume_early;
	int failed_resume_noirq;
	int last_failed_dev;
	char failed_devs[80];
	int last_failed_errno;
	int errno[2];
	int last_failed_step;
	enum suspend_stat_step failed_steps[2];
};

enum s2idle_states {
	S2IDLE_STATE_NONE = 0,
	S2IDLE_STATE_ENTER = 1,
	S2IDLE_STATE_WAKE = 2,
};

struct pbe {
	void *address;
	void *orig_address;
	struct pbe *next;
};

enum {
	Root_NFS = 255,
	Root_CIFS = 254,
	Root_RAM0 = 1048576,
	Root_RAM1 = 1048577,
	Root_FD0 = 2097152,
	Root_HDA1 = 3145729,
	Root_HDA2 = 3145730,
	Root_SDA1 = 8388609,
	Root_SDA2 = 8388610,
	Root_HDC1 = 23068673,
	Root_SR0 = 11534336,
};

struct xdr_buf {
	struct kvec head[1];
	struct kvec tail[1];
	struct bio_vec *bvec;
	struct page **pages;
	unsigned int page_base;
	unsigned int page_len;
	unsigned int flags;
	unsigned int buflen;
	unsigned int len;
};

struct rpc_rqst;

struct xdr_stream {
	__be32 *p;
	struct xdr_buf *buf;
	__be32 *end;
	struct kvec *iov;
	struct kvec scratch;
	struct page **page_ptr;
	unsigned int nwords;
	struct rpc_rqst *rqst;
};

struct rpc_xprt;

struct rpc_task;

struct rpc_cred;

struct rpc_rqst {
	struct rpc_xprt *rq_xprt;
	struct xdr_buf rq_snd_buf;
	struct xdr_buf rq_rcv_buf;
	struct rpc_task *rq_task;
	struct rpc_cred *rq_cred;
	__be32 rq_xid;
	int rq_cong;
	u32 rq_seqno;
	int rq_enc_pages_num;
	struct page **rq_enc_pages;
	void (*rq_release_snd_buf)(struct rpc_rqst *);
	union {
		struct list_head rq_list;
		struct rb_node rq_recv;
	};
	struct list_head rq_xmit;
	struct list_head rq_xmit2;
	void *rq_buffer;
	size_t rq_callsize;
	void *rq_rbuffer;
	size_t rq_rcvsize;
	size_t rq_xmit_bytes_sent;
	size_t rq_reply_bytes_recvd;
	struct xdr_buf rq_private_buf;
	long unsigned int rq_majortimeo;
	long unsigned int rq_timeout;
	ktime_t rq_rtt;
	unsigned int rq_retries;
	unsigned int rq_connect_cookie;
	atomic_t rq_pin;
	u32 rq_bytes_sent;
	ktime_t rq_xtime;
	int rq_ntrans;
};

typedef void (*kxdreproc_t)(struct rpc_rqst *, struct xdr_stream *, const void *);

typedef int (*kxdrdproc_t)(struct rpc_rqst *, struct xdr_stream *, void *);

struct rpc_procinfo;

struct rpc_message {
	const struct rpc_procinfo *rpc_proc;
	void *rpc_argp;
	void *rpc_resp;
	const struct cred *rpc_cred;
};

struct rpc_procinfo {
	u32 p_proc;
	kxdreproc_t p_encode;
	kxdrdproc_t p_decode;
	unsigned int p_arglen;
	unsigned int p_replen;
	unsigned int p_timer;
	u32 p_statidx;
	const char *p_name;
};

struct rpc_wait {
	struct list_head list;
	struct list_head links;
	struct list_head timer_list;
};

struct rpc_wait_queue;

struct rpc_call_ops;

struct rpc_clnt;

struct rpc_task {
	atomic_t tk_count;
	int tk_status;
	struct list_head tk_task;
	void (*tk_callback)(struct rpc_task *);
	void (*tk_action)(struct rpc_task *);
	long unsigned int tk_timeout;
	long unsigned int tk_runstate;
	struct rpc_wait_queue *tk_waitqueue;
	union {
		struct work_struct tk_work;
		struct rpc_wait tk_wait;
	} u;
	int tk_rpc_status;
	struct rpc_message tk_msg;
	void *tk_calldata;
	const struct rpc_call_ops *tk_ops;
	struct rpc_clnt *tk_client;
	struct rpc_xprt *tk_xprt;
	struct rpc_cred *tk_op_cred;
	struct rpc_rqst *tk_rqstp;
	struct workqueue_struct *tk_workqueue;
	ktime_t tk_start;
	pid_t tk_owner;
	short unsigned int tk_flags;
	short unsigned int tk_timeouts;
	short unsigned int tk_pid;
	unsigned char tk_priority: 2;
	unsigned char tk_garb_retry: 2;
	unsigned char tk_cred_retry: 2;
	unsigned char tk_rebind_retry: 2;
};

struct rpc_timer {
	struct list_head list;
	long unsigned int expires;
	struct delayed_work dwork;
};

struct rpc_wait_queue {
	spinlock_t lock;
	struct list_head tasks[4];
	unsigned char maxpriority;
	unsigned char priority;
	unsigned char nr;
	short unsigned int qlen;
	struct rpc_timer timer_list;
	const char *name;
};

struct rpc_call_ops {
	void (*rpc_call_prepare)(struct rpc_task *, void *);
	void (*rpc_call_done)(struct rpc_task *, void *);
	void (*rpc_count_stats)(struct rpc_task *, void *);
	void (*rpc_release)(void *);
};

struct rpc_pipe_dir_head {
	struct list_head pdh_entries;
	struct dentry *pdh_dentry;
};

struct rpc_rtt {
	long unsigned int timeo;
	long unsigned int srtt[5];
	long unsigned int sdrtt[5];
	int ntimeouts[5];
};

struct rpc_timeout {
	long unsigned int to_initval;
	long unsigned int to_maxval;
	long unsigned int to_increment;
	unsigned int to_retries;
	unsigned char to_exponential;
};

struct rpc_xprt_switch;

struct rpc_xprt_iter_ops;

struct rpc_xprt_iter {
	struct rpc_xprt_switch *xpi_xpswitch;
	struct rpc_xprt *xpi_cursor;
	const struct rpc_xprt_iter_ops *xpi_ops;
};

struct rpc_auth;

struct rpc_stat;

struct rpc_iostats;

struct rpc_program;

struct rpc_clnt {
	atomic_t cl_count;
	unsigned int cl_clid;
	struct list_head cl_clients;
	struct list_head cl_tasks;
	spinlock_t cl_lock;
	struct rpc_xprt *cl_xprt;
	const struct rpc_procinfo *cl_procinfo;
	u32 cl_prog;
	u32 cl_vers;
	u32 cl_maxproc;
	struct rpc_auth *cl_auth;
	struct rpc_stat *cl_stats;
	struct rpc_iostats *cl_metrics;
	unsigned int cl_softrtry: 1;
	unsigned int cl_softerr: 1;
	unsigned int cl_discrtry: 1;
	unsigned int cl_noretranstimeo: 1;
	unsigned int cl_autobind: 1;
	unsigned int cl_chatty: 1;
	struct rpc_rtt *cl_rtt;
	const struct rpc_timeout *cl_timeout;
	atomic_t cl_swapper;
	int cl_nodelen;
	char cl_nodename[65];
	struct rpc_pipe_dir_head cl_pipedir_objects;
	struct rpc_clnt *cl_parent;
	struct rpc_rtt cl_rtt_default;
	struct rpc_timeout cl_timeout_default;
	const struct rpc_program *cl_program;
	const char *cl_principal;
	union {
		struct rpc_xprt_iter cl_xpi;
		struct work_struct cl_work;
	};
	const struct cred *cl_cred;
};

struct rpc_xprt_ops;

struct svc_xprt;

struct rpc_xprt {
	struct kref kref;
	const struct rpc_xprt_ops *ops;
	const struct rpc_timeout *timeout;
	struct __kernel_sockaddr_storage addr;
	size_t addrlen;
	int prot;
	long unsigned int cong;
	long unsigned int cwnd;
	size_t max_payload;
	struct rpc_wait_queue binding;
	struct rpc_wait_queue sending;
	struct rpc_wait_queue pending;
	struct rpc_wait_queue backlog;
	struct list_head free;
	unsigned int max_reqs;
	unsigned int min_reqs;
	unsigned int num_reqs;
	long unsigned int state;
	unsigned char resvport: 1;
	unsigned char reuseport: 1;
	atomic_t swapper;
	unsigned int bind_index;
	struct list_head xprt_switch;
	long unsigned int bind_timeout;
	long unsigned int reestablish_timeout;
	unsigned int connect_cookie;
	struct work_struct task_cleanup;
	struct timer_list timer;
	long unsigned int last_used;
	long unsigned int idle_timeout;
	long unsigned int connect_timeout;
	long unsigned int max_reconnect_timeout;
	atomic_long_t queuelen;
	spinlock_t transport_lock;
	spinlock_t reserve_lock;
	spinlock_t queue_lock;
	u32 xid;
	struct rpc_task *snd_task;
	struct list_head xmit_queue;
	struct svc_xprt *bc_xprt;
	struct rb_root recv_queue;
	struct {
		long unsigned int bind_count;
		long unsigned int connect_count;
		long unsigned int connect_start;
		long unsigned int connect_time;
		long unsigned int sends;
		long unsigned int recvs;
		long unsigned int bad_xids;
		long unsigned int max_slots;
		long long unsigned int req_u;
		long long unsigned int bklog_u;
		long long unsigned int sending_u;
		long long unsigned int pending_u;
	} stat;
	struct net *xprt_net;
	const char *servername;
	const char *address_strings[6];
	struct callback_head rcu;
};

struct rpc_credops;

struct rpc_cred {
	struct hlist_node cr_hash;
	struct list_head cr_lru;
	struct callback_head cr_rcu;
	struct rpc_auth *cr_auth;
	const struct rpc_credops *cr_ops;
	long unsigned int cr_expire;
	long unsigned int cr_flags;
	refcount_t cr_count;
	const struct cred *cr_cred;
};

typedef u32 rpc_authflavor_t;

struct ethhdr {
	unsigned char h_dest[6];
	unsigned char h_source[6];
	__be16 h_proto;
};

struct flow_dissector {
	unsigned int used_keys;
	short unsigned int offset[27];
};

struct flowi_tunnel {
	__be64 tun_id;
};

struct flowi_common {
	int flowic_oif;
	int flowic_iif;
	__u32 flowic_mark;
	__u8 flowic_tos;
	__u8 flowic_scope;
	__u8 flowic_proto;
	__u8 flowic_flags;
	__u32 flowic_secid;
	kuid_t flowic_uid;
	struct flowi_tunnel flowic_tun_key;
	__u32 flowic_multipath_hash;
};

union flowi_uli {
	struct {
		__be16 dport;
		__be16 sport;
	} ports;
	struct {
		__u8 type;
		__u8 code;
	} icmpt;
	struct {
		__le16 dport;
		__le16 sport;
	} dnports;
	__be32 spi;
	__be32 gre_key;
	struct {
		__u8 type;
	} mht;
};

struct flowi4 {
	struct flowi_common __fl_common;
	__be32 saddr;
	__be32 daddr;
	union flowi_uli uli;
};

struct flowi6 {
	struct flowi_common __fl_common;
	struct in6_addr daddr;
	struct in6_addr saddr;
	__be32 flowlabel;
	union flowi_uli uli;
	__u32 mp_hash;
};

struct flowidn {
	struct flowi_common __fl_common;
	__le16 daddr;
	__le16 saddr;
	union flowi_uli uli;
};

struct flowi {
	union {
		struct flowi_common __fl_common;
		struct flowi4 ip4;
		struct flowi6 ip6;
		struct flowidn dn;
	} u;
};

struct ipstats_mib {
	u64 mibs[37];
	struct u64_stats_sync syncp;
};

struct icmp_mib {
	long unsigned int mibs[28];
};

struct icmpmsg_mib {
	atomic_long_t mibs[512];
};

struct icmpv6_mib {
	long unsigned int mibs[6];
};

struct icmpv6_mib_device {
	atomic_long_t mibs[6];
};

struct icmpv6msg_mib {
	atomic_long_t mibs[512];
};

struct icmpv6msg_mib_device {
	atomic_long_t mibs[512];
};

struct tcp_mib {
	long unsigned int mibs[16];
};

struct udp_mib {
	long unsigned int mibs[9];
};

struct linux_mib {
	long unsigned int mibs[122];
};

struct inet_frags;

struct fqdir {
	long int high_thresh;
	long int low_thresh;
	int timeout;
	int max_dist;
	struct inet_frags *f;
	struct net *net;
	bool dead;
	long: 56;
	long: 64;
	long: 64;
	struct rhashtable rhashtable;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	atomic_long_t mem;
	struct work_struct destroy_work;
	long: 64;
	long: 64;
	long: 64;
};

struct inet_frag_queue;

struct inet_frags {
	unsigned int qsize;
	void (*constructor)(struct inet_frag_queue *, const void *);
	void (*destructor)(struct inet_frag_queue *);
	void (*frag_expire)(struct timer_list *);
	struct kmem_cache *frags_cachep;
	const char *frags_cache_name;
	struct rhashtable_params rhash_params;
	refcount_t refcnt;
	struct completion completion;
};

struct frag_v4_compare_key {
	__be32 saddr;
	__be32 daddr;
	u32 user;
	u32 vif;
	__be16 id;
	u16 protocol;
};

struct frag_v6_compare_key {
	struct in6_addr saddr;
	struct in6_addr daddr;
	u32 user;
	__be32 id;
	u32 iif;
};

struct inet_frag_queue {
	struct rhash_head node;
	union {
		struct frag_v4_compare_key v4;
		struct frag_v6_compare_key v6;
	} key;
	struct timer_list timer;
	spinlock_t lock;
	refcount_t refcnt;
	struct rb_root rb_fragments;
	struct sk_buff *fragments_tail;
	struct sk_buff *last_run_head;
	ktime_t stamp;
	int len;
	int meat;
	__u8 flags;
	u16 max_size;
	struct fqdir *fqdir;
	struct callback_head rcu;
};

struct fib_rule;

struct fib_lookup_arg;

struct fib_rule_hdr;

struct nlattr;

struct netlink_ext_ack;

struct nla_policy;

struct fib_rules_ops {
	int family;
	struct list_head list;
	int rule_size;
	int addr_size;
	int unresolved_rules;
	int nr_goto_rules;
	unsigned int fib_rules_seq;
	int (*action)(struct fib_rule *, struct flowi *, int, struct fib_lookup_arg *);
	bool (*suppress)(struct fib_rule *, struct fib_lookup_arg *);
	int (*match)(struct fib_rule *, struct flowi *, int);
	int (*configure)(struct fib_rule *, struct sk_buff *, struct fib_rule_hdr *, struct nlattr **, struct netlink_ext_ack *);
	int (*delete)(struct fib_rule *);
	int (*compare)(struct fib_rule *, struct fib_rule_hdr *, struct nlattr **);
	int (*fill)(struct fib_rule *, struct sk_buff *, struct fib_rule_hdr *);
	size_t (*nlmsg_payload)(struct fib_rule *);
	void (*flush_cache)(struct fib_rules_ops *);
	int nlgroup;
	const struct nla_policy *policy;
	struct list_head rules_list;
	struct module *owner;
	struct net *fro_net;
	struct callback_head rcu;
};

enum tcp_ca_event {
	CA_EVENT_TX_START = 0,
	CA_EVENT_CWND_RESTART = 1,
	CA_EVENT_COMPLETE_CWR = 2,
	CA_EVENT_LOSS = 3,
	CA_EVENT_ECN_NO_CE = 4,
	CA_EVENT_ECN_IS_CE = 5,
};

struct ack_sample;

struct rate_sample;

union tcp_cc_info;

struct tcp_congestion_ops {
	struct list_head list;
	u32 key;
	u32 flags;
	void (*init)(struct sock *);
	void (*release)(struct sock *);
	u32 (*ssthresh)(struct sock *);
	void (*cong_avoid)(struct sock *, u32, u32);
	void (*set_state)(struct sock *, u8);
	void (*cwnd_event)(struct sock *, enum tcp_ca_event);
	void (*in_ack_event)(struct sock *, u32);
	u32 (*undo_cwnd)(struct sock *);
	void (*pkts_acked)(struct sock *, const struct ack_sample *);
	u32 (*min_tso_segs)(struct sock *);
	u32 (*sndbuf_expand)(struct sock *);
	void (*cong_control)(struct sock *, const struct rate_sample *);
	size_t (*get_info)(struct sock *, u32, int *, union tcp_cc_info *);
	char name[16];
	struct module *owner;
};

struct fib_notifier_ops {
	int family;
	struct list_head list;
	unsigned int (*fib_seq_read)(struct net *);
	int (*fib_dump)(struct net *, struct notifier_block *, struct netlink_ext_ack *);
	struct module *owner;
	struct callback_head rcu;
};

struct xfrm_state;

struct lwtunnel_state;

struct dst_entry {
	struct net_device *dev;
	struct dst_ops *ops;
	long unsigned int _metrics;
	long unsigned int expires;
	struct xfrm_state *xfrm;
	int (*input)(struct sk_buff *);
	int (*output)(struct net *, struct sock *, struct sk_buff *);
	short unsigned int flags;
	short int obsolete;
	short unsigned int header_len;
	short unsigned int trailer_len;
	atomic_t __refcnt;
	int __use;
	long unsigned int lastuse;
	struct lwtunnel_state *lwtstate;
	struct callback_head callback_head;
	short int error;
	short int __pad;
	__u32 tclassid;
};

struct hh_cache {
	unsigned int hh_len;
	seqlock_t hh_lock;
	long unsigned int hh_data[12];
};

struct neigh_table;

struct neigh_parms;

struct neigh_ops;

struct neighbour {
	struct neighbour *next;
	struct neigh_table *tbl;
	struct neigh_parms *parms;
	long unsigned int confirmed;
	long unsigned int updated;
	rwlock_t lock;
	refcount_t refcnt;
	unsigned int arp_queue_len_bytes;
	struct sk_buff_head arp_queue;
	struct timer_list timer;
	long unsigned int used;
	atomic_t probes;
	__u8 flags;
	__u8 nud_state;
	__u8 type;
	__u8 dead;
	u8 protocol;
	seqlock_t ha_lock;
	int: 32;
	unsigned char ha[32];
	struct hh_cache hh;
	int (*output)(struct neighbour *, struct sk_buff *);
	const struct neigh_ops *ops;
	struct list_head gc_list;
	struct callback_head rcu;
	struct net_device *dev;
	u8 primary_key[0];
};

struct ipv6_stable_secret {
	bool initialized;
	struct in6_addr secret;
};

struct ipv6_devconf {
	__s32 forwarding;
	__s32 hop_limit;
	__s32 mtu6;
	__s32 accept_ra;
	__s32 accept_redirects;
	__s32 autoconf;
	__s32 dad_transmits;
	__s32 rtr_solicits;
	__s32 rtr_solicit_interval;
	__s32 rtr_solicit_max_interval;
	__s32 rtr_solicit_delay;
	__s32 force_mld_version;
	__s32 mldv1_unsolicited_report_interval;
	__s32 mldv2_unsolicited_report_interval;
	__s32 use_tempaddr;
	__s32 temp_valid_lft;
	__s32 temp_prefered_lft;
	__s32 regen_max_retry;
	__s32 max_desync_factor;
	__s32 max_addresses;
	__s32 accept_ra_defrtr;
	__s32 accept_ra_min_hop_limit;
	__s32 accept_ra_pinfo;
	__s32 ignore_routes_with_linkdown;
	__s32 proxy_ndp;
	__s32 accept_source_route;
	__s32 accept_ra_from_local;
	__s32 disable_ipv6;
	__s32 drop_unicast_in_l2_multicast;
	__s32 accept_dad;
	__s32 force_tllao;
	__s32 ndisc_notify;
	__s32 suppress_frag_ndisc;
	__s32 accept_ra_mtu;
	__s32 drop_unsolicited_na;
	struct ipv6_stable_secret stable_secret;
	__s32 use_oif_addrs_only;
	__s32 keep_addr_on_down;
	__s32 seg6_enabled;
	__u32 enhanced_dad;
	__u32 addr_gen_mode;
	__s32 disable_policy;
	__s32 ndisc_tclass;
	__s32 rpl_seg_enabled;
	struct ctl_table_header *sysctl_header;
};

struct nf_queue_entry;

struct nf_queue_handler {
	int (*outfn)(struct nf_queue_entry *, unsigned int);
	void (*nf_hook_drop)(struct net *);
};

enum nf_log_type {
	NF_LOG_TYPE_LOG = 0,
	NF_LOG_TYPE_ULOG = 1,
	NF_LOG_TYPE_MAX = 2,
};

typedef u8 u_int8_t;

struct nf_loginfo;

typedef void nf_logfn(struct net *, u_int8_t, unsigned int, const struct sk_buff *, const struct net_device *, const struct net_device *, const struct nf_loginfo *, const char *);

struct nf_logger {
	char *name;
	enum nf_log_type type;
	nf_logfn *logfn;
	struct module *me;
};

struct hlist_nulls_head {
	struct hlist_nulls_node *first;
};

struct ip_conntrack_stat {
	unsigned int found;
	unsigned int invalid;
	unsigned int ignore;
	unsigned int insert;
	unsigned int insert_failed;
	unsigned int drop;
	unsigned int early_drop;
	unsigned int error;
	unsigned int expect_new;
	unsigned int expect_create;
	unsigned int expect_delete;
	unsigned int search_restart;
};

struct ct_pcpu {
	spinlock_t lock;
	struct hlist_nulls_head unconfirmed;
	struct hlist_nulls_head dying;
};

typedef enum {
	SS_FREE = 0,
	SS_UNCONNECTED = 1,
	SS_CONNECTING = 2,
	SS_CONNECTED = 3,
	SS_DISCONNECTING = 4,
} socket_state;

struct socket_wq {
	wait_queue_head_t wait;
	struct fasync_struct *fasync_list;
	long unsigned int flags;
	struct callback_head rcu;
	long: 64;
};

struct proto_ops;

struct socket {
	socket_state state;
	short int type;
	long unsigned int flags;
	struct file *file;
	struct sock *sk;
	const struct proto_ops *ops;
	long: 64;
	long: 64;
	long: 64;
	struct socket_wq wq;
};

typedef int (*sk_read_actor_t)(read_descriptor_t *, struct sk_buff *, unsigned int, size_t);

struct proto_ops {
	int family;
	struct module *owner;
	int (*release)(struct socket *);
	int (*bind)(struct socket *, struct sockaddr *, int);
	int (*connect)(struct socket *, struct sockaddr *, int, int);
	int (*socketpair)(struct socket *, struct socket *);
	int (*accept)(struct socket *, struct socket *, int, bool);
	int (*getname)(struct socket *, struct sockaddr *, int);
	__poll_t (*poll)(struct file *, struct socket *, struct poll_table_struct *);
	int (*ioctl)(struct socket *, unsigned int, long unsigned int);
	int (*compat_ioctl)(struct socket *, unsigned int, long unsigned int);
	int (*gettstamp)(struct socket *, void *, bool, bool);
	int (*listen)(struct socket *, int);
	int (*shutdown)(struct socket *, int);
	int (*setsockopt)(struct socket *, int, int, char *, unsigned int);
	int (*getsockopt)(struct socket *, int, int, char *, int *);
	int (*compat_setsockopt)(struct socket *, int, int, char *, unsigned int);
	int (*compat_getsockopt)(struct socket *, int, int, char *, int *);
	void (*show_fdinfo)(struct seq_file *, struct socket *);
	int (*sendmsg)(struct socket *, struct msghdr *, size_t);
	int (*recvmsg)(struct socket *, struct msghdr *, size_t, int);
	int (*mmap)(struct file *, struct socket *, struct vm_area_struct *);
	ssize_t (*sendpage)(struct socket *, struct page *, int, size_t, int);
	ssize_t (*splice_read)(struct socket *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*set_peek_off)(struct sock *, int);
	int (*peek_len)(struct socket *);
	int (*read_sock)(struct sock *, read_descriptor_t *, sk_read_actor_t);
	int (*sendpage_locked)(struct sock *, struct page *, int, size_t, int);
	int (*sendmsg_locked)(struct sock *, struct msghdr *, size_t);
	int (*set_rcvlowat)(struct sock *, int);
};

enum swiotlb_force {
	SWIOTLB_NORMAL = 0,
	SWIOTLB_FORCE = 1,
	SWIOTLB_NO_FORCE = 2,
};

struct pipe_buf_operations;

struct pipe_buffer {
	struct page *page;
	unsigned int offset;
	unsigned int len;
	const struct pipe_buf_operations *ops;
	unsigned int flags;
	long unsigned int private;
};

struct pipe_buf_operations {
	int (*confirm)(struct pipe_inode_info *, struct pipe_buffer *);
	void (*release)(struct pipe_inode_info *, struct pipe_buffer *);
	bool (*try_steal)(struct pipe_inode_info *, struct pipe_buffer *);
	bool (*get)(struct pipe_inode_info *, struct pipe_buffer *);
};

struct skb_ext {
	refcount_t refcnt;
	u8 offset[1];
	u8 chunks;
	short: 16;
	char data[0];
};

struct skb_checksum_ops {
	__wsum (*update)(const void *, int, __wsum);
	__wsum (*combine)(__wsum, __wsum, int, int);
};

struct pernet_operations {
	struct list_head list;
	int (*init)(struct net *);
	void (*pre_exit)(struct net *);
	void (*exit)(struct net *);
	void (*exit_batch)(struct list_head *);
	unsigned int *id;
	size_t size;
};

struct auth_cred {
	const struct cred *cred;
	const char *principal;
};

struct rpc_authops;

struct rpc_cred_cache;

struct rpc_auth {
	unsigned int au_cslack;
	unsigned int au_rslack;
	unsigned int au_verfsize;
	unsigned int au_ralign;
	long unsigned int au_flags;
	const struct rpc_authops *au_ops;
	rpc_authflavor_t au_flavor;
	refcount_t au_count;
	struct rpc_cred_cache *au_credcache;
};

struct rpc_credops {
	const char *cr_name;
	int (*cr_init)(struct rpc_auth *, struct rpc_cred *);
	void (*crdestroy)(struct rpc_cred *);
	int (*crmatch)(struct auth_cred *, struct rpc_cred *, int);
	int (*crmarshal)(struct rpc_task *, struct xdr_stream *);
	int (*crrefresh)(struct rpc_task *);
	int (*crvalidate)(struct rpc_task *, struct xdr_stream *);
	int (*crwrap_req)(struct rpc_task *, struct xdr_stream *);
	int (*crunwrap_resp)(struct rpc_task *, struct xdr_stream *);
	int (*crkey_timeout)(struct rpc_cred *);
	char * (*crstringify_acceptor)(struct rpc_cred *);
	bool (*crneed_reencode)(struct rpc_task *);
};

struct rpc_auth_create_args;

struct rpcsec_gss_info;

struct rpc_authops {
	struct module *owner;
	rpc_authflavor_t au_flavor;
	char *au_name;
	struct rpc_auth * (*create)(const struct rpc_auth_create_args *, struct rpc_clnt *);
	void (*destroy)(struct rpc_auth *);
	int (*hash_cred)(struct auth_cred *, unsigned int);
	struct rpc_cred * (*lookup_cred)(struct rpc_auth *, struct auth_cred *, int);
	struct rpc_cred * (*crcreate)(struct rpc_auth *, struct auth_cred *, int, gfp_t);
	rpc_authflavor_t (*info2flavor)(struct rpcsec_gss_info *);
	int (*flavor2info)(rpc_authflavor_t, struct rpcsec_gss_info *);
	int (*key_timeout)(struct rpc_auth *, struct rpc_cred *);
};

struct rpc_auth_create_args {
	rpc_authflavor_t pseudoflavor;
	const char *target_name;
};

struct rpcsec_gss_oid {
	unsigned int len;
	u8 data[32];
};

struct rpcsec_gss_info {
	struct rpcsec_gss_oid oid;
	u32 qop;
	u32 service;
};

struct rpc_xprt_ops {
	void (*set_buffer_size)(struct rpc_xprt *, size_t, size_t);
	int (*reserve_xprt)(struct rpc_xprt *, struct rpc_task *);
	void (*release_xprt)(struct rpc_xprt *, struct rpc_task *);
	void (*alloc_slot)(struct rpc_xprt *, struct rpc_task *);
	void (*free_slot)(struct rpc_xprt *, struct rpc_rqst *);
	void (*rpcbind)(struct rpc_task *);
	void (*set_port)(struct rpc_xprt *, short unsigned int);
	void (*connect)(struct rpc_xprt *, struct rpc_task *);
	int (*buf_alloc)(struct rpc_task *);
	void (*buf_free)(struct rpc_task *);
	void (*prepare_request)(struct rpc_rqst *);
	int (*send_request)(struct rpc_rqst *);
	void (*wait_for_reply_request)(struct rpc_task *);
	void (*timer)(struct rpc_xprt *, struct rpc_task *);
	void (*release_request)(struct rpc_task *);
	void (*close)(struct rpc_xprt *);
	void (*destroy)(struct rpc_xprt *);
	void (*set_connect_timeout)(struct rpc_xprt *, long unsigned int, long unsigned int);
	void (*print_stats)(struct rpc_xprt *, struct seq_file *);
	int (*enable_swap)(struct rpc_xprt *);
	void (*disable_swap)(struct rpc_xprt *);
	void (*inject_disconnect)(struct rpc_xprt *);
	int (*bc_setup)(struct rpc_xprt *, unsigned int);
	size_t (*bc_maxpayload)(struct rpc_xprt *);
	unsigned int (*bc_num_slots)(struct rpc_xprt *);
	void (*bc_free_rqst)(struct rpc_rqst *);
	void (*bc_destroy)(struct rpc_xprt *, unsigned int);
};

struct rpc_xprt_switch {
	spinlock_t xps_lock;
	struct kref xps_kref;
	unsigned int xps_nxprts;
	unsigned int xps_nactive;
	atomic_long_t xps_queuelen;
	struct list_head xps_xprt_list;
	struct net *xps_net;
	const struct rpc_xprt_iter_ops *xps_iter_ops;
	struct callback_head xps_rcu;
};

struct rpc_stat {
	const struct rpc_program *program;
	unsigned int netcnt;
	unsigned int netudpcnt;
	unsigned int nettcpcnt;
	unsigned int nettcpconn;
	unsigned int netreconn;
	unsigned int rpccnt;
	unsigned int rpcretrans;
	unsigned int rpcauthrefresh;
	unsigned int rpcgarbage;
};

struct rpc_version;

struct rpc_program {
	const char *name;
	u32 number;
	unsigned int nrvers;
	const struct rpc_version **version;
	struct rpc_stat *stats;
	const char *pipe_dir_name;
};

struct ipv6_params {
	__s32 disable_ipv6;
	__s32 autoconf;
};

struct dql {
	unsigned int num_queued;
	unsigned int adj_limit;
	unsigned int last_obj_cnt;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	unsigned int limit;
	unsigned int num_completed;
	unsigned int prev_ovlimit;
	unsigned int prev_num_queued;
	unsigned int prev_last_obj_cnt;
	unsigned int lowest_slack;
	long unsigned int slack_start_time;
	unsigned int max_limit;
	unsigned int min_limit;
	unsigned int slack_hold_time;
	long: 32;
	long: 64;
	long: 64;
};

struct ethtool_drvinfo {
	__u32 cmd;
	char driver[32];
	char version[32];
	char fw_version[32];
	char bus_info[32];
	char erom_version[32];
	char reserved2[12];
	__u32 n_priv_flags;
	__u32 n_stats;
	__u32 testinfo_len;
	__u32 eedump_len;
	__u32 regdump_len;
};

struct ethtool_wolinfo {
	__u32 cmd;
	__u32 supported;
	__u32 wolopts;
	__u8 sopass[6];
};

struct ethtool_tunable {
	__u32 cmd;
	__u32 id;
	__u32 type_id;
	__u32 len;
	void *data[0];
};

struct ethtool_regs {
	__u32 cmd;
	__u32 version;
	__u32 len;
	__u8 data[0];
};

struct ethtool_eeprom {
	__u32 cmd;
	__u32 magic;
	__u32 offset;
	__u32 len;
	__u8 data[0];
};

struct ethtool_eee {
	__u32 cmd;
	__u32 supported;
	__u32 advertised;
	__u32 lp_advertised;
	__u32 eee_active;
	__u32 eee_enabled;
	__u32 tx_lpi_enabled;
	__u32 tx_lpi_timer;
	__u32 reserved[2];
};

struct ethtool_modinfo {
	__u32 cmd;
	__u32 type;
	__u32 eeprom_len;
	__u32 reserved[8];
};

struct ethtool_coalesce {
	__u32 cmd;
	__u32 rx_coalesce_usecs;
	__u32 rx_max_coalesced_frames;
	__u32 rx_coalesce_usecs_irq;
	__u32 rx_max_coalesced_frames_irq;
	__u32 tx_coalesce_usecs;
	__u32 tx_max_coalesced_frames;
	__u32 tx_coalesce_usecs_irq;
	__u32 tx_max_coalesced_frames_irq;
	__u32 stats_block_coalesce_usecs;
	__u32 use_adaptive_rx_coalesce;
	__u32 use_adaptive_tx_coalesce;
	__u32 pkt_rate_low;
	__u32 rx_coalesce_usecs_low;
	__u32 rx_max_coalesced_frames_low;
	__u32 tx_coalesce_usecs_low;
	__u32 tx_max_coalesced_frames_low;
	__u32 pkt_rate_high;
	__u32 rx_coalesce_usecs_high;
	__u32 rx_max_coalesced_frames_high;
	__u32 tx_coalesce_usecs_high;
	__u32 tx_max_coalesced_frames_high;
	__u32 rate_sample_interval;
};

struct ethtool_ringparam {
	__u32 cmd;
	__u32 rx_max_pending;
	__u32 rx_mini_max_pending;
	__u32 rx_jumbo_max_pending;
	__u32 tx_max_pending;
	__u32 rx_pending;
	__u32 rx_mini_pending;
	__u32 rx_jumbo_pending;
	__u32 tx_pending;
};

struct ethtool_channels {
	__u32 cmd;
	__u32 max_rx;
	__u32 max_tx;
	__u32 max_other;
	__u32 max_combined;
	__u32 rx_count;
	__u32 tx_count;
	__u32 other_count;
	__u32 combined_count;
};

struct ethtool_pauseparam {
	__u32 cmd;
	__u32 autoneg;
	__u32 rx_pause;
	__u32 tx_pause;
};

struct ethtool_test {
	__u32 cmd;
	__u32 flags;
	__u32 reserved;
	__u32 len;
	__u64 data[0];
};

struct ethtool_stats {
	__u32 cmd;
	__u32 n_stats;
	__u64 data[0];
};

struct ethtool_tcpip4_spec {
	__be32 ip4src;
	__be32 ip4dst;
	__be16 psrc;
	__be16 pdst;
	__u8 tos;
};

struct ethtool_ah_espip4_spec {
	__be32 ip4src;
	__be32 ip4dst;
	__be32 spi;
	__u8 tos;
};

struct ethtool_usrip4_spec {
	__be32 ip4src;
	__be32 ip4dst;
	__be32 l4_4_bytes;
	__u8 tos;
	__u8 ip_ver;
	__u8 proto;
};

struct ethtool_tcpip6_spec {
	__be32 ip6src[4];
	__be32 ip6dst[4];
	__be16 psrc;
	__be16 pdst;
	__u8 tclass;
};

struct ethtool_ah_espip6_spec {
	__be32 ip6src[4];
	__be32 ip6dst[4];
	__be32 spi;
	__u8 tclass;
};

struct ethtool_usrip6_spec {
	__be32 ip6src[4];
	__be32 ip6dst[4];
	__be32 l4_4_bytes;
	__u8 tclass;
	__u8 l4_proto;
};

union ethtool_flow_union {
	struct ethtool_tcpip4_spec tcp_ip4_spec;
	struct ethtool_tcpip4_spec udp_ip4_spec;
	struct ethtool_tcpip4_spec sctp_ip4_spec;
	struct ethtool_ah_espip4_spec ah_ip4_spec;
	struct ethtool_ah_espip4_spec esp_ip4_spec;
	struct ethtool_usrip4_spec usr_ip4_spec;
	struct ethtool_tcpip6_spec tcp_ip6_spec;
	struct ethtool_tcpip6_spec udp_ip6_spec;
	struct ethtool_tcpip6_spec sctp_ip6_spec;
	struct ethtool_ah_espip6_spec ah_ip6_spec;
	struct ethtool_ah_espip6_spec esp_ip6_spec;
	struct ethtool_usrip6_spec usr_ip6_spec;
	struct ethhdr ether_spec;
	__u8 hdata[52];
};

struct ethtool_flow_ext {
	__u8 padding[2];
	unsigned char h_dest[6];
	__be16 vlan_etype;
	__be16 vlan_tci;
	__be32 data[2];
};

struct ethtool_rx_flow_spec {
	__u32 flow_type;
	union ethtool_flow_union h_u;
	struct ethtool_flow_ext h_ext;
	union ethtool_flow_union m_u;
	struct ethtool_flow_ext m_ext;
	__u64 ring_cookie;
	__u32 location;
};

struct ethtool_rxnfc {
	__u32 cmd;
	__u32 flow_type;
	__u64 data;
	struct ethtool_rx_flow_spec fs;
	union {
		__u32 rule_cnt;
		__u32 rss_context;
	};
	__u32 rule_locs[0];
};

struct ethtool_flash {
	__u32 cmd;
	__u32 region;
	char data[128];
};

struct ethtool_dump {
	__u32 cmd;
	__u32 version;
	__u32 flag;
	__u32 len;
	__u8 data[0];
};

struct ethtool_ts_info {
	__u32 cmd;
	__u32 so_timestamping;
	__s32 phc_index;
	__u32 tx_types;
	__u32 tx_reserved[3];
	__u32 rx_filters;
	__u32 rx_reserved[3];
};

struct ethtool_fecparam {
	__u32 cmd;
	__u32 active_fec;
	__u32 fec;
	__u32 reserved;
};

struct ethtool_link_settings {
	__u32 cmd;
	__u32 speed;
	__u8 duplex;
	__u8 port;
	__u8 phy_address;
	__u8 autoneg;
	__u8 mdio_support;
	__u8 eth_tp_mdix;
	__u8 eth_tp_mdix_ctrl;
	__s8 link_mode_masks_nwords;
	__u8 transceiver;
	__u8 master_slave_cfg;
	__u8 master_slave_state;
	__u8 reserved1[1];
	__u32 reserved[7];
	__u32 link_mode_masks[0];
};

enum ethtool_phys_id_state {
	ETHTOOL_ID_INACTIVE = 0,
	ETHTOOL_ID_ACTIVE = 1,
	ETHTOOL_ID_ON = 2,
	ETHTOOL_ID_OFF = 3,
};

struct ethtool_link_ksettings {
	struct ethtool_link_settings base;
	struct {
		long unsigned int supported[2];
		long unsigned int advertising[2];
		long unsigned int lp_advertising[2];
	} link_modes;
};

struct ethtool_ops {
	u32 supported_coalesce_params;
	void (*get_drvinfo)(struct net_device *, struct ethtool_drvinfo *);
	int (*get_regs_len)(struct net_device *);
	void (*get_regs)(struct net_device *, struct ethtool_regs *, void *);
	void (*get_wol)(struct net_device *, struct ethtool_wolinfo *);
	int (*set_wol)(struct net_device *, struct ethtool_wolinfo *);
	u32 (*get_msglevel)(struct net_device *);
	void (*set_msglevel)(struct net_device *, u32);
	int (*nway_reset)(struct net_device *);
	u32 (*get_link)(struct net_device *);
	int (*get_eeprom_len)(struct net_device *);
	int (*get_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int (*set_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int (*get_coalesce)(struct net_device *, struct ethtool_coalesce *);
	int (*set_coalesce)(struct net_device *, struct ethtool_coalesce *);
	void (*get_ringparam)(struct net_device *, struct ethtool_ringparam *);
	int (*set_ringparam)(struct net_device *, struct ethtool_ringparam *);
	void (*get_pauseparam)(struct net_device *, struct ethtool_pauseparam *);
	int (*set_pauseparam)(struct net_device *, struct ethtool_pauseparam *);
	void (*self_test)(struct net_device *, struct ethtool_test *, u64 *);
	void (*get_strings)(struct net_device *, u32, u8 *);
	int (*set_phys_id)(struct net_device *, enum ethtool_phys_id_state);
	void (*get_ethtool_stats)(struct net_device *, struct ethtool_stats *, u64 *);
	int (*begin)(struct net_device *);
	void (*complete)(struct net_device *);
	u32 (*get_priv_flags)(struct net_device *);
	int (*set_priv_flags)(struct net_device *, u32);
	int (*get_sset_count)(struct net_device *, int);
	int (*get_rxnfc)(struct net_device *, struct ethtool_rxnfc *, u32 *);
	int (*set_rxnfc)(struct net_device *, struct ethtool_rxnfc *);
	int (*flash_device)(struct net_device *, struct ethtool_flash *);
	int (*reset)(struct net_device *, u32 *);
	u32 (*get_rxfh_key_size)(struct net_device *);
	u32 (*get_rxfh_indir_size)(struct net_device *);
	int (*get_rxfh)(struct net_device *, u32 *, u8 *, u8 *);
	int (*set_rxfh)(struct net_device *, const u32 *, const u8 *, const u8);
	int (*get_rxfh_context)(struct net_device *, u32 *, u8 *, u8 *, u32);
	int (*set_rxfh_context)(struct net_device *, const u32 *, const u8 *, const u8, u32 *, bool);
	void (*get_channels)(struct net_device *, struct ethtool_channels *);
	int (*set_channels)(struct net_device *, struct ethtool_channels *);
	int (*get_dump_flag)(struct net_device *, struct ethtool_dump *);
	int (*get_dump_data)(struct net_device *, struct ethtool_dump *, void *);
	int (*set_dump)(struct net_device *, struct ethtool_dump *);
	int (*get_ts_info)(struct net_device *, struct ethtool_ts_info *);
	int (*get_module_info)(struct net_device *, struct ethtool_modinfo *);
	int (*get_module_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int (*get_eee)(struct net_device *, struct ethtool_eee *);
	int (*set_eee)(struct net_device *, struct ethtool_eee *);
	int (*get_tunable)(struct net_device *, const struct ethtool_tunable *, void *);
	int (*set_tunable)(struct net_device *, const struct ethtool_tunable *, const void *);
	int (*get_per_queue_coalesce)(struct net_device *, u32, struct ethtool_coalesce *);
	int (*set_per_queue_coalesce)(struct net_device *, u32, struct ethtool_coalesce *);
	int (*get_link_ksettings)(struct net_device *, struct ethtool_link_ksettings *);
	int (*set_link_ksettings)(struct net_device *, const struct ethtool_link_ksettings *);
	int (*get_fecparam)(struct net_device *, struct ethtool_fecparam *);
	int (*set_fecparam)(struct net_device *, struct ethtool_fecparam *);
	void (*get_ethtool_phy_stats)(struct net_device *, struct ethtool_stats *, u64 *);
};

struct xdp_mem_info {
	u32 type;
	u32 id;
};

struct xdp_rxq_info {
	struct net_device *dev;
	u32 queue_index;
	u32 reg_state;
	struct xdp_mem_info mem;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct xdp_frame {
	void *data;
	u16 len;
	u16 headroom;
	u32 metasize: 8;
	u32 frame_sz: 24;
	struct xdp_mem_info mem;
	struct net_device *dev_rx;
};

struct nlmsghdr {
	__u32 nlmsg_len;
	__u16 nlmsg_type;
	__u16 nlmsg_flags;
	__u32 nlmsg_seq;
	__u32 nlmsg_pid;
};

struct nlattr {
	__u16 nla_len;
	__u16 nla_type;
};

struct netlink_ext_ack {
	const char *_msg;
	const struct nlattr *bad_attr;
	u8 cookie[20];
	u8 cookie_len;
};

struct netlink_callback {
	struct sk_buff *skb;
	const struct nlmsghdr *nlh;
	int (*dump)(struct sk_buff *, struct netlink_callback *);
	int (*done)(struct netlink_callback *);
	void *data;
	struct module *module;
	struct netlink_ext_ack *extack;
	u16 family;
	u16 answer_flags;
	u32 min_dump_alloc;
	unsigned int prev_seq;
	unsigned int seq;
	bool strict_check;
	union {
		u8 ctx[48];
		long int args[6];
	};
};

struct ndmsg {
	__u8 ndm_family;
	__u8 ndm_pad1;
	__u16 ndm_pad2;
	__s32 ndm_ifindex;
	__u16 ndm_state;
	__u8 ndm_flags;
	__u8 ndm_type;
};

struct rtnl_link_stats64 {
	__u64 rx_packets;
	__u64 tx_packets;
	__u64 rx_bytes;
	__u64 tx_bytes;
	__u64 rx_errors;
	__u64 tx_errors;
	__u64 rx_dropped;
	__u64 tx_dropped;
	__u64 multicast;
	__u64 collisions;
	__u64 rx_length_errors;
	__u64 rx_over_errors;
	__u64 rx_crc_errors;
	__u64 rx_frame_errors;
	__u64 rx_fifo_errors;
	__u64 rx_missed_errors;
	__u64 tx_aborted_errors;
	__u64 tx_carrier_errors;
	__u64 tx_fifo_errors;
	__u64 tx_heartbeat_errors;
	__u64 tx_window_errors;
	__u64 rx_compressed;
	__u64 tx_compressed;
	__u64 rx_nohandler;
};

struct ifla_vf_guid {
	__u32 vf;
	__u64 guid;
};

struct ifla_vf_stats {
	__u64 rx_packets;
	__u64 tx_packets;
	__u64 rx_bytes;
	__u64 tx_bytes;
	__u64 broadcast;
	__u64 multicast;
	__u64 rx_dropped;
	__u64 tx_dropped;
};

struct ifla_vf_info {
	__u32 vf;
	__u8 mac[32];
	__u32 vlan;
	__u32 qos;
	__u32 spoofchk;
	__u32 linkstate;
	__u32 min_tx_rate;
	__u32 max_tx_rate;
	__u32 rss_query_en;
	__u32 trusted;
	__be16 vlan_proto;
};

struct tc_stats {
	__u64 bytes;
	__u32 packets;
	__u32 drops;
	__u32 overlimits;
	__u32 bps;
	__u32 pps;
	__u32 qlen;
	__u32 backlog;
};

struct tc_sizespec {
	unsigned char cell_log;
	unsigned char size_log;
	short int cell_align;
	int overhead;
	unsigned int linklayer;
	unsigned int mpu;
	unsigned int mtu;
	unsigned int tsize;
};

enum netdev_tx {
	__NETDEV_TX_MIN = 2147483648,
	NETDEV_TX_OK = 0,
	NETDEV_TX_BUSY = 16,
};

typedef enum netdev_tx netdev_tx_t;

struct header_ops {
	int (*create)(struct sk_buff *, struct net_device *, short unsigned int, const void *, const void *, unsigned int);
	int (*parse)(const struct sk_buff *, unsigned char *);
	int (*cache)(const struct neighbour *, struct hh_cache *, __be16);
	void (*cache_update)(struct hh_cache *, const struct net_device *, const unsigned char *);
	bool (*validate)(const char *, unsigned int);
	__be16 (*parse_protocol)(const struct sk_buff *);
};

struct gro_list {
	struct list_head list;
	int count;
};

struct napi_struct {
	struct list_head poll_list;
	long unsigned int state;
	int weight;
	int defer_hard_irqs_count;
	long unsigned int gro_bitmask;
	int (*poll)(struct napi_struct *, int);
	int poll_owner;
	struct net_device *dev;
	struct gro_list gro_hash[8];
	struct sk_buff *skb;
	struct list_head rx_list;
	int rx_count;
	struct hrtimer timer;
	struct list_head dev_list;
	struct hlist_node napi_hash_node;
	unsigned int napi_id;
};

struct xdp_umem;

struct netdev_queue {
	struct net_device *dev;
	struct Qdisc *qdisc;
	struct Qdisc *qdisc_sleeping;
	struct kobject kobj;
	int numa_node;
	long unsigned int tx_maxrate;
	long unsigned int trans_timeout;
	struct net_device *sb_dev;
	struct xdp_umem *umem;
	spinlock_t _xmit_lock;
	int xmit_lock_owner;
	long unsigned int trans_start;
	long unsigned int state;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct dql dql;
};

struct qdisc_skb_head {
	struct sk_buff *head;
	struct sk_buff *tail;
	__u32 qlen;
	spinlock_t lock;
};

struct gnet_stats_basic_packed {
	__u64 bytes;
	__u64 packets;
};

struct gnet_stats_queue {
	__u32 qlen;
	__u32 backlog;
	__u32 drops;
	__u32 requeues;
	__u32 overlimits;
};

struct Qdisc_ops;

struct qdisc_size_table;

struct net_rate_estimator;

struct gnet_stats_basic_cpu;

struct Qdisc {
	int (*enqueue)(struct sk_buff *, struct Qdisc *, struct sk_buff **);
	struct sk_buff * (*dequeue)(struct Qdisc *);
	unsigned int flags;
	u32 limit;
	const struct Qdisc_ops *ops;
	struct qdisc_size_table *stab;
	struct hlist_node hash;
	u32 handle;
	u32 parent;
	struct netdev_queue *dev_queue;
	struct net_rate_estimator *rate_est;
	struct gnet_stats_basic_cpu *cpu_bstats;
	struct gnet_stats_queue *cpu_qstats;
	int padded;
	refcount_t refcnt;
	long: 64;
	long: 64;
	long: 64;
	struct sk_buff_head gso_skb;
	struct qdisc_skb_head q;
	struct gnet_stats_basic_packed bstats;
	seqcount_t running;
	struct gnet_stats_queue qstats;
	long unsigned int state;
	struct Qdisc *next_sched;
	struct sk_buff_head skb_bad_txq;
	spinlock_t busylock;
	spinlock_t seqlock;
	bool empty;
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct rps_map {
	unsigned int len;
	struct callback_head rcu;
	u16 cpus[0];
};

struct rps_dev_flow {
	u16 cpu;
	u16 filter;
	unsigned int last_qtail;
};

struct rps_dev_flow_table {
	unsigned int mask;
	struct callback_head rcu;
	struct rps_dev_flow flows[0];
};

struct rps_sock_flow_table {
	u32 mask;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	u32 ents[0];
};

struct netdev_rx_queue {
	struct rps_map *rps_map;
	struct rps_dev_flow_table *rps_flow_table;
	struct kobject kobj;
	struct net_device *dev;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct xdp_rxq_info xdp_rxq;
	struct xdp_umem *umem;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct xps_map {
	unsigned int len;
	unsigned int alloc_len;
	struct callback_head rcu;
	u16 queues[0];
};

struct xps_dev_maps {
	struct callback_head rcu;
	struct xps_map *attr_map[0];
};

struct netdev_phys_item_id {
	unsigned char id[32];
	unsigned char id_len;
};

enum tc_setup_type {
	TC_SETUP_QDISC_MQPRIO = 0,
	TC_SETUP_CLSU32 = 1,
	TC_SETUP_CLSFLOWER = 2,
	TC_SETUP_CLSMATCHALL = 3,
	TC_SETUP_CLSBPF = 4,
	TC_SETUP_BLOCK = 5,
	TC_SETUP_QDISC_CBS = 6,
	TC_SETUP_QDISC_RED = 7,
	TC_SETUP_QDISC_PRIO = 8,
	TC_SETUP_QDISC_MQ = 9,
	TC_SETUP_QDISC_ETF = 10,
	TC_SETUP_ROOT_QDISC = 11,
	TC_SETUP_QDISC_GRED = 12,
	TC_SETUP_QDISC_TAPRIO = 13,
	TC_SETUP_FT = 14,
	TC_SETUP_QDISC_ETS = 15,
	TC_SETUP_QDISC_TBF = 16,
	TC_SETUP_QDISC_FIFO = 17,
};

enum bpf_netdev_command {
	XDP_SETUP_PROG = 0,
	XDP_SETUP_PROG_HW = 1,
	XDP_QUERY_PROG = 2,
	XDP_QUERY_PROG_HW = 3,
	BPF_OFFLOAD_MAP_ALLOC = 4,
	BPF_OFFLOAD_MAP_FREE = 5,
	XDP_SETUP_XSK_UMEM = 6,
};

struct netdev_bpf {
	enum bpf_netdev_command command;
	union {
		struct {
			u32 flags;
			struct bpf_prog *prog;
			struct netlink_ext_ack *extack;
		};
		struct {
			u32 prog_id;
			u32 prog_flags;
		};
		struct {
			struct bpf_offloaded_map *offmap;
		};
		struct {
			struct xdp_umem *umem;
			u16 queue_id;
		} xsk;
	};
};

struct dev_ifalias {
	struct callback_head rcuhead;
	char ifalias[0];
};

struct netdev_name_node {
	struct hlist_node hlist;
	struct list_head list;
	struct net_device *dev;
	const char *name;
};

struct udp_tunnel_info;

struct devlink_port;

struct ip_tunnel_parm;

struct net_device_ops {
	int (*ndo_init)(struct net_device *);
	void (*ndo_uninit)(struct net_device *);
	int (*ndo_open)(struct net_device *);
	int (*ndo_stop)(struct net_device *);
	netdev_tx_t (*ndo_start_xmit)(struct sk_buff *, struct net_device *);
	netdev_features_t (*ndo_features_check)(struct sk_buff *, struct net_device *, netdev_features_t);
	u16 (*ndo_select_queue)(struct net_device *, struct sk_buff *, struct net_device *);
	void (*ndo_change_rx_flags)(struct net_device *, int);
	void (*ndo_set_rx_mode)(struct net_device *);
	int (*ndo_set_mac_address)(struct net_device *, void *);
	int (*ndo_validate_addr)(struct net_device *);
	int (*ndo_do_ioctl)(struct net_device *, struct ifreq *, int);
	int (*ndo_set_config)(struct net_device *, struct ifmap *);
	int (*ndo_change_mtu)(struct net_device *, int);
	int (*ndo_neigh_setup)(struct net_device *, struct neigh_parms *);
	void (*ndo_tx_timeout)(struct net_device *, unsigned int);
	void (*ndo_get_stats64)(struct net_device *, struct rtnl_link_stats64 *);
	bool (*ndo_has_offload_stats)(const struct net_device *, int);
	int (*ndo_get_offload_stats)(int, const struct net_device *, void *);
	struct net_device_stats * (*ndo_get_stats)(struct net_device *);
	int (*ndo_vlan_rx_add_vid)(struct net_device *, __be16, u16);
	int (*ndo_vlan_rx_kill_vid)(struct net_device *, __be16, u16);
	void (*ndo_poll_controller)(struct net_device *);
	int (*ndo_netpoll_setup)(struct net_device *, struct netpoll_info *);
	void (*ndo_netpoll_cleanup)(struct net_device *);
	int (*ndo_set_vf_mac)(struct net_device *, int, u8 *);
	int (*ndo_set_vf_vlan)(struct net_device *, int, u16, u8, __be16);
	int (*ndo_set_vf_rate)(struct net_device *, int, int, int);
	int (*ndo_set_vf_spoofchk)(struct net_device *, int, bool);
	int (*ndo_set_vf_trust)(struct net_device *, int, bool);
	int (*ndo_get_vf_config)(struct net_device *, int, struct ifla_vf_info *);
	int (*ndo_set_vf_link_state)(struct net_device *, int, int);
	int (*ndo_get_vf_stats)(struct net_device *, int, struct ifla_vf_stats *);
	int (*ndo_set_vf_port)(struct net_device *, int, struct nlattr **);
	int (*ndo_get_vf_port)(struct net_device *, int, struct sk_buff *);
	int (*ndo_get_vf_guid)(struct net_device *, int, struct ifla_vf_guid *, struct ifla_vf_guid *);
	int (*ndo_set_vf_guid)(struct net_device *, int, u64, int);
	int (*ndo_set_vf_rss_query_en)(struct net_device *, int, bool);
	int (*ndo_setup_tc)(struct net_device *, enum tc_setup_type, void *);
	int (*ndo_rx_flow_steer)(struct net_device *, const struct sk_buff *, u16, u32);
	int (*ndo_add_slave)(struct net_device *, struct net_device *, struct netlink_ext_ack *);
	int (*ndo_del_slave)(struct net_device *, struct net_device *);
	struct net_device * (*ndo_get_xmit_slave)(struct net_device *, struct sk_buff *, bool);
	netdev_features_t (*ndo_fix_features)(struct net_device *, netdev_features_t);
	int (*ndo_set_features)(struct net_device *, netdev_features_t);
	int (*ndo_neigh_construct)(struct net_device *, struct neighbour *);
	void (*ndo_neigh_destroy)(struct net_device *, struct neighbour *);
	int (*ndo_fdb_add)(struct ndmsg *, struct nlattr **, struct net_device *, const unsigned char *, u16, u16, struct netlink_ext_ack *);
	int (*ndo_fdb_del)(struct ndmsg *, struct nlattr **, struct net_device *, const unsigned char *, u16);
	int (*ndo_fdb_dump)(struct sk_buff *, struct netlink_callback *, struct net_device *, struct net_device *, int *);
	int (*ndo_fdb_get)(struct sk_buff *, struct nlattr **, struct net_device *, const unsigned char *, u16, u32, u32, struct netlink_ext_ack *);
	int (*ndo_bridge_setlink)(struct net_device *, struct nlmsghdr *, u16, struct netlink_ext_ack *);
	int (*ndo_bridge_getlink)(struct sk_buff *, u32, u32, struct net_device *, u32, int);
	int (*ndo_bridge_dellink)(struct net_device *, struct nlmsghdr *, u16);
	int (*ndo_change_carrier)(struct net_device *, bool);
	int (*ndo_get_phys_port_id)(struct net_device *, struct netdev_phys_item_id *);
	int (*ndo_get_port_parent_id)(struct net_device *, struct netdev_phys_item_id *);
	int (*ndo_get_phys_port_name)(struct net_device *, char *, size_t);
	void (*ndo_udp_tunnel_add)(struct net_device *, struct udp_tunnel_info *);
	void (*ndo_udp_tunnel_del)(struct net_device *, struct udp_tunnel_info *);
	void * (*ndo_dfwd_add_station)(struct net_device *, struct net_device *);
	void (*ndo_dfwd_del_station)(struct net_device *, void *);
	int (*ndo_set_tx_maxrate)(struct net_device *, int, u32);
	int (*ndo_get_iflink)(const struct net_device *);
	int (*ndo_change_proto_down)(struct net_device *, bool);
	int (*ndo_fill_metadata_dst)(struct net_device *, struct sk_buff *);
	void (*ndo_set_rx_headroom)(struct net_device *, int);
	int (*ndo_bpf)(struct net_device *, struct netdev_bpf *);
	int (*ndo_xdp_xmit)(struct net_device *, int, struct xdp_frame **, u32);
	int (*ndo_xsk_wakeup)(struct net_device *, u32, u32);
	struct devlink_port * (*ndo_get_devlink_port)(struct net_device *);
	int (*ndo_tunnel_ctl)(struct net_device *, struct ip_tunnel_parm *, int);
};

struct neigh_parms {
	possible_net_t net;
	struct net_device *dev;
	struct list_head list;
	int (*neigh_setup)(struct neighbour *);
	struct neigh_table *tbl;
	void *sysctl_table;
	int dead;
	refcount_t refcnt;
	struct callback_head callback_head;
	int reachable_time;
	int data[13];
	long unsigned int data_state[1];
};

struct pcpu_lstats {
	u64_stats_t packets;
	u64_stats_t bytes;
	struct u64_stats_sync syncp;
};

struct pcpu_sw_netstats {
	u64 rx_packets;
	u64 rx_bytes;
	u64 tx_packets;
	u64 tx_bytes;
	struct u64_stats_sync syncp;
};

struct nd_opt_hdr;

struct ndisc_options;

struct prefix_info;

struct ndisc_ops {
	int (*is_useropt)(u8);
	int (*parse_options)(const struct net_device *, struct nd_opt_hdr *, struct ndisc_options *);
	void (*update)(const struct net_device *, struct neighbour *, u32, u8, const struct ndisc_options *);
	int (*opt_addr_space)(const struct net_device *, u8, struct neighbour *, u8 *, u8 **);
	void (*fill_addr_option)(const struct net_device *, struct sk_buff *, u8, const u8 *);
	void (*prefix_rcv_add_addr)(struct net *, struct net_device *, const struct prefix_info *, struct inet6_dev *, struct in6_addr *, int, u32, bool, bool, __u32, u32, bool);
};

struct ipv6_devstat {
	struct proc_dir_entry *proc_dir_entry;
	struct ipstats_mib *ipv6;
	struct icmpv6_mib_device *icmpv6dev;
	struct icmpv6msg_mib_device *icmpv6msgdev;
};

struct ifmcaddr6;

struct ifacaddr6;

struct inet6_dev {
	struct net_device *dev;
	struct list_head addr_list;
	struct ifmcaddr6 *mc_list;
	struct ifmcaddr6 *mc_tomb;
	spinlock_t mc_lock;
	unsigned char mc_qrv;
	unsigned char mc_gq_running;
	unsigned char mc_ifc_count;
	unsigned char mc_dad_count;
	long unsigned int mc_v1_seen;
	long unsigned int mc_qi;
	long unsigned int mc_qri;
	long unsigned int mc_maxdelay;
	struct timer_list mc_gq_timer;
	struct timer_list mc_ifc_timer;
	struct timer_list mc_dad_timer;
	struct ifacaddr6 *ac_list;
	rwlock_t lock;
	refcount_t refcnt;
	__u32 if_flags;
	int dead;
	u32 desync_factor;
	struct list_head tempaddr_list;
	struct in6_addr token;
	struct neigh_parms *nd_parms;
	struct ipv6_devconf cnf;
	struct ipv6_devstat stats;
	struct timer_list rs_timer;
	__s32 rs_interval;
	__u8 rs_probes;
	long unsigned int tstamp;
	struct callback_head rcu;
};

struct tcf_proto;

struct tcf_block;

struct mini_Qdisc {
	struct tcf_proto *filter_list;
	struct tcf_block *block;
	struct gnet_stats_basic_cpu *cpu_bstats;
	struct gnet_stats_queue *cpu_qstats;
	struct callback_head rcu;
};

struct rtnl_link_ops {
	struct list_head list;
	const char *kind;
	size_t priv_size;
	void (*setup)(struct net_device *);
	unsigned int maxtype;
	const struct nla_policy *policy;
	int (*validate)(struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	int (*newlink)(struct net *, struct net_device *, struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	int (*changelink)(struct net_device *, struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	void (*dellink)(struct net_device *, struct list_head *);
	size_t (*get_size)(const struct net_device *);
	int (*fill_info)(struct sk_buff *, const struct net_device *);
	size_t (*get_xstats_size)(const struct net_device *);
	int (*fill_xstats)(struct sk_buff *, const struct net_device *);
	unsigned int (*get_num_tx_queues)();
	unsigned int (*get_num_rx_queues)();
	unsigned int slave_maxtype;
	const struct nla_policy *slave_policy;
	int (*slave_changelink)(struct net_device *, struct net_device *, struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	size_t (*get_slave_size)(const struct net_device *, const struct net_device *);
	int (*fill_slave_info)(struct sk_buff *, const struct net_device *, const struct net_device *);
	struct net * (*get_link_net)(const struct net_device *);
	size_t (*get_linkxstats_size)(const struct net_device *, int);
	int (*fill_linkxstats)(struct sk_buff *, const struct net_device *, int *, int);
};

struct sd_flow_limit {
	u64 count;
	unsigned int num_buckets;
	unsigned int history_head;
	u16 history[128];
	u8 buckets[0];
};

struct softnet_data {
	struct list_head poll_list;
	struct sk_buff_head process_queue;
	unsigned int processed;
	unsigned int time_squeeze;
	unsigned int received_rps;
	struct softnet_data *rps_ipi_list;
	struct sd_flow_limit *flow_limit;
	struct Qdisc *output_queue;
	struct Qdisc **output_queue_tailp;
	struct sk_buff *completion_queue;
	struct {
		u16 recursion;
		u8 more;
	} xmit;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	unsigned int input_queue_head;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	call_single_data_t csd;
	struct softnet_data *rps_ipi_next;
	unsigned int cpu;
	unsigned int input_queue_tail;
	unsigned int dropped;
	struct sk_buff_head input_pkt_queue;
	struct napi_struct backlog;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum {
	RTAX_UNSPEC = 0,
	RTAX_LOCK = 1,
	RTAX_MTU = 2,
	RTAX_WINDOW = 3,
	RTAX_RTT = 4,
	RTAX_RTTVAR = 5,
	RTAX_SSTHRESH = 6,
	RTAX_CWND = 7,
	RTAX_ADVMSS = 8,
	RTAX_REORDERING = 9,
	RTAX_HOPLIMIT = 10,
	RTAX_INITCWND = 11,
	RTAX_FEATURES = 12,
	RTAX_RTO_MIN = 13,
	RTAX_INITRWND = 14,
	RTAX_QUICKACK = 15,
	RTAX_CC_ALGO = 16,
	RTAX_FASTOPEN_NO_COOKIE = 17,
	__RTAX_MAX = 18,
};

struct tcmsg {
	unsigned char tcm_family;
	unsigned char tcm__pad1;
	short unsigned int tcm__pad2;
	int tcm_ifindex;
	__u32 tcm_handle;
	__u32 tcm_parent;
	__u32 tcm_info;
};

struct gnet_stats_basic_cpu {
	struct gnet_stats_basic_packed bstats;
	struct u64_stats_sync syncp;
};

struct gnet_dump {
	spinlock_t *lock;
	struct sk_buff *skb;
	struct nlattr *tail;
	int compat_tc_stats;
	int compat_xstats;
	int padattr;
	void *xstats;
	int xstats_len;
	struct tc_stats tc_stats;
};

struct netlink_range_validation {
	u64 min;
	u64 max;
};

struct netlink_range_validation_signed {
	s64 min;
	s64 max;
};

struct nla_policy {
	u8 type;
	u8 validation_type;
	u16 len;
	union {
		const u32 bitfield32_valid;
		const char *reject_message;
		const struct nla_policy *nested_policy;
		struct netlink_range_validation *range;
		struct netlink_range_validation_signed *range_signed;
		struct {
			s16 min;
			s16 max;
		};
		int (*validate)(const struct nlattr *, struct netlink_ext_ack *);
		u16 strict_start_type;
	};
};

struct nl_info {
	struct nlmsghdr *nlh;
	struct net *nl_net;
	u32 portid;
	u8 skip_notify: 1;
	u8 skip_notify_kernel: 1;
};

enum flow_action_hw_stats_bit {
	FLOW_ACTION_HW_STATS_IMMEDIATE_BIT = 0,
	FLOW_ACTION_HW_STATS_DELAYED_BIT = 1,
	FLOW_ACTION_HW_STATS_DISABLED_BIT = 2,
	FLOW_ACTION_HW_STATS_NUM_BITS = 3,
};

struct flow_block {
	struct list_head cb_list;
};

typedef int flow_setup_cb_t(enum tc_setup_type, void *, void *);

struct qdisc_size_table {
	struct callback_head rcu;
	struct list_head list;
	struct tc_sizespec szopts;
	int refcnt;
	u16 data[0];
};

struct Qdisc_class_ops;

struct Qdisc_ops {
	struct Qdisc_ops *next;
	const struct Qdisc_class_ops *cl_ops;
	char id[16];
	int priv_size;
	unsigned int static_flags;
	int (*enqueue)(struct sk_buff *, struct Qdisc *, struct sk_buff **);
	struct sk_buff * (*dequeue)(struct Qdisc *);
	struct sk_buff * (*peek)(struct Qdisc *);
	int (*init)(struct Qdisc *, struct nlattr *, struct netlink_ext_ack *);
	void (*reset)(struct Qdisc *);
	void (*destroy)(struct Qdisc *);
	int (*change)(struct Qdisc *, struct nlattr *, struct netlink_ext_ack *);
	void (*attach)(struct Qdisc *);
	int (*change_tx_queue_len)(struct Qdisc *, unsigned int);
	int (*dump)(struct Qdisc *, struct sk_buff *);
	int (*dump_stats)(struct Qdisc *, struct gnet_dump *);
	void (*ingress_block_set)(struct Qdisc *, u32);
	void (*egress_block_set)(struct Qdisc *, u32);
	u32 (*ingress_block_get)(struct Qdisc *);
	u32 (*egress_block_get)(struct Qdisc *);
	struct module *owner;
};

struct qdisc_walker;

struct Qdisc_class_ops {
	unsigned int flags;
	struct netdev_queue * (*select_queue)(struct Qdisc *, struct tcmsg *);
	int (*graft)(struct Qdisc *, long unsigned int, struct Qdisc *, struct Qdisc **, struct netlink_ext_ack *);
	struct Qdisc * (*leaf)(struct Qdisc *, long unsigned int);
	void (*qlen_notify)(struct Qdisc *, long unsigned int);
	long unsigned int (*find)(struct Qdisc *, u32);
	int (*change)(struct Qdisc *, u32, u32, struct nlattr **, long unsigned int *, struct netlink_ext_ack *);
	int (*delete)(struct Qdisc *, long unsigned int);
	void (*walk)(struct Qdisc *, struct qdisc_walker *);
	struct tcf_block * (*tcf_block)(struct Qdisc *, long unsigned int, struct netlink_ext_ack *);
	long unsigned int (*bind_tcf)(struct Qdisc *, long unsigned int, u32);
	void (*unbind_tcf)(struct Qdisc *, long unsigned int);
	int (*dump)(struct Qdisc *, long unsigned int, struct sk_buff *, struct tcmsg *);
	int (*dump_stats)(struct Qdisc *, long unsigned int, struct gnet_dump *);
};

struct tcf_chain;

struct tcf_block {
	struct mutex lock;
	struct list_head chain_list;
	u32 index;
	u32 classid;
	refcount_t refcnt;
	struct net *net;
	struct Qdisc *q;
	struct rw_semaphore cb_lock;
	struct flow_block flow_block;
	struct list_head owner_list;
	bool keep_dst;
	atomic_t offloadcnt;
	unsigned int nooffloaddevcnt;
	unsigned int lockeddevcnt;
	struct {
		struct tcf_chain *chain;
		struct list_head filter_chain_list;
	} chain0;
	struct callback_head rcu;
	struct hlist_head proto_destroy_ht[128];
	struct mutex proto_destroy_lock;
};

struct tcf_result;

struct tcf_proto_ops;

struct tcf_proto {
	struct tcf_proto *next;
	void *root;
	int (*classify)(struct sk_buff *, const struct tcf_proto *, struct tcf_result *);
	__be16 protocol;
	u32 prio;
	void *data;
	const struct tcf_proto_ops *ops;
	struct tcf_chain *chain;
	spinlock_t lock;
	bool deleting;
	refcount_t refcnt;
	struct callback_head rcu;
	struct hlist_node destroy_ht_node;
};

struct tcf_result {
	union {
		struct {
			long unsigned int class;
			u32 classid;
		};
		const struct tcf_proto *goto_tp;
		struct {
			bool ingress;
			struct gnet_stats_queue *qstats;
		};
	};
};

struct tcf_walker;

struct tcf_proto_ops {
	struct list_head head;
	char kind[16];
	int (*classify)(struct sk_buff *, const struct tcf_proto *, struct tcf_result *);
	int (*init)(struct tcf_proto *);
	void (*destroy)(struct tcf_proto *, bool, struct netlink_ext_ack *);
	void * (*get)(struct tcf_proto *, u32);
	void (*put)(struct tcf_proto *, void *);
	int (*change)(struct net *, struct sk_buff *, struct tcf_proto *, long unsigned int, u32, struct nlattr **, void **, bool, bool, struct netlink_ext_ack *);
	int (*delete)(struct tcf_proto *, void *, bool *, bool, struct netlink_ext_ack *);
	bool (*delete_empty)(struct tcf_proto *);
	void (*walk)(struct tcf_proto *, struct tcf_walker *, bool);
	int (*reoffload)(struct tcf_proto *, bool, flow_setup_cb_t *, void *, struct netlink_ext_ack *);
	void (*hw_add)(struct tcf_proto *, void *);
	void (*hw_del)(struct tcf_proto *, void *);
	void (*bind_class)(void *, u32, long unsigned int, void *, long unsigned int);
	void * (*tmplt_create)(struct net *, struct tcf_chain *, struct nlattr **, struct netlink_ext_ack *);
	void (*tmplt_destroy)(void *);
	int (*dump)(struct net *, struct tcf_proto *, void *, struct sk_buff *, struct tcmsg *, bool);
	int (*terse_dump)(struct net *, struct tcf_proto *, void *, struct sk_buff *, struct tcmsg *, bool);
	int (*tmplt_dump)(struct sk_buff *, struct net *, void *);
	struct module *owner;
	int flags;
};

struct tcf_chain {
	struct mutex filter_chain_lock;
	struct tcf_proto *filter_chain;
	struct list_head list;
	struct tcf_block *block;
	u32 index;
	unsigned int refcnt;
	unsigned int action_refcnt;
	bool explicitly_created;
	bool flushing;
	const struct tcf_proto_ops *tmplt_ops;
	void *tmplt_priv;
	struct callback_head rcu;
};

struct sock_fprog_kern {
	u16 len;
	struct sock_filter *filter;
};

struct sk_filter {
	refcount_t refcnt;
	struct callback_head rcu;
	struct bpf_prog *prog;
};

struct bpf_redirect_info {
	u32 flags;
	u32 tgt_index;
	void *tgt_value;
	struct bpf_map *map;
	u32 kern_flags;
};

enum {
	NEIGH_VAR_MCAST_PROBES = 0,
	NEIGH_VAR_UCAST_PROBES = 1,
	NEIGH_VAR_APP_PROBES = 2,
	NEIGH_VAR_MCAST_REPROBES = 3,
	NEIGH_VAR_RETRANS_TIME = 4,
	NEIGH_VAR_BASE_REACHABLE_TIME = 5,
	NEIGH_VAR_DELAY_PROBE_TIME = 6,
	NEIGH_VAR_GC_STALETIME = 7,
	NEIGH_VAR_QUEUE_LEN_BYTES = 8,
	NEIGH_VAR_PROXY_QLEN = 9,
	NEIGH_VAR_ANYCAST_DELAY = 10,
	NEIGH_VAR_PROXY_DELAY = 11,
	NEIGH_VAR_LOCKTIME = 12,
	NEIGH_VAR_QUEUE_LEN = 13,
	NEIGH_VAR_RETRANS_TIME_MS = 14,
	NEIGH_VAR_BASE_REACHABLE_TIME_MS = 15,
	NEIGH_VAR_GC_INTERVAL = 16,
	NEIGH_VAR_GC_THRESH1 = 17,
	NEIGH_VAR_GC_THRESH2 = 18,
	NEIGH_VAR_GC_THRESH3 = 19,
	NEIGH_VAR_MAX = 20,
};

struct pneigh_entry;

struct neigh_statistics;

struct neigh_hash_table;

struct neigh_table {
	int family;
	unsigned int entry_size;
	unsigned int key_len;
	__be16 protocol;
	__u32 (*hash)(const void *, const struct net_device *, __u32 *);
	bool (*key_eq)(const struct neighbour *, const void *);
	int (*constructor)(struct neighbour *);
	int (*pconstructor)(struct pneigh_entry *);
	void (*pdestructor)(struct pneigh_entry *);
	void (*proxy_redo)(struct sk_buff *);
	bool (*allow_add)(const struct net_device *, struct netlink_ext_ack *);
	char *id;
	struct neigh_parms parms;
	struct list_head parms_list;
	int gc_interval;
	int gc_thresh1;
	int gc_thresh2;
	int gc_thresh3;
	long unsigned int last_flush;
	struct delayed_work gc_work;
	struct timer_list proxy_timer;
	struct sk_buff_head proxy_queue;
	atomic_t entries;
	atomic_t gc_entries;
	struct list_head gc_list;
	rwlock_t lock;
	long unsigned int last_rand;
	struct neigh_statistics *stats;
	struct neigh_hash_table *nht;
	struct pneigh_entry **phash_buckets;
};

struct neigh_statistics {
	long unsigned int allocs;
	long unsigned int destroys;
	long unsigned int hash_grows;
	long unsigned int res_failed;
	long unsigned int lookups;
	long unsigned int hits;
	long unsigned int rcv_probes_mcast;
	long unsigned int rcv_probes_ucast;
	long unsigned int periodic_gc_runs;
	long unsigned int forced_gc_runs;
	long unsigned int unres_discards;
	long unsigned int table_fulls;
};

struct neigh_ops {
	int family;
	void (*solicit)(struct neighbour *, struct sk_buff *);
	void (*error_report)(struct neighbour *, struct sk_buff *);
	int (*output)(struct neighbour *, struct sk_buff *);
	int (*connected_output)(struct neighbour *, struct sk_buff *);
};

struct pneigh_entry {
	struct pneigh_entry *next;
	possible_net_t net;
	struct net_device *dev;
	u8 flags;
	u8 protocol;
	u8 key[0];
};

struct neigh_hash_table {
	struct neighbour **hash_buckets;
	unsigned int hash_shift;
	__u32 hash_rnd[4];
	struct callback_head rcu;
};

struct dst_metrics {
	u32 metrics[17];
	refcount_t refcnt;
};

enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT = 2,
	TCP_SYN_RECV = 3,
	TCP_FIN_WAIT1 = 4,
	TCP_FIN_WAIT2 = 5,
	TCP_TIME_WAIT = 6,
	TCP_CLOSE = 7,
	TCP_CLOSE_WAIT = 8,
	TCP_LAST_ACK = 9,
	TCP_LISTEN = 10,
	TCP_CLOSING = 11,
	TCP_NEW_SYN_RECV = 12,
	TCP_MAX_STATES = 13,
};

struct fib_rule_hdr {
	__u8 family;
	__u8 dst_len;
	__u8 src_len;
	__u8 tos;
	__u8 table;
	__u8 res1;
	__u8 res2;
	__u8 action;
	__u32 flags;
};

struct fib_rule_port_range {
	__u16 start;
	__u16 end;
};

struct fib_kuid_range {
	kuid_t start;
	kuid_t end;
};

struct fib_rule {
	struct list_head list;
	int iifindex;
	int oifindex;
	u32 mark;
	u32 mark_mask;
	u32 flags;
	u32 table;
	u8 action;
	u8 l3mdev;
	u8 proto;
	u8 ip_proto;
	u32 target;
	__be64 tun_id;
	struct fib_rule *ctarget;
	struct net *fr_net;
	refcount_t refcnt;
	u32 pref;
	int suppress_ifgroup;
	int suppress_prefixlen;
	char iifname[16];
	char oifname[16];
	struct fib_kuid_range uid_range;
	struct fib_rule_port_range sport_range;
	struct fib_rule_port_range dport_range;
	struct callback_head rcu;
};

struct fib_lookup_arg {
	void *lookup_ptr;
	const void *lookup_data;
	void *result;
	struct fib_rule *rule;
	u32 table;
	int flags;
};

struct smc_hashinfo;

struct request_sock_ops;

struct timewait_sock_ops;

struct udp_table;

struct raw_hashinfo;

struct proto {
	void (*close)(struct sock *, long int);
	int (*pre_connect)(struct sock *, struct sockaddr *, int);
	int (*connect)(struct sock *, struct sockaddr *, int);
	int (*disconnect)(struct sock *, int);
	struct sock * (*accept)(struct sock *, int, int *, bool);
	int (*ioctl)(struct sock *, int, long unsigned int);
	int (*init)(struct sock *);
	void (*destroy)(struct sock *);
	void (*shutdown)(struct sock *, int);
	int (*setsockopt)(struct sock *, int, int, char *, unsigned int);
	int (*getsockopt)(struct sock *, int, int, char *, int *);
	void (*keepalive)(struct sock *, int);
	int (*compat_setsockopt)(struct sock *, int, int, char *, unsigned int);
	int (*compat_getsockopt)(struct sock *, int, int, char *, int *);
	int (*compat_ioctl)(struct sock *, unsigned int, long unsigned int);
	int (*sendmsg)(struct sock *, struct msghdr *, size_t);
	int (*recvmsg)(struct sock *, struct msghdr *, size_t, int, int, int *);
	int (*sendpage)(struct sock *, struct page *, int, size_t, int);
	int (*bind)(struct sock *, struct sockaddr *, int);
	int (*bind_add)(struct sock *, struct sockaddr *, int);
	int (*backlog_rcv)(struct sock *, struct sk_buff *);
	void (*release_cb)(struct sock *);
	int (*hash)(struct sock *);
	void (*unhash)(struct sock *);
	void (*rehash)(struct sock *);
	int (*get_port)(struct sock *, short unsigned int);
	unsigned int inuse_idx;
	bool (*stream_memory_free)(const struct sock *, int);
	bool (*stream_memory_read)(const struct sock *);
	void (*enter_memory_pressure)(struct sock *);
	void (*leave_memory_pressure)(struct sock *);
	atomic_long_t *memory_allocated;
	struct percpu_counter *sockets_allocated;
	long unsigned int *memory_pressure;
	long int *sysctl_mem;
	int *sysctl_wmem;
	int *sysctl_rmem;
	u32 sysctl_wmem_offset;
	u32 sysctl_rmem_offset;
	int max_header;
	bool no_autobind;
	struct kmem_cache *slab;
	unsigned int obj_size;
	slab_flags_t slab_flags;
	unsigned int useroffset;
	unsigned int usersize;
	struct percpu_counter *orphan_count;
	struct request_sock_ops *rsk_prot;
	struct timewait_sock_ops *twsk_prot;
	union {
		struct inet_hashinfo *hashinfo;
		struct udp_table *udp_table;
		struct raw_hashinfo *raw_hash;
		struct smc_hashinfo *smc_hash;
	} h;
	struct module *owner;
	char name[32];
	struct list_head node;
	int (*diag_destroy)(struct sock *, int);
};

struct request_sock;

struct request_sock_ops {
	int family;
	unsigned int obj_size;
	struct kmem_cache *slab;
	char *slab_name;
	int (*rtx_syn_ack)(const struct sock *, struct request_sock *);
	void (*send_ack)(const struct sock *, struct sk_buff *, struct request_sock *);
	void (*send_reset)(const struct sock *, struct sk_buff *);
	void (*destructor)(struct request_sock *);
	void (*syn_ack_timeout)(const struct request_sock *);
};

struct timewait_sock_ops {
	struct kmem_cache *twsk_slab;
	char *twsk_slab_name;
	unsigned int twsk_obj_size;
	int (*twsk_unique)(struct sock *, struct sock *, void *);
	void (*twsk_destructor)(struct sock *);
};

struct request_sock {
	struct sock_common __req_common;
	struct request_sock *dl_next;
	u16 mss;
	u8 num_retrans;
	u8 cookie_ts: 1;
	u8 num_timeout: 7;
	u32 ts_recent;
	struct timer_list rsk_timer;
	const struct request_sock_ops *rsk_ops;
	struct sock *sk;
	u32 *saved_syn;
	u32 secid;
	u32 peer_secid;
};

enum tsq_enum {
	TSQ_THROTTLED = 0,
	TSQ_QUEUED = 1,
	TCP_TSQ_DEFERRED = 2,
	TCP_WRITE_TIMER_DEFERRED = 3,
	TCP_DELACK_TIMER_DEFERRED = 4,
	TCP_MTU_REDUCED_DEFERRED = 5,
};

struct static_key_false_deferred {
	struct static_key_false key;
	long unsigned int timeout;
	struct delayed_work work;
};

struct ip6_sf_list {
	struct ip6_sf_list *sf_next;
	struct in6_addr sf_addr;
	long unsigned int sf_count[2];
	unsigned char sf_gsresp;
	unsigned char sf_oldin;
	unsigned char sf_crcount;
};

struct ifmcaddr6 {
	struct in6_addr mca_addr;
	struct inet6_dev *idev;
	struct ifmcaddr6 *next;
	struct ip6_sf_list *mca_sources;
	struct ip6_sf_list *mca_tomb;
	unsigned int mca_sfmode;
	unsigned char mca_crcount;
	long unsigned int mca_sfcount[2];
	struct timer_list mca_timer;
	unsigned int mca_flags;
	int mca_users;
	refcount_t mca_refcnt;
	spinlock_t mca_lock;
	long unsigned int mca_cstamp;
	long unsigned int mca_tstamp;
};

struct ifacaddr6 {
	struct in6_addr aca_addr;
	struct fib6_info *aca_rt;
	struct ifacaddr6 *aca_next;
	struct hlist_node aca_addr_lst;
	int aca_users;
	refcount_t aca_refcnt;
	long unsigned int aca_cstamp;
	long unsigned int aca_tstamp;
	struct callback_head rcu;
};

struct fib6_result;

struct fib6_nh;

struct fib6_config;

struct ipv6_stub {
	int (*ipv6_sock_mc_join)(struct sock *, int, const struct in6_addr *);
	int (*ipv6_sock_mc_drop)(struct sock *, int, const struct in6_addr *);
	struct dst_entry * (*ipv6_dst_lookup_flow)(struct net *, const struct sock *, struct flowi6 *, const struct in6_addr *);
	int (*ipv6_route_input)(struct sk_buff *);
	struct fib6_table * (*fib6_get_table)(struct net *, u32);
	int (*fib6_lookup)(struct net *, int, struct flowi6 *, struct fib6_result *, int);
	int (*fib6_table_lookup)(struct net *, struct fib6_table *, int, struct flowi6 *, struct fib6_result *, int);
	void (*fib6_select_path)(const struct net *, struct fib6_result *, struct flowi6 *, int, bool, const struct sk_buff *, int);
	u32 (*ip6_mtu_from_fib6)(const struct fib6_result *, const struct in6_addr *, const struct in6_addr *);
	int (*fib6_nh_init)(struct net *, struct fib6_nh *, struct fib6_config *, gfp_t, struct netlink_ext_ack *);
	void (*fib6_nh_release)(struct fib6_nh *);
	void (*fib6_update_sernum)(struct net *, struct fib6_info *);
	int (*ip6_del_rt)(struct net *, struct fib6_info *, bool);
	void (*fib6_rt_update)(struct net *, struct fib6_info *, struct nl_info *);
	void (*udpv6_encap_enable)();
	void (*ndisc_send_na)(struct net_device *, const struct in6_addr *, const struct in6_addr *, bool, bool, bool, bool);
	void (*xfrm6_local_rxpmtu)(struct sk_buff *, u32);
	int (*xfrm6_udp_encap_rcv)(struct sock *, struct sk_buff *);
	int (*xfrm6_rcv_encap)(struct sk_buff *, int, __be32, int);
	struct neigh_table *nd_tbl;
};

struct fib6_result {
	struct fib6_nh *nh;
	struct fib6_info *f6i;
	u32 fib6_flags;
	u8 fib6_type;
	struct rt6_info *rt6;
};

struct ipv6_bpf_stub {
	int (*inet6_bind)(struct sock *, struct sockaddr *, int, u32);
	struct sock * (*udp6_lib_lookup)(struct net *, const struct in6_addr *, __be16, const struct in6_addr *, __be16, int, int, struct udp_table *, struct sk_buff *);
};

enum {
	__ND_OPT_PREFIX_INFO_END = 0,
	ND_OPT_SOURCE_LL_ADDR = 1,
	ND_OPT_TARGET_LL_ADDR = 2,
	ND_OPT_PREFIX_INFO = 3,
	ND_OPT_REDIRECT_HDR = 4,
	ND_OPT_MTU = 5,
	ND_OPT_NONCE = 14,
	__ND_OPT_ARRAY_MAX = 15,
	ND_OPT_ROUTE_INFO = 24,
	ND_OPT_RDNSS = 25,
	ND_OPT_DNSSL = 31,
	ND_OPT_6CO = 34,
	ND_OPT_CAPTIVE_PORTAL = 37,
	ND_OPT_PREF64 = 38,
	__ND_OPT_MAX = 39,
};

struct nd_opt_hdr {
	__u8 nd_opt_type;
	__u8 nd_opt_len;
};

struct ndisc_options {
	struct nd_opt_hdr *nd_opt_array[15];
	struct nd_opt_hdr *nd_useropts;
	struct nd_opt_hdr *nd_useropts_end;
};

struct prefix_info {
	__u8 type;
	__u8 length;
	__u8 prefix_len;
	__u8 reserved: 6;
	__u8 autoconf: 1;
	__u8 onlink: 1;
	__be32 valid;
	__be32 prefered;
	__be32 reserved2;
	struct in6_addr prefix;
};

struct ip6_ra_chain {
	struct ip6_ra_chain *next;
	struct sock *sk;
	int sel;
	void (*destructor)(struct sock *);
};

struct rpc_xprt_iter_ops {
	void (*xpi_rewind)(struct rpc_xprt_iter *);
	struct rpc_xprt * (*xpi_xprt)(struct rpc_xprt_iter *);
	struct rpc_xprt * (*xpi_next)(struct rpc_xprt_iter *);
};

struct rpc_version {
	u32 number;
	unsigned int nrprocs;
	const struct rpc_procinfo *procs;
	unsigned int *counts;
};

struct nfs_fh {
	short unsigned int size;
	unsigned char data[128];
};

enum nfs3_stable_how {
	NFS_UNSTABLE = 0,
	NFS_DATA_SYNC = 1,
	NFS_FILE_SYNC = 2,
	NFS_INVALID_STABLE_HOW = 4294967295,
};

struct nfs4_label {
	uint32_t lfs;
	uint32_t pi;
	u32 len;
	char *label;
};

typedef struct {
	char data[8];
} nfs4_verifier;

struct nfs4_stateid_struct {
	union {
		char data[16];
		struct {
			__be32 seqid;
			char other[12];
		};
	};
	enum {
		NFS4_INVALID_STATEID_TYPE = 0,
		NFS4_SPECIAL_STATEID_TYPE = 1,
		NFS4_OPEN_STATEID_TYPE = 2,
		NFS4_LOCK_STATEID_TYPE = 3,
		NFS4_DELEGATION_STATEID_TYPE = 4,
		NFS4_LAYOUT_STATEID_TYPE = 5,
		NFS4_PNFS_DS_STATEID_TYPE = 6,
		NFS4_REVOKED_STATEID_TYPE = 7,
	} type;
};

typedef struct nfs4_stateid_struct nfs4_stateid;

enum nfs_opnum4 {
	OP_ACCESS = 3,
	OP_CLOSE = 4,
	OP_COMMIT = 5,
	OP_CREATE = 6,
	OP_DELEGPURGE = 7,
	OP_DELEGRETURN = 8,
	OP_GETATTR = 9,
	OP_GETFH = 10,
	OP_LINK = 11,
	OP_LOCK = 12,
	OP_LOCKT = 13,
	OP_LOCKU = 14,
	OP_LOOKUP = 15,
	OP_LOOKUPP = 16,
	OP_NVERIFY = 17,
	OP_OPEN = 18,
	OP_OPENATTR = 19,
	OP_OPEN_CONFIRM = 20,
	OP_OPEN_DOWNGRADE = 21,
	OP_PUTFH = 22,
	OP_PUTPUBFH = 23,
	OP_PUTROOTFH = 24,
	OP_READ = 25,
	OP_READDIR = 26,
	OP_READLINK = 27,
	OP_REMOVE = 28,
	OP_RENAME = 29,
	OP_RENEW = 30,
	OP_RESTOREFH = 31,
	OP_SAVEFH = 32,
	OP_SECINFO = 33,
	OP_SETATTR = 34,
	OP_SETCLIENTID = 35,
	OP_SETCLIENTID_CONFIRM = 36,
	OP_VERIFY = 37,
	OP_WRITE = 38,
	OP_RELEASE_LOCKOWNER = 39,
	OP_BACKCHANNEL_CTL = 40,
	OP_BIND_CONN_TO_SESSION = 41,
	OP_EXCHANGE_ID = 42,
	OP_CREATE_SESSION = 43,
	OP_DESTROY_SESSION = 44,
	OP_FREE_STATEID = 45,
	OP_GET_DIR_DELEGATION = 46,
	OP_GETDEVICEINFO = 47,
	OP_GETDEVICELIST = 48,
	OP_LAYOUTCOMMIT = 49,
	OP_LAYOUTGET = 50,
	OP_LAYOUTRETURN = 51,
	OP_SECINFO_NO_NAME = 52,
	OP_SEQUENCE = 53,
	OP_SET_SSV = 54,
	OP_TEST_STATEID = 55,
	OP_WANT_DELEGATION = 56,
	OP_DESTROY_CLIENTID = 57,
	OP_RECLAIM_COMPLETE = 58,
	OP_ALLOCATE = 59,
	OP_COPY = 60,
	OP_COPY_NOTIFY = 61,
	OP_DEALLOCATE = 62,
	OP_IO_ADVISE = 63,
	OP_LAYOUTERROR = 64,
	OP_LAYOUTSTATS = 65,
	OP_OFFLOAD_CANCEL = 66,
	OP_OFFLOAD_STATUS = 67,
	OP_READ_PLUS = 68,
	OP_SEEK = 69,
	OP_WRITE_SAME = 70,
	OP_CLONE = 71,
	OP_ILLEGAL = 10044,
};

struct nfs4_string {
	unsigned int len;
	char *data;
};

struct nfs_fsid {
	uint64_t major;
	uint64_t minor;
};

struct nfs4_threshold {
	__u32 bm;
	__u32 l_type;
	__u64 rd_sz;
	__u64 wr_sz;
	__u64 rd_io_sz;
	__u64 wr_io_sz;
};

struct nfs_fattr {
	unsigned int valid;
	umode_t mode;
	__u32 nlink;
	kuid_t uid;
	kgid_t gid;
	dev_t rdev;
	__u64 size;
	union {
		struct {
			__u32 blocksize;
			__u32 blocks;
		} nfs2;
		struct {
			__u64 used;
		} nfs3;
	} du;
	struct nfs_fsid fsid;
	__u64 fileid;
	__u64 mounted_on_fileid;
	struct timespec64 atime;
	struct timespec64 mtime;
	struct timespec64 ctime;
	__u64 change_attr;
	__u64 pre_change_attr;
	__u64 pre_size;
	struct timespec64 pre_mtime;
	struct timespec64 pre_ctime;
	long unsigned int time_start;
	long unsigned int gencount;
	struct nfs4_string *owner_name;
	struct nfs4_string *group_name;
	struct nfs4_threshold *mdsthreshold;
	struct nfs4_label *label;
};

struct nfs_fsinfo {
	struct nfs_fattr *fattr;
	__u32 rtmax;
	__u32 rtpref;
	__u32 rtmult;
	__u32 wtmax;
	__u32 wtpref;
	__u32 wtmult;
	__u32 dtpref;
	__u64 maxfilesize;
	struct timespec64 time_delta;
	__u32 lease_time;
	__u32 nlayouttypes;
	__u32 layouttype[8];
	__u32 blksize;
	__u32 clone_blksize;
};

struct nfs_fsstat {
	struct nfs_fattr *fattr;
	__u64 tbytes;
	__u64 fbytes;
	__u64 abytes;
	__u64 tfiles;
	__u64 ffiles;
	__u64 afiles;
};

struct nfs_pathconf {
	struct nfs_fattr *fattr;
	__u32 max_link;
	__u32 max_namelen;
};

struct nfs4_change_info {
	u32 atomic;
	u64 before;
	u64 after;
};

struct nfs4_slot;

struct nfs4_sequence_args {
	struct nfs4_slot *sa_slot;
	u8 sa_cache_this: 1;
	u8 sa_privileged: 1;
};

struct nfs4_sequence_res {
	struct nfs4_slot *sr_slot;
	long unsigned int sr_timestamp;
	int sr_status;
	u32 sr_status_flags;
	u32 sr_highest_slotid;
	u32 sr_target_highest_slotid;
};

struct nfs_open_context;

struct nfs_lock_context {
	refcount_t count;
	struct list_head list;
	struct nfs_open_context *open_context;
	fl_owner_t lockowner;
	atomic_t io_count;
	struct callback_head callback_head;
};

struct nfs4_state;

struct nfs_open_context {
	struct nfs_lock_context lock_context;
	fl_owner_t flock_owner;
	struct dentry *dentry;
	const struct cred *cred;
	struct rpc_cred *ll_cred;
	struct nfs4_state *state;
	fmode_t mode;
	long unsigned int flags;
	int error;
	struct list_head list;
	struct nfs4_threshold *mdsthreshold;
	struct callback_head callback_head;
};

struct nfs_auth_info {
	unsigned int flavor_len;
	rpc_authflavor_t flavors[12];
};

struct pnfs_layoutdriver_type;

struct nfs_client;

struct nlm_host;

struct nfs_iostats;

struct nfs_server {
	struct nfs_client *nfs_client;
	struct list_head client_link;
	struct list_head master_link;
	struct rpc_clnt *client;
	struct rpc_clnt *client_acl;
	struct nlm_host *nlm_host;
	struct nfs_iostats *io_stats;
	atomic_long_t writeback;
	int flags;
	unsigned int caps;
	unsigned int rsize;
	unsigned int rpages;
	unsigned int wsize;
	unsigned int wpages;
	unsigned int wtmult;
	unsigned int dtsize;
	short unsigned int port;
	unsigned int bsize;
	unsigned int acregmin;
	unsigned int acregmax;
	unsigned int acdirmin;
	unsigned int acdirmax;
	unsigned int namelen;
	unsigned int options;
	unsigned int clone_blksize;
	struct nfs_fsid fsid;
	__u64 maxfilesize;
	struct timespec64 time_delta;
	long unsigned int mount_time;
	struct super_block *super;
	dev_t s_dev;
	struct nfs_auth_info auth_info;
	u32 pnfs_blksize;
	u32 attr_bitmask[3];
	u32 attr_bitmask_nl[3];
	u32 exclcreat_bitmask[3];
	u32 cache_consistency_bitmask[3];
	u32 acl_bitmask;
	u32 fh_expire_type;
	struct pnfs_layoutdriver_type *pnfs_curr_ld;
	struct rpc_wait_queue roc_rpcwaitq;
	void *pnfs_ld_data;
	struct rb_root state_owners;
	struct ida openowner_id;
	struct ida lockowner_id;
	struct list_head state_owners_lru;
	struct list_head layouts;
	struct list_head delegations;
	struct list_head ss_copies;
	long unsigned int mig_gen;
	long unsigned int mig_status;
	void (*destroy)(struct nfs_server *);
	atomic_t active;
	struct __kernel_sockaddr_storage mountd_address;
	size_t mountd_addrlen;
	u32 mountd_version;
	short unsigned int mountd_port;
	short unsigned int mountd_protocol;
	struct rpc_wait_queue uoc_rpcwaitq;
	unsigned int read_hdrsize;
	const struct cred *cred;
};

struct nfs41_server_owner;

struct nfs41_server_scope;

struct nfs41_impl_id;

struct nfs_rpc_ops;

struct nfs_subversion;

struct idmap;

struct nfs4_minor_version_ops;

struct nfs4_slot_table;

struct nfs4_session;

struct nfs_client {
	refcount_t cl_count;
	atomic_t cl_mds_count;
	int cl_cons_state;
	long unsigned int cl_res_state;
	long unsigned int cl_flags;
	struct __kernel_sockaddr_storage cl_addr;
	size_t cl_addrlen;
	char *cl_hostname;
	char *cl_acceptor;
	struct list_head cl_share_link;
	struct list_head cl_superblocks;
	struct rpc_clnt *cl_rpcclient;
	const struct nfs_rpc_ops *rpc_ops;
	int cl_proto;
	struct nfs_subversion *cl_nfs_mod;
	u32 cl_minorversion;
	unsigned int cl_nconnect;
	const char *cl_principal;
	struct list_head cl_ds_clients;
	u64 cl_clientid;
	nfs4_verifier cl_confirm;
	long unsigned int cl_state;
	spinlock_t cl_lock;
	long unsigned int cl_lease_time;
	long unsigned int cl_last_renewal;
	struct delayed_work cl_renewd;
	struct rpc_wait_queue cl_rpcwaitq;
	struct idmap *cl_idmap;
	const char *cl_owner_id;
	u32 cl_cb_ident;
	const struct nfs4_minor_version_ops *cl_mvops;
	long unsigned int cl_mig_gen;
	struct nfs4_slot_table *cl_slot_tbl;
	u32 cl_seqid;
	u32 cl_exchange_flags;
	struct nfs4_session *cl_session;
	bool cl_preserve_clid;
	struct nfs41_server_owner *cl_serverowner;
	struct nfs41_server_scope *cl_serverscope;
	struct nfs41_impl_id *cl_implid;
	long unsigned int cl_sp4_flags;
	char cl_ipaddr[48];
	struct net *cl_net;
	struct list_head pending_cb_stateids;
};

struct nfs_write_verifier {
	char data[8];
};

struct nfs_writeverf {
	struct nfs_write_verifier verifier;
	enum nfs3_stable_how committed;
};

struct nfs_pgio_args {
	struct nfs4_sequence_args seq_args;
	struct nfs_fh *fh;
	struct nfs_open_context *context;
	struct nfs_lock_context *lock_context;
	nfs4_stateid stateid;
	__u64 offset;
	__u32 count;
	unsigned int pgbase;
	struct page **pages;
	union {
		unsigned int replen;
		struct {
			const u32 *bitmask;
			enum nfs3_stable_how stable;
		};
	};
};

struct nfs_pgio_res {
	struct nfs4_sequence_res seq_res;
	struct nfs_fattr *fattr;
	__u32 count;
	__u32 op_status;
	union {
		struct {
			unsigned int replen;
			int eof;
		};
		struct {
			struct nfs_writeverf *verf;
			const struct nfs_server *server;
		};
	};
};

struct nfs_commitargs {
	struct nfs4_sequence_args seq_args;
	struct nfs_fh *fh;
	__u64 offset;
	__u32 count;
	const u32 *bitmask;
};

struct nfs_commitres {
	struct nfs4_sequence_res seq_res;
	__u32 op_status;
	struct nfs_fattr *fattr;
	struct nfs_writeverf *verf;
	const struct nfs_server *server;
};

struct nfs_removeargs {
	struct nfs4_sequence_args seq_args;
	const struct nfs_fh *fh;
	struct qstr name;
};

struct nfs_removeres {
	struct nfs4_sequence_res seq_res;
	struct nfs_server *server;
	struct nfs_fattr *dir_attr;
	struct nfs4_change_info cinfo;
};

struct nfs_renameargs {
	struct nfs4_sequence_args seq_args;
	const struct nfs_fh *old_dir;
	const struct nfs_fh *new_dir;
	const struct qstr *old_name;
	const struct qstr *new_name;
};

struct nfs_renameres {
	struct nfs4_sequence_res seq_res;
	struct nfs_server *server;
	struct nfs4_change_info old_cinfo;
	struct nfs_fattr *old_fattr;
	struct nfs4_change_info new_cinfo;
	struct nfs_fattr *new_fattr;
};

struct nfs_entry {
	__u64 ino;
	__u64 cookie;
	__u64 prev_cookie;
	const char *name;
	unsigned int len;
	int eof;
	struct nfs_fh *fh;
	struct nfs_fattr *fattr;
	struct nfs4_label *label;
	unsigned char d_type;
	struct nfs_server *server;
};

struct pnfs_ds_commit_info {};

struct nfs_page_array {
	struct page **pagevec;
	unsigned int npages;
	struct page *page_array[8];
};

struct nfs_page;

struct pnfs_layout_segment;

struct nfs_pgio_completion_ops;

struct nfs_rw_ops;

struct nfs_io_completion;

struct nfs_direct_req;

struct nfs_pgio_header {
	struct inode *inode;
	const struct cred *cred;
	struct list_head pages;
	struct nfs_page *req;
	struct nfs_writeverf verf;
	fmode_t rw_mode;
	struct pnfs_layout_segment *lseg;
	loff_t io_start;
	const struct rpc_call_ops *mds_ops;
	void (*release)(struct nfs_pgio_header *);
	const struct nfs_pgio_completion_ops *completion_ops;
	const struct nfs_rw_ops *rw_ops;
	struct nfs_io_completion *io_completion;
	struct nfs_direct_req *dreq;
	int pnfs_error;
	int error;
	unsigned int good_bytes;
	long unsigned int flags;
	struct rpc_task task;
	struct nfs_fattr fattr;
	struct nfs_pgio_args args;
	struct nfs_pgio_res res;
	long unsigned int timestamp;
	int (*pgio_done_cb)(struct rpc_task *, struct nfs_pgio_header *);
	__u64 mds_offset;
	struct nfs_page_array page_array;
	struct nfs_client *ds_clp;
	int ds_commit_idx;
	int pgio_mirror_idx;
};

struct nfs_pgio_completion_ops {
	void (*error_cleanup)(struct list_head *, int);
	void (*init_hdr)(struct nfs_pgio_header *);
	void (*completion)(struct nfs_pgio_header *);
	void (*reschedule_io)(struct nfs_pgio_header *);
};

struct rpc_task_setup;

struct nfs_rw_ops {
	struct nfs_pgio_header * (*rw_alloc_header)();
	void (*rw_free_header)(struct nfs_pgio_header *);
	int (*rw_done)(struct rpc_task *, struct nfs_pgio_header *, struct inode *);
	void (*rw_result)(struct rpc_task *, struct nfs_pgio_header *);
	void (*rw_initiate)(struct nfs_pgio_header *, struct rpc_message *, const struct nfs_rpc_ops *, struct rpc_task_setup *, int);
};

struct nfs_mds_commit_info {
	atomic_t rpcs_out;
	atomic_long_t ncommit;
	struct list_head list;
};

struct nfs_commit_data;

struct nfs_commit_info;

struct nfs_commit_completion_ops {
	void (*completion)(struct nfs_commit_data *);
	void (*resched_write)(struct nfs_commit_info *, struct nfs_page *);
};

struct nfs_commit_data {
	struct rpc_task task;
	struct inode *inode;
	const struct cred *cred;
	struct nfs_fattr fattr;
	struct nfs_writeverf verf;
	struct list_head pages;
	struct list_head list;
	struct nfs_direct_req *dreq;
	struct nfs_commitargs args;
	struct nfs_commitres res;
	struct nfs_open_context *context;
	struct pnfs_layout_segment *lseg;
	struct nfs_client *ds_clp;
	int ds_commit_index;
	loff_t lwb;
	const struct rpc_call_ops *mds_ops;
	const struct nfs_commit_completion_ops *completion_ops;
	int (*commit_done_cb)(struct rpc_task *, struct nfs_commit_data *);
	long unsigned int flags;
};

struct nfs_commit_info {
	struct inode *inode;
	struct nfs_mds_commit_info *mds;
	struct pnfs_ds_commit_info *ds;
	struct nfs_direct_req *dreq;
	const struct nfs_commit_completion_ops *completion_ops;
};

struct nfs_unlinkdata {
	struct nfs_removeargs args;
	struct nfs_removeres res;
	struct dentry *dentry;
	wait_queue_head_t wq;
	const struct cred *cred;
	struct nfs_fattr dir_attr;
	long int timeout;
};

struct nfs_renamedata {
	struct nfs_renameargs args;
	struct nfs_renameres res;
	const struct cred *cred;
	struct inode *old_dir;
	struct dentry *old_dentry;
	struct nfs_fattr old_fattr;
	struct inode *new_dir;
	struct dentry *new_dentry;
	struct nfs_fattr new_fattr;
	void (*complete)(struct rpc_task *, struct nfs_renamedata *);
	long int timeout;
	bool cancelled;
};

struct nlmclnt_operations;

struct nfs_access_entry;

struct nfs_client_initdata;

struct nfs_rpc_ops {
	u32 version;
	const struct dentry_operations *dentry_ops;
	const struct inode_operations *dir_inode_ops;
	const struct inode_operations *file_inode_ops;
	const struct file_operations *file_ops;
	const struct nlmclnt_operations *nlmclnt_ops;
	int (*getroot)(struct nfs_server *, struct nfs_fh *, struct nfs_fsinfo *);
	int (*submount)(struct fs_context *, struct nfs_server *);
	int (*try_get_tree)(struct fs_context *);
	int (*getattr)(struct nfs_server *, struct nfs_fh *, struct nfs_fattr *, struct nfs4_label *, struct inode *);
	int (*setattr)(struct dentry *, struct nfs_fattr *, struct iattr *);
	int (*lookup)(struct inode *, struct dentry *, struct nfs_fh *, struct nfs_fattr *, struct nfs4_label *);
	int (*lookupp)(struct inode *, struct nfs_fh *, struct nfs_fattr *, struct nfs4_label *);
	int (*access)(struct inode *, struct nfs_access_entry *);
	int (*readlink)(struct inode *, struct page *, unsigned int, unsigned int);
	int (*create)(struct inode *, struct dentry *, struct iattr *, int);
	int (*remove)(struct inode *, struct dentry *);
	void (*unlink_setup)(struct rpc_message *, struct dentry *, struct inode *);
	void (*unlink_rpc_prepare)(struct rpc_task *, struct nfs_unlinkdata *);
	int (*unlink_done)(struct rpc_task *, struct inode *);
	void (*rename_setup)(struct rpc_message *, struct dentry *, struct dentry *);
	void (*rename_rpc_prepare)(struct rpc_task *, struct nfs_renamedata *);
	int (*rename_done)(struct rpc_task *, struct inode *, struct inode *);
	int (*link)(struct inode *, struct inode *, const struct qstr *);
	int (*symlink)(struct inode *, struct dentry *, struct page *, unsigned int, struct iattr *);
	int (*mkdir)(struct inode *, struct dentry *, struct iattr *);
	int (*rmdir)(struct inode *, const struct qstr *);
	int (*readdir)(struct dentry *, const struct cred *, u64, struct page **, unsigned int, bool);
	int (*mknod)(struct inode *, struct dentry *, struct iattr *, dev_t);
	int (*statfs)(struct nfs_server *, struct nfs_fh *, struct nfs_fsstat *);
	int (*fsinfo)(struct nfs_server *, struct nfs_fh *, struct nfs_fsinfo *);
	int (*pathconf)(struct nfs_server *, struct nfs_fh *, struct nfs_pathconf *);
	int (*set_capabilities)(struct nfs_server *, struct nfs_fh *);
	int (*decode_dirent)(struct xdr_stream *, struct nfs_entry *, bool);
	int (*pgio_rpc_prepare)(struct rpc_task *, struct nfs_pgio_header *);
	void (*read_setup)(struct nfs_pgio_header *, struct rpc_message *);
	int (*read_done)(struct rpc_task *, struct nfs_pgio_header *);
	void (*write_setup)(struct nfs_pgio_header *, struct rpc_message *, struct rpc_clnt **);
	int (*write_done)(struct rpc_task *, struct nfs_pgio_header *);
	void (*commit_setup)(struct nfs_commit_data *, struct rpc_message *, struct rpc_clnt **);
	void (*commit_rpc_prepare)(struct rpc_task *, struct nfs_commit_data *);
	int (*commit_done)(struct rpc_task *, struct nfs_commit_data *);
	int (*lock)(struct file *, int, struct file_lock *);
	int (*lock_check_bounds)(const struct file_lock *);
	void (*clear_acl_cache)(struct inode *);
	void (*close_context)(struct nfs_open_context *, int);
	struct inode * (*open_context)(struct inode *, struct nfs_open_context *, int, struct iattr *, int *);
	int (*have_delegation)(struct inode *, fmode_t);
	struct nfs_client * (*alloc_client)(const struct nfs_client_initdata *);
	struct nfs_client * (*init_client)(struct nfs_client *, const struct nfs_client_initdata *);
	void (*free_client)(struct nfs_client *);
	struct nfs_server * (*create_server)(struct fs_context *);
	struct nfs_server * (*clone_server)(struct nfs_server *, struct nfs_fh *, struct nfs_fattr *, rpc_authflavor_t);
};

struct nlmclnt_operations {
	void (*nlmclnt_alloc_call)(void *);
	bool (*nlmclnt_unlock_prepare)(struct rpc_task *, void *);
	void (*nlmclnt_release_call)(void *);
};

struct nfs_access_entry {
	struct rb_node rb_node;
	struct list_head lru;
	const struct cred *cred;
	__u32 mask;
	struct callback_head callback_head;
};

struct nfs_client_initdata {
	long unsigned int init_flags;
	const char *hostname;
	const struct sockaddr *addr;
	const char *nodename;
	const char *ip_addr;
	size_t addrlen;
	struct nfs_subversion *nfs_mod;
	int proto;
	u32 minorversion;
	unsigned int nconnect;
	struct net *net;
	const struct rpc_timeout *timeparms;
	const struct cred *cred;
};

struct nfs_seqid;

struct nfs_seqid_counter;

struct nfs4_state_recovery_ops;

struct nfs4_state_maintenance_ops;

struct nfs4_mig_recovery_ops;

struct nfs4_minor_version_ops {
	u32 minor_version;
	unsigned int init_caps;
	int (*init_client)(struct nfs_client *);
	void (*shutdown_client)(struct nfs_client *);
	bool (*match_stateid)(const nfs4_stateid *, const nfs4_stateid *);
	int (*find_root_sec)(struct nfs_server *, struct nfs_fh *, struct nfs_fsinfo *);
	void (*free_lock_state)(struct nfs_server *, struct nfs4_lock_state *);
	int (*test_and_free_expired)(struct nfs_server *, nfs4_stateid *, const struct cred *);
	struct nfs_seqid * (*alloc_seqid)(struct nfs_seqid_counter *, gfp_t);
	void (*session_trunk)(struct rpc_clnt *, struct rpc_xprt *, void *);
	const struct rpc_call_ops *call_sync_ops;
	const struct nfs4_state_recovery_ops *reboot_recovery_ops;
	const struct nfs4_state_recovery_ops *nograce_recovery_ops;
	const struct nfs4_state_maintenance_ops *state_renewal_ops;
	const struct nfs4_mig_recovery_ops *mig_recovery_ops;
};

enum perf_branch_sample_type_shift {
	PERF_SAMPLE_BRANCH_USER_SHIFT = 0,
	PERF_SAMPLE_BRANCH_KERNEL_SHIFT = 1,
	PERF_SAMPLE_BRANCH_HV_SHIFT = 2,
	PERF_SAMPLE_BRANCH_ANY_SHIFT = 3,
	PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT = 4,
	PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT = 5,
	PERF_SAMPLE_BRANCH_IND_CALL_SHIFT = 6,
	PERF_SAMPLE_BRANCH_ABORT_TX_SHIFT = 7,
	PERF_SAMPLE_BRANCH_IN_TX_SHIFT = 8,
	PERF_SAMPLE_BRANCH_NO_TX_SHIFT = 9,
	PERF_SAMPLE_BRANCH_COND_SHIFT = 10,
	PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT = 11,
	PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT = 12,
	PERF_SAMPLE_BRANCH_CALL_SHIFT = 13,
	PERF_SAMPLE_BRANCH_NO_FLAGS_SHIFT = 14,
	PERF_SAMPLE_BRANCH_NO_CYCLES_SHIFT = 15,
	PERF_SAMPLE_BRANCH_TYPE_SAVE_SHIFT = 16,
	PERF_SAMPLE_BRANCH_HW_INDEX_SHIFT = 17,
	PERF_SAMPLE_BRANCH_MAX_SHIFT = 18,
};

enum exception_stack_ordering {
	ESTACK_DF = 0,
	ESTACK_NMI = 1,
	ESTACK_DB = 2,
	ESTACK_MCE = 3,
	N_EXCEPTION_STACKS = 4,
};

enum {
	TSK_TRACE_FL_TRACE_BIT = 0,
	TSK_TRACE_FL_GRAPH_BIT = 1,
};

struct uuidcmp {
	const char *uuid;
	int len;
};

struct subprocess_info {
	struct work_struct work;
	struct completion *complete;
	const char *path;
	char **argv;
	char **envp;
	struct file *file;
	int wait;
	int retval;
	pid_t pid;
	int (*init)(struct subprocess_info *, struct cred *);
	void (*cleanup)(struct subprocess_info *);
	void *data;
};

struct mdu_array_info_s {
	int major_version;
	int minor_version;
	int patch_version;
	unsigned int ctime;
	int level;
	int size;
	int nr_disks;
	int raid_disks;
	int md_minor;
	int not_persistent;
	unsigned int utime;
	int state;
	int active_disks;
	int working_disks;
	int failed_disks;
	int spare_disks;
	int layout;
	int chunk_size;
};

typedef struct mdu_array_info_s mdu_array_info_t;

struct mdu_disk_info_s {
	int number;
	int major;
	int minor;
	int raid_disk;
	int state;
};

typedef struct mdu_disk_info_s mdu_disk_info_t;

struct hash {
	int ino;
	int minor;
	int major;
	umode_t mode;
	struct hash *next;
	char name[4098];
};

struct dir_entry {
	struct list_head list;
	char *name;
	time64_t mtime;
};

enum state {
	Start = 0,
	Collect = 1,
	GotHeader = 2,
	SkipIt = 3,
	GotName = 4,
	CopyFile = 5,
	GotSymlink = 6,
	Reset = 7,
};

typedef int (*decompress_fn)(unsigned char *, long int, long int (*)(void *, long unsigned int), long int (*)(void *, long unsigned int), unsigned char *, long int *, void (*)(char *));

typedef u32 note_buf_t[92];

struct kimage_arch {
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	void *elf_headers;
	long unsigned int elf_headers_sz;
	long unsigned int elf_load_addr;
};

typedef void crash_vmclear_fn();

typedef long unsigned int kimage_entry_t;

struct kexec_segment {
	union {
		void *buf;
		void *kbuf;
	};
	size_t bufsz;
	long unsigned int mem;
	size_t memsz;
};

struct kimage {
	kimage_entry_t head;
	kimage_entry_t *entry;
	kimage_entry_t *last_entry;
	long unsigned int start;
	struct page *control_code_page;
	struct page *swap_page;
	void *vmcoreinfo_data_copy;
	long unsigned int nr_segments;
	struct kexec_segment segment[16];
	struct list_head control_pages;
	struct list_head dest_pages;
	struct list_head unusable_pages;
	long unsigned int control_page;
	unsigned int type: 1;
	unsigned int preserve_context: 1;
	unsigned int file_mode: 1;
	struct kimage_arch arch;
};

enum ucount_type {
	UCOUNT_USER_NAMESPACES = 0,
	UCOUNT_PID_NAMESPACES = 1,
	UCOUNT_UTS_NAMESPACES = 2,
	UCOUNT_IPC_NAMESPACES = 3,
	UCOUNT_NET_NAMESPACES = 4,
	UCOUNT_MNT_NAMESPACES = 5,
	UCOUNT_CGROUP_NAMESPACES = 6,
	UCOUNT_TIME_NAMESPACES = 7,
	UCOUNT_INOTIFY_INSTANCES = 8,
	UCOUNT_INOTIFY_WATCHES = 9,
	UCOUNT_COUNTS = 10,
};

enum flow_dissector_key_id {
	FLOW_DISSECTOR_KEY_CONTROL = 0,
	FLOW_DISSECTOR_KEY_BASIC = 1,
	FLOW_DISSECTOR_KEY_IPV4_ADDRS = 2,
	FLOW_DISSECTOR_KEY_IPV6_ADDRS = 3,
	FLOW_DISSECTOR_KEY_PORTS = 4,
	FLOW_DISSECTOR_KEY_PORTS_RANGE = 5,
	FLOW_DISSECTOR_KEY_ICMP = 6,
	FLOW_DISSECTOR_KEY_ETH_ADDRS = 7,
	FLOW_DISSECTOR_KEY_TIPC = 8,
	FLOW_DISSECTOR_KEY_ARP = 9,
	FLOW_DISSECTOR_KEY_VLAN = 10,
	FLOW_DISSECTOR_KEY_FLOW_LABEL = 11,
	FLOW_DISSECTOR_KEY_GRE_KEYID = 12,
	FLOW_DISSECTOR_KEY_MPLS_ENTROPY = 13,
	FLOW_DISSECTOR_KEY_ENC_KEYID = 14,
	FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS = 15,
	FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS = 16,
	FLOW_DISSECTOR_KEY_ENC_CONTROL = 17,
	FLOW_DISSECTOR_KEY_ENC_PORTS = 18,
	FLOW_DISSECTOR_KEY_MPLS = 19,
	FLOW_DISSECTOR_KEY_TCP = 20,
	FLOW_DISSECTOR_KEY_IP = 21,
	FLOW_DISSECTOR_KEY_CVLAN = 22,
	FLOW_DISSECTOR_KEY_ENC_IP = 23,
	FLOW_DISSECTOR_KEY_ENC_OPTS = 24,
	FLOW_DISSECTOR_KEY_META = 25,
	FLOW_DISSECTOR_KEY_CT = 26,
	FLOW_DISSECTOR_KEY_MAX = 27,
};

enum {
	IPSTATS_MIB_NUM = 0,
	IPSTATS_MIB_INPKTS = 1,
	IPSTATS_MIB_INOCTETS = 2,
	IPSTATS_MIB_INDELIVERS = 3,
	IPSTATS_MIB_OUTFORWDATAGRAMS = 4,
	IPSTATS_MIB_OUTPKTS = 5,
	IPSTATS_MIB_OUTOCTETS = 6,
	IPSTATS_MIB_INHDRERRORS = 7,
	IPSTATS_MIB_INTOOBIGERRORS = 8,
	IPSTATS_MIB_INNOROUTES = 9,
	IPSTATS_MIB_INADDRERRORS = 10,
	IPSTATS_MIB_INUNKNOWNPROTOS = 11,
	IPSTATS_MIB_INTRUNCATEDPKTS = 12,
	IPSTATS_MIB_INDISCARDS = 13,
	IPSTATS_MIB_OUTDISCARDS = 14,
	IPSTATS_MIB_OUTNOROUTES = 15,
	IPSTATS_MIB_REASMTIMEOUT = 16,
	IPSTATS_MIB_REASMREQDS = 17,
	IPSTATS_MIB_REASMOKS = 18,
	IPSTATS_MIB_REASMFAILS = 19,
	IPSTATS_MIB_FRAGOKS = 20,
	IPSTATS_MIB_FRAGFAILS = 21,
	IPSTATS_MIB_FRAGCREATES = 22,
	IPSTATS_MIB_INMCASTPKTS = 23,
	IPSTATS_MIB_OUTMCASTPKTS = 24,
	IPSTATS_MIB_INBCASTPKTS = 25,
	IPSTATS_MIB_OUTBCASTPKTS = 26,
	IPSTATS_MIB_INMCASTOCTETS = 27,
	IPSTATS_MIB_OUTMCASTOCTETS = 28,
	IPSTATS_MIB_INBCASTOCTETS = 29,
	IPSTATS_MIB_OUTBCASTOCTETS = 30,
	IPSTATS_MIB_CSUMERRORS = 31,
	IPSTATS_MIB_NOECTPKTS = 32,
	IPSTATS_MIB_ECT1PKTS = 33,
	IPSTATS_MIB_ECT0PKTS = 34,
	IPSTATS_MIB_CEPKTS = 35,
	IPSTATS_MIB_REASM_OVERLAPS = 36,
	__IPSTATS_MIB_MAX = 37,
};

enum {
	ICMP_MIB_NUM = 0,
	ICMP_MIB_INMSGS = 1,
	ICMP_MIB_INERRORS = 2,
	ICMP_MIB_INDESTUNREACHS = 3,
	ICMP_MIB_INTIMEEXCDS = 4,
	ICMP_MIB_INPARMPROBS = 5,
	ICMP_MIB_INSRCQUENCHS = 6,
	ICMP_MIB_INREDIRECTS = 7,
	ICMP_MIB_INECHOS = 8,
	ICMP_MIB_INECHOREPS = 9,
	ICMP_MIB_INTIMESTAMPS = 10,
	ICMP_MIB_INTIMESTAMPREPS = 11,
	ICMP_MIB_INADDRMASKS = 12,
	ICMP_MIB_INADDRMASKREPS = 13,
	ICMP_MIB_OUTMSGS = 14,
	ICMP_MIB_OUTERRORS = 15,
	ICMP_MIB_OUTDESTUNREACHS = 16,
	ICMP_MIB_OUTTIMEEXCDS = 17,
	ICMP_MIB_OUTPARMPROBS = 18,
	ICMP_MIB_OUTSRCQUENCHS = 19,
	ICMP_MIB_OUTREDIRECTS = 20,
	ICMP_MIB_OUTECHOS = 21,
	ICMP_MIB_OUTECHOREPS = 22,
	ICMP_MIB_OUTTIMESTAMPS = 23,
	ICMP_MIB_OUTTIMESTAMPREPS = 24,
	ICMP_MIB_OUTADDRMASKS = 25,
	ICMP_MIB_OUTADDRMASKREPS = 26,
	ICMP_MIB_CSUMERRORS = 27,
	__ICMP_MIB_MAX = 28,
};

enum {
	ICMP6_MIB_NUM = 0,
	ICMP6_MIB_INMSGS = 1,
	ICMP6_MIB_INERRORS = 2,
	ICMP6_MIB_OUTMSGS = 3,
	ICMP6_MIB_OUTERRORS = 4,
	ICMP6_MIB_CSUMERRORS = 5,
	__ICMP6_MIB_MAX = 6,
};

enum {
	TCP_MIB_NUM = 0,
	TCP_MIB_RTOALGORITHM = 1,
	TCP_MIB_RTOMIN = 2,
	TCP_MIB_RTOMAX = 3,
	TCP_MIB_MAXCONN = 4,
	TCP_MIB_ACTIVEOPENS = 5,
	TCP_MIB_PASSIVEOPENS = 6,
	TCP_MIB_ATTEMPTFAILS = 7,
	TCP_MIB_ESTABRESETS = 8,
	TCP_MIB_CURRESTAB = 9,
	TCP_MIB_INSEGS = 10,
	TCP_MIB_OUTSEGS = 11,
	TCP_MIB_RETRANSSEGS = 12,
	TCP_MIB_INERRS = 13,
	TCP_MIB_OUTRSTS = 14,
	TCP_MIB_CSUMERRORS = 15,
	__TCP_MIB_MAX = 16,
};

enum {
	UDP_MIB_NUM = 0,
	UDP_MIB_INDATAGRAMS = 1,
	UDP_MIB_NOPORTS = 2,
	UDP_MIB_INERRORS = 3,
	UDP_MIB_OUTDATAGRAMS = 4,
	UDP_MIB_RCVBUFERRORS = 5,
	UDP_MIB_SNDBUFERRORS = 6,
	UDP_MIB_CSUMERRORS = 7,
	UDP_MIB_IGNOREDMULTI = 8,
	__UDP_MIB_MAX = 9,
};

enum {
	LINUX_MIB_NUM = 0,
	LINUX_MIB_SYNCOOKIESSENT = 1,
	LINUX_MIB_SYNCOOKIESRECV = 2,
	LINUX_MIB_SYNCOOKIESFAILED = 3,
	LINUX_MIB_EMBRYONICRSTS = 4,
	LINUX_MIB_PRUNECALLED = 5,
	LINUX_MIB_RCVPRUNED = 6,
	LINUX_MIB_OFOPRUNED = 7,
	LINUX_MIB_OUTOFWINDOWICMPS = 8,
	LINUX_MIB_LOCKDROPPEDICMPS = 9,
	LINUX_MIB_ARPFILTER = 10,
	LINUX_MIB_TIMEWAITED = 11,
	LINUX_MIB_TIMEWAITRECYCLED = 12,
	LINUX_MIB_TIMEWAITKILLED = 13,
	LINUX_MIB_PAWSACTIVEREJECTED = 14,
	LINUX_MIB_PAWSESTABREJECTED = 15,
	LINUX_MIB_DELAYEDACKS = 16,
	LINUX_MIB_DELAYEDACKLOCKED = 17,
	LINUX_MIB_DELAYEDACKLOST = 18,
	LINUX_MIB_LISTENOVERFLOWS = 19,
	LINUX_MIB_LISTENDROPS = 20,
	LINUX_MIB_TCPHPHITS = 21,
	LINUX_MIB_TCPPUREACKS = 22,
	LINUX_MIB_TCPHPACKS = 23,
	LINUX_MIB_TCPRENORECOVERY = 24,
	LINUX_MIB_TCPSACKRECOVERY = 25,
	LINUX_MIB_TCPSACKRENEGING = 26,
	LINUX_MIB_TCPSACKREORDER = 27,
	LINUX_MIB_TCPRENOREORDER = 28,
	LINUX_MIB_TCPTSREORDER = 29,
	LINUX_MIB_TCPFULLUNDO = 30,
	LINUX_MIB_TCPPARTIALUNDO = 31,
	LINUX_MIB_TCPDSACKUNDO = 32,
	LINUX_MIB_TCPLOSSUNDO = 33,
	LINUX_MIB_TCPLOSTRETRANSMIT = 34,
	LINUX_MIB_TCPRENOFAILURES = 35,
	LINUX_MIB_TCPSACKFAILURES = 36,
	LINUX_MIB_TCPLOSSFAILURES = 37,
	LINUX_MIB_TCPFASTRETRANS = 38,
	LINUX_MIB_TCPSLOWSTARTRETRANS = 39,
	LINUX_MIB_TCPTIMEOUTS = 40,
	LINUX_MIB_TCPLOSSPROBES = 41,
	LINUX_MIB_TCPLOSSPROBERECOVERY = 42,
	LINUX_MIB_TCPRENORECOVERYFAIL = 43,
	LINUX_MIB_TCPSACKRECOVERYFAIL = 44,
	LINUX_MIB_TCPRCVCOLLAPSED = 45,
	LINUX_MIB_TCPDSACKOLDSENT = 46,
	LINUX_MIB_TCPDSACKOFOSENT = 47,
	LINUX_MIB_TCPDSACKRECV = 48,
	LINUX_MIB_TCPDSACKOFORECV = 49,
	LINUX_MIB_TCPABORTONDATA = 50,
	LINUX_MIB_TCPABORTONCLOSE = 51,
	LINUX_MIB_TCPABORTONMEMORY = 52,
	LINUX_MIB_TCPABORTONTIMEOUT = 53,
	LINUX_MIB_TCPABORTONLINGER = 54,
	LINUX_MIB_TCPABORTFAILED = 55,
	LINUX_MIB_TCPMEMORYPRESSURES = 56,
	LINUX_MIB_TCPMEMORYPRESSURESCHRONO = 57,
	LINUX_MIB_TCPSACKDISCARD = 58,
	LINUX_MIB_TCPDSACKIGNOREDOLD = 59,
	LINUX_MIB_TCPDSACKIGNOREDNOUNDO = 60,
	LINUX_MIB_TCPSPURIOUSRTOS = 61,
	LINUX_MIB_TCPMD5NOTFOUND = 62,
	LINUX_MIB_TCPMD5UNEXPECTED = 63,
	LINUX_MIB_TCPMD5FAILURE = 64,
	LINUX_MIB_SACKSHIFTED = 65,
	LINUX_MIB_SACKMERGED = 66,
	LINUX_MIB_SACKSHIFTFALLBACK = 67,
	LINUX_MIB_TCPBACKLOGDROP = 68,
	LINUX_MIB_PFMEMALLOCDROP = 69,
	LINUX_MIB_TCPMINTTLDROP = 70,
	LINUX_MIB_TCPDEFERACCEPTDROP = 71,
	LINUX_MIB_IPRPFILTER = 72,
	LINUX_MIB_TCPTIMEWAITOVERFLOW = 73,
	LINUX_MIB_TCPREQQFULLDOCOOKIES = 74,
	LINUX_MIB_TCPREQQFULLDROP = 75,
	LINUX_MIB_TCPRETRANSFAIL = 76,
	LINUX_MIB_TCPRCVCOALESCE = 77,
	LINUX_MIB_TCPBACKLOGCOALESCE = 78,
	LINUX_MIB_TCPOFOQUEUE = 79,
	LINUX_MIB_TCPOFODROP = 80,
	LINUX_MIB_TCPOFOMERGE = 81,
	LINUX_MIB_TCPCHALLENGEACK = 82,
	LINUX_MIB_TCPSYNCHALLENGE = 83,
	LINUX_MIB_TCPFASTOPENACTIVE = 84,
	LINUX_MIB_TCPFASTOPENACTIVEFAIL = 85,
	LINUX_MIB_TCPFASTOPENPASSIVE = 86,
	LINUX_MIB_TCPFASTOPENPASSIVEFAIL = 87,
	LINUX_MIB_TCPFASTOPENLISTENOVERFLOW = 88,
	LINUX_MIB_TCPFASTOPENCOOKIEREQD = 89,
	LINUX_MIB_TCPFASTOPENBLACKHOLE = 90,
	LINUX_MIB_TCPSPURIOUS_RTX_HOSTQUEUES = 91,
	LINUX_MIB_BUSYPOLLRXPACKETS = 92,
	LINUX_MIB_TCPAUTOCORKING = 93,
	LINUX_MIB_TCPFROMZEROWINDOWADV = 94,
	LINUX_MIB_TCPTOZEROWINDOWADV = 95,
	LINUX_MIB_TCPWANTZEROWINDOWADV = 96,
	LINUX_MIB_TCPSYNRETRANS = 97,
	LINUX_MIB_TCPORIGDATASENT = 98,
	LINUX_MIB_TCPHYSTARTTRAINDETECT = 99,
	LINUX_MIB_TCPHYSTARTTRAINCWND = 100,
	LINUX_MIB_TCPHYSTARTDELAYDETECT = 101,
	LINUX_MIB_TCPHYSTARTDELAYCWND = 102,
	LINUX_MIB_TCPACKSKIPPEDSYNRECV = 103,
	LINUX_MIB_TCPACKSKIPPEDPAWS = 104,
	LINUX_MIB_TCPACKSKIPPEDSEQ = 105,
	LINUX_MIB_TCPACKSKIPPEDFINWAIT2 = 106,
	LINUX_MIB_TCPACKSKIPPEDTIMEWAIT = 107,
	LINUX_MIB_TCPACKSKIPPEDCHALLENGE = 108,
	LINUX_MIB_TCPWINPROBE = 109,
	LINUX_MIB_TCPKEEPALIVE = 110,
	LINUX_MIB_TCPMTUPFAIL = 111,
	LINUX_MIB_TCPMTUPSUCCESS = 112,
	LINUX_MIB_TCPDELIVERED = 113,
	LINUX_MIB_TCPDELIVEREDCE = 114,
	LINUX_MIB_TCPACKCOMPRESSED = 115,
	LINUX_MIB_TCPZEROWINDOWDROP = 116,
	LINUX_MIB_TCPRCVQDROP = 117,
	LINUX_MIB_TCPWQUEUETOOBIG = 118,
	LINUX_MIB_TCPFASTOPENPASSIVEALTKEY = 119,
	LINUX_MIB_TCPTIMEOUTREHASH = 120,
	LINUX_MIB_TCPDUPLICATEDATAREHASH = 121,
	__LINUX_MIB_MAX = 122,
};

enum {
	LINUX_MIB_XFRMNUM = 0,
	LINUX_MIB_XFRMINERROR = 1,
	LINUX_MIB_XFRMINBUFFERERROR = 2,
	LINUX_MIB_XFRMINHDRERROR = 3,
	LINUX_MIB_XFRMINNOSTATES = 4,
	LINUX_MIB_XFRMINSTATEPROTOERROR = 5,
	LINUX_MIB_XFRMINSTATEMODEERROR = 6,
	LINUX_MIB_XFRMINSTATESEQERROR = 7,
	LINUX_MIB_XFRMINSTATEEXPIRED = 8,
	LINUX_MIB_XFRMINSTATEMISMATCH = 9,
	LINUX_MIB_XFRMINSTATEINVALID = 10,
	LINUX_MIB_XFRMINTMPLMISMATCH = 11,
	LINUX_MIB_XFRMINNOPOLS = 12,
	LINUX_MIB_XFRMINPOLBLOCK = 13,
	LINUX_MIB_XFRMINPOLERROR = 14,
	LINUX_MIB_XFRMOUTERROR = 15,
	LINUX_MIB_XFRMOUTBUNDLEGENERROR = 16,
	LINUX_MIB_XFRMOUTBUNDLECHECKERROR = 17,
	LINUX_MIB_XFRMOUTNOSTATES = 18,
	LINUX_MIB_XFRMOUTSTATEPROTOERROR = 19,
	LINUX_MIB_XFRMOUTSTATEMODEERROR = 20,
	LINUX_MIB_XFRMOUTSTATESEQERROR = 21,
	LINUX_MIB_XFRMOUTSTATEEXPIRED = 22,
	LINUX_MIB_XFRMOUTPOLBLOCK = 23,
	LINUX_MIB_XFRMOUTPOLDEAD = 24,
	LINUX_MIB_XFRMOUTPOLERROR = 25,
	LINUX_MIB_XFRMFWDHDRERROR = 26,
	LINUX_MIB_XFRMOUTSTATEINVALID = 27,
	LINUX_MIB_XFRMACQUIREERROR = 28,
	__LINUX_MIB_XFRMMAX = 29,
};

enum {
	LINUX_MIB_TLSNUM = 0,
	LINUX_MIB_TLSCURRTXSW = 1,
	LINUX_MIB_TLSCURRRXSW = 2,
	LINUX_MIB_TLSCURRTXDEVICE = 3,
	LINUX_MIB_TLSCURRRXDEVICE = 4,
	LINUX_MIB_TLSTXSW = 5,
	LINUX_MIB_TLSRXSW = 6,
	LINUX_MIB_TLSTXDEVICE = 7,
	LINUX_MIB_TLSRXDEVICE = 8,
	LINUX_MIB_TLSDECRYPTERROR = 9,
	LINUX_MIB_TLSRXDEVICERESYNC = 10,
	__LINUX_MIB_TLSMAX = 11,
};

enum nf_inet_hooks {
	NF_INET_PRE_ROUTING = 0,
	NF_INET_LOCAL_IN = 1,
	NF_INET_FORWARD = 2,
	NF_INET_LOCAL_OUT = 3,
	NF_INET_POST_ROUTING = 4,
	NF_INET_NUMHOOKS = 5,
};

enum {
	NFPROTO_UNSPEC = 0,
	NFPROTO_INET = 1,
	NFPROTO_IPV4 = 2,
	NFPROTO_ARP = 3,
	NFPROTO_NETDEV = 5,
	NFPROTO_BRIDGE = 7,
	NFPROTO_IPV6 = 10,
	NFPROTO_DECNET = 12,
	NFPROTO_NUMPROTO = 13,
};

enum tcp_conntrack {
	TCP_CONNTRACK_NONE = 0,
	TCP_CONNTRACK_SYN_SENT = 1,
	TCP_CONNTRACK_SYN_RECV = 2,
	TCP_CONNTRACK_ESTABLISHED = 3,
	TCP_CONNTRACK_FIN_WAIT = 4,
	TCP_CONNTRACK_CLOSE_WAIT = 5,
	TCP_CONNTRACK_LAST_ACK = 6,
	TCP_CONNTRACK_TIME_WAIT = 7,
	TCP_CONNTRACK_CLOSE = 8,
	TCP_CONNTRACK_LISTEN = 9,
	TCP_CONNTRACK_MAX = 10,
	TCP_CONNTRACK_IGNORE = 11,
	TCP_CONNTRACK_RETRANS = 12,
	TCP_CONNTRACK_UNACK = 13,
	TCP_CONNTRACK_TIMEOUT_MAX = 14,
};

enum ct_dccp_states {
	CT_DCCP_NONE = 0,
	CT_DCCP_REQUEST = 1,
	CT_DCCP_RESPOND = 2,
	CT_DCCP_PARTOPEN = 3,
	CT_DCCP_OPEN = 4,
	CT_DCCP_CLOSEREQ = 5,
	CT_DCCP_CLOSING = 6,
	CT_DCCP_TIMEWAIT = 7,
	CT_DCCP_IGNORE = 8,
	CT_DCCP_INVALID = 9,
	__CT_DCCP_MAX = 10,
};

enum ip_conntrack_dir {
	IP_CT_DIR_ORIGINAL = 0,
	IP_CT_DIR_REPLY = 1,
	IP_CT_DIR_MAX = 2,
};

enum sctp_conntrack {
	SCTP_CONNTRACK_NONE = 0,
	SCTP_CONNTRACK_CLOSED = 1,
	SCTP_CONNTRACK_COOKIE_WAIT = 2,
	SCTP_CONNTRACK_COOKIE_ECHOED = 3,
	SCTP_CONNTRACK_ESTABLISHED = 4,
	SCTP_CONNTRACK_SHUTDOWN_SENT = 5,
	SCTP_CONNTRACK_SHUTDOWN_RECD = 6,
	SCTP_CONNTRACK_SHUTDOWN_ACK_SENT = 7,
	SCTP_CONNTRACK_HEARTBEAT_SENT = 8,
	SCTP_CONNTRACK_HEARTBEAT_ACKED = 9,
	SCTP_CONNTRACK_MAX = 10,
};

enum udp_conntrack {
	UDP_CT_UNREPLIED = 0,
	UDP_CT_REPLIED = 1,
	UDP_CT_MAX = 2,
};

enum {
	XFRM_POLICY_IN = 0,
	XFRM_POLICY_OUT = 1,
	XFRM_POLICY_FWD = 2,
	XFRM_POLICY_MASK = 3,
	XFRM_POLICY_MAX = 3,
};

enum netns_bpf_attach_type {
	NETNS_BPF_INVALID = 4294967295,
	NETNS_BPF_FLOW_DISSECTOR = 0,
	MAX_NETNS_BPF_ATTACH_TYPE = 1,
};

enum skb_ext_id {
	SKB_EXT_SEC_PATH = 0,
	SKB_EXT_NUM = 1,
};

enum sched_tunable_scaling {
	SCHED_TUNABLESCALING_NONE = 0,
	SCHED_TUNABLESCALING_LOG = 1,
	SCHED_TUNABLESCALING_LINEAR = 2,
	SCHED_TUNABLESCALING_END = 3,
};

enum audit_ntp_type {
	AUDIT_NTP_OFFSET = 0,
	AUDIT_NTP_FREQ = 1,
	AUDIT_NTP_STATUS = 2,
	AUDIT_NTP_TAI = 3,
	AUDIT_NTP_TICK = 4,
	AUDIT_NTP_ADJUST = 5,
	AUDIT_NTP_NVALS = 6,
};

typedef long int (*sys_call_ptr_t)(const struct pt_regs *);

struct io_bitmap {
	u64 sequence;
	refcount_t refcnt;
	unsigned int max;
	long unsigned int bitmap[1024];
};

struct seccomp_data {
	int nr;
	__u32 arch;
	__u64 instruction_pointer;
	__u64 args[6];
};

struct ksignal {
	struct k_sigaction ka;
	kernel_siginfo_t info;
	int sig;
};

struct __large_struct {
	long unsigned int buf[100];
};

enum {
	TASKSTATS_CMD_UNSPEC = 0,
	TASKSTATS_CMD_GET = 1,
	TASKSTATS_CMD_NEW = 2,
	__TASKSTATS_CMD_MAX = 3,
};

enum ctx_state {
	CONTEXT_DISABLED = 4294967295,
	CONTEXT_KERNEL = 0,
	CONTEXT_USER = 1,
	CONTEXT_GUEST = 2,
};

enum {
	HI_SOFTIRQ = 0,
	TIMER_SOFTIRQ = 1,
	NET_TX_SOFTIRQ = 2,
	NET_RX_SOFTIRQ = 3,
	BLOCK_SOFTIRQ = 4,
	IRQ_POLL_SOFTIRQ = 5,
	TASKLET_SOFTIRQ = 6,
	SCHED_SOFTIRQ = 7,
	HRTIMER_SOFTIRQ = 8,
	RCU_SOFTIRQ = 9,
	NR_SOFTIRQS = 10,
};

enum cpu_usage_stat {
	CPUTIME_USER = 0,
	CPUTIME_NICE = 1,
	CPUTIME_SYSTEM = 2,
	CPUTIME_SOFTIRQ = 3,
	CPUTIME_IRQ = 4,
	CPUTIME_IDLE = 5,
	CPUTIME_IOWAIT = 6,
	CPUTIME_STEAL = 7,
	CPUTIME_GUEST = 8,
	CPUTIME_GUEST_NICE = 9,
	NR_STATS = 10,
};

enum {
	EI_ETYPE_NONE = 0,
	EI_ETYPE_NULL = 1,
	EI_ETYPE_ERRNO = 2,
	EI_ETYPE_ERRNO_NULL = 3,
	EI_ETYPE_TRUE = 4,
};

enum bpf_cgroup_storage_type {
	BPF_CGROUP_STORAGE_SHARED = 0,
	BPF_CGROUP_STORAGE_PERCPU = 1,
	__BPF_CGROUP_STORAGE_MAX = 2,
};

enum cgroup_subsys_id {
	cpuset_cgrp_id = 0,
	cpu_cgrp_id = 1,
	cpuacct_cgrp_id = 2,
	freezer_cgrp_id = 3,
	CGROUP_SUBSYS_COUNT = 4,
};

typedef u8 kprobe_opcode_t;

struct arch_specific_insn {
	kprobe_opcode_t *insn;
	bool boostable;
	bool if_modifier;
};

struct kprobe;

struct prev_kprobe {
	struct kprobe *kp;
	long unsigned int status;
	long unsigned int old_flags;
	long unsigned int saved_flags;
};

typedef int (*kprobe_pre_handler_t)(struct kprobe *, struct pt_regs *);

typedef void (*kprobe_post_handler_t)(struct kprobe *, struct pt_regs *, long unsigned int);

typedef int (*kprobe_fault_handler_t)(struct kprobe *, struct pt_regs *, int);

struct kprobe {
	struct hlist_node hlist;
	struct list_head list;
	long unsigned int nmissed;
	kprobe_opcode_t *addr;
	const char *symbol_name;
	unsigned int offset;
	kprobe_pre_handler_t pre_handler;
	kprobe_post_handler_t post_handler;
	kprobe_fault_handler_t fault_handler;
	kprobe_opcode_t opcode;
	struct arch_specific_insn ainsn;
	u32 flags;
};

struct kprobe_ctlblk {
	long unsigned int kprobe_status;
	long unsigned int kprobe_old_flags;
	long unsigned int kprobe_saved_flags;
	struct prev_kprobe prev_kprobe;
};

struct kretprobe_blackpoint {
	const char *name;
	void *addr;
};

struct kprobe_insn_cache {
	struct mutex mutex;
	void * (*alloc)();
	void (*free)(void *);
	struct list_head pages;
	size_t insn_size;
	int nr_garbage;
};

struct trace_event_raw_sys_enter {
	struct trace_entry ent;
	long int id;
	long unsigned int args[6];
	char __data[0];
};

struct trace_event_raw_sys_exit {
	struct trace_entry ent;
	long int id;
	long int ret;
	char __data[0];
};

struct trace_event_data_offsets_sys_enter {};

struct trace_event_data_offsets_sys_exit {};

typedef void (*btf_trace_sys_enter)(void *, struct pt_regs *, long int);

typedef void (*btf_trace_sys_exit)(void *, struct pt_regs *, long int);

struct alt_instr {
	s32 instr_offset;
	s32 repl_offset;
	u16 cpuid;
	u8 instrlen;
	u8 replacementlen;
	u8 padlen;
} __attribute__((packed));

struct timens_offset {
	s64 sec;
	u64 nsec;
};

enum vm_fault_reason {
	VM_FAULT_OOM = 1,
	VM_FAULT_SIGBUS = 2,
	VM_FAULT_MAJOR = 4,
	VM_FAULT_WRITE = 8,
	VM_FAULT_HWPOISON = 16,
	VM_FAULT_HWPOISON_LARGE = 32,
	VM_FAULT_SIGSEGV = 64,
	VM_FAULT_NOPAGE = 256,
	VM_FAULT_LOCKED = 512,
	VM_FAULT_RETRY = 1024,
	VM_FAULT_FALLBACK = 2048,
	VM_FAULT_DONE_COW = 4096,
	VM_FAULT_NEEDDSYNC = 8192,
	VM_FAULT_HINDEX_MASK = 983040,
};

struct vm_special_mapping {
	const char *name;
	struct page **pages;
	vm_fault_t (*fault)(const struct vm_special_mapping *, struct vm_area_struct *, struct vm_fault *);
	int (*mremap)(const struct vm_special_mapping *, struct vm_area_struct *);
};

struct timens_offsets {
	struct timespec64 monotonic;
	struct timespec64 boottime;
};

struct time_namespace {
	struct kref kref;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct ns_common ns;
	struct timens_offsets offsets;
	struct page *vvar_page;
	bool frozen_offsets;
};

struct pvclock_vcpu_time_info {
	u32 version;
	u32 pad0;
	u64 tsc_timestamp;
	u64 system_time;
	u32 tsc_to_system_mul;
	s8 tsc_shift;
	u8 flags;
	u8 pad[2];
};

struct pvclock_vsyscall_time_info {
	struct pvclock_vcpu_time_info pvti;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum vdso_clock_mode {
	VDSO_CLOCKMODE_NONE = 0,
	VDSO_CLOCKMODE_TSC = 1,
	VDSO_CLOCKMODE_PVCLOCK = 2,
	VDSO_CLOCKMODE_HVCLOCK = 3,
	VDSO_CLOCKMODE_MAX = 4,
	VDSO_CLOCKMODE_TIMENS = 2147483647,
};

struct vdso_timestamp {
	u64 sec;
	u64 nsec;
};

struct vdso_data {
	u32 seq;
	s32 clock_mode;
	u64 cycle_last;
	u64 mask;
	u32 mult;
	u32 shift;
	union {
		struct vdso_timestamp basetime[12];
		struct timens_offset offset[12];
	};
	s32 tz_minuteswest;
	s32 tz_dsttime;
	u32 hrtimer_res;
	u32 __unused;
};

struct irq_desc;

typedef struct irq_desc *vector_irq_t[256];

struct ms_hyperv_tsc_page {
	volatile u32 tsc_sequence;
	u32 reserved1;
	volatile u64 tsc_scale;
	volatile s64 tsc_offset;
};

struct ms_hyperv_info {
	u32 features;
	u32 misc_features;
	u32 hints;
	u32 nested_features;
	u32 max_vp_index;
	u32 max_lp_index;
};

enum x86_pf_error_code {
	X86_PF_PROT = 1,
	X86_PF_WRITE = 2,
	X86_PF_USER = 4,
	X86_PF_RSVD = 8,
	X86_PF_INSTR = 16,
	X86_PF_PK = 32,
};

struct trace_event_raw_emulate_vsyscall {
	struct trace_entry ent;
	int nr;
	char __data[0];
};

struct trace_event_data_offsets_emulate_vsyscall {};

typedef void (*btf_trace_emulate_vsyscall)(void *, int);

enum {
	EMULATE = 0,
	XONLY = 1,
	NONE = 2,
};

enum perf_type_id {
	PERF_TYPE_HARDWARE = 0,
	PERF_TYPE_SOFTWARE = 1,
	PERF_TYPE_TRACEPOINT = 2,
	PERF_TYPE_HW_CACHE = 3,
	PERF_TYPE_RAW = 4,
	PERF_TYPE_BREAKPOINT = 5,
	PERF_TYPE_MAX = 6,
};

enum perf_hw_id {
	PERF_COUNT_HW_CPU_CYCLES = 0,
	PERF_COUNT_HW_INSTRUCTIONS = 1,
	PERF_COUNT_HW_CACHE_REFERENCES = 2,
	PERF_COUNT_HW_CACHE_MISSES = 3,
	PERF_COUNT_HW_BRANCH_INSTRUCTIONS = 4,
	PERF_COUNT_HW_BRANCH_MISSES = 5,
	PERF_COUNT_HW_BUS_CYCLES = 6,
	PERF_COUNT_HW_STALLED_CYCLES_FRONTEND = 7,
	PERF_COUNT_HW_STALLED_CYCLES_BACKEND = 8,
	PERF_COUNT_HW_REF_CPU_CYCLES = 9,
	PERF_COUNT_HW_MAX = 10,
};

enum perf_hw_cache_id {
	PERF_COUNT_HW_CACHE_L1D = 0,
	PERF_COUNT_HW_CACHE_L1I = 1,
	PERF_COUNT_HW_CACHE_LL = 2,
	PERF_COUNT_HW_CACHE_DTLB = 3,
	PERF_COUNT_HW_CACHE_ITLB = 4,
	PERF_COUNT_HW_CACHE_BPU = 5,
	PERF_COUNT_HW_CACHE_NODE = 6,
	PERF_COUNT_HW_CACHE_MAX = 7,
};

enum perf_hw_cache_op_id {
	PERF_COUNT_HW_CACHE_OP_READ = 0,
	PERF_COUNT_HW_CACHE_OP_WRITE = 1,
	PERF_COUNT_HW_CACHE_OP_PREFETCH = 2,
	PERF_COUNT_HW_CACHE_OP_MAX = 3,
};

enum perf_hw_cache_op_result_id {
	PERF_COUNT_HW_CACHE_RESULT_ACCESS = 0,
	PERF_COUNT_HW_CACHE_RESULT_MISS = 1,
	PERF_COUNT_HW_CACHE_RESULT_MAX = 2,
};

enum perf_event_sample_format {
	PERF_SAMPLE_IP = 1,
	PERF_SAMPLE_TID = 2,
	PERF_SAMPLE_TIME = 4,
	PERF_SAMPLE_ADDR = 8,
	PERF_SAMPLE_READ = 16,
	PERF_SAMPLE_CALLCHAIN = 32,
	PERF_SAMPLE_ID = 64,
	PERF_SAMPLE_CPU = 128,
	PERF_SAMPLE_PERIOD = 256,
	PERF_SAMPLE_STREAM_ID = 512,
	PERF_SAMPLE_RAW = 1024,
	PERF_SAMPLE_BRANCH_STACK = 2048,
	PERF_SAMPLE_REGS_USER = 4096,
	PERF_SAMPLE_STACK_USER = 8192,
	PERF_SAMPLE_WEIGHT = 16384,
	PERF_SAMPLE_DATA_SRC = 32768,
	PERF_SAMPLE_IDENTIFIER = 65536,
	PERF_SAMPLE_TRANSACTION = 131072,
	PERF_SAMPLE_REGS_INTR = 262144,
	PERF_SAMPLE_PHYS_ADDR = 524288,
	PERF_SAMPLE_AUX = 1048576,
	PERF_SAMPLE_CGROUP = 2097152,
	PERF_SAMPLE_MAX = 4194304,
	__PERF_SAMPLE_CALLCHAIN_EARLY = 0,
};

enum perf_branch_sample_type {
	PERF_SAMPLE_BRANCH_USER = 1,
	PERF_SAMPLE_BRANCH_KERNEL = 2,
	PERF_SAMPLE_BRANCH_HV = 4,
	PERF_SAMPLE_BRANCH_ANY = 8,
	PERF_SAMPLE_BRANCH_ANY_CALL = 16,
	PERF_SAMPLE_BRANCH_ANY_RETURN = 32,
	PERF_SAMPLE_BRANCH_IND_CALL = 64,
	PERF_SAMPLE_BRANCH_ABORT_TX = 128,
	PERF_SAMPLE_BRANCH_IN_TX = 256,
	PERF_SAMPLE_BRANCH_NO_TX = 512,
	PERF_SAMPLE_BRANCH_COND = 1024,
	PERF_SAMPLE_BRANCH_CALL_STACK = 2048,
	PERF_SAMPLE_BRANCH_IND_JUMP = 4096,
	PERF_SAMPLE_BRANCH_CALL = 8192,
	PERF_SAMPLE_BRANCH_NO_FLAGS = 16384,
	PERF_SAMPLE_BRANCH_NO_CYCLES = 32768,
	PERF_SAMPLE_BRANCH_TYPE_SAVE = 65536,
	PERF_SAMPLE_BRANCH_HW_INDEX = 131072,
	PERF_SAMPLE_BRANCH_MAX = 262144,
};

struct perf_event_mmap_page {
	__u32 version;
	__u32 compat_version;
	__u32 lock;
	__u32 index;
	__s64 offset;
	__u64 time_enabled;
	__u64 time_running;
	union {
		__u64 capabilities;
		struct {
			__u64 cap_bit0: 1;
			__u64 cap_bit0_is_deprecated: 1;
			__u64 cap_user_rdpmc: 1;
			__u64 cap_user_time: 1;
			__u64 cap_user_time_zero: 1;
			__u64 cap_____res: 59;
		};
	};
	__u16 pmc_width;
	__u16 time_shift;
	__u32 time_mult;
	__u64 time_offset;
	__u64 time_zero;
	__u32 size;
	__u8 __reserved[948];
	__u64 data_head;
	__u64 data_tail;
	__u64 data_offset;
	__u64 data_size;
	__u64 aux_head;
	__u64 aux_tail;
	__u64 aux_offset;
	__u64 aux_size;
};

struct ldt_struct {
	struct desc_struct *entries;
	unsigned int nr_entries;
	int slot;
};

struct x86_pmu_capability {
	int version;
	int num_counters_gp;
	int num_counters_fixed;
	int bit_width_gp;
	int bit_width_fixed;
	unsigned int events_mask;
	int events_mask_len;
};

enum stack_type {
	STACK_TYPE_UNKNOWN = 0,
	STACK_TYPE_TASK = 1,
	STACK_TYPE_IRQ = 2,
	STACK_TYPE_SOFTIRQ = 3,
	STACK_TYPE_ENTRY = 4,
	STACK_TYPE_EXCEPTION = 5,
	STACK_TYPE_EXCEPTION_LAST = 8,
};

struct stack_info {
	enum stack_type type;
	long unsigned int *begin;
	long unsigned int *end;
	long unsigned int *next_sp;
};

struct stack_frame {
	struct stack_frame *next_frame;
	long unsigned int return_address;
};

struct stack_frame_ia32 {
	u32 next_frame;
	u32 return_address;
};

struct perf_guest_switch_msr {
	unsigned int msr;
	u64 host;
	u64 guest;
};

struct device_attribute {
	struct attribute attr;
	ssize_t (*show)(struct device *, struct device_attribute *, char *);
	ssize_t (*store)(struct device *, struct device_attribute *, const char *, size_t);
};

enum perf_event_x86_regs {
	PERF_REG_X86_AX = 0,
	PERF_REG_X86_BX = 1,
	PERF_REG_X86_CX = 2,
	PERF_REG_X86_DX = 3,
	PERF_REG_X86_SI = 4,
	PERF_REG_X86_DI = 5,
	PERF_REG_X86_BP = 6,
	PERF_REG_X86_SP = 7,
	PERF_REG_X86_IP = 8,
	PERF_REG_X86_FLAGS = 9,
	PERF_REG_X86_CS = 10,
	PERF_REG_X86_SS = 11,
	PERF_REG_X86_DS = 12,
	PERF_REG_X86_ES = 13,
	PERF_REG_X86_FS = 14,
	PERF_REG_X86_GS = 15,
	PERF_REG_X86_R8 = 16,
	PERF_REG_X86_R9 = 17,
	PERF_REG_X86_R10 = 18,
	PERF_REG_X86_R11 = 19,
	PERF_REG_X86_R12 = 20,
	PERF_REG_X86_R13 = 21,
	PERF_REG_X86_R14 = 22,
	PERF_REG_X86_R15 = 23,
	PERF_REG_X86_32_MAX = 16,
	PERF_REG_X86_64_MAX = 24,
	PERF_REG_X86_XMM0 = 32,
	PERF_REG_X86_XMM1 = 34,
	PERF_REG_X86_XMM2 = 36,
	PERF_REG_X86_XMM3 = 38,
	PERF_REG_X86_XMM4 = 40,
	PERF_REG_X86_XMM5 = 42,
	PERF_REG_X86_XMM6 = 44,
	PERF_REG_X86_XMM7 = 46,
	PERF_REG_X86_XMM8 = 48,
	PERF_REG_X86_XMM9 = 50,
	PERF_REG_X86_XMM10 = 52,
	PERF_REG_X86_XMM11 = 54,
	PERF_REG_X86_XMM12 = 56,
	PERF_REG_X86_XMM13 = 58,
	PERF_REG_X86_XMM14 = 60,
	PERF_REG_X86_XMM15 = 62,
	PERF_REG_X86_XMM_MAX = 64,
};

struct perf_callchain_entry_ctx {
	struct perf_callchain_entry *entry;
	u32 max_stack;
	u32 nr;
	short int contexts;
	bool contexts_maxed;
};

struct perf_pmu_events_attr {
	struct device_attribute attr;
	u64 id;
	const char *event_str;
};

struct perf_pmu_events_ht_attr {
	struct device_attribute attr;
	u64 id;
	const char *event_str_ht;
	const char *event_str_noht;
};

enum {
	NMI_LOCAL = 0,
	NMI_UNKNOWN = 1,
	NMI_SERR = 2,
	NMI_IO_CHECK = 3,
	NMI_MAX = 4,
};

typedef int (*nmi_handler_t)(unsigned int, struct pt_regs *);

struct nmiaction {
	struct list_head list;
	nmi_handler_t handler;
	u64 max_duration;
	long unsigned int flags;
	const char *name;
};

struct cyc2ns_data {
	u32 cyc2ns_mul;
	u32 cyc2ns_shift;
	u64 cyc2ns_offset;
};

struct unwind_state {
	struct stack_info stack_info;
	long unsigned int stack_mask;
	struct task_struct *task;
	int graph_idx;
	bool error;
	bool signal;
	bool full_regs;
	long unsigned int sp;
	long unsigned int bp;
	long unsigned int ip;
	struct pt_regs *regs;
	struct pt_regs *prev_regs;
};

enum extra_reg_type {
	EXTRA_REG_NONE = 4294967295,
	EXTRA_REG_RSP_0 = 0,
	EXTRA_REG_RSP_1 = 1,
	EXTRA_REG_LBR = 2,
	EXTRA_REG_LDLAT = 3,
	EXTRA_REG_FE = 4,
	EXTRA_REG_MAX = 5,
};

struct event_constraint {
	union {
		long unsigned int idxmsk[1];
		u64 idxmsk64;
	};
	u64 code;
	u64 cmask;
	int weight;
	int overlap;
	int flags;
	unsigned int size;
};

struct amd_nb {
	int nb_id;
	int refcnt;
	struct perf_event *owners[64];
	struct event_constraint event_constraints[64];
};

struct er_account {
	raw_spinlock_t lock;
	u64 config;
	u64 reg;
	atomic_t ref;
};

struct intel_shared_regs {
	struct er_account regs[5];
	int refcnt;
	unsigned int core_id;
};

enum intel_excl_state_type {
	INTEL_EXCL_UNUSED = 0,
	INTEL_EXCL_SHARED = 1,
	INTEL_EXCL_EXCLUSIVE = 2,
};

struct intel_excl_states {
	enum intel_excl_state_type state[64];
	bool sched_started;
};

struct intel_excl_cntrs {
	raw_spinlock_t lock;
	struct intel_excl_states states[2];
	union {
		u16 has_exclusive[2];
		u32 exclusive_present;
	};
	int refcnt;
	unsigned int core_id;
};

enum {
	X86_PERF_KFREE_SHARED = 0,
	X86_PERF_KFREE_EXCL = 1,
	X86_PERF_KFREE_MAX = 2,
};

struct x86_perf_task_context;

struct cpu_hw_events {
	struct perf_event *events[64];
	long unsigned int active_mask[1];
	long unsigned int running[1];
	int enabled;
	int n_events;
	int n_added;
	int n_txn;
	int assign[64];
	u64 tags[64];
	struct perf_event *event_list[64];
	struct event_constraint *event_constraint[64];
	int n_excl;
	unsigned int txn_flags;
	int is_fake;
	struct debug_store *ds;
	void *ds_pebs_vaddr;
	void *ds_bts_vaddr;
	u64 pebs_enabled;
	int n_pebs;
	int n_large_pebs;
	int n_pebs_via_pt;
	int pebs_output;
	u64 pebs_data_cfg;
	u64 active_pebs_data_cfg;
	int pebs_record_size;
	int lbr_users;
	int lbr_pebs_users;
	struct perf_branch_stack lbr_stack;
	struct perf_branch_entry lbr_entries[32];
	struct er_account *lbr_sel;
	u64 br_sel;
	struct x86_perf_task_context *last_task_ctx;
	int last_log_id;
	u64 intel_ctrl_guest_mask;
	u64 intel_ctrl_host_mask;
	struct perf_guest_switch_msr guest_switch_msrs[64];
	u64 intel_cp_status;
	struct intel_shared_regs *shared_regs;
	struct event_constraint *constraint_list;
	struct intel_excl_cntrs *excl_cntrs;
	int excl_thread_id;
	u64 tfa_shadow;
	struct amd_nb *amd_nb;
	u64 perf_ctr_virt_mask;
	int n_pair;
	void *kfree_on_online[2];
};

struct x86_perf_task_context {
	u64 lbr_from[32];
	u64 lbr_to[32];
	u64 lbr_info[32];
	int tos;
	int valid_lbrs;
	int lbr_callstack_users;
	int lbr_stack_state;
	int log_id;
};

struct extra_reg {
	unsigned int event;
	unsigned int msr;
	u64 config_mask;
	u64 valid_mask;
	int idx;
	bool extra_msr_access;
};

union perf_capabilities {
	struct {
		u64 lbr_format: 6;
		u64 pebs_trap: 1;
		u64 pebs_arch_reg: 1;
		u64 pebs_format: 4;
		u64 smm_freeze: 1;
		u64 full_width_write: 1;
		u64 pebs_baseline: 1;
		u64 pebs_metrics_available: 1;
		u64 pebs_output_pt_available: 1;
	};
	u64 capabilities;
};

struct x86_pmu_quirk {
	struct x86_pmu_quirk *next;
	void (*func)();
};

enum {
	x86_lbr_exclusive_lbr = 0,
	x86_lbr_exclusive_bts = 1,
	x86_lbr_exclusive_pt = 2,
	x86_lbr_exclusive_max = 3,
};

struct x86_pmu {
	const char *name;
	int version;
	int (*handle_irq)(struct pt_regs *);
	void (*disable_all)();
	void (*enable_all)(int);
	void (*enable)(struct perf_event *);
	void (*disable)(struct perf_event *);
	void (*add)(struct perf_event *);
	void (*del)(struct perf_event *);
	void (*read)(struct perf_event *);
	int (*hw_config)(struct perf_event *);
	int (*schedule_events)(struct cpu_hw_events *, int, int *);
	unsigned int eventsel;
	unsigned int perfctr;
	int (*addr_offset)(int, bool);
	int (*rdpmc_index)(int);
	u64 (*event_map)(int);
	int max_events;
	int num_counters;
	int num_counters_fixed;
	int cntval_bits;
	u64 cntval_mask;
	union {
		long unsigned int events_maskl;
		long unsigned int events_mask[1];
	};
	int events_mask_len;
	int apic;
	u64 max_period;
	struct event_constraint * (*get_event_constraints)(struct cpu_hw_events *, int, struct perf_event *);
	void (*put_event_constraints)(struct cpu_hw_events *, struct perf_event *);
	void (*start_scheduling)(struct cpu_hw_events *);
	void (*commit_scheduling)(struct cpu_hw_events *, int, int);
	void (*stop_scheduling)(struct cpu_hw_events *);
	struct event_constraint *event_constraints;
	struct x86_pmu_quirk *quirks;
	int perfctr_second_write;
	u64 (*limit_period)(struct perf_event *, u64);
	unsigned int late_ack: 1;
	unsigned int enabled_ack: 1;
	unsigned int counter_freezing: 1;
	int attr_rdpmc_broken;
	int attr_rdpmc;
	struct attribute **format_attrs;
	ssize_t (*events_sysfs_show)(char *, u64);
	const struct attribute_group **attr_update;
	long unsigned int attr_freeze_on_smi;
	int (*cpu_prepare)(int);
	void (*cpu_starting)(int);
	void (*cpu_dying)(int);
	void (*cpu_dead)(int);
	void (*check_microcode)();
	void (*sched_task)(struct perf_event_context *, bool);
	u64 intel_ctrl;
	union perf_capabilities intel_cap;
	unsigned int bts: 1;
	unsigned int bts_active: 1;
	unsigned int pebs: 1;
	unsigned int pebs_active: 1;
	unsigned int pebs_broken: 1;
	unsigned int pebs_prec_dist: 1;
	unsigned int pebs_no_tlb: 1;
	unsigned int pebs_no_isolation: 1;
	int pebs_record_size;
	int pebs_buffer_size;
	int max_pebs_events;
	void (*drain_pebs)(struct pt_regs *);
	struct event_constraint *pebs_constraints;
	void (*pebs_aliases)(struct perf_event *);
	long unsigned int large_pebs_flags;
	u64 rtm_abort_event;
	long unsigned int lbr_tos;
	long unsigned int lbr_from;
	long unsigned int lbr_to;
	int lbr_nr;
	u64 lbr_sel_mask;
	const int *lbr_sel_map;
	bool lbr_double_abort;
	bool lbr_pt_coexist;
	atomic_t lbr_exclusive[3];
	void (*swap_task_ctx)(struct perf_event_context *, struct perf_event_context *);
	unsigned int amd_nb_constraints: 1;
	u64 perf_ctr_pair_en;
	struct extra_reg *extra_regs;
	unsigned int flags;
	struct perf_guest_switch_msr * (*guest_get_msrs)(int *);
	int (*check_period)(struct perf_event *, u64);
	int (*aux_output_match)(struct perf_event *);
};

struct sched_state {
	int weight;
	int event;
	int counter;
	int unassigned;
	int nr_gp;
	u64 used;
};

struct perf_sched {
	int max_weight;
	int max_events;
	int max_gp;
	int saved_states;
	struct event_constraint **constraints;
	struct sched_state state;
	struct sched_state saved[2];
};

typedef int pao_T__;

typedef int pto_T_____2;

typedef unsigned int pao_T_____2;

enum migratetype {
	MIGRATE_UNMOVABLE = 0,
	MIGRATE_MOVABLE = 1,
	MIGRATE_RECLAIMABLE = 2,
	MIGRATE_PCPTYPES = 3,
	MIGRATE_HIGHATOMIC = 3,
	MIGRATE_TYPES = 4,
};

enum lru_list {
	LRU_INACTIVE_ANON = 0,
	LRU_ACTIVE_ANON = 1,
	LRU_INACTIVE_FILE = 2,
	LRU_ACTIVE_FILE = 3,
	LRU_UNEVICTABLE = 4,
	NR_LRU_LISTS = 5,
};

enum zone_watermarks {
	WMARK_MIN = 0,
	WMARK_LOW = 1,
	WMARK_HIGH = 2,
	NR_WMARK = 3,
};

enum {
	ZONELIST_FALLBACK = 0,
	ZONELIST_NOFALLBACK = 1,
	MAX_ZONELISTS = 2,
};

struct perf_msr {
	u64 msr;
	struct attribute_group *grp;
	bool (*test)(int, void *);
	bool no_check;
};

typedef void (*exitcall_t)();

enum hrtimer_mode {
	HRTIMER_MODE_ABS = 0,
	HRTIMER_MODE_REL = 1,
	HRTIMER_MODE_PINNED = 2,
	HRTIMER_MODE_SOFT = 4,
	HRTIMER_MODE_HARD = 8,
	HRTIMER_MODE_ABS_PINNED = 2,
	HRTIMER_MODE_REL_PINNED = 3,
	HRTIMER_MODE_ABS_SOFT = 4,
	HRTIMER_MODE_REL_SOFT = 5,
	HRTIMER_MODE_ABS_PINNED_SOFT = 6,
	HRTIMER_MODE_REL_PINNED_SOFT = 7,
	HRTIMER_MODE_ABS_HARD = 8,
	HRTIMER_MODE_REL_HARD = 9,
	HRTIMER_MODE_ABS_PINNED_HARD = 10,
	HRTIMER_MODE_REL_PINNED_HARD = 11,
};

struct x86_cpu_id {
	__u16 vendor;
	__u16 family;
	__u16 model;
	__u16 steppings;
	__u16 feature;
	kernel_ulong_t driver_data;
};

enum perf_rapl_events {
	PERF_RAPL_PP0 = 0,
	PERF_RAPL_PKG = 1,
	PERF_RAPL_RAM = 2,
	PERF_RAPL_PP1 = 3,
	PERF_RAPL_PSYS = 4,
	PERF_RAPL_MAX = 5,
	NR_RAPL_DOMAINS = 5,
};

struct rapl_pmu {
	raw_spinlock_t lock;
	int n_active;
	int cpu;
	struct list_head active_list;
	struct pmu *pmu;
	ktime_t timer_interval;
	struct hrtimer hrtimer;
};

struct rapl_pmus {
	struct pmu pmu;
	unsigned int maxdie;
	struct rapl_pmu *pmus[0];
};

struct rapl_model {
	struct perf_msr *rapl_msrs;
	long unsigned int events;
	unsigned int msr_power_unit;
	bool apply_quirk;
};

struct amd_uncore {
	int id;
	int refcnt;
	int cpu;
	int num_counters;
	int rdpmc_base;
	u32 msr_base;
	cpumask_t *active_mask;
	struct pmu *pmu;
	struct perf_event *events[6];
	struct hlist_node node;
};

typedef int pci_power_t;

typedef unsigned int pci_channel_state_t;

typedef short unsigned int pci_dev_flags_t;

struct pci_bus;

struct pci_slot;

struct aer_stats;

struct pci_driver;

struct pcie_link_state;

struct pci_vpd;

struct pci_sriov;

struct pci_dev {
	struct list_head bus_list;
	struct pci_bus *bus;
	struct pci_bus *subordinate;
	void *sysdata;
	struct proc_dir_entry *procent;
	struct pci_slot *slot;
	unsigned int devfn;
	short unsigned int vendor;
	short unsigned int device;
	short unsigned int subsystem_vendor;
	short unsigned int subsystem_device;
	unsigned int class;
	u8 revision;
	u8 hdr_type;
	u16 aer_cap;
	struct aer_stats *aer_stats;
	u8 pcie_cap;
	u8 msi_cap;
	u8 msix_cap;
	u8 pcie_mpss: 3;
	u8 rom_base_reg;
	u8 pin;
	u16 pcie_flags_reg;
	long unsigned int *dma_alias_mask;
	struct pci_driver *driver;
	u64 dma_mask;
	struct device_dma_parameters dma_parms;
	pci_power_t current_state;
	unsigned int imm_ready: 1;
	u8 pm_cap;
	unsigned int pme_support: 5;
	unsigned int pme_poll: 1;
	unsigned int d1_support: 1;
	unsigned int d2_support: 1;
	unsigned int no_d1d2: 1;
	unsigned int no_d3cold: 1;
	unsigned int bridge_d3: 1;
	unsigned int d3cold_allowed: 1;
	unsigned int mmio_always_on: 1;
	unsigned int wakeup_prepared: 1;
	unsigned int runtime_d3cold: 1;
	unsigned int skip_bus_pm: 1;
	unsigned int ignore_hotplug: 1;
	unsigned int hotplug_user_indicators: 1;
	unsigned int clear_retrain_link: 1;
	unsigned int d3_delay;
	unsigned int d3cold_delay;
	struct pcie_link_state *link_state;
	unsigned int ltr_path: 1;
	unsigned int eetlp_prefix_path: 1;
	pci_channel_state_t error_state;
	struct device dev;
	int cfg_size;
	unsigned int irq;
	struct resource resource[11];
	bool match_driver;
	unsigned int transparent: 1;
	unsigned int io_window: 1;
	unsigned int pref_window: 1;
	unsigned int pref_64_window: 1;
	unsigned int multifunction: 1;
	unsigned int is_busmaster: 1;
	unsigned int no_msi: 1;
	unsigned int no_64bit_msi: 1;
	unsigned int block_cfg_access: 1;
	unsigned int broken_parity_status: 1;
	unsigned int irq_reroute_variant: 2;
	unsigned int msi_enabled: 1;
	unsigned int msix_enabled: 1;
	unsigned int ari_enabled: 1;
	unsigned int ats_enabled: 1;
	unsigned int pasid_enabled: 1;
	unsigned int pri_enabled: 1;
	unsigned int is_managed: 1;
	unsigned int needs_freset: 1;
	unsigned int state_saved: 1;
	unsigned int is_physfn: 1;
	unsigned int is_virtfn: 1;
	unsigned int reset_fn: 1;
	unsigned int is_hotplug_bridge: 1;
	unsigned int shpc_managed: 1;
	unsigned int is_thunderbolt: 1;
	unsigned int untrusted: 1;
	unsigned int broken_intx_masking: 1;
	unsigned int io_window_1k: 1;
	unsigned int irq_managed: 1;
	unsigned int non_compliant_bars: 1;
	unsigned int is_probed: 1;
	unsigned int link_active_reporting: 1;
	unsigned int no_vf_scan: 1;
	pci_dev_flags_t dev_flags;
	atomic_t enable_cnt;
	u32 saved_config_space[16];
	struct hlist_head saved_cap_space;
	struct bin_attribute *rom_attr;
	int rom_attr_enabled;
	struct bin_attribute *res_attr[11];
	struct bin_attribute *res_attr_wc[11];
	const struct attribute_group **msi_irq_groups;
	struct pci_vpd *vpd;
	union {
		struct pci_sriov *sriov;
		struct pci_dev *physfn;
	};
	u16 ats_cap;
	u8 ats_stu;
	u16 pri_cap;
	u32 pri_reqs_alloc;
	unsigned int pasid_required: 1;
	u16 pasid_cap;
	u16 pasid_features;
	phys_addr_t rom;
	size_t romlen;
	char *driver_override;
	long unsigned int priv_flags;
};

struct pci_device_id {
	__u32 vendor;
	__u32 device;
	__u32 subvendor;
	__u32 subdevice;
	__u32 class;
	__u32 class_mask;
	kernel_ulong_t driver_data;
};

struct hotplug_slot;

struct pci_slot {
	struct pci_bus *bus;
	struct list_head list;
	struct hotplug_slot *hotplug;
	unsigned char number;
	struct kobject kobj;
};

typedef short unsigned int pci_bus_flags_t;

struct pci_ops;

struct msi_controller;

struct pci_bus {
	struct list_head node;
	struct pci_bus *parent;
	struct list_head children;
	struct list_head devices;
	struct pci_dev *self;
	struct list_head slots;
	struct resource *resource[4];
	struct list_head resources;
	struct resource busn_res;
	struct pci_ops *ops;
	struct msi_controller *msi;
	void *sysdata;
	struct proc_dir_entry *procdir;
	unsigned char number;
	unsigned char primary;
	unsigned char max_bus_speed;
	unsigned char cur_bus_speed;
	char name[48];
	short unsigned int bridge_ctl;
	pci_bus_flags_t bus_flags;
	struct device *bridge;
	struct device dev;
	struct bin_attribute *legacy_io;
	struct bin_attribute *legacy_mem;
	unsigned int is_added: 1;
};

enum {
	PCI_STD_RESOURCES = 0,
	PCI_STD_RESOURCE_END = 5,
	PCI_ROM_RESOURCE = 6,
	PCI_BRIDGE_RESOURCES = 7,
	PCI_BRIDGE_RESOURCE_END = 10,
	PCI_NUM_RESOURCES = 11,
	DEVICE_COUNT_RESOURCE = 11,
};

enum pci_channel_state {
	pci_channel_io_normal = 1,
	pci_channel_io_frozen = 2,
	pci_channel_io_perm_failure = 3,
};

typedef unsigned int pcie_reset_state_t;

struct pci_dynids {
	spinlock_t lock;
	struct list_head list;
};

struct pci_error_handlers;

struct pci_driver {
	struct list_head node;
	const char *name;
	const struct pci_device_id *id_table;
	int (*probe)(struct pci_dev *, const struct pci_device_id *);
	void (*remove)(struct pci_dev *);
	int (*suspend)(struct pci_dev *, pm_message_t);
	int (*resume)(struct pci_dev *);
	void (*shutdown)(struct pci_dev *);
	int (*sriov_configure)(struct pci_dev *, int);
	const struct pci_error_handlers *err_handler;
	const struct attribute_group **groups;
	struct device_driver driver;
	struct pci_dynids dynids;
};

struct pci_ops {
	int (*add_bus)(struct pci_bus *);
	void (*remove_bus)(struct pci_bus *);
	void * (*map_bus)(struct pci_bus *, unsigned int, int);
	int (*read)(struct pci_bus *, unsigned int, int, int, u32 *);
	int (*write)(struct pci_bus *, unsigned int, int, int, u32);
};

typedef unsigned int pci_ers_result_t;

struct pci_error_handlers {
	pci_ers_result_t (*error_detected)(struct pci_dev *, enum pci_channel_state);
	pci_ers_result_t (*mmio_enabled)(struct pci_dev *);
	pci_ers_result_t (*slot_reset)(struct pci_dev *);
	void (*reset_prepare)(struct pci_dev *);
	void (*reset_done)(struct pci_dev *);
	void (*resume)(struct pci_dev *);
};

enum pcie_bus_config_types {
	PCIE_BUS_TUNE_OFF = 0,
	PCIE_BUS_DEFAULT = 1,
	PCIE_BUS_SAFE = 2,
	PCIE_BUS_PERFORMANCE = 3,
	PCIE_BUS_PEER2PEER = 4,
};

struct syscore_ops {
	struct list_head node;
	int (*suspend)();
	void (*resume)();
	void (*shutdown)();
};

enum ibs_states {
	IBS_ENABLED = 0,
	IBS_STARTED = 1,
	IBS_STOPPING = 2,
	IBS_STOPPED = 3,
	IBS_MAX_STATES = 4,
};

struct cpu_perf_ibs {
	struct perf_event *event;
	long unsigned int state[1];
};

struct perf_ibs {
	struct pmu pmu;
	unsigned int msr;
	u64 config_mask;
	u64 cnt_mask;
	u64 enable_mask;
	u64 valid_mask;
	u64 max_period;
	long unsigned int offset_mask[1];
	int offset_max;
	struct cpu_perf_ibs *pcpu;
	struct attribute **format_attrs;
	struct attribute_group format_group;
	const struct attribute_group *attr_groups[2];
	u64 (*get_count)(u64);
};

struct perf_ibs_data {
	u32 size;
	union {
		u32 data[0];
		u32 caps;
	};
	u64 regs[8];
};

struct amd_iommu;

struct perf_amd_iommu {
	struct list_head list;
	struct pmu pmu;
	struct amd_iommu *iommu;
	char name[16];
	u8 max_banks;
	u8 max_counters;
	u64 cntr_assign_mask;
	raw_spinlock_t lock;
};

struct amd_iommu_event_desc {
	struct kobj_attribute attr;
	const char *event;
};

enum perf_msr_id {
	PERF_MSR_TSC = 0,
	PERF_MSR_APERF = 1,
	PERF_MSR_MPERF = 2,
	PERF_MSR_PPERF = 3,
	PERF_MSR_SMI = 4,
	PERF_MSR_PTSC = 5,
	PERF_MSR_IRPERF = 6,
	PERF_MSR_THERM = 7,
	PERF_MSR_EVENT_MAX = 8,
};

struct x86_cpu_desc {
	u8 x86_family;
	u8 x86_vendor;
	u8 x86_model;
	u8 x86_stepping;
	u32 x86_microcode_rev;
};

union cpuid10_eax {
	struct {
		unsigned int version_id: 8;
		unsigned int num_counters: 8;
		unsigned int bit_width: 8;
		unsigned int mask_length: 8;
	} split;
	unsigned int full;
};

union cpuid10_ebx {
	struct {
		unsigned int no_unhalted_core_cycles: 1;
		unsigned int no_instructions_retired: 1;
		unsigned int no_unhalted_reference_cycles: 1;
		unsigned int no_llc_reference: 1;
		unsigned int no_llc_misses: 1;
		unsigned int no_branch_instruction_retired: 1;
		unsigned int no_branch_misses_retired: 1;
	} split;
	unsigned int full;
};

union cpuid10_edx {
	struct {
		unsigned int num_counters_fixed: 5;
		unsigned int bit_width_fixed: 8;
		unsigned int reserved: 19;
	} split;
	unsigned int full;
};

union x86_pmu_config {
	struct {
		u64 event: 8;
		u64 umask: 8;
		u64 usr: 1;
		u64 os: 1;
		u64 edge: 1;
		u64 pc: 1;
		u64 interrupt: 1;
		u64 __reserved1: 1;
		u64 en: 1;
		u64 inv: 1;
		u64 cmask: 8;
		u64 event2: 4;
		u64 __reserved2: 4;
		u64 go: 1;
		u64 ho: 1;
	} bits;
	u64 value;
};

enum pageflags {
	PG_locked = 0,
	PG_referenced = 1,
	PG_uptodate = 2,
	PG_dirty = 3,
	PG_lru = 4,
	PG_active = 5,
	PG_workingset = 6,
	PG_waiters = 7,
	PG_error = 8,
	PG_slab = 9,
	PG_owner_priv_1 = 10,
	PG_arch_1 = 11,
	PG_reserved = 12,
	PG_private = 13,
	PG_private_2 = 14,
	PG_writeback = 15,
	PG_head = 16,
	PG_mappedtodisk = 17,
	PG_reclaim = 18,
	PG_swapbacked = 19,
	PG_unevictable = 20,
	PG_mlocked = 21,
	PG_uncached = 22,
	__NR_PAGEFLAGS = 23,
	PG_checked = 10,
	PG_swapcache = 10,
	PG_fscache = 14,
	PG_pinned = 10,
	PG_savepinned = 3,
	PG_foreign = 10,
	PG_xen_remapped = 10,
	PG_slob_free = 13,
	PG_double_map = 14,
	PG_isolated = 18,
	PG_reported = 2,
};

struct bts_ctx {
	struct perf_output_handle handle;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct debug_store ds_back;
	int state;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum {
	BTS_STATE_STOPPED = 0,
	BTS_STATE_INACTIVE = 1,
	BTS_STATE_ACTIVE = 2,
};

struct bts_phys {
	struct page *page;
	long unsigned int size;
	long unsigned int offset;
	long unsigned int displacement;
};

struct bts_buffer {
	size_t real_size;
	unsigned int nr_pages;
	unsigned int nr_bufs;
	unsigned int cur_buf;
	bool snapshot;
	local_t data_size;
	local_t head;
	long unsigned int end;
	void **data_pages;
	struct bts_phys buf[0];
};

struct pebs_basic {
	u64 format_size;
	u64 ip;
	u64 applicable_counters;
	u64 tsc;
};

struct pebs_meminfo {
	u64 address;
	u64 aux;
	u64 latency;
	u64 tsx_tuning;
};

struct pebs_gprs {
	u64 flags;
	u64 ip;
	u64 ax;
	u64 cx;
	u64 dx;
	u64 bx;
	u64 sp;
	u64 bp;
	u64 si;
	u64 di;
	u64 r8;
	u64 r9;
	u64 r10;
	u64 r11;
	u64 r12;
	u64 r13;
	u64 r14;
	u64 r15;
};

struct pebs_xmm {
	u64 xmm[32];
};

struct pebs_lbr_entry {
	u64 from;
	u64 to;
	u64 info;
};

struct pebs_lbr {
	struct pebs_lbr_entry lbr[0];
};

struct x86_perf_regs {
	struct pt_regs regs;
	u64 *xmm_regs;
};

typedef unsigned int insn_attr_t;

typedef unsigned char insn_byte_t;

typedef int insn_value_t;

struct insn_field {
	union {
		insn_value_t value;
		insn_byte_t bytes[4];
	};
	unsigned char got;
	unsigned char nbytes;
};

struct insn {
	struct insn_field prefixes;
	struct insn_field rex_prefix;
	struct insn_field vex_prefix;
	struct insn_field opcode;
	struct insn_field modrm;
	struct insn_field sib;
	struct insn_field displacement;
	union {
		struct insn_field immediate;
		struct insn_field moffset1;
		struct insn_field immediate1;
	};
	union {
		struct insn_field moffset2;
		struct insn_field immediate2;
	};
	int emulate_prefix_size;
	insn_attr_t attr;
	unsigned char opnd_bytes;
	unsigned char addr_bytes;
	unsigned char length;
	unsigned char x86_64;
	const insn_byte_t *kaddr;
	const insn_byte_t *end_kaddr;
	const insn_byte_t *next_byte;
};

enum {
	PERF_TXN_ELISION = 1,
	PERF_TXN_TRANSACTION = 2,
	PERF_TXN_SYNC = 4,
	PERF_TXN_ASYNC = 8,
	PERF_TXN_RETRY = 16,
	PERF_TXN_CONFLICT = 32,
	PERF_TXN_CAPACITY_WRITE = 64,
	PERF_TXN_CAPACITY_READ = 128,
	PERF_TXN_MAX = 256,
	PERF_TXN_ABORT_MASK = 0,
	PERF_TXN_ABORT_SHIFT = 32,
};

struct perf_event_header {
	__u32 type;
	__u16 misc;
	__u16 size;
};

union intel_x86_pebs_dse {
	u64 val;
	struct {
		unsigned int ld_dse: 4;
		unsigned int ld_stlb_miss: 1;
		unsigned int ld_locked: 1;
		unsigned int ld_reserved: 26;
	};
	struct {
		unsigned int st_l1d_hit: 1;
		unsigned int st_reserved1: 3;
		unsigned int st_stlb_miss: 1;
		unsigned int st_locked: 1;
		unsigned int st_reserved2: 26;
	};
};

struct pebs_record_core {
	u64 flags;
	u64 ip;
	u64 ax;
	u64 bx;
	u64 cx;
	u64 dx;
	u64 si;
	u64 di;
	u64 bp;
	u64 sp;
	u64 r8;
	u64 r9;
	u64 r10;
	u64 r11;
	u64 r12;
	u64 r13;
	u64 r14;
	u64 r15;
};

struct pebs_record_nhm {
	u64 flags;
	u64 ip;
	u64 ax;
	u64 bx;
	u64 cx;
	u64 dx;
	u64 si;
	u64 di;
	u64 bp;
	u64 sp;
	u64 r8;
	u64 r9;
	u64 r10;
	u64 r11;
	u64 r12;
	u64 r13;
	u64 r14;
	u64 r15;
	u64 status;
	u64 dla;
	u64 dse;
	u64 lat;
};

union hsw_tsx_tuning {
	struct {
		u32 cycles_last_block: 32;
		u32 hle_abort: 1;
		u32 rtm_abort: 1;
		u32 instruction_abort: 1;
		u32 non_instruction_abort: 1;
		u32 retry: 1;
		u32 data_conflict: 1;
		u32 capacity_writes: 1;
		u32 capacity_reads: 1;
	};
	u64 value;
};

struct pebs_record_skl {
	u64 flags;
	u64 ip;
	u64 ax;
	u64 bx;
	u64 cx;
	u64 dx;
	u64 si;
	u64 di;
	u64 bp;
	u64 sp;
	u64 r8;
	u64 r9;
	u64 r10;
	u64 r11;
	u64 r12;
	u64 r13;
	u64 r14;
	u64 r15;
	u64 status;
	u64 dla;
	u64 dse;
	u64 lat;
	u64 real_ip;
	u64 tsx_tuning;
	u64 tsc;
};

struct bts_record {
	u64 from;
	u64 to;
	u64 flags;
};

enum {
	PERF_BR_UNKNOWN = 0,
	PERF_BR_COND = 1,
	PERF_BR_UNCOND = 2,
	PERF_BR_IND = 3,
	PERF_BR_CALL = 4,
	PERF_BR_IND_CALL = 5,
	PERF_BR_RET = 6,
	PERF_BR_SYSCALL = 7,
	PERF_BR_SYSRET = 8,
	PERF_BR_COND_CALL = 9,
	PERF_BR_COND_RET = 10,
	PERF_BR_MAX = 11,
};

enum {
	LBR_FORMAT_32 = 0,
	LBR_FORMAT_LIP = 1,
	LBR_FORMAT_EIP = 2,
	LBR_FORMAT_EIP_FLAGS = 3,
	LBR_FORMAT_EIP_FLAGS2 = 4,
	LBR_FORMAT_INFO = 5,
	LBR_FORMAT_TIME = 6,
	LBR_FORMAT_MAX_KNOWN = 6,
};

enum {
	X86_BR_NONE = 0,
	X86_BR_USER = 1,
	X86_BR_KERNEL = 2,
	X86_BR_CALL = 4,
	X86_BR_RET = 8,
	X86_BR_SYSCALL = 16,
	X86_BR_SYSRET = 32,
	X86_BR_INT = 64,
	X86_BR_IRET = 128,
	X86_BR_JCC = 256,
	X86_BR_JMP = 512,
	X86_BR_IRQ = 1024,
	X86_BR_IND_CALL = 2048,
	X86_BR_ABORT = 4096,
	X86_BR_IN_TX = 8192,
	X86_BR_NO_TX = 16384,
	X86_BR_ZERO_CALL = 32768,
	X86_BR_CALL_STACK = 65536,
	X86_BR_IND_JMP = 131072,
	X86_BR_TYPE_SAVE = 262144,
};

enum {
	LBR_NONE = 0,
	LBR_VALID = 1,
};

enum P4_EVENTS {
	P4_EVENT_TC_DELIVER_MODE = 0,
	P4_EVENT_BPU_FETCH_REQUEST = 1,
	P4_EVENT_ITLB_REFERENCE = 2,
	P4_EVENT_MEMORY_CANCEL = 3,
	P4_EVENT_MEMORY_COMPLETE = 4,
	P4_EVENT_LOAD_PORT_REPLAY = 5,
	P4_EVENT_STORE_PORT_REPLAY = 6,
	P4_EVENT_MOB_LOAD_REPLAY = 7,
	P4_EVENT_PAGE_WALK_TYPE = 8,
	P4_EVENT_BSQ_CACHE_REFERENCE = 9,
	P4_EVENT_IOQ_ALLOCATION = 10,
	P4_EVENT_IOQ_ACTIVE_ENTRIES = 11,
	P4_EVENT_FSB_DATA_ACTIVITY = 12,
	P4_EVENT_BSQ_ALLOCATION = 13,
	P4_EVENT_BSQ_ACTIVE_ENTRIES = 14,
	P4_EVENT_SSE_INPUT_ASSIST = 15,
	P4_EVENT_PACKED_SP_UOP = 16,
	P4_EVENT_PACKED_DP_UOP = 17,
	P4_EVENT_SCALAR_SP_UOP = 18,
	P4_EVENT_SCALAR_DP_UOP = 19,
	P4_EVENT_64BIT_MMX_UOP = 20,
	P4_EVENT_128BIT_MMX_UOP = 21,
	P4_EVENT_X87_FP_UOP = 22,
	P4_EVENT_TC_MISC = 23,
	P4_EVENT_GLOBAL_POWER_EVENTS = 24,
	P4_EVENT_TC_MS_XFER = 25,
	P4_EVENT_UOP_QUEUE_WRITES = 26,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE = 27,
	P4_EVENT_RETIRED_BRANCH_TYPE = 28,
	P4_EVENT_RESOURCE_STALL = 29,
	P4_EVENT_WC_BUFFER = 30,
	P4_EVENT_B2B_CYCLES = 31,
	P4_EVENT_BNR = 32,
	P4_EVENT_SNOOP = 33,
	P4_EVENT_RESPONSE = 34,
	P4_EVENT_FRONT_END_EVENT = 35,
	P4_EVENT_EXECUTION_EVENT = 36,
	P4_EVENT_REPLAY_EVENT = 37,
	P4_EVENT_INSTR_RETIRED = 38,
	P4_EVENT_UOPS_RETIRED = 39,
	P4_EVENT_UOP_TYPE = 40,
	P4_EVENT_BRANCH_RETIRED = 41,
	P4_EVENT_MISPRED_BRANCH_RETIRED = 42,
	P4_EVENT_X87_ASSIST = 43,
	P4_EVENT_MACHINE_CLEAR = 44,
	P4_EVENT_INSTR_COMPLETED = 45,
};

enum P4_EVENT_OPCODES {
	P4_EVENT_TC_DELIVER_MODE_OPCODE = 257,
	P4_EVENT_BPU_FETCH_REQUEST_OPCODE = 768,
	P4_EVENT_ITLB_REFERENCE_OPCODE = 6147,
	P4_EVENT_MEMORY_CANCEL_OPCODE = 517,
	P4_EVENT_MEMORY_COMPLETE_OPCODE = 2050,
	P4_EVENT_LOAD_PORT_REPLAY_OPCODE = 1026,
	P4_EVENT_STORE_PORT_REPLAY_OPCODE = 1282,
	P4_EVENT_MOB_LOAD_REPLAY_OPCODE = 770,
	P4_EVENT_PAGE_WALK_TYPE_OPCODE = 260,
	P4_EVENT_BSQ_CACHE_REFERENCE_OPCODE = 3079,
	P4_EVENT_IOQ_ALLOCATION_OPCODE = 774,
	P4_EVENT_IOQ_ACTIVE_ENTRIES_OPCODE = 6662,
	P4_EVENT_FSB_DATA_ACTIVITY_OPCODE = 5894,
	P4_EVENT_BSQ_ALLOCATION_OPCODE = 1287,
	P4_EVENT_BSQ_ACTIVE_ENTRIES_OPCODE = 1543,
	P4_EVENT_SSE_INPUT_ASSIST_OPCODE = 13313,
	P4_EVENT_PACKED_SP_UOP_OPCODE = 2049,
	P4_EVENT_PACKED_DP_UOP_OPCODE = 3073,
	P4_EVENT_SCALAR_SP_UOP_OPCODE = 2561,
	P4_EVENT_SCALAR_DP_UOP_OPCODE = 3585,
	P4_EVENT_64BIT_MMX_UOP_OPCODE = 513,
	P4_EVENT_128BIT_MMX_UOP_OPCODE = 6657,
	P4_EVENT_X87_FP_UOP_OPCODE = 1025,
	P4_EVENT_TC_MISC_OPCODE = 1537,
	P4_EVENT_GLOBAL_POWER_EVENTS_OPCODE = 4870,
	P4_EVENT_TC_MS_XFER_OPCODE = 1280,
	P4_EVENT_UOP_QUEUE_WRITES_OPCODE = 2304,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE_OPCODE = 1282,
	P4_EVENT_RETIRED_BRANCH_TYPE_OPCODE = 1026,
	P4_EVENT_RESOURCE_STALL_OPCODE = 257,
	P4_EVENT_WC_BUFFER_OPCODE = 1285,
	P4_EVENT_B2B_CYCLES_OPCODE = 5635,
	P4_EVENT_BNR_OPCODE = 2051,
	P4_EVENT_SNOOP_OPCODE = 1539,
	P4_EVENT_RESPONSE_OPCODE = 1027,
	P4_EVENT_FRONT_END_EVENT_OPCODE = 2053,
	P4_EVENT_EXECUTION_EVENT_OPCODE = 3077,
	P4_EVENT_REPLAY_EVENT_OPCODE = 2309,
	P4_EVENT_INSTR_RETIRED_OPCODE = 516,
	P4_EVENT_UOPS_RETIRED_OPCODE = 260,
	P4_EVENT_UOP_TYPE_OPCODE = 514,
	P4_EVENT_BRANCH_RETIRED_OPCODE = 1541,
	P4_EVENT_MISPRED_BRANCH_RETIRED_OPCODE = 772,
	P4_EVENT_X87_ASSIST_OPCODE = 773,
	P4_EVENT_MACHINE_CLEAR_OPCODE = 517,
	P4_EVENT_INSTR_COMPLETED_OPCODE = 1796,
};

enum P4_ESCR_EMASKS {
	P4_EVENT_TC_DELIVER_MODE__DD = 512,
	P4_EVENT_TC_DELIVER_MODE__DB = 1024,
	P4_EVENT_TC_DELIVER_MODE__DI = 2048,
	P4_EVENT_TC_DELIVER_MODE__BD = 4096,
	P4_EVENT_TC_DELIVER_MODE__BB = 8192,
	P4_EVENT_TC_DELIVER_MODE__BI = 16384,
	P4_EVENT_TC_DELIVER_MODE__ID = 32768,
	P4_EVENT_BPU_FETCH_REQUEST__TCMISS = 512,
	P4_EVENT_ITLB_REFERENCE__HIT = 512,
	P4_EVENT_ITLB_REFERENCE__MISS = 1024,
	P4_EVENT_ITLB_REFERENCE__HIT_UK = 2048,
	P4_EVENT_MEMORY_CANCEL__ST_RB_FULL = 2048,
	P4_EVENT_MEMORY_CANCEL__64K_CONF = 4096,
	P4_EVENT_MEMORY_COMPLETE__LSC = 512,
	P4_EVENT_MEMORY_COMPLETE__SSC = 1024,
	P4_EVENT_LOAD_PORT_REPLAY__SPLIT_LD = 1024,
	P4_EVENT_STORE_PORT_REPLAY__SPLIT_ST = 1024,
	P4_EVENT_MOB_LOAD_REPLAY__NO_STA = 1024,
	P4_EVENT_MOB_LOAD_REPLAY__NO_STD = 4096,
	P4_EVENT_MOB_LOAD_REPLAY__PARTIAL_DATA = 8192,
	P4_EVENT_MOB_LOAD_REPLAY__UNALGN_ADDR = 16384,
	P4_EVENT_PAGE_WALK_TYPE__DTMISS = 512,
	P4_EVENT_PAGE_WALK_TYPE__ITMISS = 1024,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_2ndL_HITS = 512,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_2ndL_HITE = 1024,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_2ndL_HITM = 2048,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_3rdL_HITS = 4096,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_3rdL_HITE = 8192,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_3rdL_HITM = 16384,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_2ndL_MISS = 131072,
	P4_EVENT_BSQ_CACHE_REFERENCE__RD_3rdL_MISS = 262144,
	P4_EVENT_BSQ_CACHE_REFERENCE__WR_2ndL_MISS = 524288,
	P4_EVENT_IOQ_ALLOCATION__DEFAULT = 512,
	P4_EVENT_IOQ_ALLOCATION__ALL_READ = 16384,
	P4_EVENT_IOQ_ALLOCATION__ALL_WRITE = 32768,
	P4_EVENT_IOQ_ALLOCATION__MEM_UC = 65536,
	P4_EVENT_IOQ_ALLOCATION__MEM_WC = 131072,
	P4_EVENT_IOQ_ALLOCATION__MEM_WT = 262144,
	P4_EVENT_IOQ_ALLOCATION__MEM_WP = 524288,
	P4_EVENT_IOQ_ALLOCATION__MEM_WB = 1048576,
	P4_EVENT_IOQ_ALLOCATION__OWN = 4194304,
	P4_EVENT_IOQ_ALLOCATION__OTHER = 8388608,
	P4_EVENT_IOQ_ALLOCATION__PREFETCH = 16777216,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__DEFAULT = 512,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__ALL_READ = 16384,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__ALL_WRITE = 32768,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__MEM_UC = 65536,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__MEM_WC = 131072,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__MEM_WT = 262144,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__MEM_WP = 524288,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__MEM_WB = 1048576,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__OWN = 4194304,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__OTHER = 8388608,
	P4_EVENT_IOQ_ACTIVE_ENTRIES__PREFETCH = 16777216,
	P4_EVENT_FSB_DATA_ACTIVITY__DRDY_DRV = 512,
	P4_EVENT_FSB_DATA_ACTIVITY__DRDY_OWN = 1024,
	P4_EVENT_FSB_DATA_ACTIVITY__DRDY_OTHER = 2048,
	P4_EVENT_FSB_DATA_ACTIVITY__DBSY_DRV = 4096,
	P4_EVENT_FSB_DATA_ACTIVITY__DBSY_OWN = 8192,
	P4_EVENT_FSB_DATA_ACTIVITY__DBSY_OTHER = 16384,
	P4_EVENT_BSQ_ALLOCATION__REQ_TYPE0 = 512,
	P4_EVENT_BSQ_ALLOCATION__REQ_TYPE1 = 1024,
	P4_EVENT_BSQ_ALLOCATION__REQ_LEN0 = 2048,
	P4_EVENT_BSQ_ALLOCATION__REQ_LEN1 = 4096,
	P4_EVENT_BSQ_ALLOCATION__REQ_IO_TYPE = 16384,
	P4_EVENT_BSQ_ALLOCATION__REQ_LOCK_TYPE = 32768,
	P4_EVENT_BSQ_ALLOCATION__REQ_CACHE_TYPE = 65536,
	P4_EVENT_BSQ_ALLOCATION__REQ_SPLIT_TYPE = 131072,
	P4_EVENT_BSQ_ALLOCATION__REQ_DEM_TYPE = 262144,
	P4_EVENT_BSQ_ALLOCATION__REQ_ORD_TYPE = 524288,
	P4_EVENT_BSQ_ALLOCATION__MEM_TYPE0 = 1048576,
	P4_EVENT_BSQ_ALLOCATION__MEM_TYPE1 = 2097152,
	P4_EVENT_BSQ_ALLOCATION__MEM_TYPE2 = 4194304,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_TYPE0 = 512,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_TYPE1 = 1024,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_LEN0 = 2048,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_LEN1 = 4096,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_IO_TYPE = 16384,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_LOCK_TYPE = 32768,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_CACHE_TYPE = 65536,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_SPLIT_TYPE = 131072,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_DEM_TYPE = 262144,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__REQ_ORD_TYPE = 524288,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__MEM_TYPE0 = 1048576,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__MEM_TYPE1 = 2097152,
	P4_EVENT_BSQ_ACTIVE_ENTRIES__MEM_TYPE2 = 4194304,
	P4_EVENT_SSE_INPUT_ASSIST__ALL = 16777216,
	P4_EVENT_PACKED_SP_UOP__ALL = 16777216,
	P4_EVENT_PACKED_DP_UOP__ALL = 16777216,
	P4_EVENT_SCALAR_SP_UOP__ALL = 16777216,
	P4_EVENT_SCALAR_DP_UOP__ALL = 16777216,
	P4_EVENT_64BIT_MMX_UOP__ALL = 16777216,
	P4_EVENT_128BIT_MMX_UOP__ALL = 16777216,
	P4_EVENT_X87_FP_UOP__ALL = 16777216,
	P4_EVENT_TC_MISC__FLUSH = 8192,
	P4_EVENT_GLOBAL_POWER_EVENTS__RUNNING = 512,
	P4_EVENT_TC_MS_XFER__CISC = 512,
	P4_EVENT_UOP_QUEUE_WRITES__FROM_TC_BUILD = 512,
	P4_EVENT_UOP_QUEUE_WRITES__FROM_TC_DELIVER = 1024,
	P4_EVENT_UOP_QUEUE_WRITES__FROM_ROM = 2048,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE__CONDITIONAL = 1024,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE__CALL = 2048,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE__RETURN = 4096,
	P4_EVENT_RETIRED_MISPRED_BRANCH_TYPE__INDIRECT = 8192,
	P4_EVENT_RETIRED_BRANCH_TYPE__CONDITIONAL = 1024,
	P4_EVENT_RETIRED_BRANCH_TYPE__CALL = 2048,
	P4_EVENT_RETIRED_BRANCH_TYPE__RETURN = 4096,
	P4_EVENT_RETIRED_BRANCH_TYPE__INDIRECT = 8192,
	P4_EVENT_RESOURCE_STALL__SBFULL = 16384,
	P4_EVENT_WC_BUFFER__WCB_EVICTS = 512,
	P4_EVENT_WC_BUFFER__WCB_FULL_EVICTS = 1024,
	P4_EVENT_FRONT_END_EVENT__NBOGUS = 512,
	P4_EVENT_FRONT_END_EVENT__BOGUS = 1024,
	P4_EVENT_EXECUTION_EVENT__NBOGUS0 = 512,
	P4_EVENT_EXECUTION_EVENT__NBOGUS1 = 1024,
	P4_EVENT_EXECUTION_EVENT__NBOGUS2 = 2048,
	P4_EVENT_EXECUTION_EVENT__NBOGUS3 = 4096,
	P4_EVENT_EXECUTION_EVENT__BOGUS0 = 8192,
	P4_EVENT_EXECUTION_EVENT__BOGUS1 = 16384,
	P4_EVENT_EXECUTION_EVENT__BOGUS2 = 32768,
	P4_EVENT_EXECUTION_EVENT__BOGUS3 = 65536,
	P4_EVENT_REPLAY_EVENT__NBOGUS = 512,
	P4_EVENT_REPLAY_EVENT__BOGUS = 1024,
	P4_EVENT_INSTR_RETIRED__NBOGUSNTAG = 512,
	P4_EVENT_INSTR_RETIRED__NBOGUSTAG = 1024,
	P4_EVENT_INSTR_RETIRED__BOGUSNTAG = 2048,
	P4_EVENT_INSTR_RETIRED__BOGUSTAG = 4096,
	P4_EVENT_UOPS_RETIRED__NBOGUS = 512,
	P4_EVENT_UOPS_RETIRED__BOGUS = 1024,
	P4_EVENT_UOP_TYPE__TAGLOADS = 1024,
	P4_EVENT_UOP_TYPE__TAGSTORES = 2048,
	P4_EVENT_BRANCH_RETIRED__MMNP = 512,
	P4_EVENT_BRANCH_RETIRED__MMNM = 1024,
	P4_EVENT_BRANCH_RETIRED__MMTP = 2048,
	P4_EVENT_BRANCH_RETIRED__MMTM = 4096,
	P4_EVENT_MISPRED_BRANCH_RETIRED__NBOGUS = 512,
	P4_EVENT_X87_ASSIST__FPSU = 512,
	P4_EVENT_X87_ASSIST__FPSO = 1024,
	P4_EVENT_X87_ASSIST__POAO = 2048,
	P4_EVENT_X87_ASSIST__POAU = 4096,
	P4_EVENT_X87_ASSIST__PREA = 8192,
	P4_EVENT_MACHINE_CLEAR__CLEAR = 512,
	P4_EVENT_MACHINE_CLEAR__MOCLEAR = 1024,
	P4_EVENT_MACHINE_CLEAR__SMCLEAR = 2048,
	P4_EVENT_INSTR_COMPLETED__NBOGUS = 512,
	P4_EVENT_INSTR_COMPLETED__BOGUS = 1024,
};

enum P4_PEBS_METRIC {
	P4_PEBS_METRIC__none = 0,
	P4_PEBS_METRIC__1stl_cache_load_miss_retired = 1,
	P4_PEBS_METRIC__2ndl_cache_load_miss_retired = 2,
	P4_PEBS_METRIC__dtlb_load_miss_retired = 3,
	P4_PEBS_METRIC__dtlb_store_miss_retired = 4,
	P4_PEBS_METRIC__dtlb_all_miss_retired = 5,
	P4_PEBS_METRIC__tagged_mispred_branch = 6,
	P4_PEBS_METRIC__mob_load_replay_retired = 7,
	P4_PEBS_METRIC__split_load_retired = 8,
	P4_PEBS_METRIC__split_store_retired = 9,
	P4_PEBS_METRIC__max = 10,
};

struct p4_event_bind {
	unsigned int opcode;
	unsigned int escr_msr[2];
	unsigned int escr_emask;
	unsigned int shared;
	char cntr[6];
};

struct p4_pebs_bind {
	unsigned int metric_pebs;
	unsigned int metric_vert;
};

struct p4_event_alias {
	u64 original;
	u64 alternative;
};

enum cpuid_regs_idx {
	CPUID_EAX = 0,
	CPUID_EBX = 1,
	CPUID_ECX = 2,
	CPUID_EDX = 3,
};

struct dev_ext_attribute {
	struct device_attribute attr;
	void *var;
};

enum pt_capabilities {
	PT_CAP_max_subleaf = 0,
	PT_CAP_cr3_filtering = 1,
	PT_CAP_psb_cyc = 2,
	PT_CAP_ip_filtering = 3,
	PT_CAP_mtc = 4,
	PT_CAP_ptwrite = 5,
	PT_CAP_power_event_trace = 6,
	PT_CAP_topa_output = 7,
	PT_CAP_topa_multiple_entries = 8,
	PT_CAP_single_range_output = 9,
	PT_CAP_output_subsys = 10,
	PT_CAP_payloads_lip = 11,
	PT_CAP_num_address_ranges = 12,
	PT_CAP_mtc_periods = 13,
	PT_CAP_cycle_thresholds = 14,
	PT_CAP_psb_periods = 15,
};

enum perf_addr_filter_action_t {
	PERF_ADDR_FILTER_ACTION_STOP = 0,
	PERF_ADDR_FILTER_ACTION_START = 1,
	PERF_ADDR_FILTER_ACTION_FILTER = 2,
};

struct perf_addr_filter {
	struct list_head entry;
	struct path path;
	long unsigned int offset;
	long unsigned int size;
	enum perf_addr_filter_action_t action;
};

struct topa_entry {
	u64 end: 1;
	u64 rsvd0: 1;
	u64 intr: 1;
	u64 rsvd1: 1;
	u64 stop: 1;
	u64 rsvd2: 1;
	u64 size: 4;
	u64 rsvd3: 2;
	u64 base: 36;
	u64 rsvd4: 16;
};

struct pt_pmu {
	struct pmu pmu;
	u32 caps[8];
	bool vmx;
	bool branch_en_always_on;
	long unsigned int max_nonturbo_ratio;
	unsigned int tsc_art_num;
	unsigned int tsc_art_den;
};

struct topa;

struct pt_buffer {
	struct list_head tables;
	struct topa *first;
	struct topa *last;
	struct topa *cur;
	unsigned int cur_idx;
	size_t output_off;
	long unsigned int nr_pages;
	local_t data_size;
	local64_t head;
	bool snapshot;
	bool single;
	long int stop_pos;
	long int intr_pos;
	struct topa_entry *stop_te;
	struct topa_entry *intr_te;
	void **data_pages;
};

struct topa {
	struct list_head list;
	u64 offset;
	size_t size;
	int last;
	unsigned int z_count;
};

struct pt_filter {
	long unsigned int msr_a;
	long unsigned int msr_b;
	long unsigned int config;
};

struct pt_filters {
	struct pt_filter filter[4];
	unsigned int nr_filters;
};

struct pt {
	struct perf_output_handle handle;
	struct pt_filters filters;
	int handle_nmi;
	int vmx_on;
	u64 output_base;
	u64 output_mask;
};

struct pt_cap_desc {
	const char *name;
	u32 leaf;
	u8 reg;
	u32 mask;
};

struct pt_address_range {
	long unsigned int msr_a;
	long unsigned int msr_b;
	unsigned int reg_off;
};

struct topa_page {
	struct topa_entry table[507];
	struct topa topa;
};

struct acpi_device;

struct pci_sysdata {
	int domain;
	int node;
	struct acpi_device *companion;
	void *iommu;
	void *fwnode;
};

struct pci_extra_dev {
	struct pci_dev *dev[4];
};

struct intel_uncore_pmu;

struct intel_uncore_ops;

struct uncore_event_desc;

struct freerunning_counters;

struct intel_uncore_type {
	const char *name;
	int num_counters;
	int num_boxes;
	int perf_ctr_bits;
	int fixed_ctr_bits;
	int num_freerunning_types;
	unsigned int perf_ctr;
	unsigned int event_ctl;
	unsigned int event_mask;
	unsigned int event_mask_ext;
	unsigned int fixed_ctr;
	unsigned int fixed_ctl;
	unsigned int box_ctl;
	union {
		unsigned int msr_offset;
		unsigned int mmio_offset;
	};
	unsigned int num_shared_regs: 8;
	unsigned int single_fixed: 1;
	unsigned int pair_ctr_ctl: 1;
	unsigned int *msr_offsets;
	struct event_constraint unconstrainted;
	struct event_constraint *constraints;
	struct intel_uncore_pmu *pmus;
	struct intel_uncore_ops *ops;
	struct uncore_event_desc *event_descs;
	struct freerunning_counters *freerunning;
	const struct attribute_group *attr_groups[4];
	struct pmu *pmu;
};

struct intel_uncore_box;

struct intel_uncore_pmu {
	struct pmu pmu;
	char name[32];
	int pmu_idx;
	int func_id;
	bool registered;
	atomic_t activeboxes;
	struct intel_uncore_type *type;
	struct intel_uncore_box **boxes;
};

struct intel_uncore_ops {
	void (*init_box)(struct intel_uncore_box *);
	void (*exit_box)(struct intel_uncore_box *);
	void (*disable_box)(struct intel_uncore_box *);
	void (*enable_box)(struct intel_uncore_box *);
	void (*disable_event)(struct intel_uncore_box *, struct perf_event *);
	void (*enable_event)(struct intel_uncore_box *, struct perf_event *);
	u64 (*read_counter)(struct intel_uncore_box *, struct perf_event *);
	int (*hw_config)(struct intel_uncore_box *, struct perf_event *);
	struct event_constraint * (*get_constraint)(struct intel_uncore_box *, struct perf_event *);
	void (*put_constraint)(struct intel_uncore_box *, struct perf_event *);
};

struct uncore_event_desc {
	struct kobj_attribute attr;
	const char *config;
};

struct freerunning_counters {
	unsigned int counter_base;
	unsigned int counter_offset;
	unsigned int box_offset;
	unsigned int num_counters;
	unsigned int bits;
	unsigned int *box_offsets;
};

struct intel_uncore_extra_reg {
	raw_spinlock_t lock;
	u64 config;
	u64 config1;
	u64 config2;
	atomic_t ref;
};

struct intel_uncore_box {
	int pci_phys_id;
	int dieid;
	int n_active;
	int n_events;
	int cpu;
	long unsigned int flags;
	atomic_t refcnt;
	struct perf_event *events[10];
	struct perf_event *event_list[10];
	struct event_constraint *event_constraint[10];
	long unsigned int active_mask[1];
	u64 tags[10];
	struct pci_dev *pci_dev;
	struct intel_uncore_pmu *pmu;
	u64 hrtimer_duration;
	struct hrtimer hrtimer;
	struct list_head list;
	struct list_head active_list;
	void *io_addr;
	struct intel_uncore_extra_reg shared_regs[0];
};

struct pci2phy_map {
	struct list_head list;
	int segment;
	int pbus_to_physid[256];
};

struct intel_uncore_init_fun {
	void (*cpu_init)();
	int (*pci_init)();
	void (*mmio_init)();
};

enum {
	EXTRA_REG_NHMEX_M_FILTER = 0,
	EXTRA_REG_NHMEX_M_DSP = 1,
	EXTRA_REG_NHMEX_M_ISS = 2,
	EXTRA_REG_NHMEX_M_MAP = 3,
	EXTRA_REG_NHMEX_M_MSC_THR = 4,
	EXTRA_REG_NHMEX_M_PGT = 5,
	EXTRA_REG_NHMEX_M_PLD = 6,
	EXTRA_REG_NHMEX_M_ZDP_CTL_FVC = 7,
};

enum {
	SNB_PCI_UNCORE_IMC = 0,
};

enum perf_snb_uncore_imc_freerunning_types {
	SNB_PCI_UNCORE_IMC_DATA = 0,
	SNB_PCI_UNCORE_IMC_FREERUNNING_TYPE_MAX = 1,
};

struct imc_uncore_pci_dev {
	__u32 pci_id;
	struct pci_driver *driver;
};

enum perf_tgl_uncore_imc_freerunning_types {
	TGL_MMIO_UNCORE_IMC_DATA_TOTAL = 0,
	TGL_MMIO_UNCORE_IMC_DATA_READ = 1,
	TGL_MMIO_UNCORE_IMC_DATA_WRITE = 2,
	TGL_MMIO_UNCORE_IMC_FREERUNNING_TYPE_MAX = 3,
};

enum {
	SNBEP_PCI_QPI_PORT0_FILTER = 0,
	SNBEP_PCI_QPI_PORT1_FILTER = 1,
	BDX_PCI_QPI_PORT2_FILTER = 2,
	HSWEP_PCI_PCU_3 = 3,
};

enum {
	SNBEP_PCI_UNCORE_HA = 0,
	SNBEP_PCI_UNCORE_IMC = 1,
	SNBEP_PCI_UNCORE_QPI = 2,
	SNBEP_PCI_UNCORE_R2PCIE = 3,
	SNBEP_PCI_UNCORE_R3QPI = 4,
};

enum {
	IVBEP_PCI_UNCORE_HA = 0,
	IVBEP_PCI_UNCORE_IMC = 1,
	IVBEP_PCI_UNCORE_IRP = 2,
	IVBEP_PCI_UNCORE_QPI = 3,
	IVBEP_PCI_UNCORE_R2PCIE = 4,
	IVBEP_PCI_UNCORE_R3QPI = 5,
};

enum {
	KNL_PCI_UNCORE_MC_UCLK = 0,
	KNL_PCI_UNCORE_MC_DCLK = 1,
	KNL_PCI_UNCORE_EDC_UCLK = 2,
	KNL_PCI_UNCORE_EDC_ECLK = 3,
	KNL_PCI_UNCORE_M2PCIE = 4,
	KNL_PCI_UNCORE_IRP = 5,
};

enum {
	HSWEP_PCI_UNCORE_HA = 0,
	HSWEP_PCI_UNCORE_IMC = 1,
	HSWEP_PCI_UNCORE_IRP = 2,
	HSWEP_PCI_UNCORE_QPI = 3,
	HSWEP_PCI_UNCORE_R2PCIE = 4,
	HSWEP_PCI_UNCORE_R3QPI = 5,
};

enum {
	BDX_PCI_UNCORE_HA = 0,
	BDX_PCI_UNCORE_IMC = 1,
	BDX_PCI_UNCORE_IRP = 2,
	BDX_PCI_UNCORE_QPI = 3,
	BDX_PCI_UNCORE_R2PCIE = 4,
	BDX_PCI_UNCORE_R3QPI = 5,
};

enum perf_uncore_iio_freerunning_type_id {
	SKX_IIO_MSR_IOCLK = 0,
	SKX_IIO_MSR_BW = 1,
	SKX_IIO_MSR_UTIL = 2,
	SKX_IIO_FREERUNNING_TYPE_MAX = 3,
};

enum {
	SKX_PCI_UNCORE_IMC = 0,
	SKX_PCI_UNCORE_M2M = 1,
	SKX_PCI_UNCORE_UPI = 2,
	SKX_PCI_UNCORE_M2PCIE = 3,
	SKX_PCI_UNCORE_M3UPI = 4,
};

enum perf_uncore_snr_iio_freerunning_type_id {
	SNR_IIO_MSR_IOCLK = 0,
	SNR_IIO_MSR_BW_IN = 1,
	SNR_IIO_FREERUNNING_TYPE_MAX = 2,
};

enum {
	SNR_PCI_UNCORE_M2M = 0,
};

enum perf_uncore_snr_imc_freerunning_type_id {
	SNR_IMC_DCLK = 0,
	SNR_IMC_DDR = 1,
	SNR_IMC_FREERUNNING_TYPE_MAX = 2,
};

enum perf_uncore_icx_iio_freerunning_type_id {
	ICX_IIO_MSR_IOCLK = 0,
	ICX_IIO_MSR_BW_IN = 1,
	ICX_IIO_FREERUNNING_TYPE_MAX = 2,
};

enum {
	ICX_PCI_UNCORE_M2M = 0,
	ICX_PCI_UNCORE_UPI = 1,
	ICX_PCI_UNCORE_M3UPI = 2,
};

enum perf_uncore_icx_imc_freerunning_type_id {
	ICX_IMC_DCLK = 0,
	ICX_IMC_DDR = 1,
	ICX_IMC_DDRT = 2,
	ICX_IMC_FREERUNNING_TYPE_MAX = 3,
};

struct cstate_model {
	long unsigned int core_events;
	long unsigned int pkg_events;
	long unsigned int quirks;
};

enum perf_cstate_core_events {
	PERF_CSTATE_CORE_C1_RES = 0,
	PERF_CSTATE_CORE_C3_RES = 1,
	PERF_CSTATE_CORE_C6_RES = 2,
	PERF_CSTATE_CORE_C7_RES = 3,
	PERF_CSTATE_CORE_EVENT_MAX = 4,
};

enum perf_cstate_pkg_events {
	PERF_CSTATE_PKG_C2_RES = 0,
	PERF_CSTATE_PKG_C3_RES = 1,
	PERF_CSTATE_PKG_C6_RES = 2,
	PERF_CSTATE_PKG_C7_RES = 3,
	PERF_CSTATE_PKG_C8_RES = 4,
	PERF_CSTATE_PKG_C9_RES = 5,
	PERF_CSTATE_PKG_C10_RES = 6,
	PERF_CSTATE_PKG_EVENT_MAX = 7,
};

struct real_mode_header {
	u32 text_start;
	u32 ro_end;
	u32 trampoline_start;
	u32 trampoline_header;
	u32 trampoline_pgd;
	u32 wakeup_start;
	u32 wakeup_header;
	u32 machine_real_restart_asm;
	u32 machine_real_restart_seg;
};

struct trampoline_header {
	u64 start;
	u64 efer;
	u32 cr4;
	u32 flags;
};

enum xfeature {
	XFEATURE_FP = 0,
	XFEATURE_SSE = 1,
	XFEATURE_YMM = 2,
	XFEATURE_BNDREGS = 3,
	XFEATURE_BNDCSR = 4,
	XFEATURE_OPMASK = 5,
	XFEATURE_ZMM_Hi256 = 6,
	XFEATURE_Hi16_ZMM = 7,
	XFEATURE_PT_UNIMPLEMENTED_SO_FAR = 8,
	XFEATURE_PKRU = 9,
	XFEATURE_MAX = 10,
};

struct pkru_state {
	u32 pkru;
	u32 pad;
};

enum show_regs_mode {
	SHOW_REGS_SHORT = 0,
	SHOW_REGS_USER = 1,
	SHOW_REGS_ALL = 2,
};

struct shared_info;

struct start_info;

enum which_selector {
	FS = 0,
	GS = 1,
};

typedef struct task_struct *pto_T_____3;

typedef u64 pto_T_____4;

struct sigcontext_64 {
	__u64 r8;
	__u64 r9;
	__u64 r10;
	__u64 r11;
	__u64 r12;
	__u64 r13;
	__u64 r14;
	__u64 r15;
	__u64 di;
	__u64 si;
	__u64 bp;
	__u64 bx;
	__u64 dx;
	__u64 ax;
	__u64 cx;
	__u64 sp;
	__u64 ip;
	__u64 flags;
	__u16 cs;
	__u16 gs;
	__u16 fs;
	__u16 ss;
	__u64 err;
	__u64 trapno;
	__u64 oldmask;
	__u64 cr2;
	__u64 fpstate;
	__u64 reserved1[8];
};

struct sigaltstack {
	void *ss_sp;
	int ss_flags;
	size_t ss_size;
};

typedef struct sigaltstack stack_t;

struct siginfo {
	union {
		struct {
			int si_signo;
			int si_errno;
			int si_code;
			union __sifields _sifields;
		};
		int _si_pad[32];
	};
};

struct ucontext {
	long unsigned int uc_flags;
	struct ucontext *uc_link;
	stack_t uc_stack;
	struct sigcontext_64 uc_mcontext;
	sigset_t uc_sigmask;
};

typedef u32 compat_sigset_word;

typedef struct {
	compat_sigset_word sig[2];
} compat_sigset_t;

struct mce {
	__u64 status;
	__u64 misc;
	__u64 addr;
	__u64 mcgstatus;
	__u64 ip;
	__u64 tsc;
	__u64 time;
	__u8 cpuvendor;
	__u8 inject_flags;
	__u8 severity;
	__u8 pad;
	__u32 cpuid;
	__u8 cs;
	__u8 bank;
	__u8 cpu;
	__u8 finished;
	__u32 extcpu;
	__u32 socketid;
	__u32 apicid;
	__u64 mcgcap;
	__u64 synd;
	__u64 ipid;
	__u64 ppin;
	__u32 microcode;
	__u64 kflags;
};

typedef long unsigned int mce_banks_t[1];

struct smca_hwid {
	unsigned int bank_type;
	u32 hwid_mcatype;
	u32 xec_bitmap;
	u8 count;
};

struct smca_bank {
	struct smca_hwid *hwid;
	u32 id;
	u8 sysfs_id;
};

struct kernel_vm86_regs {
	struct pt_regs pt;
	short unsigned int es;
	short unsigned int __esh;
	short unsigned int ds;
	short unsigned int __dsh;
	short unsigned int fs;
	short unsigned int __fsh;
	short unsigned int gs;
	short unsigned int __gsh;
};

struct rt_sigframe {
	char *pretcode;
	struct ucontext uc;
	struct siginfo info;
};

typedef struct siginfo siginfo_t;

typedef s32 compat_clock_t;

typedef s32 compat_pid_t;

typedef s32 compat_timer_t;

typedef s32 compat_int_t;

typedef u32 __compat_uid32_t;

union compat_sigval {
	compat_int_t sival_int;
	compat_uptr_t sival_ptr;
};

typedef union compat_sigval compat_sigval_t;

struct compat_siginfo {
	int si_signo;
	int si_errno;
	int si_code;
	union {
		int _pad[29];
		struct {
			compat_pid_t _pid;
			__compat_uid32_t _uid;
		} _kill;
		struct {
			compat_timer_t _tid;
			int _overrun;
			compat_sigval_t _sigval;
		} _timer;
		struct {
			compat_pid_t _pid;
			__compat_uid32_t _uid;
			compat_sigval_t _sigval;
		} _rt;
		struct {
			compat_pid_t _pid;
			__compat_uid32_t _uid;
			int _status;
			compat_clock_t _utime;
			compat_clock_t _stime;
		} _sigchld;
		struct {
			compat_uptr_t _addr;
			union {
				short int _addr_lsb;
				struct {
					char _dummy_bnd[4];
					compat_uptr_t _lower;
					compat_uptr_t _upper;
				} _addr_bnd;
				struct {
					char _dummy_pkey[4];
					u32 _pkey;
				} _addr_pkey;
			};
		} _sigfault;
		struct {
			compat_long_t _band;
			int _fd;
		} _sigpoll;
		struct {
			compat_uptr_t _call_addr;
			int _syscall;
			unsigned int _arch;
		} _sigsys;
	} _sifields;
};

typedef struct compat_siginfo compat_siginfo_t;

enum bug_trap_type {
	BUG_TRAP_TYPE_NONE = 0,
	BUG_TRAP_TYPE_WARN = 1,
	BUG_TRAP_TYPE_BUG = 2,
};

enum die_val {
	DIE_OOPS = 1,
	DIE_INT3 = 2,
	DIE_DEBUG = 3,
	DIE_PANIC = 4,
	DIE_NMI = 5,
	DIE_DIE = 6,
	DIE_KERNELDEBUG = 7,
	DIE_TRAP = 8,
	DIE_GPF = 9,
	DIE_CALL = 10,
	DIE_PAGE_FAULT = 11,
	DIE_NMIUNKNOWN = 12,
};

enum kernel_gp_hint {
	GP_NO_HINT = 0,
	GP_NON_CANONICAL = 1,
	GP_CANONICAL = 2,
};

struct bad_iret_stack {
	void *error_entry_ret;
	struct pt_regs regs;
};

enum {
	GATE_INTERRUPT = 14,
	GATE_TRAP = 15,
	GATE_CALL = 12,
	GATE_TASK = 5,
};

struct idt_bits {
	u16 ist: 3;
	u16 zero: 5;
	u16 type: 5;
	u16 dpl: 2;
	u16 p: 1;
};

struct gate_struct {
	u16 offset_low;
	u16 segment;
	struct idt_bits bits;
	u16 offset_middle;
	u32 offset_high;
	u32 reserved;
};

typedef struct gate_struct gate_desc;

struct idt_data {
	unsigned int vector;
	unsigned int segment;
	struct idt_bits bits;
	const void *addr;
};

enum irqreturn {
	IRQ_NONE = 0,
	IRQ_HANDLED = 1,
	IRQ_WAKE_THREAD = 2,
};

typedef enum irqreturn irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

struct irqaction {
	irq_handler_t handler;
	void *dev_id;
	void *percpu_dev_id;
	struct irqaction *next;
	irq_handler_t thread_fn;
	struct task_struct *thread;
	struct irqaction *secondary;
	unsigned int irq;
	unsigned int flags;
	long unsigned int thread_flags;
	long unsigned int thread_mask;
	const char *name;
	struct proc_dir_entry *dir;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct irq_affinity_notify {
	unsigned int irq;
	struct kref kref;
	struct work_struct work;
	void (*notify)(struct irq_affinity_notify *, const cpumask_t *);
	void (*release)(struct kref *);
};

enum irqchip_irq_state {
	IRQCHIP_STATE_PENDING = 0,
	IRQCHIP_STATE_ACTIVE = 1,
	IRQCHIP_STATE_MASKED = 2,
	IRQCHIP_STATE_LINE_LEVEL = 3,
};

struct irq_desc___2;

typedef void (*irq_flow_handler_t)(struct irq_desc___2 *);

struct msi_desc;

struct irq_common_data {
	unsigned int state_use_accessors;
	unsigned int node;
	void *handler_data;
	struct msi_desc *msi_desc;
	cpumask_var_t affinity;
	cpumask_var_t effective_affinity;
};

struct irq_chip;

struct irq_data {
	u32 mask;
	unsigned int irq;
	long unsigned int hwirq;
	struct irq_common_data *common;
	struct irq_chip *chip;
	struct irq_domain *domain;
	struct irq_data *parent_data;
	void *chip_data;
};

struct irq_desc___2 {
	struct irq_common_data irq_common_data;
	struct irq_data irq_data;
	unsigned int *kstat_irqs;
	irq_flow_handler_t handle_irq;
	struct irqaction *action;
	unsigned int status_use_accessors;
	unsigned int core_internal_state__do_not_mess_with_it;
	unsigned int depth;
	unsigned int wake_depth;
	unsigned int tot_count;
	unsigned int irq_count;
	long unsigned int last_unhandled;
	unsigned int irqs_unhandled;
	atomic_t threads_handled;
	int threads_handled_last;
	raw_spinlock_t lock;
	struct cpumask *percpu_enabled;
	const struct cpumask *percpu_affinity;
	const struct cpumask *affinity_hint;
	struct irq_affinity_notify *affinity_notify;
	cpumask_var_t pending_mask;
	long unsigned int threads_oneshot;
	atomic_t threads_active;
	wait_queue_head_t wait_for_threads;
	unsigned int nr_actions;
	unsigned int no_suspend_depth;
	unsigned int cond_suspend_depth;
	unsigned int force_resume_depth;
	struct proc_dir_entry *dir;
	struct callback_head rcu;
	struct kobject kobj;
	struct mutex request_mutex;
	int parent_irq;
	struct module *owner;
	const char *name;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct msi_msg;

struct irq_chip {
	struct device *parent_device;
	const char *name;
	unsigned int (*irq_startup)(struct irq_data *);
	void (*irq_shutdown)(struct irq_data *);
	void (*irq_enable)(struct irq_data *);
	void (*irq_disable)(struct irq_data *);
	void (*irq_ack)(struct irq_data *);
	void (*irq_mask)(struct irq_data *);
	void (*irq_mask_ack)(struct irq_data *);
	void (*irq_unmask)(struct irq_data *);
	void (*irq_eoi)(struct irq_data *);
	int (*irq_set_affinity)(struct irq_data *, const struct cpumask *, bool);
	int (*irq_retrigger)(struct irq_data *);
	int (*irq_set_type)(struct irq_data *, unsigned int);
	int (*irq_set_wake)(struct irq_data *, unsigned int);
	void (*irq_bus_lock)(struct irq_data *);
	void (*irq_bus_sync_unlock)(struct irq_data *);
	void (*irq_cpu_online)(struct irq_data *);
	void (*irq_cpu_offline)(struct irq_data *);
	void (*irq_suspend)(struct irq_data *);
	void (*irq_resume)(struct irq_data *);
	void (*irq_pm_shutdown)(struct irq_data *);
	void (*irq_calc_mask)(struct irq_data *);
	void (*irq_print_chip)(struct irq_data *, struct seq_file *);
	int (*irq_request_resources)(struct irq_data *);
	void (*irq_release_resources)(struct irq_data *);
	void (*irq_compose_msi_msg)(struct irq_data *, struct msi_msg *);
	void (*irq_write_msi_msg)(struct irq_data *, struct msi_msg *);
	int (*irq_get_irqchip_state)(struct irq_data *, enum irqchip_irq_state, bool *);
	int (*irq_set_irqchip_state)(struct irq_data *, enum irqchip_irq_state, bool);
	int (*irq_set_vcpu_affinity)(struct irq_data *, void *);
	void (*ipi_send_single)(struct irq_data *, unsigned int);
	void (*ipi_send_mask)(struct irq_data *, const struct cpumask *);
	int (*irq_nmi_setup)(struct irq_data *);
	void (*irq_nmi_teardown)(struct irq_data *);
	long unsigned int flags;
};

typedef struct irq_desc___2 *vector_irq_t___2[256];

struct trace_event_raw_x86_irq_vector {
	struct trace_entry ent;
	int vector;
	char __data[0];
};

struct trace_event_raw_vector_config {
	struct trace_entry ent;
	unsigned int irq;
	unsigned int vector;
	unsigned int cpu;
	unsigned int apicdest;
	char __data[0];
};

struct trace_event_raw_vector_mod {
	struct trace_entry ent;
	unsigned int irq;
	unsigned int vector;
	unsigned int cpu;
	unsigned int prev_vector;
	unsigned int prev_cpu;
	char __data[0];
};

struct trace_event_raw_vector_reserve {
	struct trace_entry ent;
	unsigned int irq;
	int ret;
	char __data[0];
};

struct trace_event_raw_vector_alloc {
	struct trace_entry ent;
	unsigned int irq;
	unsigned int vector;
	bool reserved;
	int ret;
	char __data[0];
};

struct trace_event_raw_vector_alloc_managed {
	struct trace_entry ent;
	unsigned int irq;
	unsigned int vector;
	int ret;
	char __data[0];
};

struct trace_event_raw_vector_activate {
	struct trace_entry ent;
	unsigned int irq;
	bool is_managed;
	bool can_reserve;
	bool reserve;
	char __data[0];
};

struct trace_event_raw_vector_teardown {
	struct trace_entry ent;
	unsigned int irq;
	bool is_managed;
	bool has_reserved;
	char __data[0];
};

struct trace_event_raw_vector_setup {
	struct trace_entry ent;
	unsigned int irq;
	bool is_legacy;
	int ret;
	char __data[0];
};

struct trace_event_raw_vector_free_moved {
	struct trace_entry ent;
	unsigned int irq;
	unsigned int cpu;
	unsigned int vector;
	bool is_managed;
	char __data[0];
};

struct trace_event_data_offsets_x86_irq_vector {};

struct trace_event_data_offsets_vector_config {};

struct trace_event_data_offsets_vector_mod {};

struct trace_event_data_offsets_vector_reserve {};

struct trace_event_data_offsets_vector_alloc {};

struct trace_event_data_offsets_vector_alloc_managed {};

struct trace_event_data_offsets_vector_activate {};

struct trace_event_data_offsets_vector_teardown {};

struct trace_event_data_offsets_vector_setup {};

struct trace_event_data_offsets_vector_free_moved {};

typedef void (*btf_trace_local_timer_entry)(void *, int);

typedef void (*btf_trace_local_timer_exit)(void *, int);

typedef void (*btf_trace_spurious_apic_entry)(void *, int);

typedef void (*btf_trace_spurious_apic_exit)(void *, int);

typedef void (*btf_trace_error_apic_entry)(void *, int);

typedef void (*btf_trace_error_apic_exit)(void *, int);

typedef void (*btf_trace_x86_platform_ipi_entry)(void *, int);

typedef void (*btf_trace_x86_platform_ipi_exit)(void *, int);

typedef void (*btf_trace_irq_work_entry)(void *, int);

typedef void (*btf_trace_irq_work_exit)(void *, int);

typedef void (*btf_trace_reschedule_entry)(void *, int);

typedef void (*btf_trace_reschedule_exit)(void *, int);

typedef void (*btf_trace_call_function_entry)(void *, int);

typedef void (*btf_trace_call_function_exit)(void *, int);

typedef void (*btf_trace_call_function_single_entry)(void *, int);

typedef void (*btf_trace_call_function_single_exit)(void *, int);

typedef void (*btf_trace_threshold_apic_entry)(void *, int);

typedef void (*btf_trace_threshold_apic_exit)(void *, int);

typedef void (*btf_trace_deferred_error_apic_entry)(void *, int);

typedef void (*btf_trace_deferred_error_apic_exit)(void *, int);

typedef void (*btf_trace_thermal_apic_entry)(void *, int);

typedef void (*btf_trace_thermal_apic_exit)(void *, int);

typedef void (*btf_trace_vector_config)(void *, unsigned int, unsigned int, unsigned int, unsigned int);

typedef void (*btf_trace_vector_update)(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

typedef void (*btf_trace_vector_clear)(void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

typedef void (*btf_trace_vector_reserve_managed)(void *, unsigned int, int);

typedef void (*btf_trace_vector_reserve)(void *, unsigned int, int);

typedef void (*btf_trace_vector_alloc)(void *, unsigned int, unsigned int, bool, int);

typedef void (*btf_trace_vector_alloc_managed)(void *, unsigned int, unsigned int, int);

typedef void (*btf_trace_vector_activate)(void *, unsigned int, bool, bool, bool);

typedef void (*btf_trace_vector_deactivate)(void *, unsigned int, bool, bool, bool);

typedef void (*btf_trace_vector_teardown)(void *, unsigned int, bool, bool);

typedef void (*btf_trace_vector_setup)(void *, unsigned int, bool, int);

typedef void (*btf_trace_vector_free_moved)(void *, unsigned int, unsigned int, unsigned int, bool);

typedef struct irq_desc___2 *pto_T_____5;

typedef struct pt_regs *pto_T_____6;

struct estack_pages {
	u32 offs;
	u16 size;
	u16 type;
};

struct clocksource {
	u64 (*read)(struct clocksource *);
	u64 mask;
	u32 mult;
	u32 shift;
	u64 max_idle_ns;
	u32 maxadj;
	u64 max_cycles;
	const char *name;
	struct list_head list;
	int rating;
	enum vdso_clock_mode vdso_clock_mode;
	long unsigned int flags;
	int (*enable)(struct clocksource *);
	void (*disable)(struct clocksource *);
	void (*suspend)(struct clocksource *);
	void (*resume)(struct clocksource *);
	void (*mark_unstable)(struct clocksource *);
	void (*tick_stable)(struct clocksource *);
	struct list_head wd_list;
	u64 cs_last;
	u64 wd_last;
	struct module *owner;
};

enum clock_event_state {
	CLOCK_EVT_STATE_DETACHED = 0,
	CLOCK_EVT_STATE_SHUTDOWN = 1,
	CLOCK_EVT_STATE_PERIODIC = 2,
	CLOCK_EVT_STATE_ONESHOT = 3,
	CLOCK_EVT_STATE_ONESHOT_STOPPED = 4,
};

struct clock_event_device {
	void (*event_handler)(struct clock_event_device *);
	int (*set_next_event)(long unsigned int, struct clock_event_device *);
	int (*set_next_ktime)(ktime_t, struct clock_event_device *);
	ktime_t next_event;
	u64 max_delta_ns;
	u64 min_delta_ns;
	u32 mult;
	u32 shift;
	enum clock_event_state state_use_accessors;
	unsigned int features;
	long unsigned int retries;
	int (*set_state_periodic)(struct clock_event_device *);
	int (*set_state_oneshot)(struct clock_event_device *);
	int (*set_state_oneshot_stopped)(struct clock_event_device *);
	int (*set_state_shutdown)(struct clock_event_device *);
	int (*tick_resume)(struct clock_event_device *);
	void (*broadcast)(const struct cpumask *);
	void (*suspend)(struct clock_event_device *);
	void (*resume)(struct clock_event_device *);
	long unsigned int min_delta_ticks;
	long unsigned int max_delta_ticks;
	const char *name;
	int rating;
	int irq;
	int bound_on;
	const struct cpumask *cpumask;
	struct list_head list;
	struct module *owner;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct irq_affinity_desc {
	struct cpumask mask;
	unsigned int is_managed: 1;
};

struct msi_msg {
	u32 address_lo;
	u32 address_hi;
	u32 data;
};

struct platform_msi_priv_data;

struct platform_msi_desc {
	struct platform_msi_priv_data *msi_priv_data;
	u16 msi_index;
};

struct fsl_mc_msi_desc {
	u16 msi_index;
};

struct ti_sci_inta_msi_desc {
	u16 dev_index;
};

struct msi_desc {
	struct list_head list;
	unsigned int irq;
	unsigned int nvec_used;
	struct device *dev;
	struct msi_msg msg;
	struct irq_affinity_desc *affinity;
	const void *iommu_cookie;
	void (*write_msi_msg)(struct msi_desc *, void *);
	void *write_msi_msg_data;
	union {
		struct {
			u32 masked;
			struct {
				u8 is_msix: 1;
				u8 multiple: 3;
				u8 multi_cap: 3;
				u8 maskbit: 1;
				u8 is_64: 1;
				u8 is_virtual: 1;
				u16 entry_nr;
				unsigned int default_irq;
			} msi_attrib;
			union {
				u8 mask_pos;
				void *mask_base;
			};
		};
		struct platform_msi_desc platform;
		struct fsl_mc_msi_desc fsl_mc;
		struct ti_sci_inta_msi_desc inta;
	};
};

struct irq_chip_regs {
	long unsigned int enable;
	long unsigned int disable;
	long unsigned int mask;
	long unsigned int ack;
	long unsigned int eoi;
	long unsigned int type;
	long unsigned int polarity;
};

struct irq_chip_type {
	struct irq_chip chip;
	struct irq_chip_regs regs;
	irq_flow_handler_t handler;
	u32 type;
	u32 mask_cache_priv;
	u32 *mask_cache;
};

struct irq_chip_generic {
	raw_spinlock_t lock;
	void *reg_base;
	u32 (*reg_readl)(void *);
	void (*reg_writel)(u32, void *);
	void (*suspend)(struct irq_chip_generic *);
	void (*resume)(struct irq_chip_generic *);
	unsigned int irq_base;
	unsigned int irq_cnt;
	u32 mask_cache;
	u32 type_cache;
	u32 polarity_cache;
	u32 wake_enabled;
	u32 wake_active;
	unsigned int num_ct;
	void *private;
	long unsigned int installed;
	long unsigned int unused;
	struct irq_domain *domain;
	struct list_head list;
	struct irq_chip_type chip_types[0];
};

enum irq_gc_flags {
	IRQ_GC_INIT_MASK_CACHE = 1,
	IRQ_GC_INIT_NESTED_LOCK = 2,
	IRQ_GC_MASK_CACHE_PER_TYPE = 4,
	IRQ_GC_NO_MASK = 8,
	IRQ_GC_BE_IO = 16,
};

struct irq_domain_chip_generic {
	unsigned int irqs_per_chip;
	unsigned int num_chips;
	unsigned int irq_flags_to_clear;
	unsigned int irq_flags_to_set;
	enum irq_gc_flags gc_flags;
	struct irq_chip_generic *gc[0];
};

struct legacy_pic {
	int nr_legacy_irqs;
	struct irq_chip *chip;
	void (*mask)(unsigned int);
	void (*unmask)(unsigned int);
	void (*mask_all)();
	void (*restore_mask)();
	void (*init)(int);
	int (*probe)();
	int (*irq_pending)(unsigned int);
	void (*make_irq)(unsigned int);
};

enum refcount_saturation_type {
	REFCOUNT_ADD_NOT_ZERO_OVF = 0,
	REFCOUNT_ADD_OVF = 1,
	REFCOUNT_ADD_UAF = 2,
	REFCOUNT_SUB_UAF = 3,
	REFCOUNT_DEC_LEAK = 4,
};

enum lockdown_reason {
	LOCKDOWN_NONE = 0,
	LOCKDOWN_MODULE_SIGNATURE = 1,
	LOCKDOWN_DEV_MEM = 2,
	LOCKDOWN_EFI_TEST = 3,
	LOCKDOWN_KEXEC = 4,
	LOCKDOWN_HIBERNATION = 5,
	LOCKDOWN_PCI_ACCESS = 6,
	LOCKDOWN_IOPORT = 7,
	LOCKDOWN_MSR = 8,
	LOCKDOWN_ACPI_TABLES = 9,
	LOCKDOWN_PCMCIA_CIS = 10,
	LOCKDOWN_TIOCSSERIAL = 11,
	LOCKDOWN_MODULE_PARAMETERS = 12,
	LOCKDOWN_MMIOTRACE = 13,
	LOCKDOWN_DEBUGFS = 14,
	LOCKDOWN_XMON_WR = 15,
	LOCKDOWN_INTEGRITY_MAX = 16,
	LOCKDOWN_KCORE = 17,
	LOCKDOWN_KPROBES = 18,
	LOCKDOWN_BPF_READ = 19,
	LOCKDOWN_PERF = 20,
	LOCKDOWN_TRACEFS = 21,
	LOCKDOWN_XMON_RW = 22,
	LOCKDOWN_CONFIDENTIALITY_MAX = 23,
};

enum lockdep_ok {
	LOCKDEP_STILL_OK = 0,
	LOCKDEP_NOW_UNRELIABLE = 1,
};

typedef long unsigned int uintptr_t;

struct machine_ops {
	void (*restart)(char *);
	void (*halt)();
	void (*power_off)();
	void (*shutdown)();
	void (*crash_shutdown)(struct pt_regs *);
	void (*emergency_restart)();
};

struct trace_event_raw_nmi_handler {
	struct trace_entry ent;
	void *handler;
	s64 delta_ns;
	int handled;
	char __data[0];
};

struct trace_event_data_offsets_nmi_handler {};

typedef void (*btf_trace_nmi_handler)(void *, void *, s64, int);

struct nmi_desc {
	raw_spinlock_t lock;
	struct list_head head;
};

struct nmi_stats {
	unsigned int normal;
	unsigned int unknown;
	unsigned int external;
	unsigned int swallow;
};

enum nmi_states {
	NMI_NOT_RUNNING = 0,
	NMI_EXECUTING = 1,
	NMI_LATCHED = 2,
};

typedef enum nmi_states pto_T_____7;

typedef bool pto_T_____8;

enum {
	DESC_TSS = 9,
	DESC_LDT = 2,
	DESCTYPE_S = 16,
};

struct ldttss_desc {
	u16 limit0;
	u16 base0;
	u16 base1: 8;
	u16 type: 5;
	u16 dpl: 2;
	u16 p: 1;
	u16 limit1: 4;
	u16 zero0: 3;
	u16 g: 1;
	u16 base2: 8;
	u32 base3;
	u32 zero1;
};

typedef struct ldttss_desc ldt_desc;

struct user_desc {
	unsigned int entry_number;
	unsigned int base_addr;
	unsigned int limit;
	unsigned int seg_32bit: 1;
	unsigned int contents: 2;
	unsigned int read_exec_only: 1;
	unsigned int limit_in_pages: 1;
	unsigned int seg_not_present: 1;
	unsigned int useable: 1;
	unsigned int lm: 1;
};

struct mmu_gather_batch {
	struct mmu_gather_batch *next;
	unsigned int nr;
	unsigned int max;
	struct page *pages[0];
};

struct mmu_gather {
	struct mm_struct *mm;
	long unsigned int start;
	long unsigned int end;
	unsigned int fullmm: 1;
	unsigned int need_flush_all: 1;
	unsigned int freed_tables: 1;
	unsigned int cleared_ptes: 1;
	unsigned int cleared_pmds: 1;
	unsigned int cleared_puds: 1;
	unsigned int cleared_p4ds: 1;
	unsigned int vma_exec: 1;
	unsigned int vma_huge: 1;
	unsigned int batch_count;
	struct mmu_gather_batch *active;
	struct mmu_gather_batch local;
	struct page *__pages[8];
};

struct hvm_start_info {
	uint32_t magic;
	uint32_t version;
	uint32_t flags;
	uint32_t nr_modules;
	uint64_t modlist_paddr;
	uint64_t cmdline_paddr;
	uint64_t rsdp_paddr;
	uint64_t memmap_paddr;
	uint32_t memmap_entries;
	uint32_t reserved;
};

struct setup_data {
	__u64 next;
	__u32 type;
	__u32 len;
	__u8 data[0];
};

struct setup_indirect {
	__u32 type;
	__u32 reserved;
	__u64 len;
	__u64 addr;
};

enum efi_secureboot_mode {
	efi_secureboot_mode_unset = 0,
	efi_secureboot_mode_unknown = 1,
	efi_secureboot_mode_disabled = 2,
	efi_secureboot_mode_enabled = 3,
};

struct acpi_table_ibft {
	struct acpi_table_header header;
	u8 reserved[12];
};

struct hstate {
	int next_nid_to_alloc;
	int next_nid_to_free;
	unsigned int order;
	long unsigned int mask;
	long unsigned int max_huge_pages;
	long unsigned int nr_huge_pages;
	long unsigned int free_huge_pages;
	long unsigned int resv_huge_pages;
	long unsigned int surplus_huge_pages;
	long unsigned int nr_overcommit_huge_pages;
	struct list_head hugepage_activelist;
	struct list_head hugepage_freelists[64];
	unsigned int nr_huge_pages_node[64];
	unsigned int free_huge_pages_node[64];
	unsigned int surplus_huge_pages_node[64];
	char name[32];
};

enum xen_domain_type {
	XEN_NATIVE = 0,
	XEN_PV_DOMAIN = 1,
	XEN_HVM_DOMAIN = 2,
};

struct efi_scratch {
	u64 phys_stack;
	struct mm_struct *prev_mm;
};

struct msi_controller {
	struct module *owner;
	struct device *dev;
	struct device_node *of_node;
	struct list_head list;
	int (*setup_irq)(struct msi_controller *, struct pci_dev *, struct msi_desc *);
	int (*setup_irqs)(struct msi_controller *, struct pci_dev *, int, int);
	void (*teardown_irq)(struct msi_controller *, unsigned int);
};

struct pci_raw_ops {
	int (*read)(unsigned int, unsigned int, unsigned int, int, int, u32 *);
	int (*write)(unsigned int, unsigned int, unsigned int, int, int, u32);
};

struct clock_event_device___2;

enum jump_label_type {
	JUMP_LABEL_NOP = 0,
	JUMP_LABEL_JMP = 1,
};

union text_poke_insn {
	u8 text[5];
	struct {
		u8 opcode;
		s32 disp;
	} __attribute__((packed));
};

enum {
	JL_STATE_START = 0,
	JL_STATE_NO_UPDATE = 1,
	JL_STATE_UPDATE = 2,
};

typedef short unsigned int __kernel_old_uid_t;

typedef short unsigned int __kernel_old_gid_t;

typedef struct {
	int val[2];
} __kernel_fsid_t;

typedef __kernel_old_uid_t old_uid_t;

typedef __kernel_old_gid_t old_gid_t;

struct kernel_clone_args {
	u64 flags;
	int *pidfd;
	int *child_tid;
	int *parent_tid;
	int exit_signal;
	long unsigned int stack;
	long unsigned int stack_size;
	long unsigned int tls;
	pid_t *set_tid;
	size_t set_tid_size;
	int cgroup;
	struct cgroup *cgrp;
	struct css_set *cset;
};

struct kstatfs {
	long int f_type;
	long int f_bsize;
	u64 f_blocks;
	u64 f_bfree;
	u64 f_bavail;
	u64 f_files;
	u64 f_ffree;
	__kernel_fsid_t f_fsid;
	long int f_namelen;
	long int f_frsize;
	long int f_flags;
	long int f_spare[4];
};

struct stat64 {
	long long unsigned int st_dev;
	unsigned char __pad0[4];
	unsigned int __st_ino;
	unsigned int st_mode;
	unsigned int st_nlink;
	unsigned int st_uid;
	unsigned int st_gid;
	long long unsigned int st_rdev;
	unsigned char __pad3[4];
	long long int st_size;
	unsigned int st_blksize;
	long long int st_blocks;
	unsigned int st_atime;
	unsigned int st_atime_nsec;
	unsigned int st_mtime;
	unsigned int st_mtime_nsec;
	unsigned int st_ctime;
	unsigned int st_ctime_nsec;
	long long unsigned int st_ino;
} __attribute__((packed));

struct mmap_arg_struct32 {
	unsigned int addr;
	unsigned int len;
	unsigned int prot;
	unsigned int flags;
	unsigned int fd;
	unsigned int offset;
};

struct vm_unmapped_area_info {
	long unsigned int flags;
	long unsigned int length;
	long unsigned int low_limit;
	long unsigned int high_limit;
	long unsigned int align_mask;
	long unsigned int align_offset;
};

enum align_flags {
	ALIGN_VA_32 = 1,
	ALIGN_VA_64 = 2,
};

enum {
	MEMREMAP_WB = 1,
	MEMREMAP_WT = 2,
	MEMREMAP_WC = 4,
	MEMREMAP_ENC = 8,
	MEMREMAP_DEC = 16,
};

enum {
	IORES_DESC_NONE = 0,
	IORES_DESC_CRASH_KERNEL = 1,
	IORES_DESC_ACPI_TABLES = 2,
	IORES_DESC_ACPI_NV_STORAGE = 3,
	IORES_DESC_PERSISTENT_MEMORY = 4,
	IORES_DESC_PERSISTENT_MEMORY_LEGACY = 5,
	IORES_DESC_DEVICE_PRIVATE_MEMORY = 6,
	IORES_DESC_RESERVED = 7,
	IORES_DESC_SOFT_RESERVED = 8,
};

struct change_member {
	struct e820_entry *entry;
	long long unsigned int addr;
};

struct iommu_fault_param;

struct iommu_fwspec;

struct dev_iommu {
	struct mutex lock;
	struct iommu_fault_param *fault_param;
	struct iommu_fwspec *fwspec;
	struct iommu_device *iommu_dev;
	void *priv;
};

struct of_phandle_args {
	struct device_node *np;
	int args_count;
	uint32_t args[16];
};

struct iommu_fault_unrecoverable {
	__u32 reason;
	__u32 flags;
	__u32 pasid;
	__u32 perm;
	__u64 addr;
	__u64 fetch_addr;
};

struct iommu_fault_page_request {
	__u32 flags;
	__u32 pasid;
	__u32 grpid;
	__u32 perm;
	__u64 addr;
	__u64 private_data[2];
};

struct iommu_fault {
	__u32 type;
	__u32 padding;
	union {
		struct iommu_fault_unrecoverable event;
		struct iommu_fault_page_request prm;
		__u8 padding2[56];
	};
};

struct iommu_page_response {
	__u32 version;
	__u32 flags;
	__u32 pasid;
	__u32 grpid;
	__u32 code;
};

struct iommu_inv_addr_info {
	__u32 flags;
	__u32 archid;
	__u64 pasid;
	__u64 addr;
	__u64 granule_size;
	__u64 nb_granules;
};

struct iommu_inv_pasid_info {
	__u32 flags;
	__u32 archid;
	__u64 pasid;
};

struct iommu_cache_invalidate_info {
	__u32 version;
	__u8 cache;
	__u8 granularity;
	__u8 padding[2];
	union {
		struct iommu_inv_pasid_info pasid_info;
		struct iommu_inv_addr_info addr_info;
	};
};

struct iommu_gpasid_bind_data_vtd {
	__u64 flags;
	__u32 pat;
	__u32 emt;
};

struct iommu_gpasid_bind_data {
	__u32 version;
	__u32 format;
	__u64 flags;
	__u64 gpgd;
	__u64 hpasid;
	__u64 gpasid;
	__u32 addr_width;
	__u8 padding[12];
	union {
		struct iommu_gpasid_bind_data_vtd vtd;
	};
};

typedef int (*iommu_fault_handler_t)(struct iommu_domain *, struct device *, long unsigned int, int, void *);

struct iommu_domain_geometry {
	dma_addr_t aperture_start;
	dma_addr_t aperture_end;
	bool force_aperture;
};

struct iommu_domain {
	unsigned int type;
	const struct iommu_ops *ops;
	long unsigned int pgsize_bitmap;
	iommu_fault_handler_t handler;
	void *handler_token;
	struct iommu_domain_geometry geometry;
	void *iova_cookie;
};

typedef int (*iommu_dev_fault_handler_t)(struct iommu_fault *, void *);

enum iommu_resv_type {
	IOMMU_RESV_DIRECT = 0,
	IOMMU_RESV_DIRECT_RELAXABLE = 1,
	IOMMU_RESV_RESERVED = 2,
	IOMMU_RESV_MSI = 3,
	IOMMU_RESV_SW_MSI = 4,
};

struct iommu_resv_region {
	struct list_head list;
	phys_addr_t start;
	size_t length;
	int prot;
	enum iommu_resv_type type;
};

struct iommu_iotlb_gather {
	long unsigned int start;
	long unsigned int end;
	size_t pgsize;
};

struct iommu_device {
	struct list_head list;
	const struct iommu_ops *ops;
	struct fwnode_handle *fwnode;
	struct device *dev;
};

struct iommu_sva {
	struct device *dev;
};

struct iommu_fault_event {
	struct iommu_fault fault;
	struct list_head list;
};

struct iommu_fault_param {
	iommu_dev_fault_handler_t handler;
	void *data;
	struct list_head faults;
	struct mutex lock;
};

struct iommu_fwspec {
	const struct iommu_ops *ops;
	struct fwnode_handle *iommu_fwnode;
	u32 flags;
	u32 num_pasid_bits;
	unsigned int num_ids;
	u32 ids[0];
};

struct iommu_table_entry {
	initcall_t detect;
	initcall_t depend;
	void (*early_init)();
	void (*late_init)();
	int flags;
};

enum dmi_field {
	DMI_NONE = 0,
	DMI_BIOS_VENDOR = 1,
	DMI_BIOS_VERSION = 2,
	DMI_BIOS_DATE = 3,
	DMI_BIOS_RELEASE = 4,
	DMI_EC_FIRMWARE_RELEASE = 5,
	DMI_SYS_VENDOR = 6,
	DMI_PRODUCT_NAME = 7,
	DMI_PRODUCT_VERSION = 8,
	DMI_PRODUCT_SERIAL = 9,
	DMI_PRODUCT_UUID = 10,
	DMI_PRODUCT_SKU = 11,
	DMI_PRODUCT_FAMILY = 12,
	DMI_BOARD_VENDOR = 13,
	DMI_BOARD_NAME = 14,
	DMI_BOARD_VERSION = 15,
	DMI_BOARD_SERIAL = 16,
	DMI_BOARD_ASSET_TAG = 17,
	DMI_CHASSIS_VENDOR = 18,
	DMI_CHASSIS_TYPE = 19,
	DMI_CHASSIS_VERSION = 20,
	DMI_CHASSIS_SERIAL = 21,
	DMI_CHASSIS_ASSET_TAG = 22,
	DMI_STRING_MAX = 23,
	DMI_OEM_STRING = 24,
};

enum {
	NONE_FORCE_HPET_RESUME = 0,
	OLD_ICH_FORCE_HPET_RESUME = 1,
	ICH_FORCE_HPET_RESUME = 2,
	VT8237_FORCE_HPET_RESUME = 3,
	NVIDIA_FORCE_HPET_RESUME = 4,
	ATI_FORCE_HPET_RESUME = 5,
};

struct cpu {
	int node_id;
	int hotpluggable;
	struct device dev;
};

struct x86_cpu {
	struct cpu cpu;
};

struct debugfs_blob_wrapper {
	void *data;
	long unsigned int size;
};

struct setup_data_node {
	u64 paddr;
	u32 type;
	u32 len;
};

typedef int (*cmp_func_t)(const void *, const void *);

struct die_args {
	struct pt_regs *regs;
	const char *str;
	long int err;
	int trapnr;
	int signr;
};

struct smp_alt_module {
	struct module *mod;
	char *name;
	const s32 *locks;
	const s32 *locks_end;
	u8 *text;
	u8 *text_end;
	struct list_head next;
};

typedef struct {
	struct mm_struct *mm;
} temp_mm_state_t;

struct text_poke_loc {
	s32 rel_addr;
	s32 rel32;
	u8 opcode;
	const u8 text[5];
};

struct bp_patching_desc {
	struct text_poke_loc *vec;
	int nr_entries;
	atomic_t refs;
};

struct paravirt_patch_site;

struct user_i387_struct {
	short unsigned int cwd;
	short unsigned int swd;
	short unsigned int twd;
	short unsigned int fop;
	__u64 rip;
	__u64 rdp;
	__u32 mxcsr;
	__u32 mxcsr_mask;
	__u32 st_space[32];
	__u32 xmm_space[64];
	__u32 padding[24];
};

struct user_regs_struct {
	long unsigned int r15;
	long unsigned int r14;
	long unsigned int r13;
	long unsigned int r12;
	long unsigned int bp;
	long unsigned int bx;
	long unsigned int r11;
	long unsigned int r10;
	long unsigned int r9;
	long unsigned int r8;
	long unsigned int ax;
	long unsigned int cx;
	long unsigned int dx;
	long unsigned int si;
	long unsigned int di;
	long unsigned int orig_ax;
	long unsigned int ip;
	long unsigned int cs;
	long unsigned int flags;
	long unsigned int sp;
	long unsigned int ss;
	long unsigned int fs_base;
	long unsigned int gs_base;
	long unsigned int ds;
	long unsigned int es;
	long unsigned int fs;
	long unsigned int gs;
};

struct user {
	struct user_regs_struct regs;
	int u_fpvalid;
	int pad0;
	struct user_i387_struct i387;
	long unsigned int u_tsize;
	long unsigned int u_dsize;
	long unsigned int u_ssize;
	long unsigned int start_code;
	long unsigned int start_stack;
	long int signal;
	int reserved;
	int pad1;
	long unsigned int u_ar0;
	struct user_i387_struct *u_fpstate;
	long unsigned int magic;
	char u_comm[32];
	long unsigned int u_debugreg[8];
	long unsigned int error_code;
	long unsigned int fault_address;
};

enum {
	HW_BREAKPOINT_LEN_1 = 1,
	HW_BREAKPOINT_LEN_2 = 2,
	HW_BREAKPOINT_LEN_3 = 3,
	HW_BREAKPOINT_LEN_4 = 4,
	HW_BREAKPOINT_LEN_5 = 5,
	HW_BREAKPOINT_LEN_6 = 6,
	HW_BREAKPOINT_LEN_7 = 7,
	HW_BREAKPOINT_LEN_8 = 8,
};

enum {
	HW_BREAKPOINT_EMPTY = 0,
	HW_BREAKPOINT_R = 1,
	HW_BREAKPOINT_W = 2,
	HW_BREAKPOINT_RW = 3,
	HW_BREAKPOINT_X = 4,
	HW_BREAKPOINT_INVALID = 7,
};

typedef unsigned int u_int;

typedef long long unsigned int cycles_t;

struct system_counterval_t {
	u64 cycles;
	struct clocksource *cs;
};

enum {
	WORK_STRUCT_PENDING_BIT = 0,
	WORK_STRUCT_DELAYED_BIT = 1,
	WORK_STRUCT_PWQ_BIT = 2,
	WORK_STRUCT_LINKED_BIT = 3,
	WORK_STRUCT_COLOR_SHIFT = 4,
	WORK_STRUCT_COLOR_BITS = 4,
	WORK_STRUCT_PENDING = 1,
	WORK_STRUCT_DELAYED = 2,
	WORK_STRUCT_PWQ = 4,
	WORK_STRUCT_LINKED = 8,
	WORK_STRUCT_STATIC = 0,
	WORK_NR_COLORS = 15,
	WORK_NO_COLOR = 15,
	WORK_CPU_UNBOUND = 64,
	WORK_STRUCT_FLAG_BITS = 8,
	WORK_OFFQ_FLAG_BASE = 4,
	__WORK_OFFQ_CANCELING = 4,
	WORK_OFFQ_CANCELING = 16,
	WORK_OFFQ_FLAG_BITS = 1,
	WORK_OFFQ_POOL_SHIFT = 5,
	WORK_OFFQ_LEFT = 59,
	WORK_OFFQ_POOL_BITS = 31,
	WORK_OFFQ_POOL_NONE = 2147483647,
	WORK_STRUCT_FLAG_MASK = 255,
	WORK_STRUCT_WQ_DATA_MASK = 4294967040,
	WORK_STRUCT_NO_POOL = 4294967264,
	WORK_BUSY_PENDING = 1,
	WORK_BUSY_RUNNING = 2,
	WORKER_DESC_LEN = 24,
};

struct plist_head {
	struct list_head node_list;
};

enum pm_qos_type {
	PM_QOS_UNITIALIZED = 0,
	PM_QOS_MAX = 1,
	PM_QOS_MIN = 2,
};

struct pm_qos_constraints {
	struct plist_head list;
	s32 target_value;
	s32 default_value;
	s32 no_constraint_value;
	enum pm_qos_type type;
	struct blocking_notifier_head *notifiers;
};

struct freq_constraints {
	struct pm_qos_constraints min_freq;
	struct blocking_notifier_head min_freq_notifiers;
	struct pm_qos_constraints max_freq;
	struct blocking_notifier_head max_freq_notifiers;
};

struct pm_qos_flags {
	struct list_head list;
	s32 effective_flags;
};

struct dev_pm_qos_request;

struct dev_pm_qos {
	struct pm_qos_constraints resume_latency;
	struct pm_qos_constraints latency_tolerance;
	struct freq_constraints freq;
	struct pm_qos_flags flags;
	struct dev_pm_qos_request *resume_latency_req;
	struct dev_pm_qos_request *latency_tolerance_req;
	struct dev_pm_qos_request *flags_req;
};

struct pm_qos_flags_request {
	struct list_head node;
	s32 flags;
};

enum freq_qos_req_type {
	FREQ_QOS_MIN = 1,
	FREQ_QOS_MAX = 2,
};

struct freq_qos_request {
	enum freq_qos_req_type type;
	struct plist_node pnode;
	struct freq_constraints *qos;
};

enum dev_pm_qos_req_type {
	DEV_PM_QOS_RESUME_LATENCY = 1,
	DEV_PM_QOS_LATENCY_TOLERANCE = 2,
	DEV_PM_QOS_MIN_FREQUENCY = 3,
	DEV_PM_QOS_MAX_FREQUENCY = 4,
	DEV_PM_QOS_FLAGS = 5,
};

struct dev_pm_qos_request {
	enum dev_pm_qos_req_type type;
	union {
		struct plist_node pnode;
		struct pm_qos_flags_request flr;
		struct freq_qos_request freq;
	} data;
	struct device *dev;
};

enum cpufreq_table_sorting {
	CPUFREQ_TABLE_UNSORTED = 0,
	CPUFREQ_TABLE_SORTED_ASCENDING = 1,
	CPUFREQ_TABLE_SORTED_DESCENDING = 2,
};

struct cpufreq_cpuinfo {
	unsigned int max_freq;
	unsigned int min_freq;
	unsigned int transition_latency;
};

struct cpufreq_stats;

struct clk;

struct cpufreq_governor;

struct cpufreq_frequency_table;

struct thermal_cooling_device;

struct cpufreq_policy {
	cpumask_var_t cpus;
	cpumask_var_t related_cpus;
	cpumask_var_t real_cpus;
	unsigned int shared_type;
	unsigned int cpu;
	struct clk *clk;
	struct cpufreq_cpuinfo cpuinfo;
	unsigned int min;
	unsigned int max;
	unsigned int cur;
	unsigned int restore_freq;
	unsigned int suspend_freq;
	unsigned int policy;
	unsigned int last_policy;
	struct cpufreq_governor *governor;
	void *governor_data;
	char last_governor[16];
	struct work_struct update;
	struct freq_constraints constraints;
	struct freq_qos_request *min_freq_req;
	struct freq_qos_request *max_freq_req;
	struct cpufreq_frequency_table *freq_table;
	enum cpufreq_table_sorting freq_table_sorted;
	struct list_head policy_list;
	struct kobject kobj;
	struct completion kobj_unregister;
	struct rw_semaphore rwsem;
	bool fast_switch_possible;
	bool fast_switch_enabled;
	unsigned int transition_delay_us;
	bool dvfs_possible_from_any_cpu;
	unsigned int cached_target_freq;
	int cached_resolved_idx;
	bool transition_ongoing;
	spinlock_t transition_lock;
	wait_queue_head_t transition_wait;
	struct task_struct *transition_task;
	struct cpufreq_stats *stats;
	void *driver_data;
	struct thermal_cooling_device *cdev;
	struct notifier_block nb_min;
	struct notifier_block nb_max;
};

struct cpufreq_governor {
	char name[16];
	int (*init)(struct cpufreq_policy *);
	void (*exit)(struct cpufreq_policy *);
	int (*start)(struct cpufreq_policy *);
	void (*stop)(struct cpufreq_policy *);
	void (*limits)(struct cpufreq_policy *);
	ssize_t (*show_setspeed)(struct cpufreq_policy *, char *);
	int (*store_setspeed)(struct cpufreq_policy *, unsigned int);
	bool dynamic_switching;
	struct list_head governor_list;
	struct module *owner;
};

struct cpufreq_frequency_table {
	unsigned int flags;
	unsigned int driver_data;
	unsigned int frequency;
};

struct cpufreq_freqs {
	struct cpufreq_policy *policy;
	unsigned int old;
	unsigned int new;
	u8 flags;
};

struct freq_attr {
	struct attribute attr;
	ssize_t (*show)(struct cpufreq_policy *, char *);
	ssize_t (*store)(struct cpufreq_policy *, const char *, size_t);
};

struct cyc2ns {
	struct cyc2ns_data data[2];
	seqcount_t seq;
};

struct muldiv {
	u32 multiplier;
	u32 divider;
};

struct freq_desc {
	bool use_msr_plat;
	struct muldiv muldiv[16];
	u32 freqs[16];
	u32 mask;
};

struct dmi_strmatch {
	unsigned char slot: 7;
	unsigned char exact_match: 1;
	char substr[79];
};

struct dmi_system_id {
	int (*callback)(const struct dmi_system_id *);
	const char *ident;
	struct dmi_strmatch matches[4];
	void *driver_data;
};

struct pdev_archdata {};

struct mfd_cell;

struct platform_device_id;

struct platform_device {
	const char *name;
	int id;
	bool id_auto;
	struct device dev;
	u64 platform_dma_mask;
	struct device_dma_parameters dma_parms;
	u32 num_resources;
	struct resource *resource;
	const struct platform_device_id *id_entry;
	char *driver_override;
	struct mfd_cell *mfd_cell;
	struct pdev_archdata archdata;
};

struct platform_device_id {
	char name[20];
	kernel_ulong_t driver_data;
};

struct rtc_time {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct pnp_device_id {
	__u8 id[8];
	kernel_ulong_t driver_data;
};

struct pnp_card_device_id {
	__u8 id[8];
	kernel_ulong_t driver_data;
	struct {
		__u8 id[8];
	} devs[8];
};

struct pnp_protocol;

struct pnp_id;

struct pnp_card {
	struct device dev;
	unsigned char number;
	struct list_head global_list;
	struct list_head protocol_list;
	struct list_head devices;
	struct pnp_protocol *protocol;
	struct pnp_id *id;
	char name[50];
	unsigned char pnpver;
	unsigned char productver;
	unsigned int serial;
	unsigned char checksum;
	struct proc_dir_entry *procdir;
};

struct pnp_dev;

struct pnp_protocol {
	struct list_head protocol_list;
	char *name;
	int (*get)(struct pnp_dev *);
	int (*set)(struct pnp_dev *);
	int (*disable)(struct pnp_dev *);
	bool (*can_wakeup)(struct pnp_dev *);
	int (*suspend)(struct pnp_dev *, pm_message_t);
	int (*resume)(struct pnp_dev *);
	unsigned char number;
	struct device dev;
	struct list_head cards;
	struct list_head devices;
};

struct pnp_id {
	char id[8];
	struct pnp_id *next;
};

struct pnp_card_driver;

struct pnp_card_link {
	struct pnp_card *card;
	struct pnp_card_driver *driver;
	void *driver_data;
	pm_message_t pm_state;
};

struct pnp_driver {
	const char *name;
	const struct pnp_device_id *id_table;
	unsigned int flags;
	int (*probe)(struct pnp_dev *, const struct pnp_device_id *);
	void (*remove)(struct pnp_dev *);
	void (*shutdown)(struct pnp_dev *);
	int (*suspend)(struct pnp_dev *, pm_message_t);
	int (*resume)(struct pnp_dev *);
	struct device_driver driver;
};

struct pnp_card_driver {
	struct list_head global_list;
	char *name;
	const struct pnp_card_device_id *id_table;
	unsigned int flags;
	int (*probe)(struct pnp_card_link *, const struct pnp_card_device_id *);
	void (*remove)(struct pnp_card_link *);
	int (*suspend)(struct pnp_card_link *, pm_message_t);
	int (*resume)(struct pnp_card_link *);
	struct pnp_driver link;
};

struct pnp_dev {
	struct device dev;
	u64 dma_mask;
	unsigned int number;
	int status;
	struct list_head global_list;
	struct list_head protocol_list;
	struct list_head card_list;
	struct list_head rdev_list;
	struct pnp_protocol *protocol;
	struct pnp_card *card;
	struct pnp_driver *driver;
	struct pnp_card_link *card_link;
	struct pnp_id *id;
	int active;
	int capabilities;
	unsigned int num_dependent_sets;
	struct list_head resources;
	struct list_head options;
	char name[50];
	int flags;
	struct proc_dir_entry *procent;
	void *data;
};

struct sfi_rtc_table_entry {
	u64 phys_addr;
	u32 irq;
} __attribute__((packed));

enum intel_mid_cpu_type {
	INTEL_MID_CPU_CHIP_PENWELL = 2,
	INTEL_MID_CPU_CHIP_CLOVERVIEW = 3,
	INTEL_MID_CPU_CHIP_TANGIER = 4,
};

enum intel_mid_timer_options {
	INTEL_MID_TIMER_DEFAULT = 0,
	INTEL_MID_TIMER_APBT_ONLY = 1,
	INTEL_MID_TIMER_LAPIC_APBT = 2,
};

typedef struct ldttss_desc tss_desc;

enum idle_boot_override {
	IDLE_NO_OVERRIDE = 0,
	IDLE_HALT = 1,
	IDLE_NOMWAIT = 2,
	IDLE_POLL = 3,
};

enum tick_broadcast_mode {
	TICK_BROADCAST_OFF = 0,
	TICK_BROADCAST_ON = 1,
	TICK_BROADCAST_FORCE = 2,
};

enum tick_broadcast_state {
	TICK_BROADCAST_EXIT = 0,
	TICK_BROADCAST_ENTER = 1,
};

struct cpuidle_state_usage {
	long long unsigned int disable;
	long long unsigned int usage;
	u64 time_ns;
	long long unsigned int above;
	long long unsigned int below;
	long long unsigned int s2idle_usage;
	long long unsigned int s2idle_time;
};

struct cpuidle_driver_kobj;

struct cpuidle_state_kobj;

struct cpuidle_device_kobj;

struct cpuidle_device {
	unsigned int registered: 1;
	unsigned int enabled: 1;
	unsigned int poll_time_limit: 1;
	unsigned int cpu;
	ktime_t next_hrtimer;
	int last_state_idx;
	u64 last_residency_ns;
	u64 poll_limit_ns;
	u64 forced_idle_latency_limit_ns;
	struct cpuidle_state_usage states_usage[10];
	struct cpuidle_state_kobj *kobjs[10];
	struct cpuidle_driver_kobj *kobj_driver;
	struct cpuidle_device_kobj *kobj_dev;
	struct list_head device_list;
};

struct inactive_task_frame {
	long unsigned int r15;
	long unsigned int r14;
	long unsigned int r13;
	long unsigned int r12;
	long unsigned int bx;
	long unsigned int bp;
	long unsigned int ret_addr;
};

struct fork_frame {
	struct inactive_task_frame frame;
	struct pt_regs regs;
};

struct ssb_state {
	struct ssb_state *shared_state;
	raw_spinlock_t lock;
	unsigned int disable_state;
	long unsigned int local_state;
};

typedef u16 pto_T_____9;

struct trace_event_raw_x86_fpu {
	struct trace_entry ent;
	struct fpu *fpu;
	bool load_fpu;
	u64 xfeatures;
	u64 xcomp_bv;
	char __data[0];
};

struct trace_event_data_offsets_x86_fpu {};

typedef void (*btf_trace_x86_fpu_before_save)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_after_save)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_before_restore)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_after_restore)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_regs_activated)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_regs_deactivated)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_init_state)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_dropped)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_copy_src)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_copy_dst)(void *, struct fpu *);

typedef void (*btf_trace_x86_fpu_xstate_check_failed)(void *, struct fpu *);

typedef struct fpu *pto_T_____10;

struct _fpreg {
	__u16 significand[4];
	__u16 exponent;
};

struct _fpxreg {
	__u16 significand[4];
	__u16 exponent;
	__u16 padding[3];
};

struct user_i387_ia32_struct {
	u32 cwd;
	u32 swd;
	u32 twd;
	u32 fip;
	u32 fcs;
	u32 foo;
	u32 fos;
	u32 st_space[20];
};

struct user_regset;

typedef int user_regset_active_fn(struct task_struct *, const struct user_regset *);

typedef int user_regset_get_fn(struct task_struct *, const struct user_regset *, unsigned int, unsigned int, void *, void *);

typedef int user_regset_set_fn(struct task_struct *, const struct user_regset *, unsigned int, unsigned int, const void *, const void *);

typedef int user_regset_writeback_fn(struct task_struct *, const struct user_regset *, int);

typedef unsigned int user_regset_get_size_fn(struct task_struct *, const struct user_regset *);

struct user_regset {
	user_regset_get_fn *get;
	user_regset_set_fn *set;
	user_regset_active_fn *active;
	user_regset_writeback_fn *writeback;
	user_regset_get_size_fn *get_size;
	unsigned int n;
	unsigned int size;
	unsigned int align;
	unsigned int bias;
	unsigned int core_note_type;
};

struct _fpx_sw_bytes {
	__u32 magic1;
	__u32 extended_size;
	__u64 xfeatures;
	__u32 xstate_size;
	__u32 padding[7];
};

struct _xmmreg {
	__u32 element[4];
};

struct _fpstate_32 {
	__u32 cw;
	__u32 sw;
	__u32 tag;
	__u32 ipoff;
	__u32 cssel;
	__u32 dataoff;
	__u32 datasel;
	struct _fpreg _st[8];
	__u16 status;
	__u16 magic;
	__u32 _fxsr_env[6];
	__u32 mxcsr;
	__u32 reserved;
	struct _fpxreg _fxsr_st[8];
	struct _xmmreg _xmm[8];
	union {
		__u32 padding1[44];
		__u32 padding[44];
	};
	union {
		__u32 padding2[12];
		struct _fpx_sw_bytes sw_reserved;
	};
};

typedef u32 compat_ulong_t;

struct user_regset_view {
	const char *name;
	const struct user_regset *regsets;
	unsigned int n;
	u32 e_flags;
	u16 e_machine;
	u8 ei_osabi;
};

enum x86_regset {
	REGSET_GENERAL = 0,
	REGSET_FP = 1,
	REGSET_XFP = 2,
	REGSET_IOPERM64 = 2,
	REGSET_XSTATE = 3,
	REGSET_TLS = 4,
	REGSET_IOPERM32 = 5,
};

struct pt_regs_offset {
	const char *name;
	int offset;
};

typedef bool (*stack_trace_consume_fn)(void *, long unsigned int, bool);

struct stack_frame_user {
	const void *next_fp;
	long unsigned int ret_addr;
};

enum cache_type {
	CACHE_TYPE_NOCACHE = 0,
	CACHE_TYPE_INST = 1,
	CACHE_TYPE_DATA = 2,
	CACHE_TYPE_SEPARATE = 3,
	CACHE_TYPE_UNIFIED = 4,
};

struct cacheinfo {
	unsigned int id;
	enum cache_type type;
	unsigned int level;
	unsigned int coherency_line_size;
	unsigned int number_of_sets;
	unsigned int ways_of_associativity;
	unsigned int physical_line_partition;
	unsigned int size;
	cpumask_t shared_cpu_map;
	unsigned int attributes;
	void *fw_token;
	bool disable_sysfs;
	void *priv;
};

struct cpu_cacheinfo {
	struct cacheinfo *info_list;
	unsigned int num_levels;
	unsigned int num_leaves;
	bool cpu_map_populated;
};

struct amd_nb_bus_dev_range {
	u8 bus;
	u8 dev_base;
	u8 dev_limit;
};

struct amd_l3_cache {
	unsigned int indices;
	u8 subcaches[4];
};

struct threshold_block {
	unsigned int block;
	unsigned int bank;
	unsigned int cpu;
	u32 address;
	u16 interrupt_enable;
	bool interrupt_capable;
	u16 threshold_limit;
	struct kobject kobj;
	struct list_head miscj;
};

struct threshold_bank {
	struct kobject *kobj;
	struct threshold_block *blocks;
	refcount_t cpus;
	unsigned int shared;
};

struct amd_northbridge {
	struct pci_dev *root;
	struct pci_dev *misc;
	struct pci_dev *link;
	struct amd_l3_cache l3_cache;
	struct threshold_bank *bank4;
};

struct cpu_dev {
	const char *c_vendor;
	const char *c_ident[2];
	void (*c_early_init)(struct cpuinfo_x86 *);
	void (*c_bsp_init)(struct cpuinfo_x86 *);
	void (*c_init)(struct cpuinfo_x86 *);
	void (*c_identify)(struct cpuinfo_x86 *);
	void (*c_detect_tlb)(struct cpuinfo_x86 *);
	int c_x86_vendor;
};

enum tsx_ctrl_states {
	TSX_CTRL_ENABLE = 0,
	TSX_CTRL_DISABLE = 1,
	TSX_CTRL_NOT_SUPPORTED = 2,
};

struct _cache_table {
	unsigned char descriptor;
	char cache_type;
	short int size;
};

enum _cache_type {
	CTYPE_NULL = 0,
	CTYPE_DATA = 1,
	CTYPE_INST = 2,
	CTYPE_UNIFIED = 3,
};

union _cpuid4_leaf_eax {
	struct {
		enum _cache_type type: 5;
		unsigned int level: 3;
		unsigned int is_self_initializing: 1;
		unsigned int is_fully_associative: 1;
		unsigned int reserved: 4;
		unsigned int num_threads_sharing: 12;
		unsigned int num_cores_on_die: 6;
	} split;
	u32 full;
};

union _cpuid4_leaf_ebx {
	struct {
		unsigned int coherency_line_size: 12;
		unsigned int physical_line_partition: 10;
		unsigned int ways_of_associativity: 10;
	} split;
	u32 full;
};

union _cpuid4_leaf_ecx {
	struct {
		unsigned int number_of_sets: 32;
	} split;
	u32 full;
};

struct _cpuid4_info_regs {
	union _cpuid4_leaf_eax eax;
	union _cpuid4_leaf_ebx ebx;
	union _cpuid4_leaf_ecx ecx;
	unsigned int id;
	long unsigned int size;
	struct amd_northbridge *nb;
};

union l1_cache {
	struct {
		unsigned int line_size: 8;
		unsigned int lines_per_tag: 8;
		unsigned int assoc: 8;
		unsigned int size_in_kb: 8;
	};
	unsigned int val;
};

union l2_cache {
	struct {
		unsigned int line_size: 8;
		unsigned int lines_per_tag: 4;
		unsigned int assoc: 4;
		unsigned int size_in_kb: 16;
	};
	unsigned int val;
};

union l3_cache {
	struct {
		unsigned int line_size: 8;
		unsigned int lines_per_tag: 4;
		unsigned int assoc: 4;
		unsigned int res: 2;
		unsigned int size_encoded: 14;
	};
	unsigned int val;
};

struct cpuid_bit {
	u16 feature;
	u8 reg;
	u8 bit;
	u32 level;
	u32 sub_leaf;
};

enum cpuid_leafs {
	CPUID_1_EDX = 0,
	CPUID_8000_0001_EDX = 1,
	CPUID_8086_0001_EDX = 2,
	CPUID_LNX_1 = 3,
	CPUID_1_ECX = 4,
	CPUID_C000_0001_EDX = 5,
	CPUID_8000_0001_ECX = 6,
	CPUID_LNX_2 = 7,
	CPUID_LNX_3 = 8,
	CPUID_7_0_EBX = 9,
	CPUID_D_1_EAX = 10,
	CPUID_LNX_4 = 11,
	CPUID_7_1_EAX = 12,
	CPUID_8000_0008_EBX = 13,
	CPUID_6_EAX = 14,
	CPUID_8000_000A_EDX = 15,
	CPUID_7_ECX = 16,
	CPUID_8000_0007_EBX = 17,
	CPUID_7_EDX = 18,
};

struct cpuid_dependent_feature {
	u32 feature;
	u32 level;
};

enum spectre_v2_mitigation {
	SPECTRE_V2_NONE = 0,
	SPECTRE_V2_RETPOLINE_GENERIC = 1,
	SPECTRE_V2_RETPOLINE_AMD = 2,
	SPECTRE_V2_IBRS_ENHANCED = 3,
};

enum spectre_v2_user_mitigation {
	SPECTRE_V2_USER_NONE = 0,
	SPECTRE_V2_USER_STRICT = 1,
	SPECTRE_V2_USER_STRICT_PREFERRED = 2,
	SPECTRE_V2_USER_PRCTL = 3,
	SPECTRE_V2_USER_SECCOMP = 4,
};

enum ssb_mitigation {
	SPEC_STORE_BYPASS_NONE = 0,
	SPEC_STORE_BYPASS_DISABLE = 1,
	SPEC_STORE_BYPASS_PRCTL = 2,
	SPEC_STORE_BYPASS_SECCOMP = 3,
};

enum mds_mitigations {
	MDS_MITIGATION_OFF = 0,
	MDS_MITIGATION_FULL = 1,
	MDS_MITIGATION_VMWERV = 2,
};

enum vmx_l1d_flush_state {
	VMENTER_L1D_FLUSH_AUTO = 0,
	VMENTER_L1D_FLUSH_NEVER = 1,
	VMENTER_L1D_FLUSH_COND = 2,
	VMENTER_L1D_FLUSH_ALWAYS = 3,
	VMENTER_L1D_FLUSH_EPT_DISABLED = 4,
	VMENTER_L1D_FLUSH_NOT_REQUIRED = 5,
};

enum x86_hypervisor_type {
	X86_HYPER_NATIVE = 0,
	X86_HYPER_VMWARE = 1,
	X86_HYPER_MS_HYPERV = 2,
	X86_HYPER_XEN_PV = 3,
	X86_HYPER_XEN_HVM = 4,
	X86_HYPER_KVM = 5,
	X86_HYPER_JAILHOUSE = 6,
	X86_HYPER_ACRN = 7,
};

enum taa_mitigations {
	TAA_MITIGATION_OFF = 0,
	TAA_MITIGATION_UCODE_NEEDED = 1,
	TAA_MITIGATION_VERW = 2,
	TAA_MITIGATION_TSX_DISABLED = 3,
};

enum srbds_mitigations {
	SRBDS_MITIGATION_OFF = 0,
	SRBDS_MITIGATION_UCODE_NEEDED = 1,
	SRBDS_MITIGATION_FULL = 2,
	SRBDS_MITIGATION_TSX_OFF = 3,
	SRBDS_MITIGATION_HYPERVISOR = 4,
};

enum spectre_v1_mitigation {
	SPECTRE_V1_MITIGATION_NONE = 0,
	SPECTRE_V1_MITIGATION_AUTO = 1,
};

enum spectre_v2_mitigation_cmd {
	SPECTRE_V2_CMD_NONE = 0,
	SPECTRE_V2_CMD_AUTO = 1,
	SPECTRE_V2_CMD_FORCE = 2,
	SPECTRE_V2_CMD_RETPOLINE = 3,
	SPECTRE_V2_CMD_RETPOLINE_GENERIC = 4,
	SPECTRE_V2_CMD_RETPOLINE_AMD = 5,
};

enum spectre_v2_user_cmd {
	SPECTRE_V2_USER_CMD_NONE = 0,
	SPECTRE_V2_USER_CMD_AUTO = 1,
	SPECTRE_V2_USER_CMD_FORCE = 2,
	SPECTRE_V2_USER_CMD_PRCTL = 3,
	SPECTRE_V2_USER_CMD_PRCTL_IBPB = 4,
	SPECTRE_V2_USER_CMD_SECCOMP = 5,
	SPECTRE_V2_USER_CMD_SECCOMP_IBPB = 6,
};

enum ssb_mitigation_cmd {
	SPEC_STORE_BYPASS_CMD_NONE = 0,
	SPEC_STORE_BYPASS_CMD_AUTO = 1,
	SPEC_STORE_BYPASS_CMD_ON = 2,
	SPEC_STORE_BYPASS_CMD_PRCTL = 3,
	SPEC_STORE_BYPASS_CMD_SECCOMP = 4,
};

enum hk_flags {
	HK_FLAG_TIMER = 1,
	HK_FLAG_RCU = 2,
	HK_FLAG_MISC = 4,
	HK_FLAG_SCHED = 8,
	HK_FLAG_TICK = 16,
	HK_FLAG_DOMAIN = 32,
	HK_FLAG_WQ = 64,
	HK_FLAG_MANAGED_IRQ = 128,
};

struct aperfmperf_sample {
	unsigned int khz;
	ktime_t time;
	u64 aperf;
	u64 mperf;
};

struct cpuid_dep {
	unsigned int feature;
	unsigned int depends;
};

enum vmx_feature_leafs {
	MISC_FEATURES = 0,
	PRIMARY_CTLS = 1,
	SECONDARY_CTLS = 2,
	NR_VMX_FEATURE_WORDS = 3,
};

struct _tlb_table {
	unsigned char descriptor;
	char tlb_type;
	unsigned int entries;
	char info[128];
};

enum split_lock_detect_state {
	sld_off = 0,
	sld_warn = 1,
	sld_fatal = 2,
};

struct sku_microcode {
	u8 model;
	u8 stepping;
	u32 microcode;
};

struct cpuid_regs {
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
};

enum pconfig_target {
	INVALID_TARGET = 0,
	MKTME_TARGET = 1,
	PCONFIG_TARGET_NR = 2,
};

enum {
	PCONFIG_CPUID_SUBLEAF_INVALID = 0,
	PCONFIG_CPUID_SUBLEAF_TARGETID = 1,
};

typedef u8 pto_T_____11;

enum mf_flags {
	MF_COUNT_INCREASED = 1,
	MF_ACTION_REQUIRED = 2,
	MF_MUST_KILL = 4,
	MF_SOFT_OFFLINE = 8,
};

enum mce_notifier_prios {
	MCE_PRIO_LOWEST = 0,
	MCE_PRIO_MCELOG = 1,
	MCE_PRIO_EDAC = 2,
	MCE_PRIO_NFIT = 3,
	MCE_PRIO_EXTLOG = 4,
	MCE_PRIO_UC = 5,
	MCE_PRIO_EARLY = 6,
	MCE_PRIO_CEC = 7,
};

enum mcp_flags {
	MCP_TIMESTAMP = 1,
	MCP_UC = 2,
	MCP_DONTLOG = 4,
};

enum severity_level {
	MCE_NO_SEVERITY = 0,
	MCE_DEFERRED_SEVERITY = 1,
	MCE_UCNA_SEVERITY = 1,
	MCE_KEEP_SEVERITY = 2,
	MCE_SOME_SEVERITY = 3,
	MCE_AO_SEVERITY = 4,
	MCE_UC_SEVERITY = 5,
	MCE_AR_SEVERITY = 6,
	MCE_PANIC_SEVERITY = 7,
};

struct mce_evt_llist {
	struct llist_node llnode;
	struct mce mce;
};

struct mca_config {
	bool dont_log_ce;
	bool cmci_disabled;
	bool ignore_ce;
	bool print_all;
	__u64 lmce_disabled: 1;
	__u64 disabled: 1;
	__u64 ser: 1;
	__u64 recovery: 1;
	__u64 bios_cmci_threshold: 1;
	int: 27;
	__u64 __reserved: 59;
	s8 bootlog;
	int tolerant;
	int monarch_timeout;
	int panic_timeout;
	u32 rip_msr;
};

struct mce_vendor_flags {
	__u64 overflow_recov: 1;
	__u64 succor: 1;
	__u64 smca: 1;
	__u64 amd_threshold: 1;
	__u64 __reserved_0: 60;
};

struct mca_msr_regs {
	u32 (*ctl)(int);
	u32 (*status)(int);
	u32 (*addr)(int);
	u32 (*misc)(int);
};

struct trace_event_raw_mce_record {
	struct trace_entry ent;
	u64 mcgcap;
	u64 mcgstatus;
	u64 status;
	u64 addr;
	u64 misc;
	u64 synd;
	u64 ipid;
	u64 ip;
	u64 tsc;
	u64 walltime;
	u32 cpu;
	u32 cpuid;
	u32 apicid;
	u32 socketid;
	u8 cs;
	u8 bank;
	u8 cpuvendor;
	char __data[0];
};

struct trace_event_data_offsets_mce_record {};

typedef void (*btf_trace_mce_record)(void *, struct mce *);

struct mce_bank {
	u64 ctl;
	bool init;
};

struct mce_bank_dev {
	struct device_attribute attr;
	char attrname[16];
	u8 bank;
};

typedef unsigned int pto_T_____12;

enum context {
	IN_KERNEL = 1,
	IN_USER = 2,
	IN_KERNEL_RECOV = 3,
};

enum ser {
	SER_REQUIRED = 1,
	NO_SER = 2,
};

enum exception {
	EXCP_CONTEXT = 1,
	NO_EXCP = 2,
};

struct severity {
	u64 mask;
	u64 result;
	unsigned char sev;
	unsigned char mcgmask;
	unsigned char mcgres;
	unsigned char ser;
	unsigned char context;
	unsigned char excp;
	unsigned char covered;
	char *msg;
};

struct gen_pool;

typedef long unsigned int (*genpool_algo_t)(long unsigned int *, long unsigned int, long unsigned int, unsigned int, void *, struct gen_pool *, long unsigned int);

struct gen_pool {
	spinlock_t lock;
	struct list_head chunks;
	int min_alloc_order;
	genpool_algo_t algo;
	void *data;
	const char *name;
};

enum {
	CMCI_STORM_NONE = 0,
	CMCI_STORM_ACTIVE = 1,
	CMCI_STORM_SUBSIDED = 2,
};

enum kobject_action {
	KOBJ_ADD = 0,
	KOBJ_REMOVE = 1,
	KOBJ_CHANGE = 2,
	KOBJ_MOVE = 3,
	KOBJ_ONLINE = 4,
	KOBJ_OFFLINE = 5,
	KOBJ_BIND = 6,
	KOBJ_UNBIND = 7,
	KOBJ_MAX = 8,
};

enum smca_bank_types {
	SMCA_LS = 0,
	SMCA_LS_V2 = 1,
	SMCA_IF = 2,
	SMCA_L2_CACHE = 3,
	SMCA_DE = 4,
	SMCA_RESERVED = 5,
	SMCA_EX = 6,
	SMCA_FP = 7,
	SMCA_L3_CACHE = 8,
	SMCA_CS = 9,
	SMCA_CS_V2 = 10,
	SMCA_PIE = 11,
	SMCA_UMC = 12,
	SMCA_PB = 13,
	SMCA_PSP = 14,
	SMCA_PSP_V2 = 15,
	SMCA_SMU = 16,
	SMCA_SMU_V2 = 17,
	SMCA_MP5 = 18,
	SMCA_NBIO = 19,
	SMCA_PCIE = 20,
	N_SMCA_BANK_TYPES = 21,
};

struct smca_bank_name {
	const char *name;
	const char *long_name;
};

struct thresh_restart {
	struct threshold_block *b;
	int reset;
	int set_lvt_off;
	int lvt_off;
	u16 old_limit;
};

struct threshold_attr {
	struct attribute attr;
	ssize_t (*show)(struct threshold_block *, char *);
	ssize_t (*store)(struct threshold_block *, const char *, size_t);
};

typedef struct threshold_bank **pto_T_____13;

struct _thermal_state {
	u64 next_check;
	u64 last_interrupt_time;
	struct delayed_work therm_work;
	long unsigned int count;
	long unsigned int last_count;
	long unsigned int max_time_ms;
	long unsigned int total_time_ms;
	bool rate_control_active;
	bool new_event;
	u8 level;
	u8 sample_index;
	u8 sample_count;
	u8 average;
	u8 baseline_temp;
	u8 temp_samples[3];
};

struct thermal_state {
	struct _thermal_state core_throttle;
	struct _thermal_state core_power_limit;
	struct _thermal_state package_throttle;
	struct _thermal_state package_power_limit;
	struct _thermal_state core_thresh0;
	struct _thermal_state core_thresh1;
	struct _thermal_state pkg_thresh0;
	struct _thermal_state pkg_thresh1;
};

struct mtrr_var_range {
	__u32 base_lo;
	__u32 base_hi;
	__u32 mask_lo;
	__u32 mask_hi;
};

typedef __u8 mtrr_type;

struct mtrr_state_type {
	struct mtrr_var_range var_ranges[256];
	mtrr_type fixed_ranges[88];
	unsigned char enabled;
	unsigned char have_fixed;
	mtrr_type def_type;
};

struct mtrr_ops {
	u32 vendor;
	u32 use_intel_if;
	void (*set)(unsigned int, long unsigned int, long unsigned int, mtrr_type);
	void (*set_all)();
	void (*get)(unsigned int, long unsigned int *, long unsigned int *, mtrr_type *);
	int (*get_free_region)(long unsigned int, long unsigned int, int);
	int (*validate_add_page)(long unsigned int, long unsigned int, unsigned int);
	int (*have_wrcomb)();
};

struct set_mtrr_data {
	long unsigned int smp_base;
	long unsigned int smp_size;
	unsigned int smp_reg;
	mtrr_type smp_type;
};

struct mtrr_value {
	mtrr_type ltype;
	long unsigned int lbase;
	long unsigned int lsize;
};

struct proc_ops {
	unsigned int proc_flags;
	int (*proc_open)(struct inode *, struct file *);
	ssize_t (*proc_read)(struct file *, char *, size_t, loff_t *);
	ssize_t (*proc_write)(struct file *, const char *, size_t, loff_t *);
	loff_t (*proc_lseek)(struct file *, loff_t, int);
	int (*proc_release)(struct inode *, struct file *);
	__poll_t (*proc_poll)(struct file *, struct poll_table_struct *);
	long int (*proc_ioctl)(struct file *, unsigned int, long unsigned int);
	long int (*proc_compat_ioctl)(struct file *, unsigned int, long unsigned int);
	int (*proc_mmap)(struct file *, struct vm_area_struct *);
	long unsigned int (*proc_get_unmapped_area)(struct file *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);
};

struct mtrr_sentry {
	__u64 base;
	__u32 size;
	__u32 type;
};

struct mtrr_gentry {
	__u64 base;
	__u32 size;
	__u32 regnum;
	__u32 type;
	__u32 _pad;
};

typedef u32 compat_uint_t;

struct mtrr_sentry32 {
	compat_ulong_t base;
	compat_uint_t size;
	compat_uint_t type;
};

struct mtrr_gentry32 {
	compat_ulong_t regnum;
	compat_uint_t base;
	compat_uint_t size;
	compat_uint_t type;
};

struct fixed_range_block {
	int base_msr;
	int ranges;
};

struct var_mtrr_range_state {
	long unsigned int base_pfn;
	long unsigned int size_pfn;
	mtrr_type type;
};

struct subsys_interface {
	const char *name;
	struct bus_type *subsys;
	struct list_head node;
	int (*add_dev)(struct device *, struct subsys_interface *);
	void (*remove_dev)(struct device *, struct subsys_interface *);
};

struct property_entry;

struct platform_device_info {
	struct device *parent;
	struct fwnode_handle *fwnode;
	bool of_node_reused;
	const char *name;
	int id;
	const struct resource *res;
	unsigned int num_res;
	const void *data;
	size_t size_data;
	u64 dma_mask;
	const struct property_entry *properties;
};

enum dev_prop_type {
	DEV_PROP_U8 = 0,
	DEV_PROP_U16 = 1,
	DEV_PROP_U32 = 2,
	DEV_PROP_U64 = 3,
	DEV_PROP_STRING = 4,
	DEV_PROP_REF = 5,
};

struct property_entry {
	const char *name;
	size_t length;
	bool is_inline;
	enum dev_prop_type type;
	union {
		const void *pointer;
		union {
			u8 u8_data[8];
			u16 u16_data[4];
			u32 u32_data[2];
			u64 u64_data[1];
			const char *str[1];
		} value;
	};
};

struct builtin_fw {
	char *name;
	void *data;
	long unsigned int size;
};

struct cpio_data {
	void *data;
	size_t size;
	char name[18];
};

enum ucode_state {
	UCODE_OK = 0,
	UCODE_NEW = 1,
	UCODE_UPDATED = 2,
	UCODE_NFOUND = 3,
	UCODE_ERROR = 4,
};

struct microcode_ops {
	enum ucode_state (*request_microcode_user)(int, const void *, size_t);
	enum ucode_state (*request_microcode_fw)(int, struct device *, bool);
	void (*microcode_fini_cpu)(int);
	enum ucode_state (*apply_microcode)(int);
	int (*collect_cpu_info)(int, struct cpu_signature *);
};

struct cpu_info_ctx {
	struct cpu_signature *cpu_sig;
	int err;
};

struct firmware {
	size_t size;
	const u8 *data;
	void *priv;
};

struct ucode_patch {
	struct list_head plist;
	void *data;
	u32 patch_id;
	u16 equiv_cpu;
};

struct microcode_header_intel {
	unsigned int hdrver;
	unsigned int rev;
	unsigned int date;
	unsigned int sig;
	unsigned int cksum;
	unsigned int ldrver;
	unsigned int pf;
	unsigned int datasize;
	unsigned int totalsize;
	unsigned int reserved[3];
};

struct microcode_intel {
	struct microcode_header_intel hdr;
	unsigned int bits[0];
};

struct extended_signature {
	unsigned int sig;
	unsigned int pf;
	unsigned int cksum;
};

struct extended_sigtable {
	unsigned int count;
	unsigned int cksum;
	unsigned int reserved[3];
	struct extended_signature sigs[0];
};

struct equiv_cpu_entry {
	u32 installed_cpu;
	u32 fixed_errata_mask;
	u32 fixed_errata_compare;
	u16 equiv_cpu;
	u16 res;
};

struct microcode_header_amd {
	u32 data_code;
	u32 patch_id;
	u16 mc_patch_data_id;
	u8 mc_patch_data_len;
	u8 init_flag;
	u32 mc_patch_data_checksum;
	u32 nb_dev_id;
	u32 sb_dev_id;
	u16 processor_rev_id;
	u8 nb_rev_id;
	u8 sb_rev_id;
	u8 bios_api_rev;
	u8 reserved1[3];
	u32 match_reg[8];
};

struct microcode_amd {
	struct microcode_header_amd hdr;
	unsigned int mpb[0];
};

struct equiv_cpu_table {
	unsigned int num_entries;
	struct equiv_cpu_entry *entry;
};

struct cont_desc {
	struct microcode_amd *mc;
	u32 cpuid_1_eax;
	u32 psize;
	u8 *data;
	size_t size;
};

enum mp_irq_source_types {
	mp_INT = 0,
	mp_NMI = 1,
	mp_SMI = 2,
	mp_ExtINT = 3,
};

struct IO_APIC_route_entry {
	__u32 vector: 8;
	__u32 delivery_mode: 3;
	__u32 dest_mode: 1;
	__u32 delivery_status: 1;
	__u32 polarity: 1;
	__u32 irr: 1;
	__u32 trigger: 1;
	__u32 mask: 1;
	__u32 __reserved_2: 15;
	__u32 __reserved_3: 24;
	__u32 dest: 8;
};

typedef u64 acpi_physical_address;

typedef u32 acpi_status;

typedef void *acpi_handle;

typedef u8 acpi_adr_space_type;

struct acpi_subtable_header {
	u8 type;
	u8 length;
};

struct acpi_table_bgrt {
	struct acpi_table_header header;
	u16 version;
	u8 status;
	u8 image_type;
	u64 image_address;
	u32 image_offset_x;
	u32 image_offset_y;
};

struct acpi_table_boot {
	struct acpi_table_header header;
	u8 cmos_index;
	u8 reserved[3];
};

struct acpi_hmat_structure {
	u16 type;
	u16 reserved;
	u32 length;
};

struct acpi_table_hpet {
	struct acpi_table_header header;
	u32 id;
	struct acpi_generic_address address;
	u8 sequence;
	u16 minimum_tick;
	u8 flags;
} __attribute__((packed));

struct acpi_table_madt {
	struct acpi_table_header header;
	u32 address;
	u32 flags;
};

enum acpi_madt_type {
	ACPI_MADT_TYPE_LOCAL_APIC = 0,
	ACPI_MADT_TYPE_IO_APIC = 1,
	ACPI_MADT_TYPE_INTERRUPT_OVERRIDE = 2,
	ACPI_MADT_TYPE_NMI_SOURCE = 3,
	ACPI_MADT_TYPE_LOCAL_APIC_NMI = 4,
	ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE = 5,
	ACPI_MADT_TYPE_IO_SAPIC = 6,
	ACPI_MADT_TYPE_LOCAL_SAPIC = 7,
	ACPI_MADT_TYPE_INTERRUPT_SOURCE = 8,
	ACPI_MADT_TYPE_LOCAL_X2APIC = 9,
	ACPI_MADT_TYPE_LOCAL_X2APIC_NMI = 10,
	ACPI_MADT_TYPE_GENERIC_INTERRUPT = 11,
	ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR = 12,
	ACPI_MADT_TYPE_GENERIC_MSI_FRAME = 13,
	ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR = 14,
	ACPI_MADT_TYPE_GENERIC_TRANSLATOR = 15,
	ACPI_MADT_TYPE_RESERVED = 16,
};

struct acpi_madt_local_apic {
	struct acpi_subtable_header header;
	u8 processor_id;
	u8 id;
	u32 lapic_flags;
};

struct acpi_madt_io_apic {
	struct acpi_subtable_header header;
	u8 id;
	u8 reserved;
	u32 address;
	u32 global_irq_base;
};

struct acpi_madt_interrupt_override {
	struct acpi_subtable_header header;
	u8 bus;
	u8 source_irq;
	u32 global_irq;
	u16 inti_flags;
} __attribute__((packed));

struct acpi_madt_nmi_source {
	struct acpi_subtable_header header;
	u16 inti_flags;
	u32 global_irq;
};

struct acpi_madt_local_apic_nmi {
	struct acpi_subtable_header header;
	u8 processor_id;
	u16 inti_flags;
	u8 lint;
} __attribute__((packed));

struct acpi_madt_local_apic_override {
	struct acpi_subtable_header header;
	u16 reserved;
	u64 address;
} __attribute__((packed));

struct acpi_madt_local_sapic {
	struct acpi_subtable_header header;
	u8 processor_id;
	u8 id;
	u8 eid;
	u8 reserved[3];
	u32 lapic_flags;
	u32 uid;
	char uid_string[1];
} __attribute__((packed));

struct acpi_madt_local_x2apic {
	struct acpi_subtable_header header;
	u16 reserved;
	u32 local_apic_id;
	u32 lapic_flags;
	u32 uid;
};

struct acpi_madt_local_x2apic_nmi {
	struct acpi_subtable_header header;
	u16 inti_flags;
	u32 uid;
	u8 lint;
	u8 reserved[3];
};

union acpi_subtable_headers {
	struct acpi_subtable_header common;
	struct acpi_hmat_structure hmat;
};

typedef int (*acpi_tbl_entry_handler)(union acpi_subtable_headers *, const long unsigned int);

struct acpi_subtable_proc {
	int id;
	acpi_tbl_entry_handler handler;
	int count;
};

typedef u32 phys_cpuid_t;

struct gpio_desc;

enum irq_alloc_type {
	X86_IRQ_ALLOC_TYPE_IOAPIC = 1,
	X86_IRQ_ALLOC_TYPE_HPET = 2,
	X86_IRQ_ALLOC_TYPE_MSI = 3,
	X86_IRQ_ALLOC_TYPE_MSIX = 4,
	X86_IRQ_ALLOC_TYPE_DMAR = 5,
	X86_IRQ_ALLOC_TYPE_UV = 6,
};

struct irq_alloc_info {
	enum irq_alloc_type type;
	u32 flags;
	const struct cpumask *mask;
	union {
		int unused;
		struct {
			int hpet_id;
			int hpet_index;
			void *hpet_data;
		};
		struct {
			struct pci_dev *msi_dev;
			irq_hw_number_t msi_hwirq;
		};
		struct {
			int ioapic_id;
			int ioapic_pin;
			int ioapic_node;
			u32 ioapic_trigger: 1;
			u32 ioapic_polarity: 1;
			u32 ioapic_valid: 1;
			struct IO_APIC_route_entry *ioapic_entry;
		};
		struct {
			int dmar_id;
			void *dmar_data;
		};
	};
};

struct circ_buf {
	char *buf;
	int head;
	int tail;
};

struct serial_icounter_struct {
	int cts;
	int dsr;
	int rng;
	int dcd;
	int rx;
	int tx;
	int frame;
	int overrun;
	int parity;
	int brk;
	int buf_overrun;
	int reserved[9];
};

struct serial_struct {
	int type;
	int line;
	unsigned int port;
	int irq;
	int flags;
	int xmit_fifo_size;
	int custom_divisor;
	int baud_base;
	short unsigned int close_delay;
	char io_type;
	char reserved_char[1];
	int hub6;
	short unsigned int closing_wait;
	short unsigned int closing_wait2;
	unsigned char *iomem_base;
	short unsigned int iomem_reg_shift;
	unsigned int port_high;
	long unsigned int iomap_base;
};

struct sysrq_key_op {
	void (* const handler)(int);
	const char * const help_msg;
	const char * const action_msg;
	const int enable_mask;
};

struct serial_rs485 {
	__u32 flags;
	__u32 delay_rts_before_send;
	__u32 delay_rts_after_send;
	__u32 padding[5];
};

struct serial_iso7816 {
	__u32 flags;
	__u32 tg;
	__u32 sc_fi;
	__u32 sc_di;
	__u32 clk;
	__u32 reserved[5];
};

struct uart_port;

struct uart_ops {
	unsigned int (*tx_empty)(struct uart_port *);
	void (*set_mctrl)(struct uart_port *, unsigned int);
	unsigned int (*get_mctrl)(struct uart_port *);
	void (*stop_tx)(struct uart_port *);
	void (*start_tx)(struct uart_port *);
	void (*throttle)(struct uart_port *);
	void (*unthrottle)(struct uart_port *);
	void (*send_xchar)(struct uart_port *, char);
	void (*stop_rx)(struct uart_port *);
	void (*enable_ms)(struct uart_port *);
	void (*break_ctl)(struct uart_port *, int);
	int (*startup)(struct uart_port *);
	void (*shutdown)(struct uart_port *);
	void (*flush_buffer)(struct uart_port *);
	void (*set_termios)(struct uart_port *, struct ktermios *, struct ktermios *);
	void (*set_ldisc)(struct uart_port *, struct ktermios *);
	void (*pm)(struct uart_port *, unsigned int, unsigned int);
	const char * (*type)(struct uart_port *);
	void (*release_port)(struct uart_port *);
	int (*request_port)(struct uart_port *);
	void (*config_port)(struct uart_port *, int);
	int (*verify_port)(struct uart_port *, struct serial_struct *);
	int (*ioctl)(struct uart_port *, unsigned int, long unsigned int);
};

struct uart_icount {
	__u32 cts;
	__u32 dsr;
	__u32 rng;
	__u32 dcd;
	__u32 rx;
	__u32 tx;
	__u32 frame;
	__u32 overrun;
	__u32 parity;
	__u32 brk;
	__u32 buf_overrun;
};

typedef unsigned int upf_t;

typedef unsigned int upstat_t;

struct uart_state;

struct uart_port {
	spinlock_t lock;
	long unsigned int iobase;
	unsigned char *membase;
	unsigned int (*serial_in)(struct uart_port *, int);
	void (*serial_out)(struct uart_port *, int, int);
	void (*set_termios)(struct uart_port *, struct ktermios *, struct ktermios *);
	void (*set_ldisc)(struct uart_port *, struct ktermios *);
	unsigned int (*get_mctrl)(struct uart_port *);
	void (*set_mctrl)(struct uart_port *, unsigned int);
	unsigned int (*get_divisor)(struct uart_port *, unsigned int, unsigned int *);
	void (*set_divisor)(struct uart_port *, unsigned int, unsigned int, unsigned int);
	int (*startup)(struct uart_port *);
	void (*shutdown)(struct uart_port *);
	void (*throttle)(struct uart_port *);
	void (*unthrottle)(struct uart_port *);
	int (*handle_irq)(struct uart_port *);
	void (*pm)(struct uart_port *, unsigned int, unsigned int);
	void (*handle_break)(struct uart_port *);
	int (*rs485_config)(struct uart_port *, struct serial_rs485 *);
	int (*iso7816_config)(struct uart_port *, struct serial_iso7816 *);
	unsigned int irq;
	long unsigned int irqflags;
	unsigned int uartclk;
	unsigned int fifosize;
	unsigned char x_char;
	unsigned char regshift;
	unsigned char iotype;
	unsigned char quirks;
	unsigned int read_status_mask;
	unsigned int ignore_status_mask;
	struct uart_state *state;
	struct uart_icount icount;
	struct console *cons;
	upf_t flags;
	upstat_t status;
	int hw_stopped;
	unsigned int mctrl;
	unsigned int timeout;
	unsigned int type;
	const struct uart_ops *ops;
	unsigned int custom_divisor;
	unsigned int line;
	unsigned int minor;
	resource_size_t mapbase;
	resource_size_t mapsize;
	struct device *dev;
	long unsigned int sysrq;
	unsigned int sysrq_ch;
	unsigned char has_sysrq;
	unsigned char sysrq_seq;
	unsigned char hub6;
	unsigned char suspended;
	const char *name;
	struct attribute_group *attr_group;
	const struct attribute_group **tty_groups;
	struct serial_rs485 rs485;
	struct gpio_desc *rs485_term_gpio;
	struct serial_iso7816 iso7816;
	void *private_data;
};

enum uart_pm_state {
	UART_PM_STATE_ON = 0,
	UART_PM_STATE_OFF = 3,
	UART_PM_STATE_UNDEFINED = 4,
};

struct uart_state {
	struct tty_port port;
	enum uart_pm_state pm_state;
	struct circ_buf xmit;
	atomic_t refcount;
	wait_queue_head_t remove_wait;
	struct uart_port *uart_port;
};

struct earlycon_device {
	struct console *con;
	struct uart_port port;
	char options[16];
	unsigned int baud;
};

struct earlycon_id {
	char name[15];
	char name_term;
	char compatible[128];
	int (*setup)(struct earlycon_device *, const char *);
};

enum ioapic_domain_type {
	IOAPIC_DOMAIN_INVALID = 0,
	IOAPIC_DOMAIN_LEGACY = 1,
	IOAPIC_DOMAIN_STRICT = 2,
	IOAPIC_DOMAIN_DYNAMIC = 3,
};

struct ioapic_domain_cfg {
	enum ioapic_domain_type type;
	const struct irq_domain_ops *ops;
	struct device_node *dev;
};

struct thermal_cooling_device_ops;

struct thermal_cooling_device {
	int id;
	char type[20];
	struct device device;
	struct device_node *np;
	void *devdata;
	void *stats;
	const struct thermal_cooling_device_ops *ops;
	bool updated;
	struct mutex lock;
	struct list_head thermal_instances;
	struct list_head node;
};

enum thermal_device_mode {
	THERMAL_DEVICE_DISABLED = 0,
	THERMAL_DEVICE_ENABLED = 1,
};

enum thermal_trip_type {
	THERMAL_TRIP_ACTIVE = 0,
	THERMAL_TRIP_PASSIVE = 1,
	THERMAL_TRIP_HOT = 2,
	THERMAL_TRIP_CRITICAL = 3,
};

enum thermal_trend {
	THERMAL_TREND_STABLE = 0,
	THERMAL_TREND_RAISING = 1,
	THERMAL_TREND_DROPPING = 2,
	THERMAL_TREND_RAISE_FULL = 3,
	THERMAL_TREND_DROP_FULL = 4,
};

enum thermal_notify_event {
	THERMAL_EVENT_UNSPECIFIED = 0,
	THERMAL_EVENT_TEMP_SAMPLE = 1,
	THERMAL_TRIP_VIOLATED = 2,
	THERMAL_TRIP_CHANGED = 3,
	THERMAL_DEVICE_DOWN = 4,
	THERMAL_DEVICE_UP = 5,
	THERMAL_DEVICE_POWER_CAPABILITY_CHANGED = 6,
	THERMAL_TABLE_CHANGED = 7,
};

struct thermal_zone_device;

struct thermal_zone_device_ops {
	int (*bind)(struct thermal_zone_device *, struct thermal_cooling_device *);
	int (*unbind)(struct thermal_zone_device *, struct thermal_cooling_device *);
	int (*get_temp)(struct thermal_zone_device *, int *);
	int (*set_trips)(struct thermal_zone_device *, int, int);
	int (*get_mode)(struct thermal_zone_device *, enum thermal_device_mode *);
	int (*set_mode)(struct thermal_zone_device *, enum thermal_device_mode);
	int (*get_trip_type)(struct thermal_zone_device *, int, enum thermal_trip_type *);
	int (*get_trip_temp)(struct thermal_zone_device *, int, int *);
	int (*set_trip_temp)(struct thermal_zone_device *, int, int);
	int (*get_trip_hyst)(struct thermal_zone_device *, int, int *);
	int (*set_trip_hyst)(struct thermal_zone_device *, int, int);
	int (*get_crit_temp)(struct thermal_zone_device *, int *);
	int (*set_emul_temp)(struct thermal_zone_device *, int);
	int (*get_trend)(struct thermal_zone_device *, int, enum thermal_trend *);
	int (*notify)(struct thermal_zone_device *, int, enum thermal_trip_type);
};

struct thermal_attr;

struct thermal_zone_params;

struct thermal_governor;

struct thermal_zone_device {
	int id;
	char type[20];
	struct device device;
	struct attribute_group trips_attribute_group;
	struct thermal_attr *trip_temp_attrs;
	struct thermal_attr *trip_type_attrs;
	struct thermal_attr *trip_hyst_attrs;
	void *devdata;
	int trips;
	long unsigned int trips_disabled;
	int passive_delay;
	int polling_delay;
	int temperature;
	int last_temperature;
	int emul_temperature;
	int passive;
	int prev_low_trip;
	int prev_high_trip;
	unsigned int forced_passive;
	atomic_t need_update;
	struct thermal_zone_device_ops *ops;
	struct thermal_zone_params *tzp;
	struct thermal_governor *governor;
	void *governor_data;
	struct list_head thermal_instances;
	struct ida ida;
	struct mutex lock;
	struct list_head node;
	struct delayed_work poll_queue;
	enum thermal_notify_event notify_event;
};

struct thermal_cooling_device_ops {
	int (*get_max_state)(struct thermal_cooling_device *, long unsigned int *);
	int (*get_cur_state)(struct thermal_cooling_device *, long unsigned int *);
	int (*set_cur_state)(struct thermal_cooling_device *, long unsigned int);
	int (*get_requested_power)(struct thermal_cooling_device *, struct thermal_zone_device *, u32 *);
	int (*state2power)(struct thermal_cooling_device *, struct thermal_zone_device *, long unsigned int, u32 *);
	int (*power2state)(struct thermal_cooling_device *, struct thermal_zone_device *, u32, long unsigned int *);
};

struct thermal_bind_params;

struct thermal_zone_params {
	char governor_name[20];
	bool no_hwmon;
	int num_tbps;
	struct thermal_bind_params *tbp;
	u32 sustainable_power;
	s32 k_po;
	s32 k_pu;
	s32 k_i;
	s32 k_d;
	s32 integral_cutoff;
	int slope;
	int offset;
};

struct thermal_governor {
	char name[20];
	int (*bind_to_tz)(struct thermal_zone_device *);
	void (*unbind_from_tz)(struct thermal_zone_device *);
	int (*throttle)(struct thermal_zone_device *, int);
	struct list_head governor_list;
};

struct thermal_bind_params {
	struct thermal_cooling_device *cdev;
	int weight;
	int trip_mask;
	long unsigned int *binding_limits;
	int (*match)(struct thermal_zone_device *, struct thermal_cooling_device *);
};

struct acpi_processor_cx {
	u8 valid;
	u8 type;
	u32 address;
	u8 entry_method;
	u8 index;
	u32 latency;
	u8 bm_sts_skip;
	char desc[32];
};

struct acpi_lpi_state {
	u32 min_residency;
	u32 wake_latency;
	u32 flags;
	u32 arch_flags;
	u32 res_cnt_freq;
	u32 enable_parent_state;
	u64 address;
	u8 index;
	u8 entry_method;
	char desc[32];
};

struct acpi_processor_power {
	int count;
	union {
		struct acpi_processor_cx states[8];
		struct acpi_lpi_state lpi_states[8];
	};
	int timer_broadcast_on_state;
};

struct acpi_psd_package {
	u64 num_entries;
	u64 revision;
	u64 domain;
	u64 coord_type;
	u64 num_processors;
};

struct acpi_pct_register {
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 reserved;
	u64 address;
} __attribute__((packed));

struct acpi_processor_px {
	u64 core_frequency;
	u64 power;
	u64 transition_latency;
	u64 bus_master_latency;
	u64 control;
	u64 status;
};

struct acpi_processor_performance {
	unsigned int state;
	unsigned int platform_limit;
	struct acpi_pct_register control_register;
	struct acpi_pct_register status_register;
	short: 16;
	unsigned int state_count;
	int: 32;
	struct acpi_processor_px *states;
	struct acpi_psd_package domain_info;
	cpumask_var_t shared_cpu_map;
	unsigned int shared_type;
	int: 32;
} __attribute__((packed));

struct acpi_tsd_package {
	u64 num_entries;
	u64 revision;
	u64 domain;
	u64 coord_type;
	u64 num_processors;
};

struct acpi_processor_tx_tss {
	u64 freqpercentage;
	u64 power;
	u64 transition_latency;
	u64 control;
	u64 status;
};

struct acpi_processor_tx {
	u16 power;
	u16 performance;
};

struct acpi_processor;

struct acpi_processor_throttling {
	unsigned int state;
	unsigned int platform_limit;
	struct acpi_pct_register control_register;
	struct acpi_pct_register status_register;
	short: 16;
	unsigned int state_count;
	int: 32;
	struct acpi_processor_tx_tss *states_tss;
	struct acpi_tsd_package domain_info;
	cpumask_var_t shared_cpu_map;
	int (*acpi_processor_get_throttling)(struct acpi_processor *);
	int (*acpi_processor_set_throttling)(struct acpi_processor *, int, bool);
	u32 address;
	u8 duty_offset;
	u8 duty_width;
	u8 tsd_valid_flag;
	char: 8;
	unsigned int shared_type;
	struct acpi_processor_tx states[16];
	int: 32;
} __attribute__((packed));

struct acpi_processor_flags {
	u8 power: 1;
	u8 performance: 1;
	u8 throttling: 1;
	u8 limit: 1;
	u8 bm_control: 1;
	u8 bm_check: 1;
	u8 has_cst: 1;
	u8 has_lpi: 1;
	u8 power_setup_done: 1;
	u8 bm_rld_set: 1;
	u8 need_hotplug_init: 1;
};

struct acpi_processor_lx {
	int px;
	int tx;
};

struct acpi_processor_limit {
	struct acpi_processor_lx state;
	struct acpi_processor_lx thermal;
	struct acpi_processor_lx user;
};

struct acpi_processor {
	acpi_handle handle;
	u32 acpi_id;
	phys_cpuid_t phys_id;
	u32 id;
	u32 pblk;
	int performance_platform_limit;
	int throttling_platform_limit;
	struct acpi_processor_flags flags;
	struct acpi_processor_power power;
	struct acpi_processor_performance *performance;
	struct acpi_processor_throttling throttling;
	struct acpi_processor_limit limit;
	struct thermal_cooling_device *cdev;
	struct device *dev;
	struct freq_qos_request perflib_req;
	struct freq_qos_request thermal_req;
};

struct acpi_processor_errata {
	u8 smp;
	struct {
		u8 throttle: 1;
		u8 fdma: 1;
		u8 reserved: 6;
		u32 bmisx;
	} piix4;
};

struct cpuidle_driver;

struct wakeup_header {
	u16 video_mode;
	u32 pmode_entry;
	u16 pmode_cs;
	u32 pmode_cr0;
	u32 pmode_cr3;
	u32 pmode_cr4;
	u32 pmode_efer_low;
	u32 pmode_efer_high;
	u64 pmode_gdt;
	u32 pmode_misc_en_low;
	u32 pmode_misc_en_high;
	u32 pmode_behavior;
	u32 realmode_flags;
	u32 real_magic;
	u32 signature;
} __attribute__((packed));

struct cpc_reg {
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_width;
	u64 address;
} __attribute__((packed));

struct acpi_power_register {
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 address;
} __attribute__((packed));

struct cstate_entry {
	struct {
		unsigned int eax;
		unsigned int ecx;
	} states[8];
};

typedef void (*nmi_shootdown_cb)(int, struct pt_regs *);

struct pci_ops___2;

struct cpuid_regs_done {
	struct cpuid_regs regs;
	struct completion done;
};

struct intel_early_ops {
	resource_size_t (*stolen_size)(int, int, int);
	resource_size_t (*stolen_base)(int, int, int, resource_size_t);
};

struct chipset {
	u32 vendor;
	u32 device;
	u32 class;
	u32 class_mask;
	u32 flags;
	void (*f)(int, int, int);
};

struct sched_domain_shared {
	atomic_t ref;
	atomic_t nr_busy_cpus;
	int has_idle_cores;
};

struct sched_group;

struct sched_domain {
	struct sched_domain *parent;
	struct sched_domain *child;
	struct sched_group *groups;
	long unsigned int min_interval;
	long unsigned int max_interval;
	unsigned int busy_factor;
	unsigned int imbalance_pct;
	unsigned int cache_nice_tries;
	int nohz_idle;
	int flags;
	int level;
	long unsigned int last_balance;
	unsigned int balance_interval;
	unsigned int nr_balance_failed;
	u64 max_newidle_lb_cost;
	long unsigned int next_decay_max_lb_cost;
	u64 avg_scan_cost;
	unsigned int lb_count[3];
	unsigned int lb_failed[3];
	unsigned int lb_balanced[3];
	unsigned int lb_imbalance[3];
	unsigned int lb_gained[3];
	unsigned int lb_hot_gained[3];
	unsigned int lb_nobusyg[3];
	unsigned int lb_nobusyq[3];
	unsigned int alb_count;
	unsigned int alb_failed;
	unsigned int alb_pushed;
	unsigned int sbe_count;
	unsigned int sbe_balanced;
	unsigned int sbe_pushed;
	unsigned int sbf_count;
	unsigned int sbf_balanced;
	unsigned int sbf_pushed;
	unsigned int ttwu_wake_remote;
	unsigned int ttwu_move_affine;
	unsigned int ttwu_move_balance;
	union {
		void *private;
		struct callback_head rcu;
	};
	struct sched_domain_shared *shared;
	unsigned int span_weight;
	long unsigned int span[0];
};

typedef const struct cpumask * (*sched_domain_mask_f)(int);

typedef int (*sched_domain_flags_f)();

struct sched_group_capacity;

struct sd_data {
	struct sched_domain **sd;
	struct sched_domain_shared **sds;
	struct sched_group **sg;
	struct sched_group_capacity **sgc;
};

struct sched_domain_topology_level {
	sched_domain_mask_f mask;
	sched_domain_flags_f sd_flags;
	int flags;
	int numa_level;
	struct sd_data data;
};

struct tsc_adjust {
	s64 bootval;
	s64 adjusted;
	long unsigned int nextcheck;
	bool warned;
};

enum {
	DUMP_PREFIX_NONE = 0,
	DUMP_PREFIX_ADDRESS = 1,
	DUMP_PREFIX_OFFSET = 2,
};

struct mpf_intel {
	char signature[4];
	unsigned int physptr;
	unsigned char length;
	unsigned char specification;
	unsigned char checksum;
	unsigned char feature1;
	unsigned char feature2;
	unsigned char feature3;
	unsigned char feature4;
	unsigned char feature5;
};

struct mpc_ioapic {
	unsigned char type;
	unsigned char apicid;
	unsigned char apicver;
	unsigned char flags;
	unsigned int apicaddr;
};

struct mpc_lintsrc {
	unsigned char type;
	unsigned char irqtype;
	short unsigned int irqflag;
	unsigned char srcbusid;
	unsigned char srcbusirq;
	unsigned char destapic;
	unsigned char destapiclint;
};

enum page_cache_mode {
	_PAGE_CACHE_MODE_WB = 0,
	_PAGE_CACHE_MODE_WC = 1,
	_PAGE_CACHE_MODE_UC_MINUS = 2,
	_PAGE_CACHE_MODE_UC = 3,
	_PAGE_CACHE_MODE_WT = 4,
	_PAGE_CACHE_MODE_WP = 5,
	_PAGE_CACHE_MODE_NUM = 8,
};

union apic_ir {
	long unsigned int map[4];
	u32 regs[8];
};

enum ioapic_irq_destination_types {
	dest_Fixed = 0,
	dest_LowestPrio = 1,
	dest_SMI = 2,
	dest__reserved_1 = 3,
	dest_NMI = 4,
	dest_INIT = 5,
	dest__reserved_2 = 6,
	dest_ExtINT = 7,
};

enum {
	IRQ_SET_MASK_OK = 0,
	IRQ_SET_MASK_OK_NOCOPY = 1,
	IRQ_SET_MASK_OK_DONE = 2,
};

enum {
	IRQD_TRIGGER_MASK = 15,
	IRQD_SETAFFINITY_PENDING = 256,
	IRQD_ACTIVATED = 512,
	IRQD_NO_BALANCING = 1024,
	IRQD_PER_CPU = 2048,
	IRQD_AFFINITY_SET = 4096,
	IRQD_LEVEL = 8192,
	IRQD_WAKEUP_STATE = 16384,
	IRQD_MOVE_PCNTXT = 32768,
	IRQD_IRQ_DISABLED = 65536,
	IRQD_IRQ_MASKED = 131072,
	IRQD_IRQ_INPROGRESS = 262144,
	IRQD_WAKEUP_ARMED = 524288,
	IRQD_FORWARDED_TO_VCPU = 1048576,
	IRQD_AFFINITY_MANAGED = 2097152,
	IRQD_IRQ_STARTED = 4194304,
	IRQD_MANAGED_SHUTDOWN = 8388608,
	IRQD_SINGLE_TARGET = 16777216,
	IRQD_DEFAULT_TRIGGER_SET = 33554432,
	IRQD_CAN_RESERVE = 67108864,
	IRQD_MSI_NOMASK_QUIRK = 134217728,
	IRQD_HANDLE_ENFORCE_IRQCTX = 268435456,
};

struct irq_cfg {
	unsigned int dest_apicid;
	unsigned int vector;
};

enum {
	IRQCHIP_FWNODE_REAL = 0,
	IRQCHIP_FWNODE_NAMED = 1,
	IRQCHIP_FWNODE_NAMED_ID = 2,
};

enum {
	X86_IRQ_ALLOC_CONTIGUOUS_VECTORS = 1,
	X86_IRQ_ALLOC_LEGACY = 2,
};

struct apic_chip_data {
	struct irq_cfg hw_irq_cfg;
	unsigned int vector;
	unsigned int prev_vector;
	unsigned int cpu;
	unsigned int prev_cpu;
	unsigned int irq;
	struct hlist_node clist;
	unsigned int move_in_progress: 1;
	unsigned int is_managed: 1;
	unsigned int can_reserve: 1;
	unsigned int has_reserved: 1;
};

struct irq_matrix;

union IO_APIC_reg_00 {
	u32 raw;
	struct {
		u32 __reserved_2: 14;
		u32 LTS: 1;
		u32 delivery_type: 1;
		u32 __reserved_1: 8;
		u32 ID: 8;
	} bits;
};

union IO_APIC_reg_01 {
	u32 raw;
	struct {
		u32 version: 8;
		u32 __reserved_2: 7;
		u32 PRQ: 1;
		u32 entries: 8;
		u32 __reserved_1: 8;
	} bits;
};

union IO_APIC_reg_02 {
	u32 raw;
	struct {
		u32 __reserved_2: 24;
		u32 arbitration: 4;
		u32 __reserved_1: 4;
	} bits;
};

union IO_APIC_reg_03 {
	u32 raw;
	struct {
		u32 boot_DT: 1;
		u32 __reserved_1: 31;
	} bits;
};

struct IR_IO_APIC_route_entry {
	__u64 vector: 8;
	__u64 zero: 3;
	__u64 index2: 1;
	__u64 delivery_status: 1;
	__u64 polarity: 1;
	__u64 irr: 1;
	__u64 trigger: 1;
	__u64 mask: 1;
	__u64 reserved: 31;
	__u64 format: 1;
	__u64 index: 15;
};

enum {
	IRQ_TYPE_NONE = 0,
	IRQ_TYPE_EDGE_RISING = 1,
	IRQ_TYPE_EDGE_FALLING = 2,
	IRQ_TYPE_EDGE_BOTH = 3,
	IRQ_TYPE_LEVEL_HIGH = 4,
	IRQ_TYPE_LEVEL_LOW = 8,
	IRQ_TYPE_LEVEL_MASK = 12,
	IRQ_TYPE_SENSE_MASK = 15,
	IRQ_TYPE_DEFAULT = 15,
	IRQ_TYPE_PROBE = 16,
	IRQ_LEVEL = 256,
	IRQ_PER_CPU = 512,
	IRQ_NOPROBE = 1024,
	IRQ_NOREQUEST = 2048,
	IRQ_NOAUTOEN = 4096,
	IRQ_NO_BALANCING = 8192,
	IRQ_MOVE_PCNTXT = 16384,
	IRQ_NESTED_THREAD = 32768,
	IRQ_NOTHREAD = 65536,
	IRQ_PER_CPU_DEVID = 131072,
	IRQ_IS_POLLED = 262144,
	IRQ_DISABLE_UNLAZY = 524288,
};

enum {
	IRQCHIP_SET_TYPE_MASKED = 1,
	IRQCHIP_EOI_IF_HANDLED = 2,
	IRQCHIP_MASK_ON_SUSPEND = 4,
	IRQCHIP_ONOFFLINE_ENABLED = 8,
	IRQCHIP_SKIP_SET_WAKE = 16,
	IRQCHIP_ONESHOT_SAFE = 32,
	IRQCHIP_EOI_THREADED = 64,
	IRQCHIP_SUPPORTS_LEVEL_MSI = 128,
	IRQCHIP_SUPPORTS_NMI = 256,
};

struct irq_pin_list {
	struct list_head list;
	int apic;
	int pin;
};

struct mp_chip_data {
	struct list_head irq_2_pin;
	struct IO_APIC_route_entry entry;
	int trigger;
	int polarity;
	u32 count;
	bool isa_irq;
};

struct mp_ioapic_gsi {
	u32 gsi_base;
	u32 gsi_end;
};

struct ioapic {
	int nr_registers;
	struct IO_APIC_route_entry *saved_registers;
	struct mpc_ioapic mp_config;
	struct mp_ioapic_gsi gsi_config;
	struct ioapic_domain_cfg irqdomain_cfg;
	struct irq_domain *irqdomain;
	struct resource *iomem_res;
};

struct io_apic {
	unsigned int index;
	unsigned int unused[3];
	unsigned int data;
	unsigned int unused2[11];
	unsigned int eoi;
};

union entry_union {
	struct {
		u32 w1;
		u32 w2;
	};
	struct IO_APIC_route_entry entry;
};

enum {
	IRQ_DOMAIN_FLAG_HIERARCHY = 1,
	IRQ_DOMAIN_NAME_ALLOCATED = 2,
	IRQ_DOMAIN_FLAG_IPI_PER_CPU = 4,
	IRQ_DOMAIN_FLAG_IPI_SINGLE = 8,
	IRQ_DOMAIN_FLAG_MSI = 16,
	IRQ_DOMAIN_FLAG_MSI_REMAP = 32,
	IRQ_DOMAIN_MSI_NOMASK_QUIRK = 64,
	IRQ_DOMAIN_FLAG_NONCORE = 65536,
};

typedef struct irq_alloc_info msi_alloc_info_t;

struct msi_domain_info;

struct msi_domain_ops {
	irq_hw_number_t (*get_hwirq)(struct msi_domain_info *, msi_alloc_info_t *);
	int (*msi_init)(struct irq_domain *, struct msi_domain_info *, unsigned int, irq_hw_number_t, msi_alloc_info_t *);
	void (*msi_free)(struct irq_domain *, struct msi_domain_info *, unsigned int);
	int (*msi_check)(struct irq_domain *, struct msi_domain_info *, struct device *);
	int (*msi_prepare)(struct irq_domain *, struct device *, int, msi_alloc_info_t *);
	void (*msi_finish)(msi_alloc_info_t *, int);
	void (*set_desc)(msi_alloc_info_t *, struct msi_desc *);
	int (*handle_error)(struct irq_domain *, struct msi_desc *, int);
};

struct msi_domain_info {
	u32 flags;
	struct msi_domain_ops *ops;
	struct irq_chip *chip;
	void *chip_data;
	irq_flow_handler_t handler;
	void *handler_data;
	const char *handler_name;
	void *data;
};

enum {
	MSI_FLAG_USE_DEF_DOM_OPS = 1,
	MSI_FLAG_USE_DEF_CHIP_OPS = 2,
	MSI_FLAG_MULTI_PCI_MSI = 4,
	MSI_FLAG_PCI_MSIX = 8,
	MSI_FLAG_ACTIVATE_EARLY = 16,
	MSI_FLAG_MUST_REACTIVATE = 32,
	MSI_FLAG_LEVEL_CAPABLE = 64,
};

struct hpet_channel;

struct x86_mapping_info {
	void * (*alloc_pgt_page)(void *);
	void *context;
	long unsigned int page_flag;
	long unsigned int offset;
	bool direct_gbpages;
	long unsigned int kernpg_flag;
};

struct kexec_file_ops;

struct init_pgtable_data {
	struct x86_mapping_info *info;
	pgd_t *level4p;
};

struct kretprobe_instance;

typedef int (*kretprobe_handler_t)(struct kretprobe_instance *, struct pt_regs *);

struct kretprobe;

struct kretprobe_instance {
	struct hlist_node hlist;
	struct kretprobe *rp;
	kprobe_opcode_t *ret_addr;
	struct task_struct *task;
	void *fp;
	char data[0];
};

struct kretprobe {
	struct kprobe kp;
	kretprobe_handler_t handler;
	kretprobe_handler_t entry_handler;
	int maxactive;
	int nmissed;
	size_t data_size;
	struct hlist_head free_instances;
	raw_spinlock_t lock;
};

typedef struct kprobe *pto_T_____14;

struct __arch_relative_insn {
	u8 op;
	s32 raddr;
} __attribute__((packed));

struct arch_optimized_insn {
	kprobe_opcode_t copied_insn[4];
	kprobe_opcode_t *insn;
	size_t size;
};

struct optimized_kprobe {
	struct kprobe kp;
	struct list_head list;
	struct arch_optimized_insn optinsn;
};

typedef __u64 Elf64_Off;

struct elf64_rela {
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
	Elf64_Sxword r_addend;
};

typedef struct elf64_rela Elf64_Rela;

struct elf64_hdr {
	unsigned char e_ident[16];
	Elf64_Half e_type;
	Elf64_Half e_machine;
	Elf64_Word e_version;
	Elf64_Addr e_entry;
	Elf64_Off e_phoff;
	Elf64_Off e_shoff;
	Elf64_Word e_flags;
	Elf64_Half e_ehsize;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;
	Elf64_Half e_shstrndx;
};

typedef struct elf64_hdr Elf64_Ehdr;

struct elf64_shdr {
	Elf64_Word sh_name;
	Elf64_Word sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
};

typedef struct elf64_shdr Elf64_Shdr;

struct hpet_data {
	long unsigned int hd_phys_address;
	void *hd_address;
	short unsigned int hd_nirqs;
	unsigned int hd_state;
	unsigned int hd_irq[32];
};

typedef irqreturn_t (*rtc_irq_handler)(int, void *);

enum hpet_mode {
	HPET_MODE_UNUSED = 0,
	HPET_MODE_LEGACY = 1,
	HPET_MODE_CLOCKEVT = 2,
	HPET_MODE_DEVICE = 3,
};

struct hpet_channel___2 {
	struct clock_event_device evt;
	unsigned int num;
	unsigned int cpu;
	unsigned int irq;
	unsigned int in_use;
	enum hpet_mode mode;
	unsigned int boot_cfg;
	char name[10];
	long: 48;
	long: 64;
	long: 64;
	long: 64;
};

struct hpet_base {
	unsigned int nr_channels;
	unsigned int nr_clockevents;
	unsigned int boot_cfg;
	struct hpet_channel___2 *channels;
};

union hpet_lock {
	struct {
		arch_spinlock_t lock;
		u32 value;
	};
	u64 lockval;
};

struct amd_northbridge_info {
	u16 num;
	u64 flags;
	struct amd_northbridge *nb;
};

struct scan_area {
	u64 addr;
	u64 size;
};

struct uprobe_xol_ops;

struct arch_uprobe {
	union {
		u8 insn[16];
		u8 ixol[16];
	};
	const struct uprobe_xol_ops *ops;
	union {
		struct {
			s32 offs;
			u8 ilen;
			u8 opc1;
		} branch;
		struct {
			u8 fixups;
			u8 ilen;
		} defparam;
		struct {
			u8 reg_offset;
			u8 ilen;
		} push;
	};
};

struct uprobe_xol_ops {
	bool (*emulate)(struct arch_uprobe *, struct pt_regs *);
	int (*pre_xol)(struct arch_uprobe *, struct pt_regs *);
	int (*post_xol)(struct arch_uprobe *, struct pt_regs *);
	void (*abort)(struct arch_uprobe *, struct pt_regs *);
};

enum rp_check {
	RP_CHECK_CALL = 0,
	RP_CHECK_CHAIN_CALL = 1,
	RP_CHECK_RET = 2,
};

struct fb_fix_screeninfo {
	char id[16];
	long unsigned int smem_start;
	__u32 smem_len;
	__u32 type;
	__u32 type_aux;
	__u32 visual;
	__u16 xpanstep;
	__u16 ypanstep;
	__u16 ywrapstep;
	__u32 line_length;
	long unsigned int mmio_start;
	__u32 mmio_len;
	__u32 accel;
	__u16 capabilities;
	__u16 reserved[2];
};

struct fb_bitfield {
	__u32 offset;
	__u32 length;
	__u32 msb_right;
};

struct fb_var_screeninfo {
	__u32 xres;
	__u32 yres;
	__u32 xres_virtual;
	__u32 yres_virtual;
	__u32 xoffset;
	__u32 yoffset;
	__u32 bits_per_pixel;
	__u32 grayscale;
	struct fb_bitfield red;
	struct fb_bitfield green;
	struct fb_bitfield blue;
	struct fb_bitfield transp;
	__u32 nonstd;
	__u32 activate;
	__u32 height;
	__u32 width;
	__u32 accel_flags;
	__u32 pixclock;
	__u32 left_margin;
	__u32 right_margin;
	__u32 upper_margin;
	__u32 lower_margin;
	__u32 hsync_len;
	__u32 vsync_len;
	__u32 sync;
	__u32 vmode;
	__u32 rotate;
	__u32 colorspace;
	__u32 reserved[4];
};

struct fb_cmap {
	__u32 start;
	__u32 len;
	__u16 *red;
	__u16 *green;
	__u16 *blue;
	__u16 *transp;
};

struct fb_copyarea {
	__u32 dx;
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 sx;
	__u32 sy;
};

struct fb_fillrect {
	__u32 dx;
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 color;
	__u32 rop;
};

struct fb_image {
	__u32 dx;
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 fg_color;
	__u32 bg_color;
	__u8 depth;
	const char *data;
	struct fb_cmap cmap;
};

struct fbcurpos {
	__u16 x;
	__u16 y;
};

struct fb_cursor {
	__u16 set;
	__u16 enable;
	__u16 rop;
	const char *mask;
	struct fbcurpos hot;
	struct fb_image image;
};

struct fb_chroma {
	__u32 redx;
	__u32 greenx;
	__u32 bluex;
	__u32 whitex;
	__u32 redy;
	__u32 greeny;
	__u32 bluey;
	__u32 whitey;
};

struct fb_videomode;

struct fb_monspecs {
	struct fb_chroma chroma;
	struct fb_videomode *modedb;
	__u8 manufacturer[4];
	__u8 monitor[14];
	__u8 serial_no[14];
	__u8 ascii[14];
	__u32 modedb_len;
	__u32 model;
	__u32 serial;
	__u32 year;
	__u32 week;
	__u32 hfmin;
	__u32 hfmax;
	__u32 dclkmin;
	__u32 dclkmax;
	__u16 input;
	__u16 dpms;
	__u16 signal;
	__u16 vfmin;
	__u16 vfmax;
	__u16 gamma;
	__u16 gtf: 1;
	__u16 misc;
	__u8 version;
	__u8 revision;
	__u8 max_x;
	__u8 max_y;
};

struct fb_info;

struct fb_pixmap {
	u8 *addr;
	u32 size;
	u32 offset;
	u32 buf_align;
	u32 scan_align;
	u32 access_align;
	u32 flags;
	u32 blit_x;
	u32 blit_y;
	void (*writeio)(struct fb_info *, void *, void *, unsigned int);
	void (*readio)(struct fb_info *, void *, void *, unsigned int);
};

struct fb_deferred_io;

struct fb_ops;

struct fb_tile_ops;

struct apertures_struct;

struct fb_info {
	atomic_t count;
	int node;
	int flags;
	int fbcon_rotate_hint;
	struct mutex lock;
	struct mutex mm_lock;
	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;
	struct fb_monspecs monspecs;
	struct work_struct queue;
	struct fb_pixmap pixmap;
	struct fb_pixmap sprite;
	struct fb_cmap cmap;
	struct list_head modelist;
	struct fb_videomode *mode;
	struct delayed_work deferred_work;
	struct fb_deferred_io *fbdefio;
	const struct fb_ops *fbops;
	struct device *device;
	struct device *dev;
	int class_flag;
	struct fb_tile_ops *tileops;
	union {
		char *screen_base;
		char *screen_buffer;
	};
	long unsigned int screen_size;
	void *pseudo_palette;
	u32 state;
	void *fbcon_par;
	void *par;
	struct apertures_struct *apertures;
	bool skip_vt_switch;
};

struct fb_videomode {
	const char *name;
	u32 refresh;
	u32 xres;
	u32 yres;
	u32 pixclock;
	u32 left_margin;
	u32 right_margin;
	u32 upper_margin;
	u32 lower_margin;
	u32 hsync_len;
	u32 vsync_len;
	u32 sync;
	u32 vmode;
	u32 flag;
};

struct fb_blit_caps {
	u32 x;
	u32 y;
	u32 len;
	u32 flags;
};

struct fb_deferred_io {
	long unsigned int delay;
	struct mutex lock;
	struct list_head pagelist;
	void (*first_io)(struct fb_info *);
	void (*deferred_io)(struct fb_info *, struct list_head *);
};

struct fb_ops {
	struct module *owner;
	int (*fb_open)(struct fb_info *, int);
	int (*fb_release)(struct fb_info *, int);
	ssize_t (*fb_read)(struct fb_info *, char *, size_t, loff_t *);
	ssize_t (*fb_write)(struct fb_info *, const char *, size_t, loff_t *);
	int (*fb_check_var)(struct fb_var_screeninfo *, struct fb_info *);
	int (*fb_set_par)(struct fb_info *);
	int (*fb_setcolreg)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, struct fb_info *);
	int (*fb_setcmap)(struct fb_cmap *, struct fb_info *);
	int (*fb_blank)(int, struct fb_info *);
	int (*fb_pan_display)(struct fb_var_screeninfo *, struct fb_info *);
	void (*fb_fillrect)(struct fb_info *, const struct fb_fillrect *);
	void (*fb_copyarea)(struct fb_info *, const struct fb_copyarea *);
	void (*fb_imageblit)(struct fb_info *, const struct fb_image *);
	int (*fb_cursor)(struct fb_info *, struct fb_cursor *);
	int (*fb_sync)(struct fb_info *);
	int (*fb_ioctl)(struct fb_info *, unsigned int, long unsigned int);
	int (*fb_compat_ioctl)(struct fb_info *, unsigned int, long unsigned int);
	int (*fb_mmap)(struct fb_info *, struct vm_area_struct *);
	void (*fb_get_caps)(struct fb_info *, struct fb_blit_caps *, struct fb_var_screeninfo *);
	void (*fb_destroy)(struct fb_info *);
	int (*fb_debug_enter)(struct fb_info *);
	int (*fb_debug_leave)(struct fb_info *);
};

struct fb_tilemap {
	__u32 width;
	__u32 height;
	__u32 depth;
	__u32 length;
	const __u8 *data;
};

struct fb_tilerect {
	__u32 sx;
	__u32 sy;
	__u32 width;
	__u32 height;
	__u32 index;
	__u32 fg;
	__u32 bg;
	__u32 rop;
};

struct fb_tilearea {
	__u32 sx;
	__u32 sy;
	__u32 dx;
	__u32 dy;
	__u32 width;
	__u32 height;
};

struct fb_tileblit {
	__u32 sx;
	__u32 sy;
	__u32 width;
	__u32 height;
	__u32 fg;
	__u32 bg;
	__u32 length;
	__u32 *indices;
};

struct fb_tilecursor {
	__u32 sx;
	__u32 sy;
	__u32 mode;
	__u32 shape;
	__u32 fg;
	__u32 bg;
};

struct fb_tile_ops {
	void (*fb_settile)(struct fb_info *, struct fb_tilemap *);
	void (*fb_tilecopy)(struct fb_info *, struct fb_tilearea *);
	void (*fb_tilefill)(struct fb_info *, struct fb_tilerect *);
	void (*fb_tileblit)(struct fb_info *, struct fb_tileblit *);
	void (*fb_tilecursor)(struct fb_info *, struct fb_tilecursor *);
	int (*fb_get_tilemax)(struct fb_info *);
};

struct aperture {
	resource_size_t base;
	resource_size_t size;
};

struct apertures_struct {
	unsigned int count;
	struct aperture ranges[0];
};

struct dmt_videomode {
	u32 dmt_id;
	u32 std_2byte_code;
	u32 cvt_3byte_code;
	const struct fb_videomode *mode;
};

struct simplefb_platform_data {
	u32 width;
	u32 height;
	u32 stride;
	const char *format;
};

struct efifb_dmi_info {
	char *optname;
	long unsigned int base;
	int stride;
	int width;
	int height;
	int flags;
};

enum {
	M_I17 = 0,
	M_I20 = 1,
	M_I20_SR = 2,
	M_I24 = 3,
	M_I24_8_1 = 4,
	M_I24_10_1 = 5,
	M_I27_11_1 = 6,
	M_MINI = 7,
	M_MINI_3_1 = 8,
	M_MINI_4_1 = 9,
	M_MB = 10,
	M_MB_2 = 11,
	M_MB_3 = 12,
	M_MB_5_1 = 13,
	M_MB_6_1 = 14,
	M_MB_7_1 = 15,
	M_MB_SR = 16,
	M_MBA = 17,
	M_MBA_3 = 18,
	M_MBP = 19,
	M_MBP_2 = 20,
	M_MBP_2_2 = 21,
	M_MBP_SR = 22,
	M_MBP_4 = 23,
	M_MBP_5_1 = 24,
	M_MBP_5_2 = 25,
	M_MBP_5_3 = 26,
	M_MBP_6_1 = 27,
	M_MBP_6_2 = 28,
	M_MBP_7_1 = 29,
	M_MBP_8_2 = 30,
	M_UNKNOWN = 31,
};

enum {
	OVERRIDE_NONE = 0,
	OVERRIDE_BASE = 1,
	OVERRIDE_STRIDE = 2,
	OVERRIDE_HEIGHT = 4,
	OVERRIDE_WIDTH = 8,
};

enum perf_sample_regs_abi {
	PERF_SAMPLE_REGS_ABI_NONE = 0,
	PERF_SAMPLE_REGS_ABI_32 = 1,
	PERF_SAMPLE_REGS_ABI_64 = 2,
};

struct __va_list_tag {
	unsigned int gp_offset;
	unsigned int fp_offset;
	void *overflow_arg_area;
	void *reg_save_area;
};

typedef __builtin_va_list __gnuc_va_list;

typedef __gnuc_va_list va_list;

struct va_format {
	const char *fmt;
	va_list *va;
};

struct pci_hostbridge_probe {
	u32 bus;
	u32 slot;
	u32 vendor;
	u32 device;
};

typedef u8 uint8_t;

typedef u16 uint16_t;

enum pg_level {
	PG_LEVEL_NONE = 0,
	PG_LEVEL_4K = 1,
	PG_LEVEL_2M = 2,
	PG_LEVEL_1G = 3,
	PG_LEVEL_512G = 4,
	PG_LEVEL_NUM = 5,
};

struct trace_print_flags {
	long unsigned int mask;
	const char *name;
};

enum tlb_flush_reason {
	TLB_FLUSH_ON_TASK_SWITCH = 0,
	TLB_REMOTE_SHOOTDOWN = 1,
	TLB_LOCAL_SHOOTDOWN = 2,
	TLB_LOCAL_MM_SHOOTDOWN = 3,
	TLB_REMOTE_SEND_IPI = 4,
	NR_TLB_FLUSH_REASONS = 5,
};

enum {
	REGION_INTERSECTS = 0,
	REGION_DISJOINT = 1,
	REGION_MIXED = 2,
};

struct trace_event_raw_tlb_flush {
	struct trace_entry ent;
	int reason;
	long unsigned int pages;
	char __data[0];
};

struct trace_event_data_offsets_tlb_flush {};

typedef void (*btf_trace_tlb_flush)(void *, int, long unsigned int);

struct map_range {
	long unsigned int start;
	long unsigned int end;
	unsigned int page_size_mask;
};

enum kcore_type {
	KCORE_TEXT = 0,
	KCORE_VMALLOC = 1,
	KCORE_RAM = 2,
	KCORE_VMEMMAP = 3,
	KCORE_USER = 4,
	KCORE_OTHER = 5,
	KCORE_REMAP = 6,
};

struct kcore_list {
	struct list_head list;
	long unsigned int addr;
	long unsigned int vaddr;
	size_t size;
	int type;
};

struct trace_event_raw_x86_exceptions {
	struct trace_entry ent;
	long unsigned int address;
	long unsigned int ip;
	long unsigned int error_code;
	char __data[0];
};

struct trace_event_data_offsets_x86_exceptions {};

typedef void (*btf_trace_page_fault_user)(void *, long unsigned int, struct pt_regs *, long unsigned int);

typedef void (*btf_trace_page_fault_kernel)(void *, long unsigned int, struct pt_regs *, long unsigned int);

enum {
	IORES_MAP_SYSTEM_RAM = 1,
	IORES_MAP_ENCRYPTED = 2,
};

struct ioremap_desc {
	unsigned int flags;
};

typedef bool (*ex_handler_t)(const struct exception_table_entry *, struct pt_regs *, int, long unsigned int, long unsigned int);

struct flush_tlb_info {
	struct mm_struct *mm;
	long unsigned int start;
	long unsigned int end;
	u64 new_tlb_gen;
	unsigned int stride_shift;
	bool freed_tables;
};

typedef struct mm_struct *pto_T_____15;

struct exception_stacks {
	char DF_stack_guard[0];
	char DF_stack[4096];
	char NMI_stack_guard[0];
	char NMI_stack[4096];
	char DB_stack_guard[0];
	char DB_stack[4096];
	char MCE_stack_guard[0];
	char MCE_stack[4096];
	char IST_top_guard[0];
};

struct cpa_data {
	long unsigned int *vaddr;
	pgd_t *pgd;
	pgprot_t mask_set;
	pgprot_t mask_clr;
	long unsigned int numpages;
	long unsigned int curpage;
	long unsigned int pfn;
	unsigned int flags;
	unsigned int force_split: 1;
	unsigned int force_static_prot: 1;
	unsigned int force_flush_all: 1;
	struct page **pages;
};

enum cpa_warn {
	CPA_CONFLICT = 0,
	CPA_PROTECT = 1,
	CPA_DETECT = 2,
};

typedef struct {
	u64 val;
} pfn_t;

struct memtype {
	u64 start;
	u64 end;
	u64 subtree_max_end;
	enum page_cache_mode type;
	struct rb_node rb;
};

enum {
	PAT_UC = 0,
	PAT_WC = 1,
	PAT_WT = 4,
	PAT_WP = 5,
	PAT_WB = 6,
	PAT_UC_MINUS = 7,
};

struct pagerange_state {
	long unsigned int cur_pfn;
	int ram;
	int not_ram;
};

struct rb_augment_callbacks {
	void (*propagate)(struct rb_node *, struct rb_node *);
	void (*copy)(struct rb_node *, struct rb_node *);
	void (*rotate)(struct rb_node *, struct rb_node *);
};

enum {
	MEMTYPE_EXACT_MATCH = 0,
	MEMTYPE_END_MATCH = 1,
};

struct hugepage_subpool {
	spinlock_t lock;
	long int count;
	long int max_hpages;
	long int used_hpages;
	struct hstate *hstate;
	long int min_hpages;
	long int rsv_hpages;
};

struct hugetlbfs_sb_info {
	long int max_inodes;
	long int free_inodes;
	spinlock_t stat_lock;
	struct hstate *hstate;
	struct hugepage_subpool *spool;
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
};

struct numa_memblk {
	u64 start;
	u64 end;
	int nid;
};

struct numa_meminfo {
	int nr_blks;
	struct numa_memblk blk[128];
};

struct acpi_srat_cpu_affinity {
	struct acpi_subtable_header header;
	u8 proximity_domain_lo;
	u8 apic_id;
	u32 flags;
	u8 local_sapic_eid;
	u8 proximity_domain_hi[3];
	u32 clock_domain;
};

struct acpi_srat_x2apic_cpu_affinity {
	struct acpi_subtable_header header;
	u16 reserved;
	u32 proximity_domain;
	u32 apic_id;
	u32 flags;
	u32 clock_domain;
	u32 reserved2;
};

enum uv_system_type {
	UV_NONE = 0,
	UV_LEGACY_APIC = 1,
	UV_X2APIC = 2,
	UV_NON_UNIQUE_APIC = 3,
};

struct kaslr_memory_region {
	long unsigned int *base;
	long unsigned int size_tb;
};

enum pti_mode {
	PTI_AUTO = 0,
	PTI_FORCE_OFF = 1,
	PTI_FORCE_ON = 2,
};

enum pti_clone_level {
	PTI_CLONE_PMD = 0,
	PTI_CLONE_PTE = 1,
};

struct sigcontext_32 {
	__u16 gs;
	__u16 __gsh;
	__u16 fs;
	__u16 __fsh;
	__u16 es;
	__u16 __esh;
	__u16 ds;
	__u16 __dsh;
	__u32 di;
	__u32 si;
	__u32 bp;
	__u32 sp;
	__u32 bx;
	__u32 dx;
	__u32 cx;
	__u32 ax;
	__u32 trapno;
	__u32 err;
	__u32 ip;
	__u16 cs;
	__u16 __csh;
	__u32 flags;
	__u32 sp_at_signal;
	__u16 ss;
	__u16 __ssh;
	__u32 fpstate;
	__u32 oldmask;
	__u32 cr2;
};

typedef u32 compat_size_t;

struct compat_sigaltstack {
	compat_uptr_t ss_sp;
	int ss_flags;
	compat_size_t ss_size;
};

typedef struct compat_sigaltstack compat_stack_t;

struct ucontext_ia32 {
	unsigned int uc_flags;
	unsigned int uc_link;
	compat_stack_t uc_stack;
	struct sigcontext_32 uc_mcontext;
	compat_sigset_t uc_sigmask;
};

struct sigframe_ia32 {
	u32 pretcode;
	int sig;
	struct sigcontext_32 sc;
	struct _fpstate_32 fpstate_unused;
	unsigned int extramask[1];
	char retcode[8];
};

struct rt_sigframe_ia32 {
	u32 pretcode;
	int sig;
	u32 pinfo;
	u32 puc;
	compat_siginfo_t info;
	struct ucontext_ia32 uc;
	char retcode[8];
};

typedef struct {
	efi_guid_t guid;
	u64 table;
} efi_config_table_64_t;

struct efi_memory_map_data {
	phys_addr_t phys_map;
	long unsigned int size;
	long unsigned int desc_version;
	long unsigned int desc_size;
	long unsigned int flags;
};

struct efi_mem_range {
	struct range range;
	u64 attribute;
};

struct efi_setup_data {
	u64 fw_vendor;
	u64 __unused;
	u64 tables;
	u64 smbios;
	u64 reserved[8];
};

typedef struct {
	efi_guid_t guid;
	long unsigned int *ptr;
	const char name[16];
} efi_config_table_type_t;

typedef struct {
	efi_table_hdr_t hdr;
	u64 fw_vendor;
	u32 fw_revision;
	u32 __pad1;
	u64 con_in_handle;
	u64 con_in;
	u64 con_out_handle;
	u64 con_out;
	u64 stderr_handle;
	u64 stderr;
	u64 runtime;
	u64 boottime;
	u32 nr_tables;
	u32 __pad2;
	u64 tables;
} efi_system_table_64_t;

typedef struct {
	efi_table_hdr_t hdr;
	u32 fw_vendor;
	u32 fw_revision;
	u32 con_in_handle;
	u32 con_in;
	u32 con_out_handle;
	u32 con_out;
	u32 stderr_handle;
	u32 stderr;
	u32 runtime;
	u32 boottime;
	u32 nr_tables;
	u32 tables;
} efi_system_table_32_t;

typedef struct {
	u32 version;
	u32 length;
	u64 memory_protection_attribute;
} efi_properties_table_t;

union efi_boot_services;

typedef union efi_boot_services efi_boot_services_t;

union efi_simple_text_input_protocol;

typedef union efi_simple_text_input_protocol efi_simple_text_input_protocol_t;

union efi_simple_text_output_protocol;

typedef union efi_simple_text_output_protocol efi_simple_text_output_protocol_t;

typedef union {
	struct {
		efi_table_hdr_t hdr;
		long unsigned int fw_vendor;
		u32 fw_revision;
		long unsigned int con_in_handle;
		efi_simple_text_input_protocol_t *con_in;
		long unsigned int con_out_handle;
		efi_simple_text_output_protocol_t *con_out;
		long unsigned int stderr_handle;
		long unsigned int stderr;
		efi_runtime_services_t *runtime;
		efi_boot_services_t *boottime;
		long unsigned int nr_tables;
		long unsigned int tables;
	};
	efi_system_table_32_t mixed_mode;
} efi_system_table_t;

struct wait_queue_entry;

typedef int (*wait_queue_func_t)(struct wait_queue_entry *, unsigned int, int, void *);

struct wait_queue_entry {
	unsigned int flags;
	void *private;
	wait_queue_func_t func;
	struct list_head entry;
};

struct pm_qos_request {
	struct plist_node node;
	struct pm_qos_constraints *qos;
};

enum {
	BPF_REG_0 = 0,
	BPF_REG_1 = 1,
	BPF_REG_2 = 2,
	BPF_REG_3 = 3,
	BPF_REG_4 = 4,
	BPF_REG_5 = 5,
	BPF_REG_6 = 6,
	BPF_REG_7 = 7,
	BPF_REG_8 = 8,
	BPF_REG_9 = 9,
	BPF_REG_10 = 10,
	__MAX_BPF_REG = 11,
};

struct bpf_tramp_progs {
	struct bpf_prog *progs[40];
	int nr_progs;
};

enum bpf_jit_poke_reason {
	BPF_POKE_REASON_TAIL_CALL = 0,
};

struct bpf_array_aux {
	enum bpf_prog_type type;
	bool jited;
	struct list_head poke_progs;
	struct bpf_map *map;
	struct mutex poke_mutex;
	struct work_struct work;
};

struct bpf_array {
	struct bpf_map map;
	u32 elem_size;
	u32 index_mask;
	struct bpf_array_aux *aux;
	union {
		char value[0];
		void *ptrs[0];
		void *pptrs[0];
	};
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum bpf_text_poke_type {
	BPF_MOD_CALL = 0,
	BPF_MOD_JUMP = 1,
};

struct bpf_binary_header {
	u32 pages;
	int: 32;
	u8 image[0];
};

struct jit_context {
	int cleanup_addr;
};

struct x64_jit_data {
	struct bpf_binary_header *header;
	int *addrs;
	u8 *image;
	int proglen;
	struct jit_context ctx;
};

enum tk_offsets {
	TK_OFFS_REAL = 0,
	TK_OFFS_BOOT = 1,
	TK_OFFS_TAI = 2,
	TK_OFFS_MAX = 3,
};

struct clone_args {
	__u64 flags;
	__u64 pidfd;
	__u64 child_tid;
	__u64 parent_tid;
	__u64 exit_signal;
	__u64 stack;
	__u64 stack_size;
	__u64 tls;
	__u64 set_tid;
	__u64 set_tid_size;
	__u64 cgroup;
};

struct fdtable {
	unsigned int max_fds;
	struct file **fd;
	long unsigned int *close_on_exec;
	long unsigned int *open_fds;
	long unsigned int *full_fds_bits;
	struct callback_head rcu;
};

struct files_struct {
	atomic_t count;
	bool resize_in_progress;
	wait_queue_head_t resize_wait;
	struct fdtable *fdt;
	struct fdtable fdtab;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t file_lock;
	unsigned int next_fd;
	long unsigned int close_on_exec_init[1];
	long unsigned int open_fds_init[1];
	long unsigned int full_fds_bits_init[1];
	struct file *fd_array[64];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct robust_list {
	struct robust_list *next;
};

struct robust_list_head {
	struct robust_list list;
	long int futex_offset;
	struct robust_list *list_op_pending;
};

struct multiprocess_signals {
	sigset_t signal;
	struct hlist_node node;
};

typedef int (*proc_visitor)(struct task_struct *, void *);

enum {
	IOPRIO_CLASS_NONE = 0,
	IOPRIO_CLASS_RT = 1,
	IOPRIO_CLASS_BE = 2,
	IOPRIO_CLASS_IDLE = 3,
};

enum memcg_stat_item {
	MEMCG_SWAP = 33,
	MEMCG_SOCK = 34,
	MEMCG_KERNEL_STACK_KB = 35,
	MEMCG_NR_STAT = 36,
};

typedef struct poll_table_struct poll_table;

enum {
	FUTEX_STATE_OK = 0,
	FUTEX_STATE_EXITING = 1,
	FUTEX_STATE_DEAD = 2,
};

enum proc_hidepid {
	HIDEPID_OFF = 0,
	HIDEPID_NO_ACCESS = 1,
	HIDEPID_INVISIBLE = 2,
	HIDEPID_NOT_PTRACEABLE = 4,
};

enum proc_pidonly {
	PROC_PIDONLY_OFF = 0,
	PROC_PIDONLY_ON = 1,
};

struct proc_fs_info {
	struct pid_namespace *pid_ns;
	struct dentry *proc_self;
	struct dentry *proc_thread_self;
	kgid_t pid_gid;
	enum proc_hidepid hide_pid;
	enum proc_pidonly pidonly;
};

struct trace_event_raw_task_newtask {
	struct trace_entry ent;
	pid_t pid;
	char comm[16];
	long unsigned int clone_flags;
	short int oom_score_adj;
	char __data[0];
};

struct trace_event_raw_task_rename {
	struct trace_entry ent;
	pid_t pid;
	char oldcomm[16];
	char newcomm[16];
	short int oom_score_adj;
	char __data[0];
};

struct trace_event_data_offsets_task_newtask {};

struct trace_event_data_offsets_task_rename {};

typedef void (*btf_trace_task_newtask)(void *, struct task_struct *, long unsigned int);

typedef void (*btf_trace_task_rename)(void *, struct task_struct *, const char *);

typedef long unsigned int pao_T_____3;

enum kmsg_dump_reason {
	KMSG_DUMP_UNDEF = 0,
	KMSG_DUMP_PANIC = 1,
	KMSG_DUMP_OOPS = 2,
	KMSG_DUMP_EMERG = 3,
	KMSG_DUMP_SHUTDOWN = 4,
	KMSG_DUMP_MAX = 5,
};

struct vt_mode {
	char mode;
	char waitv;
	short int relsig;
	short int acqsig;
	short int frsig;
};

struct console_font {
	unsigned int width;
	unsigned int height;
	unsigned int charcount;
	unsigned char *data;
};

struct uni_pagedir;

struct uni_screen;

struct vc_data {
	struct tty_port port;
	short unsigned int vc_num;
	unsigned int vc_cols;
	unsigned int vc_rows;
	unsigned int vc_size_row;
	unsigned int vc_scan_lines;
	long unsigned int vc_origin;
	long unsigned int vc_scr_end;
	long unsigned int vc_visible_origin;
	unsigned int vc_top;
	unsigned int vc_bottom;
	const struct consw *vc_sw;
	short unsigned int *vc_screenbuf;
	unsigned int vc_screenbuf_size;
	unsigned char vc_mode;
	unsigned char vc_attr;
	unsigned char vc_def_color;
	unsigned char vc_color;
	unsigned char vc_s_color;
	unsigned char vc_ulcolor;
	unsigned char vc_itcolor;
	unsigned char vc_halfcolor;
	unsigned int vc_cursor_type;
	short unsigned int vc_complement_mask;
	short unsigned int vc_s_complement_mask;
	unsigned int vc_x;
	unsigned int vc_y;
	unsigned int vc_saved_x;
	unsigned int vc_saved_y;
	long unsigned int vc_pos;
	short unsigned int vc_hi_font_mask;
	struct console_font vc_font;
	short unsigned int vc_video_erase_char;
	unsigned int vc_state;
	unsigned int vc_npar;
	unsigned int vc_par[16];
	struct vt_mode vt_mode;
	struct pid *vt_pid;
	int vt_newvt;
	wait_queue_head_t paste_wait;
	unsigned int vc_charset: 1;
	unsigned int vc_s_charset: 1;
	unsigned int vc_disp_ctrl: 1;
	unsigned int vc_toggle_meta: 1;
	unsigned int vc_decscnm: 1;
	unsigned int vc_decom: 1;
	unsigned int vc_decawm: 1;
	unsigned int vc_deccm: 1;
	unsigned int vc_decim: 1;
	unsigned int vc_intensity: 2;
	unsigned int vc_italic: 1;
	unsigned int vc_underline: 1;
	unsigned int vc_blink: 1;
	unsigned int vc_reverse: 1;
	unsigned int vc_s_intensity: 2;
	unsigned int vc_s_italic: 1;
	unsigned int vc_s_underline: 1;
	unsigned int vc_s_blink: 1;
	unsigned int vc_s_reverse: 1;
	unsigned int vc_priv: 3;
	unsigned int vc_need_wrap: 1;
	unsigned int vc_can_do_color: 1;
	unsigned int vc_report_mouse: 2;
	unsigned char vc_utf: 1;
	unsigned char vc_utf_count;
	int vc_utf_char;
	unsigned int vc_tab_stop[8];
	unsigned char vc_palette[48];
	short unsigned int *vc_translate;
	unsigned char vc_G0_charset;
	unsigned char vc_G1_charset;
	unsigned char vc_saved_G0;
	unsigned char vc_saved_G1;
	unsigned int vc_resize_user;
	unsigned int vc_bell_pitch;
	unsigned int vc_bell_duration;
	short unsigned int vc_cur_blink_ms;
	struct vc_data **vc_display_fg;
	struct uni_pagedir *vc_uni_pagedir;
	struct uni_pagedir **vc_uni_pagedir_loc;
	struct uni_screen *vc_uni_screen;
};

struct vc {
	struct vc_data *d;
	struct work_struct SAK_work;
};

struct vt_spawn_console {
	spinlock_t lock;
	struct pid *pid;
	int sig;
};

enum con_flush_mode {
	CONSOLE_FLUSH_PENDING = 0,
	CONSOLE_REPLAY_ALL = 1,
};

struct warn_args {
	const char *fmt;
	va_list args;
};

struct smp_hotplug_thread {
	struct task_struct **store;
	struct list_head list;
	int (*thread_should_run)(unsigned int);
	void (*thread_fn)(unsigned int);
	void (*create)(unsigned int);
	void (*setup)(unsigned int);
	void (*cleanup)(unsigned int, bool);
	void (*park)(unsigned int);
	void (*unpark)(unsigned int);
	bool selfparking;
	const char *thread_comm;
};

struct trace_event_raw_cpuhp_enter {
	struct trace_entry ent;
	unsigned int cpu;
	int target;
	int idx;
	void *fun;
	char __data[0];
};

struct trace_event_raw_cpuhp_multi_enter {
	struct trace_entry ent;
	unsigned int cpu;
	int target;
	int idx;
	void *fun;
	char __data[0];
};

struct trace_event_raw_cpuhp_exit {
	struct trace_entry ent;
	unsigned int cpu;
	int state;
	int idx;
	int ret;
	char __data[0];
};

struct trace_event_data_offsets_cpuhp_enter {};

struct trace_event_data_offsets_cpuhp_multi_enter {};

struct trace_event_data_offsets_cpuhp_exit {};

typedef void (*btf_trace_cpuhp_enter)(void *, unsigned int, int, int, int (*)(unsigned int));

typedef void (*btf_trace_cpuhp_multi_enter)(void *, unsigned int, int, int, int (*)(unsigned int, struct hlist_node *), struct hlist_node *);

typedef void (*btf_trace_cpuhp_exit)(void *, unsigned int, int, int, int);

struct cpuhp_cpu_state {
	enum cpuhp_state state;
	enum cpuhp_state target;
	enum cpuhp_state fail;
	struct task_struct *thread;
	bool should_run;
	bool rollback;
	bool single;
	bool bringup;
	struct hlist_node *node;
	struct hlist_node *last;
	enum cpuhp_state cb_state;
	int result;
	struct completion done_up;
	struct completion done_down;
};

struct cpuhp_step {
	const char *name;
	union {
		int (*single)(unsigned int);
		int (*multi)(unsigned int, struct hlist_node *);
	} startup;
	union {
		int (*single)(unsigned int);
		int (*multi)(unsigned int, struct hlist_node *);
	} teardown;
	struct hlist_head list;
	bool cant_stop;
	bool multi_instance;
};

enum cpu_mitigations {
	CPU_MITIGATIONS_OFF = 0,
	CPU_MITIGATIONS_AUTO = 1,
	CPU_MITIGATIONS_AUTO_NOSMT = 2,
};

typedef enum cpuhp_state pto_T_____16;

struct __kernel_old_timeval {
	__kernel_long_t tv_sec;
	__kernel_long_t tv_usec;
};

typedef struct wait_queue_entry wait_queue_entry_t;

struct old_timeval32 {
	old_time32_t tv_sec;
	s32 tv_usec;
};

struct rusage {
	struct __kernel_old_timeval ru_utime;
	struct __kernel_old_timeval ru_stime;
	__kernel_long_t ru_maxrss;
	__kernel_long_t ru_ixrss;
	__kernel_long_t ru_idrss;
	__kernel_long_t ru_isrss;
	__kernel_long_t ru_minflt;
	__kernel_long_t ru_majflt;
	__kernel_long_t ru_nswap;
	__kernel_long_t ru_inblock;
	__kernel_long_t ru_oublock;
	__kernel_long_t ru_msgsnd;
	__kernel_long_t ru_msgrcv;
	__kernel_long_t ru_nsignals;
	__kernel_long_t ru_nvcsw;
	__kernel_long_t ru_nivcsw;
};

struct fd {
	struct file *file;
	unsigned int flags;
};

struct compat_rusage {
	struct old_timeval32 ru_utime;
	struct old_timeval32 ru_stime;
	compat_long_t ru_maxrss;
	compat_long_t ru_ixrss;
	compat_long_t ru_idrss;
	compat_long_t ru_isrss;
	compat_long_t ru_minflt;
	compat_long_t ru_majflt;
	compat_long_t ru_nswap;
	compat_long_t ru_inblock;
	compat_long_t ru_oublock;
	compat_long_t ru_msgsnd;
	compat_long_t ru_msgrcv;
	compat_long_t ru_nsignals;
	compat_long_t ru_nvcsw;
	compat_long_t ru_nivcsw;
};

struct waitid_info {
	pid_t pid;
	uid_t uid;
	int status;
	int cause;
};

struct wait_opts {
	enum pid_type wo_type;
	int wo_flags;
	struct pid *wo_pid;
	struct waitid_info *wo_info;
	int wo_stat;
	struct rusage *wo_rusage;
	wait_queue_entry_t child_wait;
	int notask_error;
};

struct softirq_action {
	void (*action)(struct softirq_action *);
};

struct tasklet_struct {
	struct tasklet_struct *next;
	long unsigned int state;
	atomic_t count;
	void (*func)(long unsigned int);
	long unsigned int data;
};

enum {
	TASKLET_STATE_SCHED = 0,
	TASKLET_STATE_RUN = 1,
};

struct trace_event_raw_irq_handler_entry {
	struct trace_entry ent;
	int irq;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_irq_handler_exit {
	struct trace_entry ent;
	int irq;
	int ret;
	char __data[0];
};

struct trace_event_raw_softirq {
	struct trace_entry ent;
	unsigned int vec;
	char __data[0];
};

struct trace_event_data_offsets_irq_handler_entry {
	u32 name;
};

struct trace_event_data_offsets_irq_handler_exit {};

struct trace_event_data_offsets_softirq {};

typedef void (*btf_trace_irq_handler_entry)(void *, int, struct irqaction *);

typedef void (*btf_trace_irq_handler_exit)(void *, int, struct irqaction *, int);

typedef void (*btf_trace_softirq_entry)(void *, unsigned int);

typedef void (*btf_trace_softirq_exit)(void *, unsigned int);

typedef void (*btf_trace_softirq_raise)(void *, unsigned int);

struct tasklet_head {
	struct tasklet_struct *head;
	struct tasklet_struct **tail;
};

typedef struct tasklet_struct **pto_T_____17;

struct resource_entry {
	struct list_head node;
	struct resource *res;
	resource_size_t offset;
	struct resource __res;
};

struct resource_constraint {
	resource_size_t min;
	resource_size_t max;
	resource_size_t align;
	resource_size_t (*alignf)(void *, const struct resource *, resource_size_t, resource_size_t);
	void *alignf_data;
};

enum {
	MAX_IORES_LEVEL = 5,
};

struct region_devres {
	struct resource *parent;
	resource_size_t start;
	resource_size_t n;
};

enum sysctl_writes_mode {
	SYSCTL_WRITES_LEGACY = 4294967295,
	SYSCTL_WRITES_WARN = 0,
	SYSCTL_WRITES_STRICT = 1,
};

struct do_proc_dointvec_minmax_conv_param {
	int *min;
	int *max;
};

struct do_proc_douintvec_minmax_conv_param {
	unsigned int *min;
	unsigned int *max;
};

struct __sysctl_args {
	int *name;
	int nlen;
	void *oldval;
	size_t *oldlenp;
	void *newval;
	size_t newlen;
	long unsigned int __unused[4];
};

enum {
	CTL_KERN = 1,
	CTL_VM = 2,
	CTL_NET = 3,
	CTL_PROC = 4,
	CTL_FS = 5,
	CTL_DEBUG = 6,
	CTL_DEV = 7,
	CTL_BUS = 8,
	CTL_ABI = 9,
	CTL_CPU = 10,
	CTL_ARLAN = 254,
	CTL_S390DBF = 5677,
	CTL_SUNRPC = 7249,
	CTL_PM = 9899,
	CTL_FRV = 9898,
};

enum {
	KERN_OSTYPE = 1,
	KERN_OSRELEASE = 2,
	KERN_OSREV = 3,
	KERN_VERSION = 4,
	KERN_SECUREMASK = 5,
	KERN_PROF = 6,
	KERN_NODENAME = 7,
	KERN_DOMAINNAME = 8,
	KERN_PANIC = 15,
	KERN_REALROOTDEV = 16,
	KERN_SPARC_REBOOT = 21,
	KERN_CTLALTDEL = 22,
	KERN_PRINTK = 23,
	KERN_NAMETRANS = 24,
	KERN_PPC_HTABRECLAIM = 25,
	KERN_PPC_ZEROPAGED = 26,
	KERN_PPC_POWERSAVE_NAP = 27,
	KERN_MODPROBE = 28,
	KERN_SG_BIG_BUFF = 29,
	KERN_ACCT = 30,
	KERN_PPC_L2CR = 31,
	KERN_RTSIGNR = 32,
	KERN_RTSIGMAX = 33,
	KERN_SHMMAX = 34,
	KERN_MSGMAX = 35,
	KERN_MSGMNB = 36,
	KERN_MSGPOOL = 37,
	KERN_SYSRQ = 38,
	KERN_MAX_THREADS = 39,
	KERN_RANDOM = 40,
	KERN_SHMALL = 41,
	KERN_MSGMNI = 42,
	KERN_SEM = 43,
	KERN_SPARC_STOP_A = 44,
	KERN_SHMMNI = 45,
	KERN_OVERFLOWUID = 46,
	KERN_OVERFLOWGID = 47,
	KERN_SHMPATH = 48,
	KERN_HOTPLUG = 49,
	KERN_IEEE_EMULATION_WARNINGS = 50,
	KERN_S390_USER_DEBUG_LOGGING = 51,
	KERN_CORE_USES_PID = 52,
	KERN_TAINTED = 53,
	KERN_CADPID = 54,
	KERN_PIDMAX = 55,
	KERN_CORE_PATTERN = 56,
	KERN_PANIC_ON_OOPS = 57,
	KERN_HPPA_PWRSW = 58,
	KERN_HPPA_UNALIGNED = 59,
	KERN_PRINTK_RATELIMIT = 60,
	KERN_PRINTK_RATELIMIT_BURST = 61,
	KERN_PTY = 62,
	KERN_NGROUPS_MAX = 63,
	KERN_SPARC_SCONS_PWROFF = 64,
	KERN_HZ_TIMER = 65,
	KERN_UNKNOWN_NMI_PANIC = 66,
	KERN_BOOTLOADER_TYPE = 67,
	KERN_RANDOMIZE = 68,
	KERN_SETUID_DUMPABLE = 69,
	KERN_SPIN_RETRY = 70,
	KERN_ACPI_VIDEO_FLAGS = 71,
	KERN_IA64_UNALIGNED = 72,
	KERN_COMPAT_LOG = 73,
	KERN_MAX_LOCK_DEPTH = 74,
	KERN_NMI_WATCHDOG = 75,
	KERN_PANIC_ON_NMI = 76,
	KERN_PANIC_ON_WARN = 77,
	KERN_PANIC_PRINT = 78,
};

struct xfs_sysctl_val {
	int min;
	int val;
	int max;
};

typedef struct xfs_sysctl_val xfs_sysctl_val_t;

struct xfs_param {
	xfs_sysctl_val_t sgid_inherit;
	xfs_sysctl_val_t symlink_mode;
	xfs_sysctl_val_t panic_mask;
	xfs_sysctl_val_t error_level;
	xfs_sysctl_val_t syncd_timer;
	xfs_sysctl_val_t stats_clear;
	xfs_sysctl_val_t inherit_sync;
	xfs_sysctl_val_t inherit_nodump;
	xfs_sysctl_val_t inherit_noatim;
	xfs_sysctl_val_t xfs_buf_timer;
	xfs_sysctl_val_t xfs_buf_age;
	xfs_sysctl_val_t inherit_nosym;
	xfs_sysctl_val_t rotorstep;
	xfs_sysctl_val_t inherit_nodfrg;
	xfs_sysctl_val_t fstrm_timer;
	xfs_sysctl_val_t eofb_timer;
	xfs_sysctl_val_t cowb_timer;
};

typedef struct xfs_param xfs_param_t;

struct xfs_globals {
	int log_recovery_delay;
	int mount_delay;
	bool bug_on_assert;
	bool always_cow;
};

enum ethtool_link_mode_bit_indices {
	ETHTOOL_LINK_MODE_10baseT_Half_BIT = 0,
	ETHTOOL_LINK_MODE_10baseT_Full_BIT = 1,
	ETHTOOL_LINK_MODE_100baseT_Half_BIT = 2,
	ETHTOOL_LINK_MODE_100baseT_Full_BIT = 3,
	ETHTOOL_LINK_MODE_1000baseT_Half_BIT = 4,
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT = 5,
	ETHTOOL_LINK_MODE_Autoneg_BIT = 6,
	ETHTOOL_LINK_MODE_TP_BIT = 7,
	ETHTOOL_LINK_MODE_AUI_BIT = 8,
	ETHTOOL_LINK_MODE_MII_BIT = 9,
	ETHTOOL_LINK_MODE_FIBRE_BIT = 10,
	ETHTOOL_LINK_MODE_BNC_BIT = 11,
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT = 12,
	ETHTOOL_LINK_MODE_Pause_BIT = 13,
	ETHTOOL_LINK_MODE_Asym_Pause_BIT = 14,
	ETHTOOL_LINK_MODE_2500baseX_Full_BIT = 15,
	ETHTOOL_LINK_MODE_Backplane_BIT = 16,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT = 17,
	ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT = 18,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT = 19,
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT = 20,
	ETHTOOL_LINK_MODE_20000baseMLD2_Full_BIT = 21,
	ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT = 22,
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT = 23,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT = 24,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT = 25,
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT = 26,
	ETHTOOL_LINK_MODE_56000baseKR4_Full_BIT = 27,
	ETHTOOL_LINK_MODE_56000baseCR4_Full_BIT = 28,
	ETHTOOL_LINK_MODE_56000baseSR4_Full_BIT = 29,
	ETHTOOL_LINK_MODE_56000baseLR4_Full_BIT = 30,
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT = 31,
	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT = 32,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT = 33,
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT = 34,
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT = 35,
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT = 36,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT = 37,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT = 38,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT = 39,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT = 40,
	ETHTOOL_LINK_MODE_1000baseX_Full_BIT = 41,
	ETHTOOL_LINK_MODE_10000baseCR_Full_BIT = 42,
	ETHTOOL_LINK_MODE_10000baseSR_Full_BIT = 43,
	ETHTOOL_LINK_MODE_10000baseLR_Full_BIT = 44,
	ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT = 45,
	ETHTOOL_LINK_MODE_10000baseER_Full_BIT = 46,
	ETHTOOL_LINK_MODE_2500baseT_Full_BIT = 47,
	ETHTOOL_LINK_MODE_5000baseT_Full_BIT = 48,
	ETHTOOL_LINK_MODE_FEC_NONE_BIT = 49,
	ETHTOOL_LINK_MODE_FEC_RS_BIT = 50,
	ETHTOOL_LINK_MODE_FEC_BASER_BIT = 51,
	ETHTOOL_LINK_MODE_50000baseKR_Full_BIT = 52,
	ETHTOOL_LINK_MODE_50000baseSR_Full_BIT = 53,
	ETHTOOL_LINK_MODE_50000baseCR_Full_BIT = 54,
	ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT = 55,
	ETHTOOL_LINK_MODE_50000baseDR_Full_BIT = 56,
	ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT = 57,
	ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT = 58,
	ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT = 59,
	ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT = 60,
	ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT = 61,
	ETHTOOL_LINK_MODE_200000baseKR4_Full_BIT = 62,
	ETHTOOL_LINK_MODE_200000baseSR4_Full_BIT = 63,
	ETHTOOL_LINK_MODE_200000baseLR4_ER4_FR4_Full_BIT = 64,
	ETHTOOL_LINK_MODE_200000baseDR4_Full_BIT = 65,
	ETHTOOL_LINK_MODE_200000baseCR4_Full_BIT = 66,
	ETHTOOL_LINK_MODE_100baseT1_Full_BIT = 67,
	ETHTOOL_LINK_MODE_1000baseT1_Full_BIT = 68,
	ETHTOOL_LINK_MODE_400000baseKR8_Full_BIT = 69,
	ETHTOOL_LINK_MODE_400000baseSR8_Full_BIT = 70,
	ETHTOOL_LINK_MODE_400000baseLR8_ER8_FR8_Full_BIT = 71,
	ETHTOOL_LINK_MODE_400000baseDR8_Full_BIT = 72,
	ETHTOOL_LINK_MODE_400000baseCR8_Full_BIT = 73,
	ETHTOOL_LINK_MODE_FEC_LLRS_BIT = 74,
	__ETHTOOL_LINK_MODE_MASK_NBITS = 75,
};

enum {
	NAPI_STATE_SCHED = 0,
	NAPI_STATE_MISSED = 1,
	NAPI_STATE_DISABLE = 2,
	NAPI_STATE_NPSVC = 3,
	NAPI_STATE_HASHED = 4,
	NAPI_STATE_NO_BUSY_POLL = 5,
	NAPI_STATE_IN_BUSY_POLL = 6,
};

enum {
	NETIF_MSG_DRV_BIT = 0,
	NETIF_MSG_PROBE_BIT = 1,
	NETIF_MSG_LINK_BIT = 2,
	NETIF_MSG_TIMER_BIT = 3,
	NETIF_MSG_IFDOWN_BIT = 4,
	NETIF_MSG_IFUP_BIT = 5,
	NETIF_MSG_RX_ERR_BIT = 6,
	NETIF_MSG_TX_ERR_BIT = 7,
	NETIF_MSG_TX_QUEUED_BIT = 8,
	NETIF_MSG_INTR_BIT = 9,
	NETIF_MSG_TX_DONE_BIT = 10,
	NETIF_MSG_RX_STATUS_BIT = 11,
	NETIF_MSG_PKTDATA_BIT = 12,
	NETIF_MSG_HW_BIT = 13,
	NETIF_MSG_WOL_BIT = 14,
	NETIF_MSG_CLASS_COUNT = 15,
};

struct compat_sysctl_args {
	compat_uptr_t name;
	int nlen;
	compat_uptr_t oldval;
	compat_uptr_t oldlenp;
	compat_uptr_t newval;
	compat_size_t newlen;
	compat_ulong_t __unused[4];
};

struct __user_cap_header_struct {
	__u32 version;
	int pid;
};

typedef struct __user_cap_header_struct *cap_user_header_t;

struct __user_cap_data_struct {
	__u32 effective;
	__u32 permitted;
	__u32 inheritable;
};

typedef struct __user_cap_data_struct *cap_user_data_t;

struct sigqueue {
	struct list_head list;
	int flags;
	kernel_siginfo_t info;
	struct user_struct *user;
};

struct ptrace_peeksiginfo_args {
	__u64 off;
	__u32 flags;
	__s32 nr;
};

struct ptrace_syscall_info {
	__u8 op;
	__u32 arch;
	__u64 instruction_pointer;
	__u64 stack_pointer;
	union {
		struct {
			__u64 nr;
			__u64 args[6];
		} entry;
		struct {
			__s64 rval;
			__u8 is_error;
		} exit;
		struct {
			__u64 nr;
			__u64 args[6];
			__u32 ret_data;
		} seccomp;
	};
};

struct compat_iovec {
	compat_uptr_t iov_base;
	compat_size_t iov_len;
};

typedef long unsigned int old_sigset_t;

enum siginfo_layout {
	SIL_KILL = 0,
	SIL_TIMER = 1,
	SIL_POLL = 2,
	SIL_FAULT = 3,
	SIL_FAULT_MCEERR = 4,
	SIL_FAULT_BNDERR = 5,
	SIL_FAULT_PKUERR = 6,
	SIL_CHLD = 7,
	SIL_RT = 8,
	SIL_SYS = 9,
};

typedef u32 compat_old_sigset_t;

struct compat_sigaction {
	compat_uptr_t sa_handler;
	compat_ulong_t sa_flags;
	compat_uptr_t sa_restorer;
	compat_sigset_t sa_mask;
};

struct compat_old_sigaction {
	compat_uptr_t sa_handler;
	compat_old_sigset_t sa_mask;
	compat_ulong_t sa_flags;
	compat_uptr_t sa_restorer;
};

enum {
	TRACE_SIGNAL_DELIVERED = 0,
	TRACE_SIGNAL_IGNORED = 1,
	TRACE_SIGNAL_ALREADY_PENDING = 2,
	TRACE_SIGNAL_OVERFLOW_FAIL = 3,
	TRACE_SIGNAL_LOSE_INFO = 4,
};

struct trace_event_raw_signal_generate {
	struct trace_entry ent;
	int sig;
	int errno;
	int code;
	char comm[16];
	pid_t pid;
	int group;
	int result;
	char __data[0];
};

struct trace_event_raw_signal_deliver {
	struct trace_entry ent;
	int sig;
	int errno;
	int code;
	long unsigned int sa_handler;
	long unsigned int sa_flags;
	char __data[0];
};

struct trace_event_data_offsets_signal_generate {};

struct trace_event_data_offsets_signal_deliver {};

typedef void (*btf_trace_signal_generate)(void *, int, struct kernel_siginfo *, struct task_struct *, int, int);

typedef void (*btf_trace_signal_deliver)(void *, int, struct kernel_siginfo *, struct k_sigaction *);

typedef __kernel_clock_t clock_t;

struct sysinfo {
	__kernel_long_t uptime;
	__kernel_ulong_t loads[3];
	__kernel_ulong_t totalram;
	__kernel_ulong_t freeram;
	__kernel_ulong_t sharedram;
	__kernel_ulong_t bufferram;
	__kernel_ulong_t totalswap;
	__kernel_ulong_t freeswap;
	__u16 procs;
	__u16 pad;
	__kernel_ulong_t totalhigh;
	__kernel_ulong_t freehigh;
	__u32 mem_unit;
	char _f[0];
};

enum {
	PER_LINUX = 0,
	PER_LINUX_32BIT = 8388608,
	PER_LINUX_FDPIC = 524288,
	PER_SVR4 = 68157441,
	PER_SVR3 = 83886082,
	PER_SCOSVR3 = 117440515,
	PER_OSR5 = 100663299,
	PER_WYSEV386 = 83886084,
	PER_ISCR4 = 67108869,
	PER_BSD = 6,
	PER_SUNOS = 67108870,
	PER_XENIX = 83886087,
	PER_LINUX32 = 8,
	PER_LINUX32_3GB = 134217736,
	PER_IRIX32 = 67108873,
	PER_IRIXN32 = 67108874,
	PER_IRIX64 = 67108875,
	PER_RISCOS = 12,
	PER_SOLARIS = 67108877,
	PER_UW7 = 68157454,
	PER_OSF4 = 15,
	PER_HPUX = 16,
	PER_MASK = 255,
};

struct rlimit64 {
	__u64 rlim_cur;
	__u64 rlim_max;
};

struct oldold_utsname {
	char sysname[9];
	char nodename[9];
	char release[9];
	char version[9];
	char machine[9];
};

struct old_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
};

enum uts_proc {
	UTS_PROC_OSTYPE = 0,
	UTS_PROC_OSRELEASE = 1,
	UTS_PROC_VERSION = 2,
	UTS_PROC_HOSTNAME = 3,
	UTS_PROC_DOMAINNAME = 4,
};

struct prctl_mm_map {
	__u64 start_code;
	__u64 end_code;
	__u64 start_data;
	__u64 end_data;
	__u64 start_brk;
	__u64 brk;
	__u64 start_stack;
	__u64 arg_start;
	__u64 arg_end;
	__u64 env_start;
	__u64 env_end;
	__u64 *auxv;
	__u32 auxv_size;
	__u32 exe_fd;
};

struct tms {
	__kernel_clock_t tms_utime;
	__kernel_clock_t tms_stime;
	__kernel_clock_t tms_cutime;
	__kernel_clock_t tms_cstime;
};

struct getcpu_cache {
	long unsigned int blob[16];
};

struct compat_tms {
	compat_clock_t tms_utime;
	compat_clock_t tms_stime;
	compat_clock_t tms_cutime;
	compat_clock_t tms_cstime;
};

struct compat_rlimit {
	compat_ulong_t rlim_cur;
	compat_ulong_t rlim_max;
};

struct compat_sysinfo {
	s32 uptime;
	u32 loads[3];
	u32 totalram;
	u32 freeram;
	u32 sharedram;
	u32 bufferram;
	u32 totalswap;
	u32 freeswap;
	u16 procs;
	u16 pad;
	u32 totalhigh;
	u32 freehigh;
	u32 mem_unit;
	char _f[8];
};

struct umh_info {
	const char *cmdline;
	struct file *pipe_to_umh;
	struct file *pipe_from_umh;
	struct list_head list;
	void (*cleanup)(struct umh_info *);
	pid_t pid;
};

struct wq_flusher;

struct worker;

struct workqueue_attrs;

struct pool_workqueue;

struct wq_device;

struct workqueue_struct {
	struct list_head pwqs;
	struct list_head list;
	struct mutex mutex;
	int work_color;
	int flush_color;
	atomic_t nr_pwqs_to_flush;
	struct wq_flusher *first_flusher;
	struct list_head flusher_queue;
	struct list_head flusher_overflow;
	struct list_head maydays;
	struct worker *rescuer;
	int nr_drainers;
	int saved_max_active;
	struct workqueue_attrs *unbound_attrs;
	struct pool_workqueue *dfl_pwq;
	struct wq_device *wq_dev;
	char name[24];
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	unsigned int flags;
	struct pool_workqueue *cpu_pwqs;
	struct pool_workqueue *numa_pwq_tbl[0];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct workqueue_attrs {
	int nice;
	cpumask_var_t cpumask;
	bool no_numa;
};

struct execute_work {
	struct work_struct work;
};

enum {
	WQ_UNBOUND = 2,
	WQ_FREEZABLE = 4,
	WQ_MEM_RECLAIM = 8,
	WQ_HIGHPRI = 16,
	WQ_CPU_INTENSIVE = 32,
	WQ_SYSFS = 64,
	WQ_POWER_EFFICIENT = 128,
	__WQ_DRAINING = 65536,
	__WQ_ORDERED = 131072,
	__WQ_LEGACY = 262144,
	__WQ_ORDERED_EXPLICIT = 524288,
	WQ_MAX_ACTIVE = 512,
	WQ_MAX_UNBOUND_PER_CPU = 4,
	WQ_DFL_ACTIVE = 256,
};

typedef unsigned int xa_mark_t;

enum xa_lock_type {
	XA_LOCK_IRQ = 1,
	XA_LOCK_BH = 2,
};

struct __una_u32 {
	u32 x;
};

struct worker_pool;

struct worker {
	union {
		struct list_head entry;
		struct hlist_node hentry;
	};
	struct work_struct *current_work;
	work_func_t current_func;
	struct pool_workqueue *current_pwq;
	struct list_head scheduled;
	struct task_struct *task;
	struct worker_pool *pool;
	struct list_head node;
	long unsigned int last_active;
	unsigned int flags;
	int id;
	int sleeping;
	char desc[24];
	struct workqueue_struct *rescue_wq;
	work_func_t last_func;
};

struct pool_workqueue {
	struct worker_pool *pool;
	struct workqueue_struct *wq;
	int work_color;
	int flush_color;
	int refcnt;
	int nr_in_flight[15];
	int nr_active;
	int max_active;
	struct list_head delayed_works;
	struct list_head pwqs_node;
	struct list_head mayday_node;
	struct work_struct unbound_release_work;
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct worker_pool {
	raw_spinlock_t lock;
	int cpu;
	int node;
	int id;
	unsigned int flags;
	long unsigned int watchdog_ts;
	struct list_head worklist;
	int nr_workers;
	int nr_idle;
	struct list_head idle_list;
	struct timer_list idle_timer;
	struct timer_list mayday_timer;
	struct hlist_head busy_hash[64];
	struct worker *manager;
	struct list_head workers;
	struct completion *detach_completion;
	struct ida worker_ida;
	struct workqueue_attrs *attrs;
	struct hlist_node hash_node;
	int refcnt;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	atomic_t nr_running;
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum {
	POOL_MANAGER_ACTIVE = 1,
	POOL_DISASSOCIATED = 4,
	WORKER_DIE = 2,
	WORKER_IDLE = 4,
	WORKER_PREP = 8,
	WORKER_CPU_INTENSIVE = 64,
	WORKER_UNBOUND = 128,
	WORKER_REBOUND = 256,
	WORKER_NOT_RUNNING = 456,
	NR_STD_WORKER_POOLS = 2,
	UNBOUND_POOL_HASH_ORDER = 6,
	BUSY_WORKER_HASH_ORDER = 6,
	MAX_IDLE_WORKERS_RATIO = 4,
	IDLE_WORKER_TIMEOUT = 300000,
	MAYDAY_INITIAL_TIMEOUT = 10,
	MAYDAY_INTERVAL = 100,
	CREATE_COOLDOWN = 1000,
	RESCUER_NICE_LEVEL = 4294967276,
	HIGHPRI_NICE_LEVEL = 4294967276,
	WQ_NAME_LEN = 24,
};

struct wq_flusher {
	struct list_head list;
	int flush_color;
	struct completion done;
};

struct wq_device {
	struct workqueue_struct *wq;
	struct device dev;
};

struct trace_event_raw_workqueue_queue_work {
	struct trace_entry ent;
	void *work;
	void *function;
	void *workqueue;
	unsigned int req_cpu;
	unsigned int cpu;
	char __data[0];
};

struct trace_event_raw_workqueue_activate_work {
	struct trace_entry ent;
	void *work;
	char __data[0];
};

struct trace_event_raw_workqueue_execute_start {
	struct trace_entry ent;
	void *work;
	void *function;
	char __data[0];
};

struct trace_event_raw_workqueue_execute_end {
	struct trace_entry ent;
	void *work;
	void *function;
	char __data[0];
};

struct trace_event_data_offsets_workqueue_queue_work {};

struct trace_event_data_offsets_workqueue_activate_work {};

struct trace_event_data_offsets_workqueue_execute_start {};

struct trace_event_data_offsets_workqueue_execute_end {};

typedef void (*btf_trace_workqueue_queue_work)(void *, unsigned int, struct pool_workqueue *, struct work_struct *);

typedef void (*btf_trace_workqueue_activate_work)(void *, struct work_struct *);

typedef void (*btf_trace_workqueue_execute_start)(void *, struct work_struct *);

typedef void (*btf_trace_workqueue_execute_end)(void *, struct work_struct *, work_func_t);

struct wq_barrier {
	struct work_struct work;
	struct completion done;
	struct task_struct *task;
};

struct cwt_wait {
	wait_queue_entry_t wait;
	struct work_struct *work;
};

struct apply_wqattrs_ctx {
	struct workqueue_struct *wq;
	struct workqueue_attrs *attrs;
	struct list_head list;
	struct pool_workqueue *dfl_pwq;
	struct pool_workqueue *pwq_tbl[0];
};

struct work_for_cpu {
	struct work_struct work;
	long int (*fn)(void *);
	void *arg;
	long int ret;
};

typedef void (*task_work_func_t)(struct callback_head *);

enum {
	KERNEL_PARAM_OPS_FL_NOARG = 1,
};

enum {
	KERNEL_PARAM_FL_UNSAFE = 1,
	KERNEL_PARAM_FL_HWPARAM = 2,
};

struct param_attribute {
	struct module_attribute mattr;
	const struct kernel_param *param;
};

struct module_param_attrs {
	unsigned int num;
	struct attribute_group grp;
	struct param_attribute attrs[0];
};

struct module_version_attribute {
	struct module_attribute mattr;
	const char *module_name;
	const char *version;
};

struct kmalloced_param {
	struct list_head list;
	char val[0];
};

struct sched_param {
	int sched_priority;
};

struct kthread_work;

typedef void (*kthread_work_func_t)(struct kthread_work *);

struct kthread_worker;

struct kthread_work {
	struct list_head node;
	kthread_work_func_t func;
	struct kthread_worker *worker;
	int canceling;
};

enum {
	KTW_FREEZABLE = 1,
};

struct kthread_worker {
	unsigned int flags;
	raw_spinlock_t lock;
	struct list_head work_list;
	struct list_head delayed_work_list;
	struct task_struct *task;
	struct kthread_work *current_work;
};

struct kthread_delayed_work {
	struct kthread_work work;
	struct timer_list timer;
};

struct kthread_create_info {
	int (*threadfn)(void *);
	void *data;
	int node;
	struct task_struct *result;
	struct completion *done;
	struct list_head list;
};

struct kthread {
	long unsigned int flags;
	unsigned int cpu;
	int (*threadfn)(void *);
	void *data;
	mm_segment_t oldfs;
	struct completion parked;
	struct completion exited;
};

enum KTHREAD_BITS {
	KTHREAD_IS_PER_CPU = 0,
	KTHREAD_SHOULD_STOP = 1,
	KTHREAD_SHOULD_PARK = 2,
};

struct kthread_flush_work {
	struct kthread_work work;
	struct completion done;
};

struct pt_regs___2;

struct ipc_ids {
	int in_use;
	short unsigned int seq;
	struct rw_semaphore rwsem;
	struct idr ipcs_idr;
	int max_idx;
	int last_idx;
	struct rhashtable key_ht;
};

struct ipc_namespace {
	refcount_t count;
	struct ipc_ids ids[3];
	int sem_ctls[4];
	int used_sems;
	unsigned int msg_ctlmax;
	unsigned int msg_ctlmnb;
	unsigned int msg_ctlmni;
	atomic_t msg_bytes;
	atomic_t msg_hdrs;
	size_t shm_ctlmax;
	size_t shm_ctlall;
	long unsigned int shm_tot;
	int shm_ctlmni;
	int shm_rmid_forced;
	struct notifier_block ipcns_nb;
	struct vfsmount *mq_mnt;
	unsigned int mq_queues_count;
	unsigned int mq_queues_max;
	unsigned int mq_msg_max;
	unsigned int mq_msgsize_max;
	unsigned int mq_msg_default;
	unsigned int mq_msgsize_default;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct llist_node mnt_llist;
	struct ns_common ns;
};

struct srcu_notifier_head {
	struct mutex mutex;
	struct srcu_struct srcu;
	struct notifier_block *head;
};

enum what {
	PROC_EVENT_NONE = 0,
	PROC_EVENT_FORK = 1,
	PROC_EVENT_EXEC = 2,
	PROC_EVENT_UID = 4,
	PROC_EVENT_GID = 64,
	PROC_EVENT_SID = 128,
	PROC_EVENT_PTRACE = 256,
	PROC_EVENT_COMM = 512,
	PROC_EVENT_COREDUMP = 1073741824,
	PROC_EVENT_EXIT = 2147483648,
};

typedef u64 async_cookie_t;

typedef void (*async_func_t)(void *, async_cookie_t);

struct async_domain {
	struct list_head pending;
	unsigned int registered: 1;
};

struct async_entry {
	struct list_head domain_list;
	struct list_head global_list;
	struct work_struct work;
	async_cookie_t cookie;
	async_func_t func;
	void *data;
	struct async_domain *domain;
};

struct smpboot_thread_data {
	unsigned int cpu;
	unsigned int status;
	struct smp_hotplug_thread *ht;
};

enum {
	HP_THREAD_NONE = 0,
	HP_THREAD_ACTIVE = 1,
	HP_THREAD_PARKED = 2,
};

struct pin_cookie {};

enum {
	CSD_FLAG_LOCK = 1,
	IRQ_WORK_PENDING = 1,
	IRQ_WORK_BUSY = 2,
	IRQ_WORK_LAZY = 4,
	IRQ_WORK_HARD_IRQ = 8,
	IRQ_WORK_CLAIMED = 3,
	CSD_TYPE_ASYNC = 0,
	CSD_TYPE_SYNC = 16,
	CSD_TYPE_IRQ_WORK = 32,
	CSD_TYPE_TTWU = 48,
	CSD_FLAG_TYPE_MASK = 240,
};

struct dl_bw {
	raw_spinlock_t lock;
	u64 bw;
	u64 total_bw;
};

struct cpudl_item;

struct cpudl {
	raw_spinlock_t lock;
	int size;
	cpumask_var_t free_cpus;
	struct cpudl_item *elements;
};

struct cpupri_vec {
	atomic_t count;
	cpumask_var_t mask;
};

struct cpupri {
	struct cpupri_vec pri_to_cpu[102];
	int *cpu_to_pri;
};

struct perf_domain;

struct root_domain___2 {
	atomic_t refcount;
	atomic_t rto_count;
	struct callback_head rcu;
	cpumask_var_t span;
	cpumask_var_t online;
	int overload;
	int overutilized;
	cpumask_var_t dlo_mask;
	atomic_t dlo_count;
	struct dl_bw dl_bw;
	struct cpudl cpudl;
	struct irq_work rto_push_work;
	raw_spinlock_t rto_lock;
	int rto_loop;
	int rto_cpu;
	atomic_t rto_loop_next;
	atomic_t rto_loop_start;
	cpumask_var_t rto_mask;
	struct cpupri cpupri;
	long unsigned int max_cpu_capacity;
	struct perf_domain *pd;
};

struct cfs_rq {
	struct load_weight load;
	unsigned int nr_running;
	unsigned int h_nr_running;
	unsigned int idle_h_nr_running;
	u64 exec_clock;
	u64 min_vruntime;
	struct rb_root_cached tasks_timeline;
	struct sched_entity *curr;
	struct sched_entity *next;
	struct sched_entity *last;
	struct sched_entity *skip;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct sched_avg avg;
	struct {
		raw_spinlock_t lock;
		int nr;
		long unsigned int load_avg;
		long unsigned int util_avg;
		long unsigned int runnable_avg;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	} removed;
	long unsigned int tg_load_avg_contrib;
	long int propagate;
	long int prop_runnable_sum;
	long unsigned int h_load;
	u64 last_h_load_update;
	struct sched_entity *h_load_next;
	struct rq *rq;
	int on_list;
	struct list_head leaf_cfs_rq_list;
	struct task_group *tg;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct cfs_bandwidth {};

struct task_group {
	struct cgroup_subsys_state css;
	struct sched_entity **se;
	struct cfs_rq **cfs_rq;
	long unsigned int shares;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	atomic_long_t load_avg;
	struct callback_head rcu;
	struct list_head list;
	struct task_group *parent;
	struct list_head siblings;
	struct list_head children;
	struct cfs_bandwidth cfs_bandwidth;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct update_util_data {
	void (*func)(struct update_util_data *, u64, unsigned int);
};

enum {
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY = 1,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED = 2,
	MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY = 4,
	MEMBARRIER_STATE_GLOBAL_EXPEDITED = 8,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY = 16,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE = 32,
};

struct sched_group {
	struct sched_group *next;
	atomic_t ref;
	unsigned int group_weight;
	struct sched_group_capacity *sgc;
	int asym_prefer_cpu;
	long unsigned int cpumask[0];
};

struct sched_group_capacity {
	atomic_t ref;
	long unsigned int capacity;
	long unsigned int min_capacity;
	long unsigned int max_capacity;
	long unsigned int next_update;
	int imbalance;
	long unsigned int cpumask[0];
};

struct wake_q_head {
	struct wake_q_node *first;
	struct wake_q_node **lastp;
};

struct sched_attr {
	__u32 size;
	__u32 sched_policy;
	__u64 sched_flags;
	__s32 sched_nice;
	__u32 sched_priority;
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
	__u32 sched_util_min;
	__u32 sched_util_max;
};

struct cpuidle_driver___2;

struct cpuidle_state {
	char name[16];
	char desc[32];
	u64 exit_latency_ns;
	u64 target_residency_ns;
	unsigned int flags;
	unsigned int exit_latency;
	int power_usage;
	unsigned int target_residency;
	int (*enter)(struct cpuidle_device *, struct cpuidle_driver___2 *, int);
	int (*enter_dead)(struct cpuidle_device *, int);
	void (*enter_s2idle)(struct cpuidle_device *, struct cpuidle_driver___2 *, int);
};

struct cpuidle_driver___2 {
	const char *name;
	struct module *owner;
	unsigned int bctimer: 1;
	struct cpuidle_state states[10];
	int state_count;
	int safe_state_index;
	struct cpumask *cpumask;
	const char *governor;
};

struct em_cap_state {
	long unsigned int frequency;
	long unsigned int power;
	long unsigned int cost;
};

struct em_perf_domain {
	struct em_cap_state *table;
	int nr_cap_states;
	long unsigned int cpus[0];
};

enum {
	CFTYPE_ONLY_ON_ROOT = 1,
	CFTYPE_NOT_ON_ROOT = 2,
	CFTYPE_NS_DELEGATABLE = 4,
	CFTYPE_NO_PREFIX = 8,
	CFTYPE_WORLD_WRITABLE = 16,
	CFTYPE_DEBUG = 32,
	__CFTYPE_ONLY_ON_DFL = 65536,
	__CFTYPE_NOT_ON_DFL = 131072,
};

typedef int (*cpu_stop_fn_t)(void *);

struct cpu_stop_done;

struct cpu_stop_work {
	struct list_head list;
	cpu_stop_fn_t fn;
	void *arg;
	struct cpu_stop_done *done;
};

struct cpudl_item {
	u64 dl;
	int cpu;
	int idx;
};

struct rt_prio_array {
	long unsigned int bitmap[2];
	struct list_head queue[100];
};

struct rt_bandwidth {
	raw_spinlock_t rt_runtime_lock;
	ktime_t rt_period;
	u64 rt_runtime;
	struct hrtimer rt_period_timer;
	unsigned int rt_period_active;
};

struct dl_bandwidth {
	raw_spinlock_t dl_runtime_lock;
	u64 dl_runtime;
	u64 dl_period;
};

typedef int (*tg_visitor)(struct task_group *, void *);

struct rt_rq {
	struct rt_prio_array active;
	unsigned int rt_nr_running;
	unsigned int rr_nr_running;
	struct {
		int curr;
		int next;
	} highest_prio;
	long unsigned int rt_nr_migratory;
	long unsigned int rt_nr_total;
	int overloaded;
	struct plist_head pushable_tasks;
	int rt_queued;
	int rt_throttled;
	u64 rt_time;
	u64 rt_runtime;
	raw_spinlock_t rt_runtime_lock;
};

struct dl_rq {
	struct rb_root_cached root;
	long unsigned int dl_nr_running;
	struct {
		u64 curr;
		u64 next;
	} earliest_dl;
	long unsigned int dl_nr_migratory;
	int overloaded;
	struct rb_root_cached pushable_dl_tasks_root;
	u64 running_bw;
	u64 this_bw;
	u64 extra_bw;
	u64 bw_ratio;
};

struct rq {
	raw_spinlock_t lock;
	unsigned int nr_running;
	long unsigned int last_blocked_load_update_tick;
	unsigned int has_blocked_load;
	long: 32;
	long: 64;
	call_single_data_t nohz_csd;
	unsigned int nohz_tick_stopped;
	atomic_t nohz_flags;
	unsigned int ttwu_pending;
	u64 nr_switches;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cfs_rq cfs;
	struct rt_rq rt;
	struct dl_rq dl;
	struct list_head leaf_cfs_rq_list;
	struct list_head *tmp_alone_branch;
	long unsigned int nr_uninterruptible;
	struct task_struct *curr;
	struct task_struct *idle;
	struct task_struct *stop;
	long unsigned int next_balance;
	struct mm_struct *prev_mm;
	unsigned int clock_update_flags;
	u64 clock;
	long: 64;
	long: 64;
	long: 64;
	u64 clock_task;
	u64 clock_pelt;
	long unsigned int lost_idle_time;
	atomic_t nr_iowait;
	int membarrier_state;
	struct root_domain___2 *rd;
	struct sched_domain *sd;
	long unsigned int cpu_capacity;
	long unsigned int cpu_capacity_orig;
	struct callback_head *balance_callback;
	unsigned char nohz_idle_balance;
	unsigned char idle_balance;
	long unsigned int misfit_task_load;
	int active_balance;
	int push_cpu;
	struct cpu_stop_work active_balance_work;
	int cpu;
	int online;
	struct list_head cfs_tasks;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct sched_avg avg_rt;
	struct sched_avg avg_dl;
	u64 idle_stamp;
	u64 avg_idle;
	u64 max_idle_balance_cost;
	long unsigned int calc_load_update;
	long int calc_load_active;
	long: 64;
	long: 64;
	long: 64;
	call_single_data_t hrtick_csd;
	struct hrtimer hrtick_timer;
	struct sched_info rq_sched_info;
	long long unsigned int rq_cpu_time;
	unsigned int yld_count;
	unsigned int sched_count;
	unsigned int sched_goidle;
	unsigned int ttwu_count;
	unsigned int ttwu_local;
	struct cpuidle_state *idle_state;
	long: 64;
	long: 64;
	long: 64;
};

struct perf_domain {
	struct em_perf_domain *em_pd;
	struct perf_domain *next;
	struct callback_head rcu;
};

struct rq_flags {
	long unsigned int flags;
	struct pin_cookie cookie;
};

enum numa_topology_type {
	NUMA_DIRECT = 0,
	NUMA_GLUELESS_MESH = 1,
	NUMA_BACKPLANE = 2,
};

enum {
	__SCHED_FEAT_GENTLE_FAIR_SLEEPERS = 0,
	__SCHED_FEAT_START_DEBIT = 1,
	__SCHED_FEAT_NEXT_BUDDY = 2,
	__SCHED_FEAT_LAST_BUDDY = 3,
	__SCHED_FEAT_CACHE_HOT_BUDDY = 4,
	__SCHED_FEAT_WAKEUP_PREEMPTION = 5,
	__SCHED_FEAT_HRTICK = 6,
	__SCHED_FEAT_DOUBLE_TICK = 7,
	__SCHED_FEAT_NONTASK_CAPACITY = 8,
	__SCHED_FEAT_TTWU_QUEUE = 9,
	__SCHED_FEAT_SIS_AVG_CPU = 10,
	__SCHED_FEAT_SIS_PROP = 11,
	__SCHED_FEAT_WARN_DOUBLE_CLOCK = 12,
	__SCHED_FEAT_RT_PUSH_IPI = 13,
	__SCHED_FEAT_RT_RUNTIME_SHARE = 14,
	__SCHED_FEAT_LB_MIN = 15,
	__SCHED_FEAT_ATTACH_AGE_LOAD = 16,
	__SCHED_FEAT_WA_IDLE = 17,
	__SCHED_FEAT_WA_WEIGHT = 18,
	__SCHED_FEAT_WA_BIAS = 19,
	__SCHED_FEAT_UTIL_EST = 20,
	__SCHED_FEAT_UTIL_EST_FASTUP = 21,
	__SCHED_FEAT_NR = 22,
};

struct trace_event_raw_sched_kthread_stop {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	char __data[0];
};

struct trace_event_raw_sched_kthread_stop_ret {
	struct trace_entry ent;
	int ret;
	char __data[0];
};

struct trace_event_raw_sched_wakeup_template {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	int success;
	int target_cpu;
	char __data[0];
};

struct trace_event_raw_sched_switch {
	struct trace_entry ent;
	char prev_comm[16];
	pid_t prev_pid;
	int prev_prio;
	long int prev_state;
	char next_comm[16];
	pid_t next_pid;
	int next_prio;
	char __data[0];
};

struct trace_event_raw_sched_migrate_task {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	int orig_cpu;
	int dest_cpu;
	char __data[0];
};

struct trace_event_raw_sched_process_template {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	char __data[0];
};

struct trace_event_raw_sched_process_wait {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	char __data[0];
};

struct trace_event_raw_sched_process_fork {
	struct trace_entry ent;
	char parent_comm[16];
	pid_t parent_pid;
	char child_comm[16];
	pid_t child_pid;
	char __data[0];
};

struct trace_event_raw_sched_process_exec {
	struct trace_entry ent;
	u32 __data_loc_filename;
	pid_t pid;
	pid_t old_pid;
	char __data[0];
};

struct trace_event_raw_sched_stat_template {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	u64 delay;
	char __data[0];
};

struct trace_event_raw_sched_stat_runtime {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	u64 runtime;
	u64 vruntime;
	char __data[0];
};

struct trace_event_raw_sched_pi_setprio {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int oldprio;
	int newprio;
	char __data[0];
};

struct trace_event_raw_sched_move_numa {
	struct trace_entry ent;
	pid_t pid;
	pid_t tgid;
	pid_t ngid;
	int src_cpu;
	int src_nid;
	int dst_cpu;
	int dst_nid;
	char __data[0];
};

struct trace_event_raw_sched_numa_pair_template {
	struct trace_entry ent;
	pid_t src_pid;
	pid_t src_tgid;
	pid_t src_ngid;
	int src_cpu;
	int src_nid;
	pid_t dst_pid;
	pid_t dst_tgid;
	pid_t dst_ngid;
	int dst_cpu;
	int dst_nid;
	char __data[0];
};

struct trace_event_raw_sched_wake_idle_without_ipi {
	struct trace_entry ent;
	int cpu;
	char __data[0];
};

struct trace_event_data_offsets_sched_kthread_stop {};

struct trace_event_data_offsets_sched_kthread_stop_ret {};

struct trace_event_data_offsets_sched_wakeup_template {};

struct trace_event_data_offsets_sched_switch {};

struct trace_event_data_offsets_sched_migrate_task {};

struct trace_event_data_offsets_sched_process_template {};

struct trace_event_data_offsets_sched_process_wait {};

struct trace_event_data_offsets_sched_process_fork {};

struct trace_event_data_offsets_sched_process_exec {
	u32 filename;
};

struct trace_event_data_offsets_sched_stat_template {};

struct trace_event_data_offsets_sched_stat_runtime {};

struct trace_event_data_offsets_sched_pi_setprio {};

struct trace_event_data_offsets_sched_move_numa {};

struct trace_event_data_offsets_sched_numa_pair_template {};

struct trace_event_data_offsets_sched_wake_idle_without_ipi {};

typedef void (*btf_trace_sched_kthread_stop)(void *, struct task_struct *);

typedef void (*btf_trace_sched_kthread_stop_ret)(void *, int);

typedef void (*btf_trace_sched_waking)(void *, struct task_struct *);

typedef void (*btf_trace_sched_wakeup)(void *, struct task_struct *);

typedef void (*btf_trace_sched_wakeup_new)(void *, struct task_struct *);

typedef void (*btf_trace_sched_switch)(void *, bool, struct task_struct *, struct task_struct *);

typedef void (*btf_trace_sched_migrate_task)(void *, struct task_struct *, int);

typedef void (*btf_trace_sched_process_free)(void *, struct task_struct *);

typedef void (*btf_trace_sched_process_exit)(void *, struct task_struct *);

typedef void (*btf_trace_sched_wait_task)(void *, struct task_struct *);

typedef void (*btf_trace_sched_process_wait)(void *, struct pid *);

typedef void (*btf_trace_sched_process_fork)(void *, struct task_struct *, struct task_struct *);

typedef void (*btf_trace_sched_process_exec)(void *, struct task_struct *, pid_t, struct linux_binprm *);

typedef void (*btf_trace_sched_stat_wait)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_sleep)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_iowait)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_blocked)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_runtime)(void *, struct task_struct *, u64, u64);

typedef void (*btf_trace_sched_pi_setprio)(void *, struct task_struct *, struct task_struct *);

typedef void (*btf_trace_sched_move_numa)(void *, struct task_struct *, int, int);

typedef void (*btf_trace_sched_stick_numa)(void *, struct task_struct *, int, struct task_struct *, int);

typedef void (*btf_trace_sched_swap_numa)(void *, struct task_struct *, int, struct task_struct *, int);

typedef void (*btf_trace_sched_wake_idle_without_ipi)(void *, int);

struct migration_arg {
	struct task_struct *task;
	int dest_cpu;
};

enum {
	cpuset = 0,
	possible = 1,
	fail = 2,
};

enum tick_dep_bits {
	TICK_DEP_BIT_POSIX_TIMER = 0,
	TICK_DEP_BIT_PERF_EVENTS = 1,
	TICK_DEP_BIT_SCHED = 2,
	TICK_DEP_BIT_CLOCK_UNSTABLE = 3,
	TICK_DEP_BIT_RCU = 4,
	TICK_DEP_BIT_RCU_EXP = 5,
};

struct sched_clock_data {
	u64 tick_raw;
	u64 tick_gtod;
	u64 clock;
};

typedef u64 pao_T_____4;

struct idle_timer {
	struct hrtimer timer;
	int done;
};

enum schedutil_type {
	FREQUENCY_UTIL = 0,
	ENERGY_UTIL = 1,
};

enum fbq_type {
	regular = 0,
	remote = 1,
	all = 2,
};

enum group_type {
	group_has_spare = 0,
	group_fully_busy = 1,
	group_misfit_task = 2,
	group_asym_packing = 3,
	group_imbalanced = 4,
	group_overloaded = 5,
};

enum migration_type {
	migrate_load = 0,
	migrate_util = 1,
	migrate_task = 2,
	migrate_misfit = 3,
};

struct lb_env {
	struct sched_domain *sd;
	struct rq *src_rq;
	int src_cpu;
	int dst_cpu;
	struct rq *dst_rq;
	struct cpumask *dst_grpmask;
	int new_dst_cpu;
	enum cpu_idle_type idle;
	long int imbalance;
	struct cpumask *cpus;
	unsigned int flags;
	unsigned int loop;
	unsigned int loop_break;
	unsigned int loop_max;
	enum fbq_type fbq_type;
	enum migration_type migration_type;
	struct list_head tasks;
};

struct sg_lb_stats {
	long unsigned int avg_load;
	long unsigned int group_load;
	long unsigned int group_capacity;
	long unsigned int group_util;
	long unsigned int group_runnable;
	unsigned int sum_nr_running;
	unsigned int sum_h_nr_running;
	unsigned int idle_cpus;
	unsigned int group_weight;
	enum group_type group_type;
	unsigned int group_asym_packing;
	long unsigned int group_misfit_task_load;
};

struct sd_lb_stats {
	struct sched_group *busiest;
	struct sched_group *local;
	long unsigned int total_load;
	long unsigned int total_capacity;
	long unsigned int avg_load;
	unsigned int prefer_sibling;
	struct sg_lb_stats busiest_stat;
	struct sg_lb_stats local_stat;
};

typedef struct rt_rq *rt_rq_iter_t;

struct wait_bit_key {
	void *flags;
	int bit_nr;
	long unsigned int timeout;
};

struct wait_bit_queue_entry {
	struct wait_bit_key key;
	struct wait_queue_entry wq_entry;
};

typedef int wait_bit_action_f(struct wait_bit_key *, int);

struct swait_queue {
	struct task_struct *task;
	struct list_head task_list;
};

struct sched_domain_attr {
	int relax_domain_level;
};

struct s_data {
	struct sched_domain **sd;
	struct root_domain___2 *rd;
};

enum s_alloc {
	sa_rootdomain = 0,
	sa_sd = 1,
	sa_sd_storage = 2,
	sa_none = 3,
};

enum cpuacct_stat_index {
	CPUACCT_STAT_USER = 0,
	CPUACCT_STAT_SYSTEM = 1,
	CPUACCT_STAT_NSTATS = 2,
};

struct cpuacct_usage {
	u64 usages[2];
};

struct cpuacct {
	struct cgroup_subsys_state css;
	struct cpuacct_usage *cpuusage;
	struct kernel_cpustat *cpustat;
};

struct gov_attr_set {
	struct kobject kobj;
	struct list_head policy_list;
	struct mutex update_lock;
	int usage_count;
};

struct governor_attr {
	struct attribute attr;
	ssize_t (*show)(struct gov_attr_set *, char *);
	ssize_t (*store)(struct gov_attr_set *, const char *, size_t);
};

struct sugov_tunables {
	struct gov_attr_set attr_set;
	unsigned int rate_limit_us;
};

struct sugov_policy {
	struct cpufreq_policy *policy;
	struct sugov_tunables *tunables;
	struct list_head tunables_hook;
	raw_spinlock_t update_lock;
	u64 last_freq_update_time;
	s64 freq_update_delay_ns;
	unsigned int next_freq;
	unsigned int cached_raw_freq;
	struct irq_work irq_work;
	struct kthread_work work;
	struct mutex work_lock;
	struct kthread_worker worker;
	struct task_struct *thread;
	bool work_in_progress;
	bool limits_changed;
	bool need_freq_update;
};

struct sugov_cpu {
	struct update_util_data update_util;
	struct sugov_policy *sg_policy;
	unsigned int cpu;
	bool iowait_boost_pending;
	unsigned int iowait_boost;
	u64 last_update;
	long unsigned int bw_dl;
	long unsigned int max;
	long unsigned int saved_idle_calls;
};

enum {
	MEMBARRIER_FLAG_SYNC_CORE = 1,
};

enum membarrier_cmd {
	MEMBARRIER_CMD_QUERY = 0,
	MEMBARRIER_CMD_GLOBAL = 1,
	MEMBARRIER_CMD_GLOBAL_EXPEDITED = 2,
	MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED = 4,
	MEMBARRIER_CMD_PRIVATE_EXPEDITED = 8,
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED = 16,
	MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE = 32,
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE = 64,
	MEMBARRIER_CMD_SHARED = 1,
};

struct ww_acquire_ctx;

struct mutex_waiter {
	struct list_head list;
	struct task_struct *task;
	struct ww_acquire_ctx *ww_ctx;
};

struct ww_acquire_ctx {
	struct task_struct *task;
	long unsigned int stamp;
	unsigned int acquired;
	short unsigned int wounded;
	short unsigned int is_wait_die;
};

enum mutex_trylock_recursive_enum {
	MUTEX_TRYLOCK_FAILED = 0,
	MUTEX_TRYLOCK_SUCCESS = 1,
	MUTEX_TRYLOCK_RECURSIVE = 2,
};

struct ww_mutex {
	struct mutex base;
	struct ww_acquire_ctx *ctx;
};

struct semaphore {
	raw_spinlock_t lock;
	unsigned int count;
	struct list_head wait_list;
};

struct semaphore_waiter {
	struct list_head list;
	struct task_struct *task;
	bool up;
};

enum rwsem_waiter_type {
	RWSEM_WAITING_FOR_WRITE = 0,
	RWSEM_WAITING_FOR_READ = 1,
};

struct rwsem_waiter {
	struct list_head list;
	struct task_struct *task;
	enum rwsem_waiter_type type;
	long unsigned int timeout;
	long unsigned int last_rowner;
};

enum rwsem_wake_type {
	RWSEM_WAKE_ANY = 0,
	RWSEM_WAKE_READERS = 1,
	RWSEM_WAKE_READ_OWNED = 2,
};

enum writer_wait_state {
	WRITER_NOT_FIRST = 0,
	WRITER_FIRST = 1,
	WRITER_HANDOFF = 2,
};

enum owner_state {
	OWNER_NULL = 1,
	OWNER_WRITER = 2,
	OWNER_READER = 4,
	OWNER_NONSPINNABLE = 8,
};

struct optimistic_spin_node {
	struct optimistic_spin_node *next;
	struct optimistic_spin_node *prev;
	int locked;
	int cpu;
};

struct mcs_spinlock {
	struct mcs_spinlock *next;
	int locked;
	int count;
};

struct qnode {
	struct mcs_spinlock mcs;
};

struct hrtimer_sleeper {
	struct hrtimer timer;
	struct task_struct *task;
};

struct rt_mutex;

struct rt_mutex_waiter {
	struct rb_node tree_entry;
	struct rb_node pi_tree_entry;
	struct task_struct *task;
	struct rt_mutex *lock;
	int prio;
	u64 deadline;
};

struct rt_mutex {
	raw_spinlock_t wait_lock;
	struct rb_root_cached waiters;
	struct task_struct *owner;
};

enum rtmutex_chainwalk {
	RT_MUTEX_MIN_CHAINWALK = 0,
	RT_MUTEX_FULL_CHAINWALK = 1,
};

enum pm_qos_req_action {
	PM_QOS_ADD_REQ = 0,
	PM_QOS_UPDATE_REQ = 1,
	PM_QOS_REMOVE_REQ = 2,
};

struct miscdevice {
	int minor;
	const char *name;
	const struct file_operations *fops;
	struct list_head list;
	struct device *parent;
	struct device *this_device;
	const struct attribute_group **groups;
	const char *nodename;
	umode_t mode;
};

enum {
	TEST_NONE = 0,
	TEST_CORE = 1,
	TEST_CPUS = 2,
	TEST_PLATFORM = 3,
	TEST_DEVICES = 4,
	TEST_FREEZER = 5,
	__TEST_AFTER_LAST = 6,
};

struct pm_vt_switch {
	struct list_head head;
	struct device *dev;
	bool required;
};

struct platform_suspend_ops {
	int (*valid)(suspend_state_t);
	int (*begin)(suspend_state_t);
	int (*prepare)();
	int (*prepare_late)();
	int (*enter)(suspend_state_t);
	void (*wake)();
	void (*finish)();
	bool (*suspend_again)();
	void (*end)();
	void (*recover)();
};

struct platform_s2idle_ops {
	int (*begin)();
	int (*prepare)();
	int (*prepare_late)();
	bool (*wake)();
	void (*restore_early)();
	void (*restore)();
	void (*end)();
};

struct platform_hibernation_ops {
	int (*begin)(pm_message_t);
	void (*end)();
	int (*pre_snapshot)();
	void (*finish)();
	int (*prepare)();
	int (*enter)();
	void (*leave)();
	int (*pre_restore)();
	void (*restore_cleanup)();
	void (*recover)();
};

enum {
	HIBERNATION_INVALID = 0,
	HIBERNATION_PLATFORM = 1,
	HIBERNATION_SHUTDOWN = 2,
	HIBERNATION_REBOOT = 3,
	HIBERNATION_SUSPEND = 4,
	HIBERNATION_TEST_RESUME = 5,
	__HIBERNATION_AFTER_LAST = 6,
};

struct swsusp_info {
	struct new_utsname uts;
	u32 version_code;
	long unsigned int num_physpages;
	int cpus;
	long unsigned int image_pages;
	long unsigned int pages;
	long unsigned int size;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct snapshot_handle {
	unsigned int cur;
	void *buffer;
	int sync_read;
};

struct linked_page {
	struct linked_page *next;
	char data[4088];
};

struct chain_allocator {
	struct linked_page *chain;
	unsigned int used_space;
	gfp_t gfp_mask;
	int safe_needed;
};

struct rtree_node {
	struct list_head list;
	long unsigned int *data;
};

struct mem_zone_bm_rtree {
	struct list_head list;
	struct list_head nodes;
	struct list_head leaves;
	long unsigned int start_pfn;
	long unsigned int end_pfn;
	struct rtree_node *rtree;
	int levels;
	unsigned int blocks;
};

struct bm_position {
	struct mem_zone_bm_rtree *zone;
	struct rtree_node *node;
	long unsigned int node_pfn;
	int node_bit;
};

struct memory_bitmap {
	struct list_head zones;
	struct linked_page *p_list;
	struct bm_position cur;
};

struct mem_extent {
	struct list_head hook;
	long unsigned int start;
	long unsigned int end;
};

struct nosave_region {
	struct list_head list;
	long unsigned int start_pfn;
	long unsigned int end_pfn;
};

typedef struct {
	long unsigned int val;
} swp_entry_t;

enum {
	BIO_NO_PAGE_REF = 0,
	BIO_CLONED = 1,
	BIO_BOUNCED = 2,
	BIO_USER_MAPPED = 3,
	BIO_NULL_MAPPED = 4,
	BIO_WORKINGSET = 5,
	BIO_QUIET = 6,
	BIO_CHAIN = 7,
	BIO_REFFED = 8,
	BIO_THROTTLED = 9,
	BIO_TRACE_COMPLETION = 10,
	BIO_CGROUP_ACCT = 11,
	BIO_TRACKED = 12,
	BIO_FLAG_LAST = 13,
};

enum req_opf {
	REQ_OP_READ = 0,
	REQ_OP_WRITE = 1,
	REQ_OP_FLUSH = 2,
	REQ_OP_DISCARD = 3,
	REQ_OP_SECURE_ERASE = 5,
	REQ_OP_ZONE_RESET = 6,
	REQ_OP_WRITE_SAME = 7,
	REQ_OP_ZONE_RESET_ALL = 8,
	REQ_OP_WRITE_ZEROES = 9,
	REQ_OP_ZONE_OPEN = 10,
	REQ_OP_ZONE_CLOSE = 11,
	REQ_OP_ZONE_FINISH = 12,
	REQ_OP_ZONE_APPEND = 13,
	REQ_OP_SCSI_IN = 32,
	REQ_OP_SCSI_OUT = 33,
	REQ_OP_DRV_IN = 34,
	REQ_OP_DRV_OUT = 35,
	REQ_OP_LAST = 36,
};

enum req_flag_bits {
	__REQ_FAILFAST_DEV = 8,
	__REQ_FAILFAST_TRANSPORT = 9,
	__REQ_FAILFAST_DRIVER = 10,
	__REQ_SYNC = 11,
	__REQ_META = 12,
	__REQ_PRIO = 13,
	__REQ_NOMERGE = 14,
	__REQ_IDLE = 15,
	__REQ_INTEGRITY = 16,
	__REQ_FUA = 17,
	__REQ_PREFLUSH = 18,
	__REQ_RAHEAD = 19,
	__REQ_BACKGROUND = 20,
	__REQ_NOWAIT = 21,
	__REQ_CGROUP_PUNT = 22,
	__REQ_NOUNMAP = 23,
	__REQ_HIPRI = 24,
	__REQ_DRV = 25,
	__REQ_SWAP = 26,
	__REQ_NR_BITS = 27,
};

struct swap_map_page {
	sector_t entries[511];
	sector_t next_swap;
};

struct swap_map_page_list {
	struct swap_map_page *map;
	struct swap_map_page_list *next;
};

struct swap_map_handle {
	struct swap_map_page *cur;
	struct swap_map_page_list *maps;
	sector_t cur_swap;
	sector_t first_sector;
	unsigned int k;
	long unsigned int reqd_free_pages;
	u32 crc32;
};

struct swsusp_header {
	char reserved[4060];
	u32 crc32;
	sector_t image;
	unsigned int flags;
	char orig_sig[10];
	char sig[10];
};

struct swsusp_extent {
	struct rb_node node;
	long unsigned int start;
	long unsigned int end;
};

struct hib_bio_batch {
	atomic_t count;
	wait_queue_head_t wait;
	blk_status_t error;
};

struct crc_data {
	struct task_struct *thr;
	atomic_t ready;
	atomic_t stop;
	unsigned int run_threads;
	wait_queue_head_t go;
	wait_queue_head_t done;
	u32 *crc32;
	size_t *unc_len[3];
	unsigned char *unc[3];
};

struct cmp_data {
	struct task_struct *thr;
	atomic_t ready;
	atomic_t stop;
	int ret;
	wait_queue_head_t go;
	wait_queue_head_t done;
	size_t unc_len;
	size_t cmp_len;
	unsigned char unc[131072];
	unsigned char cmp[143360];
	unsigned char wrk[16384];
};

struct dec_data {
	struct task_struct *thr;
	atomic_t ready;
	atomic_t stop;
	int ret;
	wait_queue_head_t go;
	wait_queue_head_t done;
	size_t unc_len;
	size_t cmp_len;
	unsigned char unc[131072];
	unsigned char cmp[143360];
};

typedef s64 compat_loff_t;

struct resume_swap_area {
	__kernel_loff_t offset;
	__u32 dev;
} __attribute__((packed));

struct snapshot_data {
	struct snapshot_handle handle;
	int swap;
	int mode;
	bool frozen;
	bool ready;
	bool platform_support;
	bool free_bitmaps;
	struct inode *bd_inode;
};

struct compat_resume_swap_area {
	compat_loff_t offset;
	u32 dev;
} __attribute__((packed));

struct kmsg_dumper {
	struct list_head list;
	void (*dump)(struct kmsg_dumper *, enum kmsg_dump_reason);
	enum kmsg_dump_reason max_reason;
	bool active;
	bool registered;
	u32 cur_idx;
	u32 next_idx;
	u64 cur_seq;
	u64 next_seq;
};

struct trace_event_raw_console {
	struct trace_entry ent;
	u32 __data_loc_msg;
	char __data[0];
};

struct trace_event_data_offsets_console {
	u32 msg;
};

typedef void (*btf_trace_console)(void *, const char *, size_t);

struct console_cmdline {
	char name[16];
	int index;
	bool user_specified;
	char *options;
};

enum devkmsg_log_bits {
	__DEVKMSG_LOG_BIT_ON = 0,
	__DEVKMSG_LOG_BIT_OFF = 1,
	__DEVKMSG_LOG_BIT_LOCK = 2,
};

enum devkmsg_log_masks {
	DEVKMSG_LOG_MASK_ON = 1,
	DEVKMSG_LOG_MASK_OFF = 2,
	DEVKMSG_LOG_MASK_LOCK = 4,
};

enum con_msg_format_flags {
	MSG_FORMAT_DEFAULT = 0,
	MSG_FORMAT_SYSLOG = 1,
};

enum log_flags {
	LOG_NEWLINE = 2,
	LOG_CONT = 8,
};

struct printk_log {
	u64 ts_nsec;
	u16 len;
	u16 text_len;
	u16 dict_len;
	u8 facility;
	u8 flags: 5;
	u8 level: 3;
};

struct devkmsg_user {
	u64 seq;
	u32 idx;
	struct ratelimit_state rs;
	struct mutex lock;
	char buf[8192];
};

struct cont {
	char buf[992];
	size_t len;
	u32 caller_id;
	u64 ts_nsec;
	u8 level;
	u8 facility;
	enum log_flags flags;
};

struct printk_safe_seq_buf {
	atomic_t len;
	atomic_t message_lost;
	struct irq_work work;
	unsigned char buffer[8160];
};

enum {
	IRQS_AUTODETECT = 1,
	IRQS_SPURIOUS_DISABLED = 2,
	IRQS_POLL_INPROGRESS = 8,
	IRQS_ONESHOT = 32,
	IRQS_REPLAY = 64,
	IRQS_WAITING = 128,
	IRQS_PENDING = 512,
	IRQS_SUSPENDED = 2048,
	IRQS_TIMINGS = 4096,
	IRQS_NMI = 8192,
};

enum {
	_IRQ_DEFAULT_INIT_FLAGS = 0,
	_IRQ_PER_CPU = 512,
	_IRQ_LEVEL = 256,
	_IRQ_NOPROBE = 1024,
	_IRQ_NOREQUEST = 2048,
	_IRQ_NOTHREAD = 65536,
	_IRQ_NOAUTOEN = 4096,
	_IRQ_MOVE_PCNTXT = 16384,
	_IRQ_NO_BALANCING = 8192,
	_IRQ_NESTED_THREAD = 32768,
	_IRQ_PER_CPU_DEVID = 131072,
	_IRQ_IS_POLLED = 262144,
	_IRQ_DISABLE_UNLAZY = 524288,
	_IRQF_MODIFY_MASK = 1048335,
};

enum {
	IRQTF_RUNTHREAD = 0,
	IRQTF_WARNED = 1,
	IRQTF_AFFINITY = 2,
	IRQTF_FORCED_THREAD = 3,
};

enum {
	IRQC_IS_HARDIRQ = 0,
	IRQC_IS_NESTED = 1,
};

enum {
	IRQ_STARTUP_NORMAL = 0,
	IRQ_STARTUP_MANAGED = 1,
	IRQ_STARTUP_ABORT = 2,
};

struct irq_devres {
	unsigned int irq;
	void *dev_id;
};

struct irq_desc_devres {
	unsigned int from;
	unsigned int cnt;
};

struct irqchip_fwid {
	struct fwnode_handle fwnode;
	unsigned int type;
	char *name;
	phys_addr_t *pa;
};

enum {
	AFFINITY = 0,
	AFFINITY_LIST = 1,
	EFFECTIVE = 2,
	EFFECTIVE_LIST = 3,
};

struct irq_affinity {
	unsigned int pre_vectors;
	unsigned int post_vectors;
	unsigned int nr_sets;
	unsigned int set_size[4];
	void (*calc_sets)(struct irq_affinity *, unsigned int);
	void *priv;
};

struct node_vectors {
	unsigned int id;
	union {
		unsigned int nvectors;
		unsigned int ncpus;
	};
};

struct cpumap {
	unsigned int available;
	unsigned int allocated;
	unsigned int managed;
	unsigned int managed_allocated;
	bool initialized;
	bool online;
	long unsigned int alloc_map[4];
	long unsigned int managed_map[4];
};

struct irq_matrix___2 {
	unsigned int matrix_bits;
	unsigned int alloc_start;
	unsigned int alloc_end;
	unsigned int alloc_size;
	unsigned int global_available;
	unsigned int global_reserved;
	unsigned int systembits_inalloc;
	unsigned int total_allocated;
	unsigned int online_maps;
	struct cpumap *maps;
	long unsigned int scratch_map[4];
	long unsigned int system_map[4];
};

struct trace_event_raw_irq_matrix_global {
	struct trace_entry ent;
	unsigned int online_maps;
	unsigned int global_available;
	unsigned int global_reserved;
	unsigned int total_allocated;
	char __data[0];
};

struct trace_event_raw_irq_matrix_global_update {
	struct trace_entry ent;
	int bit;
	unsigned int online_maps;
	unsigned int global_available;
	unsigned int global_reserved;
	unsigned int total_allocated;
	char __data[0];
};

struct trace_event_raw_irq_matrix_cpu {
	struct trace_entry ent;
	int bit;
	unsigned int cpu;
	bool online;
	unsigned int available;
	unsigned int allocated;
	unsigned int managed;
	unsigned int online_maps;
	unsigned int global_available;
	unsigned int global_reserved;
	unsigned int total_allocated;
	char __data[0];
};

struct trace_event_data_offsets_irq_matrix_global {};

struct trace_event_data_offsets_irq_matrix_global_update {};

struct trace_event_data_offsets_irq_matrix_cpu {};

typedef void (*btf_trace_irq_matrix_online)(void *, struct irq_matrix___2 *);

typedef void (*btf_trace_irq_matrix_offline)(void *, struct irq_matrix___2 *);

typedef void (*btf_trace_irq_matrix_reserve)(void *, struct irq_matrix___2 *);

typedef void (*btf_trace_irq_matrix_remove_reserved)(void *, struct irq_matrix___2 *);

typedef void (*btf_trace_irq_matrix_assign_system)(void *, int, struct irq_matrix___2 *);

typedef void (*btf_trace_irq_matrix_alloc_reserved)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*btf_trace_irq_matrix_reserve_managed)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*btf_trace_irq_matrix_remove_managed)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*btf_trace_irq_matrix_alloc_managed)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*btf_trace_irq_matrix_assign)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*btf_trace_irq_matrix_alloc)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*btf_trace_irq_matrix_free)(void *, int, unsigned int, struct irq_matrix___2 *, struct cpumap *);

typedef void (*rcu_callback_t)(struct callback_head *);

typedef void (*call_rcu_func_t)(struct callback_head *, rcu_callback_t);

struct rcu_synchronize {
	struct callback_head head;
	struct completion completion;
};

struct trace_event_raw_rcu_utilization {
	struct trace_entry ent;
	const char *s;
	char __data[0];
};

struct trace_event_raw_rcu_grace_period {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	const char *gpevent;
	char __data[0];
};

struct trace_event_raw_rcu_future_grace_period {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	long unsigned int gp_seq_req;
	u8 level;
	int grplo;
	int grphi;
	const char *gpevent;
	char __data[0];
};

struct trace_event_raw_rcu_grace_period_init {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	u8 level;
	int grplo;
	int grphi;
	long unsigned int qsmask;
	char __data[0];
};

struct trace_event_raw_rcu_exp_grace_period {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gpseq;
	const char *gpevent;
	char __data[0];
};

struct trace_event_raw_rcu_exp_funnel_lock {
	struct trace_entry ent;
	const char *rcuname;
	u8 level;
	int grplo;
	int grphi;
	const char *gpevent;
	char __data[0];
};

struct trace_event_raw_rcu_preempt_task {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	int pid;
	char __data[0];
};

struct trace_event_raw_rcu_unlock_preempted_task {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	int pid;
	char __data[0];
};

struct trace_event_raw_rcu_quiescent_state_report {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	long unsigned int mask;
	long unsigned int qsmask;
	u8 level;
	int grplo;
	int grphi;
	u8 gp_tasks;
	char __data[0];
};

struct trace_event_raw_rcu_fqs {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int gp_seq;
	int cpu;
	const char *qsevent;
	char __data[0];
};

struct trace_event_raw_rcu_dyntick {
	struct trace_entry ent;
	const char *polarity;
	long int oldnesting;
	long int newnesting;
	int dynticks;
	char __data[0];
};

struct trace_event_raw_rcu_callback {
	struct trace_entry ent;
	const char *rcuname;
	void *rhp;
	void *func;
	long int qlen;
	char __data[0];
};

struct trace_event_raw_rcu_kfree_callback {
	struct trace_entry ent;
	const char *rcuname;
	void *rhp;
	long unsigned int offset;
	long int qlen;
	char __data[0];
};

struct trace_event_raw_rcu_batch_start {
	struct trace_entry ent;
	const char *rcuname;
	long int qlen;
	long int blimit;
	char __data[0];
};

struct trace_event_raw_rcu_invoke_callback {
	struct trace_entry ent;
	const char *rcuname;
	void *rhp;
	void *func;
	char __data[0];
};

struct trace_event_raw_rcu_invoke_kfree_callback {
	struct trace_entry ent;
	const char *rcuname;
	void *rhp;
	long unsigned int offset;
	char __data[0];
};

struct trace_event_raw_rcu_invoke_kfree_bulk_callback {
	struct trace_entry ent;
	const char *rcuname;
	long unsigned int nr_records;
	void **p;
	char __data[0];
};

struct trace_event_raw_rcu_batch_end {
	struct trace_entry ent;
	const char *rcuname;
	int callbacks_invoked;
	char cb;
	char nr;
	char iit;
	char risk;
	char __data[0];
};

struct trace_event_raw_rcu_torture_read {
	struct trace_entry ent;
	char rcutorturename[8];
	struct callback_head *rhp;
	long unsigned int secs;
	long unsigned int c_old;
	long unsigned int c;
	char __data[0];
};

struct trace_event_raw_rcu_barrier {
	struct trace_entry ent;
	const char *rcuname;
	const char *s;
	int cpu;
	int cnt;
	long unsigned int done;
	char __data[0];
};

struct trace_event_data_offsets_rcu_utilization {};

struct trace_event_data_offsets_rcu_grace_period {};

struct trace_event_data_offsets_rcu_future_grace_period {};

struct trace_event_data_offsets_rcu_grace_period_init {};

struct trace_event_data_offsets_rcu_exp_grace_period {};

struct trace_event_data_offsets_rcu_exp_funnel_lock {};

struct trace_event_data_offsets_rcu_preempt_task {};

struct trace_event_data_offsets_rcu_unlock_preempted_task {};

struct trace_event_data_offsets_rcu_quiescent_state_report {};

struct trace_event_data_offsets_rcu_fqs {};

struct trace_event_data_offsets_rcu_dyntick {};

struct trace_event_data_offsets_rcu_callback {};

struct trace_event_data_offsets_rcu_kfree_callback {};

struct trace_event_data_offsets_rcu_batch_start {};

struct trace_event_data_offsets_rcu_invoke_callback {};

struct trace_event_data_offsets_rcu_invoke_kfree_callback {};

struct trace_event_data_offsets_rcu_invoke_kfree_bulk_callback {};

struct trace_event_data_offsets_rcu_batch_end {};

struct trace_event_data_offsets_rcu_torture_read {};

struct trace_event_data_offsets_rcu_barrier {};

typedef void (*btf_trace_rcu_utilization)(void *, const char *);

typedef void (*btf_trace_rcu_grace_period)(void *, const char *, long unsigned int, const char *);

typedef void (*btf_trace_rcu_future_grace_period)(void *, const char *, long unsigned int, long unsigned int, u8, int, int, const char *);

typedef void (*btf_trace_rcu_grace_period_init)(void *, const char *, long unsigned int, u8, int, int, long unsigned int);

typedef void (*btf_trace_rcu_exp_grace_period)(void *, const char *, long unsigned int, const char *);

typedef void (*btf_trace_rcu_exp_funnel_lock)(void *, const char *, u8, int, int, const char *);

typedef void (*btf_trace_rcu_preempt_task)(void *, const char *, int, long unsigned int);

typedef void (*btf_trace_rcu_unlock_preempted_task)(void *, const char *, long unsigned int, int);

typedef void (*btf_trace_rcu_quiescent_state_report)(void *, const char *, long unsigned int, long unsigned int, long unsigned int, u8, int, int, int);

typedef void (*btf_trace_rcu_fqs)(void *, const char *, long unsigned int, int, const char *);

typedef void (*btf_trace_rcu_dyntick)(void *, const char *, long int, long int, int);

typedef void (*btf_trace_rcu_callback)(void *, const char *, struct callback_head *, long int);

typedef void (*btf_trace_rcu_kfree_callback)(void *, const char *, struct callback_head *, long unsigned int, long int);

typedef void (*btf_trace_rcu_batch_start)(void *, const char *, long int, long int);

typedef void (*btf_trace_rcu_invoke_callback)(void *, const char *, struct callback_head *);

typedef void (*btf_trace_rcu_invoke_kfree_callback)(void *, const char *, struct callback_head *, long unsigned int);

typedef void (*btf_trace_rcu_invoke_kfree_bulk_callback)(void *, const char *, long unsigned int, void **);

typedef void (*btf_trace_rcu_batch_end)(void *, const char *, int, char, char, char, char);

typedef void (*btf_trace_rcu_torture_read)(void *, const char *, struct callback_head *, long unsigned int, long unsigned int, long unsigned int);

typedef void (*btf_trace_rcu_barrier)(void *, const char *, const char *, int, int, long unsigned int);

enum {
	GP_IDLE = 0,
	GP_ENTER = 1,
	GP_PASSED = 2,
	GP_EXIT = 3,
	GP_REPLAY = 4,
};

typedef long unsigned int ulong;

struct rcu_cblist {
	struct callback_head *head;
	struct callback_head **tail;
	long int len;
};

enum rcutorture_type {
	RCU_FLAVOR = 0,
	RCU_TASKS_FLAVOR = 1,
	RCU_TASKS_RUDE_FLAVOR = 2,
	RCU_TASKS_TRACING_FLAVOR = 3,
	RCU_TRIVIAL_FLAVOR = 4,
	SRCU_FLAVOR = 5,
	INVALID_RCU_FLAVOR = 6,
};

enum tick_device_mode {
	TICKDEV_MODE_PERIODIC = 0,
	TICKDEV_MODE_ONESHOT = 1,
};

struct tick_device___2 {
	struct clock_event_device *evtdev;
	enum tick_device_mode mode;
};

struct rcu_exp_work {
	long unsigned int rew_s;
	struct work_struct rew_work;
};

struct rcu_node {
	raw_spinlock_t lock;
	long unsigned int gp_seq;
	long unsigned int gp_seq_needed;
	long unsigned int completedqs;
	long unsigned int qsmask;
	long unsigned int rcu_gp_init_mask;
	long unsigned int qsmaskinit;
	long unsigned int qsmaskinitnext;
	long unsigned int expmask;
	long unsigned int expmaskinit;
	long unsigned int expmaskinitnext;
	long unsigned int cbovldmask;
	long unsigned int ffmask;
	long unsigned int grpmask;
	int grplo;
	int grphi;
	u8 grpnum;
	u8 level;
	bool wait_blkd_tasks;
	struct rcu_node *parent;
	struct list_head blkd_tasks;
	struct list_head *gp_tasks;
	struct list_head *exp_tasks;
	struct list_head *boost_tasks;
	struct rt_mutex boost_mtx;
	long unsigned int boost_time;
	struct task_struct *boost_kthread_task;
	unsigned int boost_kthread_status;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	raw_spinlock_t fqslock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t exp_lock;
	long unsigned int exp_seq_rq;
	wait_queue_head_t exp_wq[4];
	struct rcu_exp_work rew;
	bool exp_need_flush;
	long: 56;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

union rcu_noqs {
	struct {
		u8 norm;
		u8 exp;
	} b;
	u16 s;
};

struct rcu_data {
	long unsigned int gp_seq;
	long unsigned int gp_seq_needed;
	union rcu_noqs cpu_no_qs;
	bool core_needs_qs;
	bool beenonline;
	bool gpwrap;
	bool exp_deferred_qs;
	struct rcu_node *mynode;
	long unsigned int grpmask;
	long unsigned int ticks_this_gp;
	struct irq_work defer_qs_iw;
	bool defer_qs_iw_pending;
	struct rcu_segcblist cblist;
	long int qlen_last_fqs_check;
	long unsigned int n_force_qs_snap;
	long int blimit;
	int dynticks_snap;
	long int dynticks_nesting;
	long int dynticks_nmi_nesting;
	atomic_t dynticks;
	bool rcu_need_heavy_qs;
	bool rcu_urgent_qs;
	bool rcu_forced_tick;
	bool rcu_forced_tick_exp;
	struct callback_head barrier_head;
	int exp_dynticks_snap;
	struct task_struct *rcu_cpu_kthread_task;
	unsigned int rcu_cpu_kthread_status;
	char rcu_cpu_has_work;
	unsigned int softirq_snap;
	struct irq_work rcu_iw;
	bool rcu_iw_pending;
	long unsigned int rcu_iw_gp_seq;
	long unsigned int rcu_ofl_gp_seq;
	short int rcu_ofl_gp_flags;
	long unsigned int rcu_onl_gp_seq;
	short int rcu_onl_gp_flags;
	long unsigned int last_fqs_resched;
	int cpu;
};

struct rcu_state {
	struct rcu_node node[5];
	struct rcu_node *level[3];
	int ncpus;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	u8 boost;
	long unsigned int gp_seq;
	struct task_struct *gp_kthread;
	struct swait_queue_head gp_wq;
	short int gp_flags;
	short int gp_state;
	long unsigned int gp_wake_time;
	long unsigned int gp_wake_seq;
	struct mutex barrier_mutex;
	atomic_t barrier_cpu_count;
	struct completion barrier_completion;
	long unsigned int barrier_sequence;
	struct mutex exp_mutex;
	struct mutex exp_wake_mutex;
	long unsigned int expedited_sequence;
	atomic_t expedited_need_qs;
	struct swait_queue_head expedited_wq;
	int ncpus_snap;
	u8 cbovld;
	u8 cbovldnext;
	long unsigned int jiffies_force_qs;
	long unsigned int jiffies_kick_kthreads;
	long unsigned int n_force_qs;
	long unsigned int gp_start;
	long unsigned int gp_end;
	long unsigned int gp_activity;
	long unsigned int gp_req_activity;
	long unsigned int jiffies_stall;
	long unsigned int jiffies_resched;
	long unsigned int n_force_qs_gpstart;
	long unsigned int gp_max;
	const char *name;
	char abbr;
	long: 56;
	long: 64;
	long: 64;
	raw_spinlock_t ofl_lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct kfree_rcu_bulk_data {
	long unsigned int nr_records;
	void *records[509];
	struct kfree_rcu_bulk_data *next;
	struct callback_head *head_free_debug;
};

struct kfree_rcu_cpu;

struct kfree_rcu_cpu_work {
	struct rcu_work rcu_work;
	struct callback_head *head_free;
	struct kfree_rcu_bulk_data *bhead_free;
	struct kfree_rcu_cpu *krcp;
};

struct kfree_rcu_cpu {
	struct callback_head *head;
	struct kfree_rcu_bulk_data *bhead;
	struct kfree_rcu_bulk_data *bcached;
	struct kfree_rcu_cpu_work krw_arr[2];
	spinlock_t lock;
	struct delayed_work monitor_work;
	bool monitor_todo;
	bool initialized;
	int count;
};

typedef char pto_T_____18;

struct dma_devres {
	size_t size;
	void *vaddr;
	dma_addr_t dma_handle;
	long unsigned int attrs;
};

enum dma_sync_target {
	SYNC_FOR_CPU = 0,
	SYNC_FOR_DEVICE = 1,
};

struct trace_event_raw_swiotlb_bounced {
	struct trace_entry ent;
	u32 __data_loc_dev_name;
	u64 dma_mask;
	dma_addr_t dev_addr;
	size_t size;
	enum swiotlb_force swiotlb_force;
	char __data[0];
};

struct trace_event_data_offsets_swiotlb_bounced {
	u32 dev_name;
};

typedef void (*btf_trace_swiotlb_bounced)(void *, struct device *, dma_addr_t, size_t, enum swiotlb_force);

enum profile_type {
	PROFILE_TASK_EXIT = 0,
	PROFILE_MUNMAP = 1,
};

struct profile_hit {
	u32 pc;
	u32 hits;
};

struct stacktrace_cookie {
	long unsigned int *store;
	unsigned int size;
	unsigned int skip;
	unsigned int len;
};

typedef __kernel_long_t __kernel_suseconds_t;

typedef __kernel_long_t __kernel_old_time_t;

typedef __kernel_suseconds_t suseconds_t;

typedef __u64 timeu64_t;

struct __kernel_itimerspec {
	struct __kernel_timespec it_interval;
	struct __kernel_timespec it_value;
};

struct itimerspec64 {
	struct timespec64 it_interval;
	struct timespec64 it_value;
};

struct old_itimerspec32 {
	struct old_timespec32 it_interval;
	struct old_timespec32 it_value;
};

struct old_timex32 {
	u32 modes;
	s32 offset;
	s32 freq;
	s32 maxerror;
	s32 esterror;
	s32 status;
	s32 constant;
	s32 precision;
	s32 tolerance;
	struct old_timeval32 time;
	s32 tick;
	s32 ppsfreq;
	s32 jitter;
	s32 shift;
	s32 stabil;
	s32 jitcnt;
	s32 calcnt;
	s32 errcnt;
	s32 stbcnt;
	s32 tai;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct __kernel_timex_timeval {
	__kernel_time64_t tv_sec;
	long long int tv_usec;
};

struct __kernel_timex {
	unsigned int modes;
	long long int offset;
	long long int freq;
	long long int maxerror;
	long long int esterror;
	int status;
	long long int constant;
	long long int precision;
	long long int tolerance;
	struct __kernel_timex_timeval time;
	long long int tick;
	long long int ppsfreq;
	long long int jitter;
	int shift;
	long long int stabil;
	long long int jitcnt;
	long long int calcnt;
	long long int errcnt;
	long long int stbcnt;
	int tai;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct trace_event_raw_timer_class {
	struct trace_entry ent;
	void *timer;
	char __data[0];
};

struct trace_event_raw_timer_start {
	struct trace_entry ent;
	void *timer;
	void *function;
	long unsigned int expires;
	long unsigned int now;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_timer_expire_entry {
	struct trace_entry ent;
	void *timer;
	long unsigned int now;
	void *function;
	long unsigned int baseclk;
	char __data[0];
};

struct trace_event_raw_hrtimer_init {
	struct trace_entry ent;
	void *hrtimer;
	clockid_t clockid;
	enum hrtimer_mode mode;
	char __data[0];
};

struct trace_event_raw_hrtimer_start {
	struct trace_entry ent;
	void *hrtimer;
	void *function;
	s64 expires;
	s64 softexpires;
	enum hrtimer_mode mode;
	char __data[0];
};

struct trace_event_raw_hrtimer_expire_entry {
	struct trace_entry ent;
	void *hrtimer;
	s64 now;
	void *function;
	char __data[0];
};

struct trace_event_raw_hrtimer_class {
	struct trace_entry ent;
	void *hrtimer;
	char __data[0];
};

struct trace_event_raw_itimer_state {
	struct trace_entry ent;
	int which;
	long long unsigned int expires;
	long int value_sec;
	long int value_nsec;
	long int interval_sec;
	long int interval_nsec;
	char __data[0];
};

struct trace_event_raw_itimer_expire {
	struct trace_entry ent;
	int which;
	pid_t pid;
	long long unsigned int now;
	char __data[0];
};

struct trace_event_raw_tick_stop {
	struct trace_entry ent;
	int success;
	int dependency;
	char __data[0];
};

struct trace_event_data_offsets_timer_class {};

struct trace_event_data_offsets_timer_start {};

struct trace_event_data_offsets_timer_expire_entry {};

struct trace_event_data_offsets_hrtimer_init {};

struct trace_event_data_offsets_hrtimer_start {};

struct trace_event_data_offsets_hrtimer_expire_entry {};

struct trace_event_data_offsets_hrtimer_class {};

struct trace_event_data_offsets_itimer_state {};

struct trace_event_data_offsets_itimer_expire {};

struct trace_event_data_offsets_tick_stop {};

typedef void (*btf_trace_timer_init)(void *, struct timer_list *);

typedef void (*btf_trace_timer_start)(void *, struct timer_list *, long unsigned int, unsigned int);

typedef void (*btf_trace_timer_expire_entry)(void *, struct timer_list *, long unsigned int);

typedef void (*btf_trace_timer_expire_exit)(void *, struct timer_list *);

typedef void (*btf_trace_timer_cancel)(void *, struct timer_list *);

typedef void (*btf_trace_hrtimer_init)(void *, struct hrtimer *, clockid_t, enum hrtimer_mode);

typedef void (*btf_trace_hrtimer_start)(void *, struct hrtimer *, enum hrtimer_mode);

typedef void (*btf_trace_hrtimer_expire_entry)(void *, struct hrtimer *, ktime_t *);

typedef void (*btf_trace_hrtimer_expire_exit)(void *, struct hrtimer *);

typedef void (*btf_trace_hrtimer_cancel)(void *, struct hrtimer *);

typedef void (*btf_trace_itimer_state)(void *, int, const struct itimerspec64 * const, long long unsigned int);

typedef void (*btf_trace_itimer_expire)(void *, int, struct pid *, long long unsigned int);

typedef void (*btf_trace_tick_stop)(void *, int, int);

struct timer_base {
	raw_spinlock_t lock;
	struct timer_list *running_timer;
	long unsigned int clk;
	long unsigned int next_expiry;
	unsigned int cpu;
	bool is_idle;
	bool must_forward_clk;
	long unsigned int pending_map[9];
	struct hlist_head vectors[576];
	long: 64;
	long: 64;
};

struct process_timer {
	struct timer_list timer;
	struct task_struct *task;
};

typedef __u32 pao_T_____5;

struct system_time_snapshot {
	u64 cycles;
	ktime_t real;
	ktime_t raw;
	unsigned int clock_was_set_seq;
	u8 cs_was_changed_seq;
};

struct system_device_crosststamp {
	ktime_t device;
	ktime_t sys_realtime;
	ktime_t sys_monoraw;
};

struct tk_read_base {
	struct clocksource *clock;
	u64 mask;
	u64 cycle_last;
	u32 mult;
	u32 shift;
	u64 xtime_nsec;
	ktime_t base;
	u64 base_real;
};

struct timekeeper {
	struct tk_read_base tkr_mono;
	struct tk_read_base tkr_raw;
	u64 xtime_sec;
	long unsigned int ktime_sec;
	struct timespec64 wall_to_monotonic;
	ktime_t offs_real;
	ktime_t offs_boot;
	ktime_t offs_tai;
	s32 tai_offset;
	unsigned int clock_was_set_seq;
	u8 cs_was_changed_seq;
	ktime_t next_leap_ktime;
	u64 raw_sec;
	struct timespec64 monotonic_to_boot;
	u64 cycle_interval;
	u64 xtime_interval;
	s64 xtime_remainder;
	u64 raw_interval;
	u64 ntp_tick;
	s64 ntp_error;
	u32 ntp_error_shift;
	u32 ntp_err_mult;
	u32 skip_second_overflow;
};

struct audit_ntp_val {
	long long int oldval;
	long long int newval;
};

struct audit_ntp_data {
	struct audit_ntp_val vals[6];
};

enum timekeeping_adv_mode {
	TK_ADV_TICK = 0,
	TK_ADV_FREQ = 1,
};

struct tk_fast {
	seqcount_t seq;
	struct tk_read_base base[2];
};

typedef s64 int64_t;

enum tick_nohz_mode {
	NOHZ_MODE_INACTIVE = 0,
	NOHZ_MODE_LOWRES = 1,
	NOHZ_MODE_HIGHRES = 2,
};

struct tick_sched {
	struct hrtimer sched_timer;
	long unsigned int check_clocks;
	enum tick_nohz_mode nohz_mode;
	unsigned int inidle: 1;
	unsigned int tick_stopped: 1;
	unsigned int idle_active: 1;
	unsigned int do_timer_last: 1;
	unsigned int got_idle_tick: 1;
	ktime_t last_tick;
	ktime_t next_tick;
	long unsigned int idle_jiffies;
	long unsigned int idle_calls;
	long unsigned int idle_sleeps;
	ktime_t idle_entrytime;
	ktime_t idle_waketime;
	ktime_t idle_exittime;
	ktime_t idle_sleeptime;
	ktime_t iowait_sleeptime;
	long unsigned int last_jiffies;
	u64 timer_expires;
	u64 timer_expires_base;
	u64 next_timer;
	ktime_t idle_expires;
	atomic_t tick_dep_mask;
};

struct timer_list_iter {
	int cpu;
	bool second_pass;
	u64 now;
};

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	long int tm_year;
	int tm_wday;
	int tm_yday;
};

struct cyclecounter {
	u64 (*read)(const struct cyclecounter *);
	u64 mask;
	u32 mult;
	u32 shift;
};

struct timecounter {
	const struct cyclecounter *cc;
	u64 cycle_last;
	u64 nsec;
	u64 mask;
	u64 frac;
};

typedef __kernel_timer_t timer_t;

struct rtc_wkalrm {
	unsigned char enabled;
	unsigned char pending;
	struct rtc_time time;
};

enum alarmtimer_type {
	ALARM_REALTIME = 0,
	ALARM_BOOTTIME = 1,
	ALARM_NUMTYPE = 2,
	ALARM_REALTIME_FREEZER = 3,
	ALARM_BOOTTIME_FREEZER = 4,
};

enum alarmtimer_restart {
	ALARMTIMER_NORESTART = 0,
	ALARMTIMER_RESTART = 1,
};

struct alarm {
	struct timerqueue_node node;
	struct hrtimer timer;
	enum alarmtimer_restart (*function)(struct alarm *, ktime_t);
	enum alarmtimer_type type;
	int state;
	void *data;
};

struct cpu_timer {
	struct timerqueue_node node;
	struct timerqueue_head *head;
	struct pid *pid;
	struct list_head elist;
	int firing;
};

struct k_clock;

struct k_itimer {
	struct list_head list;
	struct hlist_node t_hash;
	spinlock_t it_lock;
	const struct k_clock *kclock;
	clockid_t it_clock;
	timer_t it_id;
	int it_active;
	s64 it_overrun;
	s64 it_overrun_last;
	int it_requeue_pending;
	int it_sigev_notify;
	ktime_t it_interval;
	struct signal_struct *it_signal;
	union {
		struct pid *it_pid;
		struct task_struct *it_process;
	};
	struct sigqueue *sigq;
	union {
		struct {
			struct hrtimer timer;
		} real;
		struct cpu_timer cpu;
		struct {
			struct alarm alarmtimer;
		} alarm;
	} it;
	struct callback_head rcu;
};

struct k_clock {
	int (*clock_getres)(const clockid_t, struct timespec64 *);
	int (*clock_set)(const clockid_t, const struct timespec64 *);
	int (*clock_get_timespec)(const clockid_t, struct timespec64 *);
	ktime_t (*clock_get_ktime)(const clockid_t);
	int (*clock_adj)(const clockid_t, struct __kernel_timex *);
	int (*timer_create)(struct k_itimer *);
	int (*nsleep)(const clockid_t, int, const struct timespec64 *);
	int (*timer_set)(struct k_itimer *, int, struct itimerspec64 *, struct itimerspec64 *);
	int (*timer_del)(struct k_itimer *);
	void (*timer_get)(struct k_itimer *, struct itimerspec64 *);
	void (*timer_rearm)(struct k_itimer *);
	s64 (*timer_forward)(struct k_itimer *, ktime_t);
	ktime_t (*timer_remaining)(struct k_itimer *, ktime_t);
	int (*timer_try_to_cancel)(struct k_itimer *);
	void (*timer_arm)(struct k_itimer *, ktime_t, bool, bool);
	void (*timer_wait_running)(struct k_itimer *);
};

struct class_interface {
	struct list_head node;
	struct class *class;
	int (*add_dev)(struct device *, struct class_interface *);
	void (*remove_dev)(struct device *, struct class_interface *);
};

struct rtc_class_ops {
	int (*ioctl)(struct device *, unsigned int, long unsigned int);
	int (*read_time)(struct device *, struct rtc_time *);
	int (*set_time)(struct device *, struct rtc_time *);
	int (*read_alarm)(struct device *, struct rtc_wkalrm *);
	int (*set_alarm)(struct device *, struct rtc_wkalrm *);
	int (*proc)(struct device *, struct seq_file *);
	int (*alarm_irq_enable)(struct device *, unsigned int);
	int (*read_offset)(struct device *, long int *);
	int (*set_offset)(struct device *, long int);
};

struct rtc_device;

struct rtc_timer {
	struct timerqueue_node node;
	ktime_t period;
	void (*func)(struct rtc_device *);
	struct rtc_device *rtc;
	int enabled;
};

struct rtc_device {
	struct device dev;
	struct module *owner;
	int id;
	const struct rtc_class_ops *ops;
	struct mutex ops_lock;
	struct cdev char_dev;
	long unsigned int flags;
	long unsigned int irq_data;
	spinlock_t irq_lock;
	wait_queue_head_t irq_queue;
	struct fasync_struct *async_queue;
	int irq_freq;
	int max_user_freq;
	struct timerqueue_head timerqueue;
	struct rtc_timer aie_timer;
	struct rtc_timer uie_rtctimer;
	struct hrtimer pie_timer;
	int pie_enabled;
	struct work_struct irqwork;
	int uie_unsupported;
	long int set_offset_nsec;
	bool registered;
	bool nvram_old_abi;
	struct bin_attribute *nvram;
	time64_t range_min;
	timeu64_t range_max;
	time64_t start_secs;
	time64_t offset_secs;
	bool set_start_time;
};

struct platform_driver {
	int (*probe)(struct platform_device *);
	int (*remove)(struct platform_device *);
	void (*shutdown)(struct platform_device *);
	int (*suspend)(struct platform_device *, pm_message_t);
	int (*resume)(struct platform_device *);
	struct device_driver driver;
	const struct platform_device_id *id_table;
	bool prevent_deferred_probe;
};

struct trace_event_raw_alarmtimer_suspend {
	struct trace_entry ent;
	s64 expires;
	unsigned char alarm_type;
	char __data[0];
};

struct trace_event_raw_alarm_class {
	struct trace_entry ent;
	void *alarm;
	unsigned char alarm_type;
	s64 expires;
	s64 now;
	char __data[0];
};

struct trace_event_data_offsets_alarmtimer_suspend {};

struct trace_event_data_offsets_alarm_class {};

typedef void (*btf_trace_alarmtimer_suspend)(void *, ktime_t, int);

typedef void (*btf_trace_alarmtimer_fired)(void *, struct alarm *, ktime_t);

typedef void (*btf_trace_alarmtimer_start)(void *, struct alarm *, ktime_t);

typedef void (*btf_trace_alarmtimer_cancel)(void *, struct alarm *, ktime_t);

struct alarm_base {
	spinlock_t lock;
	struct timerqueue_head timerqueue;
	ktime_t (*get_ktime)();
	void (*get_timespec)(struct timespec64 *);
	clockid_t base_clockid;
};

struct sigevent {
	sigval_t sigev_value;
	int sigev_signo;
	int sigev_notify;
	union {
		int _pad[12];
		int _tid;
		struct {
			void (*_function)(sigval_t);
			void *_attribute;
		} _sigev_thread;
	} _sigev_un;
};

typedef struct sigevent sigevent_t;

struct compat_sigevent {
	compat_sigval_t sigev_value;
	compat_int_t sigev_signo;
	compat_int_t sigev_notify;
	union {
		compat_int_t _pad[13];
		compat_int_t _tid;
		struct {
			compat_uptr_t _function;
			compat_uptr_t _attribute;
		} _sigev_thread;
	} _sigev_un;
};

typedef unsigned int uint;

struct posix_clock;

struct posix_clock_operations {
	struct module *owner;
	int (*clock_adjtime)(struct posix_clock *, struct __kernel_timex *);
	int (*clock_gettime)(struct posix_clock *, struct timespec64 *);
	int (*clock_getres)(struct posix_clock *, struct timespec64 *);
	int (*clock_settime)(struct posix_clock *, const struct timespec64 *);
	long int (*ioctl)(struct posix_clock *, unsigned int, long unsigned int);
	int (*open)(struct posix_clock *, fmode_t);
	__poll_t (*poll)(struct posix_clock *, struct file *, poll_table *);
	int (*release)(struct posix_clock *);
	ssize_t (*read)(struct posix_clock *, uint, char *, size_t);
};

struct posix_clock {
	struct posix_clock_operations ops;
	struct cdev cdev;
	struct device *dev;
	struct rw_semaphore rwsem;
	bool zombie;
};

struct posix_clock_desc {
	struct file *fp;
	struct posix_clock *clk;
};

struct __kernel_old_itimerval {
	struct __kernel_old_timeval it_interval;
	struct __kernel_old_timeval it_value;
};

struct old_itimerval32 {
	struct old_timeval32 it_interval;
	struct old_timeval32 it_value;
};

struct ce_unbind {
	struct clock_event_device *ce;
	int res;
};

typedef ktime_t pto_T_____19;

struct proc_timens_offset {
	int clockid;
	struct timespec64 val;
};

union futex_key {
	struct {
		u64 i_seq;
		long unsigned int pgoff;
		unsigned int offset;
	} shared;
	struct {
		union {
			struct mm_struct *mm;
			u64 __tmp;
		};
		long unsigned int address;
		unsigned int offset;
	} private;
	struct {
		u64 ptr;
		long unsigned int word;
		unsigned int offset;
	} both;
};

struct futex_pi_state {
	struct list_head list;
	struct rt_mutex pi_mutex;
	struct task_struct *owner;
	refcount_t refcount;
	union futex_key key;
};

struct futex_q {
	struct plist_node list;
	struct task_struct *task;
	spinlock_t *lock_ptr;
	union futex_key key;
	struct futex_pi_state *pi_state;
	struct rt_mutex_waiter *rt_waiter;
	union futex_key *requeue_pi_key;
	u32 bitset;
};

struct futex_hash_bucket {
	atomic_t waiters;
	spinlock_t lock;
	struct plist_head chain;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum futex_access {
	FUTEX_READ = 0,
	FUTEX_WRITE = 1,
};

struct dma_chan {
	int lock;
	const char *device_id;
};

typedef bool (*smp_cond_func_t)(int, void *);

struct call_function_data {
	call_single_data_t *csd;
	cpumask_var_t cpumask;
	cpumask_var_t cpumask_ipi;
};

struct smp_call_on_cpu_struct {
	struct work_struct work;
	struct completion done;
	int (*func)(void *);
	void *data;
	int ret;
	int cpu;
};

struct latch_tree_root {
	seqcount_t seq;
	struct rb_root tree[2];
};

struct latch_tree_ops {
	bool (*less)(struct latch_tree_node *, struct latch_tree_node *);
	int (*comp)(void *, struct latch_tree_node *);
};

struct module_use {
	struct list_head source_list;
	struct list_head target_list;
	struct module *source;
	struct module *target;
};

struct module_sect_attr {
	struct bin_attribute battr;
	long unsigned int address;
};

struct module_sect_attrs {
	struct attribute_group grp;
	unsigned int nsections;
	struct module_sect_attr attrs[0];
};

struct module_notes_attrs {
	struct kobject *dir;
	unsigned int notes;
	struct bin_attribute attrs[0];
};

struct symsearch {
	const struct kernel_symbol *start;
	const struct kernel_symbol *stop;
	const s32 *crcs;
	enum {
		NOT_GPL_ONLY = 0,
		GPL_ONLY = 1,
		WILL_BE_GPL_ONLY = 2,
	} licence;
	bool unused;
};

enum kernel_read_file_id {
	READING_UNKNOWN = 0,
	READING_FIRMWARE = 1,
	READING_FIRMWARE_PREALLOC_BUFFER = 2,
	READING_FIRMWARE_EFI_EMBEDDED = 3,
	READING_MODULE = 4,
	READING_KEXEC_IMAGE = 5,
	READING_KEXEC_INITRAMFS = 6,
	READING_POLICY = 7,
	READING_X509_CERTIFICATE = 8,
	READING_MAX_ID = 9,
};

enum kernel_load_data_id {
	LOADING_UNKNOWN = 0,
	LOADING_FIRMWARE = 1,
	LOADING_FIRMWARE_PREALLOC_BUFFER = 2,
	LOADING_FIRMWARE_EFI_EMBEDDED = 3,
	LOADING_MODULE = 4,
	LOADING_KEXEC_IMAGE = 5,
	LOADING_KEXEC_INITRAMFS = 6,
	LOADING_POLICY = 7,
	LOADING_X509_CERTIFICATE = 8,
	LOADING_MAX_ID = 9,
};

enum {
	PROC_ENTRY_PERMANENT = 1,
};

struct _ddebug {
	const char *modname;
	const char *function;
	const char *filename;
	const char *format;
	unsigned int lineno: 18;
	unsigned int flags: 8;
	union {
		struct static_key_true dd_key_true;
		struct static_key_false dd_key_false;
	} key;
};

struct load_info {
	const char *name;
	struct module *mod;
	Elf64_Ehdr *hdr;
	long unsigned int len;
	Elf64_Shdr *sechdrs;
	char *secstrings;
	char *strtab;
	long unsigned int symoffs;
	long unsigned int stroffs;
	long unsigned int init_typeoffs;
	long unsigned int core_typeoffs;
	struct _ddebug *debug;
	unsigned int num_debug;
	bool sig_ok;
	long unsigned int mod_kallsyms_init_off;
	struct {
		unsigned int sym;
		unsigned int str;
		unsigned int mod;
		unsigned int vers;
		unsigned int info;
		unsigned int pcpu;
	} index;
};

struct trace_event_raw_module_load {
	struct trace_entry ent;
	unsigned int taints;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_module_free {
	struct trace_entry ent;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_module_refcnt {
	struct trace_entry ent;
	long unsigned int ip;
	int refcnt;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_module_request {
	struct trace_entry ent;
	long unsigned int ip;
	bool wait;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_data_offsets_module_load {
	u32 name;
};

struct trace_event_data_offsets_module_free {
	u32 name;
};

struct trace_event_data_offsets_module_refcnt {
	u32 name;
};

struct trace_event_data_offsets_module_request {
	u32 name;
};

typedef void (*btf_trace_module_load)(void *, struct module *);

typedef void (*btf_trace_module_free)(void *, struct module *);

typedef void (*btf_trace_module_get)(void *, struct module *, long unsigned int);

typedef void (*btf_trace_module_put)(void *, struct module *, long unsigned int);

typedef void (*btf_trace_module_request)(void *, char *, bool, long unsigned int);

struct mod_tree_root {
	struct latch_tree_root root;
	long unsigned int addr_min;
	long unsigned int addr_max;
};

struct find_symbol_arg {
	const char *name;
	bool gplok;
	bool warn;
	struct module *owner;
	const s32 *crc;
	const struct kernel_symbol *sym;
};

struct mod_initfree {
	struct llist_node node;
	void *module_init;
};

struct kallsym_iter {
	loff_t pos;
	loff_t pos_arch_end;
	loff_t pos_mod_end;
	loff_t pos_ftrace_mod_end;
	long unsigned int value;
	unsigned int nameoff;
	char type;
	char name[128];
	char module_name[56];
	int exported;
	int show_value;
};

enum {
	SB_UNFROZEN = 0,
	SB_FREEZE_WRITE = 1,
	SB_FREEZE_PAGEFAULT = 2,
	SB_FREEZE_FS = 3,
	SB_FREEZE_COMPLETE = 4,
};

typedef __u16 comp_t;

typedef __u32 comp2_t;

struct acct {
	char ac_flag;
	char ac_version;
	__u16 ac_uid16;
	__u16 ac_gid16;
	__u16 ac_tty;
	__u32 ac_btime;
	comp_t ac_utime;
	comp_t ac_stime;
	comp_t ac_etime;
	comp_t ac_mem;
	comp_t ac_io;
	comp_t ac_rw;
	comp_t ac_minflt;
	comp_t ac_majflt;
	comp_t ac_swaps;
	__u16 ac_ahz;
	__u32 ac_exitcode;
	char ac_comm[17];
	__u8 ac_etime_hi;
	__u16 ac_etime_lo;
	__u32 ac_uid;
	__u32 ac_gid;
};

typedef struct acct acct_t;

struct fs_pin {
	wait_queue_head_t wait;
	int done;
	struct hlist_node s_list;
	struct hlist_node m_list;
	void (*kill)(struct fs_pin *);
};

struct bsd_acct_struct {
	struct fs_pin pin;
	atomic_long_t count;
	struct callback_head rcu;
	struct mutex lock;
	int active;
	long unsigned int needcheck;
	struct file *file;
	struct pid_namespace *ns;
	struct work_struct work;
	struct completion done;
};

struct elf64_note {
	Elf64_Word n_namesz;
	Elf64_Word n_descsz;
	Elf64_Word n_type;
};

typedef long unsigned int elf_greg_t;

typedef elf_greg_t elf_gregset_t[27];

struct elf_siginfo {
	int si_signo;
	int si_code;
	int si_errno;
};

struct elf_prstatus {
	struct elf_siginfo pr_info;
	short int pr_cursig;
	long unsigned int pr_sigpend;
	long unsigned int pr_sighold;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgrp;
	pid_t pr_sid;
	struct __kernel_old_timeval pr_utime;
	struct __kernel_old_timeval pr_stime;
	struct __kernel_old_timeval pr_cutime;
	struct __kernel_old_timeval pr_cstime;
	elf_gregset_t pr_reg;
	int pr_fpvalid;
};

struct compat_kexec_segment {
	compat_uptr_t buf;
	compat_size_t bufsz;
	compat_ulong_t mem;
	compat_size_t memsz;
};

enum migrate_reason {
	MR_COMPACTION = 0,
	MR_MEMORY_FAILURE = 1,
	MR_MEMORY_HOTPLUG = 2,
	MR_SYSCALL = 3,
	MR_MEMPOLICY_MBIND = 4,
	MR_NUMA_MISPLACED = 5,
	MR_CONTIG_RANGE = 6,
	MR_TYPES = 7,
};

typedef __kernel_ulong_t __kernel_ino_t;

typedef __kernel_ino_t ino_t;

enum kernfs_node_type {
	KERNFS_DIR = 1,
	KERNFS_FILE = 2,
	KERNFS_LINK = 4,
};

enum kernfs_root_flag {
	KERNFS_ROOT_CREATE_DEACTIVATED = 1,
	KERNFS_ROOT_EXTRA_OPEN_PERM_CHECK = 2,
	KERNFS_ROOT_SUPPORT_EXPORTOP = 4,
	KERNFS_ROOT_SUPPORT_USER_XATTR = 8,
};

struct kernfs_fs_context {
	struct kernfs_root *root;
	void *ns_tag;
	long unsigned int magic;
	bool new_sb_created;
};

enum {
	__PERCPU_REF_ATOMIC = 1,
	__PERCPU_REF_DEAD = 2,
	__PERCPU_REF_ATOMIC_DEAD = 3,
	__PERCPU_REF_FLAG_BITS = 2,
};

enum bpf_link_type {
	BPF_LINK_TYPE_UNSPEC = 0,
	BPF_LINK_TYPE_RAW_TRACEPOINT = 1,
	BPF_LINK_TYPE_TRACING = 2,
	BPF_LINK_TYPE_CGROUP = 3,
	BPF_LINK_TYPE_ITER = 4,
	BPF_LINK_TYPE_NETNS = 5,
	MAX_BPF_LINK_TYPE = 6,
};

struct bpf_link_info {
	__u32 type;
	__u32 id;
	__u32 prog_id;
	union {
		struct {
			__u64 tp_name;
			__u32 tp_name_len;
		} raw_tracepoint;
		struct {
			__u32 attach_type;
		} tracing;
		struct {
			__u64 cgroup_id;
			__u32 attach_type;
		} cgroup;
		struct {
			__u32 netns_ino;
			__u32 attach_type;
		} netns;
	};
};

struct bpf_link_ops;

struct bpf_link {
	atomic64_t refcnt;
	u32 id;
	enum bpf_link_type type;
	const struct bpf_link_ops *ops;
	struct bpf_prog *prog;
	struct work_struct work;
};

struct bpf_link_ops {
	void (*release)(struct bpf_link *);
	void (*dealloc)(struct bpf_link *);
	int (*update_prog)(struct bpf_link *, struct bpf_prog *, struct bpf_prog *);
	void (*show_fdinfo)(const struct bpf_link *, struct seq_file *);
	int (*fill_link_info)(const struct bpf_link *, struct bpf_link_info *);
};

struct bpf_cgroup_link {
	struct bpf_link link;
	struct cgroup *cgroup;
	enum bpf_attach_type type;
};

enum {
	CSS_NO_REF = 1,
	CSS_ONLINE = 2,
	CSS_RELEASED = 4,
	CSS_VISIBLE = 8,
	CSS_DYING = 16,
};

enum {
	CGRP_NOTIFY_ON_RELEASE = 0,
	CGRP_CPUSET_CLONE_CHILDREN = 1,
	CGRP_FREEZE = 2,
	CGRP_FROZEN = 3,
};

enum {
	CGRP_ROOT_NOPREFIX = 2,
	CGRP_ROOT_XATTR = 4,
	CGRP_ROOT_NS_DELEGATE = 8,
	CGRP_ROOT_CPUSET_V2_MODE = 16,
	CGRP_ROOT_MEMORY_LOCAL_EVENTS = 32,
	CGRP_ROOT_MEMORY_RECURSIVE_PROT = 64,
};

struct cgroup_taskset {
	struct list_head src_csets;
	struct list_head dst_csets;
	int nr_tasks;
	int ssid;
	struct list_head *csets;
	struct css_set *cur_cset;
	struct task_struct *cur_task;
};

struct css_task_iter {
	struct cgroup_subsys *ss;
	unsigned int flags;
	struct list_head *cset_pos;
	struct list_head *cset_head;
	struct list_head *tcset_pos;
	struct list_head *tcset_head;
	struct list_head *task_pos;
	struct list_head *cur_tasks_head;
	struct css_set *cur_cset;
	struct css_set *cur_dcset;
	struct task_struct *cur_task;
	struct list_head iters_node;
};

struct cgroup_fs_context {
	struct kernfs_fs_context kfc;
	struct cgroup_root *root;
	struct cgroup_namespace *ns;
	unsigned int flags;
	bool cpuset_clone_children;
	bool none;
	bool all_ss;
	u16 subsys_mask;
	char *name;
	char *release_agent;
};

struct cgrp_cset_link {
	struct cgroup *cgrp;
	struct css_set *cset;
	struct list_head cset_link;
	struct list_head cgrp_link;
};

struct cgroup_mgctx {
	struct list_head preloaded_src_csets;
	struct list_head preloaded_dst_csets;
	struct cgroup_taskset tset;
	u16 ss_mask;
};

struct trace_event_raw_cgroup_root {
	struct trace_entry ent;
	int root;
	u16 ss_mask;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_cgroup {
	struct trace_entry ent;
	int root;
	int id;
	int level;
	u32 __data_loc_path;
	char __data[0];
};

struct trace_event_raw_cgroup_migrate {
	struct trace_entry ent;
	int dst_root;
	int dst_id;
	int dst_level;
	int pid;
	u32 __data_loc_dst_path;
	u32 __data_loc_comm;
	char __data[0];
};

struct trace_event_raw_cgroup_event {
	struct trace_entry ent;
	int root;
	int id;
	int level;
	u32 __data_loc_path;
	int val;
	char __data[0];
};

struct trace_event_data_offsets_cgroup_root {
	u32 name;
};

struct trace_event_data_offsets_cgroup {
	u32 path;
};

struct trace_event_data_offsets_cgroup_migrate {
	u32 dst_path;
	u32 comm;
};

struct trace_event_data_offsets_cgroup_event {
	u32 path;
};

typedef void (*btf_trace_cgroup_setup_root)(void *, struct cgroup_root *);

typedef void (*btf_trace_cgroup_destroy_root)(void *, struct cgroup_root *);

typedef void (*btf_trace_cgroup_remount)(void *, struct cgroup_root *);

typedef void (*btf_trace_cgroup_mkdir)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_rmdir)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_release)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_rename)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_freeze)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_unfreeze)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_attach_task)(void *, struct cgroup *, const char *, struct task_struct *, bool);

typedef void (*btf_trace_cgroup_transfer_tasks)(void *, struct cgroup *, const char *, struct task_struct *, bool);

typedef void (*btf_trace_cgroup_notify_populated)(void *, struct cgroup *, const char *, int);

typedef void (*btf_trace_cgroup_notify_frozen)(void *, struct cgroup *, const char *, int);

enum cgroup2_param {
	Opt_nsdelegate = 0,
	Opt_memory_localevents = 1,
	Opt_memory_recursiveprot = 2,
	nr__cgroup2_params = 3,
};

struct cgroupstats {
	__u64 nr_sleeping;
	__u64 nr_running;
	__u64 nr_stopped;
	__u64 nr_uninterruptible;
	__u64 nr_io_wait;
};

enum cgroup_filetype {
	CGROUP_FILE_PROCS = 0,
	CGROUP_FILE_TASKS = 1,
};

struct cgroup_pidlist {
	struct {
		enum cgroup_filetype type;
		struct pid_namespace *ns;
	} key;
	pid_t *list;
	int length;
	struct list_head links;
	struct cgroup *owner;
	struct delayed_work destroy_dwork;
};

enum cgroup1_param {
	Opt_all = 0,
	Opt_clone_children = 1,
	Opt_cpuset_v2_mode = 2,
	Opt_name = 3,
	Opt_none = 4,
	Opt_noprefix = 5,
	Opt_release_agent = 6,
	Opt_xattr = 7,
};

enum freezer_state_flags {
	CGROUP_FREEZER_ONLINE = 1,
	CGROUP_FREEZING_SELF = 2,
	CGROUP_FREEZING_PARENT = 4,
	CGROUP_FROZEN = 8,
	CGROUP_FREEZING = 6,
};

struct freezer {
	struct cgroup_subsys_state css;
	unsigned int state;
};

struct fmeter {
	int cnt;
	int val;
	time64_t time;
	spinlock_t lock;
};

struct cpuset {
	struct cgroup_subsys_state css;
	long unsigned int flags;
	cpumask_var_t cpus_allowed;
	nodemask_t mems_allowed;
	cpumask_var_t effective_cpus;
	nodemask_t effective_mems;
	cpumask_var_t subparts_cpus;
	nodemask_t old_mems_allowed;
	struct fmeter fmeter;
	int attach_in_progress;
	int pn;
	int relax_domain_level;
	int nr_subparts_cpus;
	int partition_root_state;
	int use_parent_ecpus;
	int child_ecpus_count;
};

struct tmpmasks {
	cpumask_var_t addmask;
	cpumask_var_t delmask;
	cpumask_var_t new_cpus;
};

typedef enum {
	CS_ONLINE = 0,
	CS_CPU_EXCLUSIVE = 1,
	CS_MEM_EXCLUSIVE = 2,
	CS_MEM_HARDWALL = 3,
	CS_MEMORY_MIGRATE = 4,
	CS_SCHED_LOAD_BALANCE = 5,
	CS_SPREAD_PAGE = 6,
	CS_SPREAD_SLAB = 7,
} cpuset_flagbits_t;

enum subparts_cmd {
	partcmd_enable = 0,
	partcmd_disable = 1,
	partcmd_update = 2,
};

struct cpuset_migrate_mm_work {
	struct work_struct work;
	struct mm_struct *mm;
	nodemask_t from;
	nodemask_t to;
};

typedef enum {
	FILE_MEMORY_MIGRATE = 0,
	FILE_CPULIST = 1,
	FILE_MEMLIST = 2,
	FILE_EFFECTIVE_CPULIST = 3,
	FILE_EFFECTIVE_MEMLIST = 4,
	FILE_SUBPARTS_CPULIST = 5,
	FILE_CPU_EXCLUSIVE = 6,
	FILE_MEM_EXCLUSIVE = 7,
	FILE_MEM_HARDWALL = 8,
	FILE_SCHED_LOAD_BALANCE = 9,
	FILE_PARTITION_ROOT = 10,
	FILE_SCHED_RELAX_DOMAIN_LEVEL = 11,
	FILE_MEMORY_PRESSURE_ENABLED = 12,
	FILE_MEMORY_PRESSURE = 13,
	FILE_SPREAD_PAGE = 14,
	FILE_SPREAD_SLAB = 15,
} cpuset_filetype_t;

struct cpu_stop_done {
	atomic_t nr_todo;
	int ret;
	struct completion completion;
};

struct cpu_stopper {
	struct task_struct *thread;
	raw_spinlock_t lock;
	bool enabled;
	struct list_head works;
	struct cpu_stop_work stop_work;
};

enum multi_stop_state {
	MULTI_STOP_NONE = 0,
	MULTI_STOP_PREPARE = 1,
	MULTI_STOP_DISABLE_IRQ = 2,
	MULTI_STOP_RUN = 3,
	MULTI_STOP_EXIT = 4,
};

struct multi_stop_data {
	cpu_stop_fn_t fn;
	void *data;
	unsigned int num_threads;
	const struct cpumask *active_cpus;
	enum multi_stop_state state;
	atomic_t thread_ack;
};

typedef int __kernel_mqd_t;

typedef __kernel_mqd_t mqd_t;

enum audit_state {
	AUDIT_DISABLED = 0,
	AUDIT_BUILD_CONTEXT = 1,
	AUDIT_RECORD_CONTEXT = 2,
};

struct audit_cap_data {
	kernel_cap_t permitted;
	kernel_cap_t inheritable;
	union {
		unsigned int fE;
		kernel_cap_t effective;
	};
	kernel_cap_t ambient;
	kuid_t rootid;
};

struct audit_names {
	struct list_head list;
	struct filename *name;
	int name_len;
	bool hidden;
	long unsigned int ino;
	dev_t dev;
	umode_t mode;
	kuid_t uid;
	kgid_t gid;
	dev_t rdev;
	u32 osid;
	struct audit_cap_data fcap;
	unsigned int fcap_ver;
	unsigned char type;
	bool should_free;
};

struct mq_attr {
	__kernel_long_t mq_flags;
	__kernel_long_t mq_maxmsg;
	__kernel_long_t mq_msgsize;
	__kernel_long_t mq_curmsgs;
	__kernel_long_t __reserved[4];
};

struct audit_proctitle {
	int len;
	char *value;
};

struct audit_aux_data;

struct audit_tree_refs;

struct audit_context {
	int dummy;
	int in_syscall;
	enum audit_state state;
	enum audit_state current_state;
	unsigned int serial;
	int major;
	struct timespec64 ctime;
	long unsigned int argv[4];
	long int return_code;
	u64 prio;
	int return_valid;
	struct audit_names preallocated_names[5];
	int name_count;
	struct list_head names_list;
	char *filterkey;
	struct path pwd;
	struct audit_aux_data *aux;
	struct audit_aux_data *aux_pids;
	struct __kernel_sockaddr_storage *sockaddr;
	size_t sockaddr_len;
	pid_t pid;
	pid_t ppid;
	kuid_t uid;
	kuid_t euid;
	kuid_t suid;
	kuid_t fsuid;
	kgid_t gid;
	kgid_t egid;
	kgid_t sgid;
	kgid_t fsgid;
	long unsigned int personality;
	int arch;
	pid_t target_pid;
	kuid_t target_auid;
	kuid_t target_uid;
	unsigned int target_sessionid;
	u32 target_sid;
	char target_comm[16];
	struct audit_tree_refs *trees;
	struct audit_tree_refs *first_trees;
	struct list_head killed_trees;
	int tree_count;
	int type;
	union {
		struct {
			int nargs;
			long int args[6];
		} socketcall;
		struct {
			kuid_t uid;
			kgid_t gid;
			umode_t mode;
			u32 osid;
			int has_perm;
			uid_t perm_uid;
			gid_t perm_gid;
			umode_t perm_mode;
			long unsigned int qbytes;
		} ipc;
		struct {
			mqd_t mqdes;
			struct mq_attr mqstat;
		} mq_getsetattr;
		struct {
			mqd_t mqdes;
			int sigev_signo;
		} mq_notify;
		struct {
			mqd_t mqdes;
			size_t msg_len;
			unsigned int msg_prio;
			struct timespec64 abs_timeout;
		} mq_sendrecv;
		struct {
			int oflag;
			umode_t mode;
			struct mq_attr attr;
		} mq_open;
		struct {
			pid_t pid;
			struct audit_cap_data cap;
		} capset;
		struct {
			int fd;
			int flags;
		} mmap;
		struct {
			int argc;
		} execve;
		struct {
			char *name;
		} module;
	};
	int fds[2];
	struct audit_proctitle proctitle;
};

enum audit_nlgrps {
	AUDIT_NLGRP_NONE = 0,
	AUDIT_NLGRP_READLOG = 1,
	__AUDIT_NLGRP_MAX = 2,
};

struct audit_status {
	__u32 mask;
	__u32 enabled;
	__u32 failure;
	__u32 pid;
	__u32 rate_limit;
	__u32 backlog_limit;
	__u32 lost;
	__u32 backlog;
	union {
		__u32 version;
		__u32 feature_bitmap;
	};
	__u32 backlog_wait_time;
};

struct audit_features {
	__u32 vers;
	__u32 mask;
	__u32 features;
	__u32 lock;
};

struct audit_tty_status {
	__u32 enabled;
	__u32 log_passwd;
};

struct audit_sig_info {
	uid_t uid;
	pid_t pid;
	char ctx[0];
};

struct net_generic {
	union {
		struct {
			unsigned int len;
			struct callback_head rcu;
		} s;
		void *ptr[0];
	};
};

struct scm_creds {
	u32 pid;
	kuid_t uid;
	kgid_t gid;
};

struct netlink_skb_parms {
	struct scm_creds creds;
	__u32 portid;
	__u32 dst_group;
	__u32 flags;
	struct sock *sk;
	bool nsid_is_set;
	int nsid;
};

struct netlink_kernel_cfg {
	unsigned int groups;
	unsigned int flags;
	void (*input)(struct sk_buff *);
	struct mutex *cb_mutex;
	int (*bind)(struct net *, int);
	void (*unbind)(struct net *, int);
	bool (*compare)(struct net *, struct sock *);
};

struct audit_netlink_list {
	__u32 portid;
	struct net *net;
	struct sk_buff_head q;
};

struct audit_net {
	struct sock *sk;
};

struct auditd_connection {
	struct pid *pid;
	u32 portid;
	struct net *net;
	struct callback_head rcu;
};

struct audit_ctl_mutex {
	struct mutex lock;
	void *owner;
};

struct audit_buffer {
	struct sk_buff *skb;
	struct audit_context *ctx;
	gfp_t gfp_mask;
};

struct audit_reply {
	__u32 portid;
	struct net *net;
	struct sk_buff *skb;
};

enum {
	Audit_equal = 0,
	Audit_not_equal = 1,
	Audit_bitmask = 2,
	Audit_bittest = 3,
	Audit_lt = 4,
	Audit_gt = 5,
	Audit_le = 6,
	Audit_ge = 7,
	Audit_bad = 8,
};

struct audit_rule_data {
	__u32 flags;
	__u32 action;
	__u32 field_count;
	__u32 mask[64];
	__u32 fields[64];
	__u32 values[64];
	__u32 fieldflags[64];
	__u32 buflen;
	char buf[0];
};

struct audit_field;

struct audit_watch;

struct audit_tree;

struct audit_fsnotify_mark;

struct audit_krule {
	u32 pflags;
	u32 flags;
	u32 listnr;
	u32 action;
	u32 mask[64];
	u32 buflen;
	u32 field_count;
	char *filterkey;
	struct audit_field *fields;
	struct audit_field *arch_f;
	struct audit_field *inode_f;
	struct audit_watch *watch;
	struct audit_tree *tree;
	struct audit_fsnotify_mark *exe;
	struct list_head rlist;
	struct list_head list;
	u64 prio;
};

struct audit_field {
	u32 type;
	union {
		u32 val;
		kuid_t uid;
		kgid_t gid;
		struct {
			char *lsm_str;
			void *lsm_rule;
		};
	};
	u32 op;
};

struct audit_entry {
	struct list_head list;
	struct callback_head rcu;
	struct audit_krule rule;
};

struct audit_buffer___2;

typedef int __kernel_key_t;

typedef __kernel_key_t key_t;

struct cpu_vfs_cap_data {
	__u32 magic_etc;
	kernel_cap_t permitted;
	kernel_cap_t inheritable;
	kuid_t rootid;
};

struct kern_ipc_perm {
	spinlock_t lock;
	bool deleted;
	int id;
	key_t key;
	kuid_t uid;
	kgid_t gid;
	kuid_t cuid;
	kgid_t cgid;
	umode_t mode;
	long unsigned int seq;
	void *security;
	struct rhash_head khtnode;
	struct callback_head rcu;
	refcount_t refcount;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

typedef struct fsnotify_mark_connector *fsnotify_connp_t;

struct fsnotify_mark_connector {
	spinlock_t lock;
	short unsigned int type;
	short unsigned int flags;
	__kernel_fsid_t fsid;
	union {
		fsnotify_connp_t *obj;
		struct fsnotify_mark_connector *destroy_next;
	};
	struct hlist_head list;
};

enum audit_nfcfgop {
	AUDIT_XT_OP_REGISTER = 0,
	AUDIT_XT_OP_REPLACE = 1,
	AUDIT_XT_OP_UNREGISTER = 2,
};

enum fsnotify_obj_type {
	FSNOTIFY_OBJ_TYPE_INODE = 0,
	FSNOTIFY_OBJ_TYPE_VFSMOUNT = 1,
	FSNOTIFY_OBJ_TYPE_SB = 2,
	FSNOTIFY_OBJ_TYPE_COUNT = 3,
	FSNOTIFY_OBJ_TYPE_DETACHED = 3,
};

struct audit_aux_data {
	struct audit_aux_data *next;
	int type;
};

struct audit_chunk;

struct audit_tree_refs {
	struct audit_tree_refs *next;
	struct audit_chunk *c[31];
};

struct audit_aux_data_pids {
	struct audit_aux_data d;
	pid_t target_pid[16];
	kuid_t target_auid[16];
	kuid_t target_uid[16];
	unsigned int target_sessionid[16];
	u32 target_sid[16];
	char target_comm[256];
	int pid_count;
};

struct audit_aux_data_bprm_fcaps {
	struct audit_aux_data d;
	struct audit_cap_data fcap;
	unsigned int fcap_ver;
	struct audit_cap_data old_pcap;
	struct audit_cap_data new_pcap;
};

struct audit_nfcfgop_tab {
	enum audit_nfcfgop op;
	const char *s;
};

struct audit_parent;

struct audit_watch {
	refcount_t count;
	dev_t dev;
	char *path;
	long unsigned int ino;
	struct audit_parent *parent;
	struct list_head wlist;
	struct list_head rules;
};

struct fsnotify_group;

struct fsnotify_iter_info;

struct fsnotify_mark;

struct fsnotify_event;

struct fsnotify_ops {
	int (*handle_event)(struct fsnotify_group *, struct inode *, u32, const void *, int, const struct qstr *, u32, struct fsnotify_iter_info *);
	void (*free_group_priv)(struct fsnotify_group *);
	void (*freeing_mark)(struct fsnotify_mark *, struct fsnotify_group *);
	void (*free_event)(struct fsnotify_event *);
	void (*free_mark)(struct fsnotify_mark *);
};

struct inotify_group_private_data {
	spinlock_t idr_lock;
	struct idr idr;
	struct ucounts *ucounts;
};

struct fsnotify_group {
	const struct fsnotify_ops *ops;
	refcount_t refcnt;
	spinlock_t notification_lock;
	struct list_head notification_list;
	wait_queue_head_t notification_waitq;
	unsigned int q_len;
	unsigned int max_events;
	unsigned int priority;
	bool shutdown;
	struct mutex mark_mutex;
	atomic_t num_marks;
	atomic_t user_waits;
	struct list_head marks_list;
	struct fasync_struct *fsn_fa;
	struct fsnotify_event *overflow_event;
	struct mem_cgroup *memcg;
	union {
		void *private;
		struct inotify_group_private_data inotify_data;
	};
};

struct fsnotify_iter_info {
	struct fsnotify_mark *marks[3];
	unsigned int report_mask;
	int srcu_idx;
};

struct fsnotify_mark {
	__u32 mask;
	refcount_t refcnt;
	struct fsnotify_group *group;
	struct list_head g_list;
	spinlock_t lock;
	struct hlist_node obj_list;
	struct fsnotify_mark_connector *connector;
	__u32 ignored_mask;
	unsigned int flags;
};

struct fsnotify_event {
	struct list_head list;
	long unsigned int objectid;
};

enum fsnotify_data_type {
	FSNOTIFY_EVENT_NONE = 0,
	FSNOTIFY_EVENT_PATH = 1,
	FSNOTIFY_EVENT_INODE = 2,
};

struct audit_parent {
	struct list_head watches;
	struct fsnotify_mark mark;
};

struct audit_fsnotify_mark {
	dev_t dev;
	long unsigned int ino;
	char *path;
	struct fsnotify_mark mark;
	struct audit_krule *rule;
};

struct audit_chunk___2;

struct audit_tree {
	refcount_t count;
	int goner;
	struct audit_chunk___2 *root;
	struct list_head chunks;
	struct list_head rules;
	struct list_head list;
	struct list_head same_root;
	struct callback_head head;
	char pathname[0];
};

struct node___2 {
	struct list_head list;
	struct audit_tree *owner;
	unsigned int index;
};

struct audit_chunk___2 {
	struct list_head hash;
	long unsigned int key;
	struct fsnotify_mark *mark;
	struct list_head trees;
	int count;
	atomic_long_t refs;
	struct callback_head head;
	struct node___2 owners[0];
};

struct audit_tree_mark {
	struct fsnotify_mark mark;
	struct audit_chunk___2 *chunk;
};

enum {
	HASH_SIZE = 128,
};

struct kprobe_blacklist_entry {
	struct list_head list;
	long unsigned int start_addr;
	long unsigned int end_addr;
};

struct kprobe_insn_page {
	struct list_head list;
	kprobe_opcode_t *insns;
	struct kprobe_insn_cache *cache;
	int nused;
	int ngarbage;
	char slot_used[0];
};

enum kprobe_slot_state {
	SLOT_CLEAN = 0,
	SLOT_DIRTY = 1,
	SLOT_USED = 2,
};

struct seccomp_notif_sizes {
	__u16 seccomp_notif;
	__u16 seccomp_notif_resp;
	__u16 seccomp_data;
};

struct seccomp_notif {
	__u64 id;
	__u32 pid;
	__u32 flags;
	struct seccomp_data data;
};

struct seccomp_notif_resp {
	__u64 id;
	__s64 val;
	__s32 error;
	__u32 flags;
};

struct notification;

struct seccomp_filter {
	refcount_t usage;
	bool log;
	struct seccomp_filter *prev;
	struct bpf_prog *prog;
	struct notification *notif;
	struct mutex notify_lock;
};

struct ctl_path {
	const char *procname;
};

struct sock_fprog {
	short unsigned int len;
	struct sock_filter *filter;
};

struct compat_sock_fprog {
	u16 len;
	compat_uptr_t filter;
};

enum notify_state {
	SECCOMP_NOTIFY_INIT = 0,
	SECCOMP_NOTIFY_SENT = 1,
	SECCOMP_NOTIFY_REPLIED = 2,
};

struct seccomp_knotif {
	struct task_struct *task;
	u64 id;
	const struct seccomp_data *data;
	enum notify_state state;
	int error;
	long int val;
	u32 flags;
	struct completion ready;
	struct list_head list;
};

struct notification {
	struct semaphore request;
	u64 next_id;
	struct list_head notifications;
	wait_queue_head_t wqh;
};

struct seccomp_log_name {
	u32 log;
	const char *name;
};

struct rchan;

struct rchan_buf {
	void *start;
	void *data;
	size_t offset;
	size_t subbufs_produced;
	size_t subbufs_consumed;
	struct rchan *chan;
	wait_queue_head_t read_wait;
	struct irq_work wakeup_work;
	struct dentry *dentry;
	struct kref kref;
	struct page **page_array;
	unsigned int page_count;
	unsigned int finalized;
	size_t *padding;
	size_t prev_padding;
	size_t bytes_consumed;
	size_t early_bytes;
	unsigned int cpu;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
};

struct rchan_callbacks;

struct rchan {
	u32 version;
	size_t subbuf_size;
	size_t n_subbufs;
	size_t alloc_size;
	struct rchan_callbacks *cb;
	struct kref kref;
	void *private_data;
	size_t last_toobig;
	struct rchan_buf **buf;
	int is_global;
	struct list_head list;
	struct dentry *parent;
	int has_base_filename;
	char base_filename[255];
};

struct rchan_callbacks {
	int (*subbuf_start)(struct rchan_buf *, void *, void *, size_t);
	void (*buf_mapped)(struct rchan_buf *, struct file *);
	void (*buf_unmapped)(struct rchan_buf *, struct file *);
	struct dentry * (*create_buf_file)(const char *, struct dentry *, umode_t, struct rchan_buf *, int *);
	int (*remove_buf_file)(struct dentry *);
};

struct partial_page {
	unsigned int offset;
	unsigned int len;
	long unsigned int private;
};

struct splice_pipe_desc {
	struct page **pages;
	struct partial_page *partial;
	int nr_pages;
	unsigned int nr_pages_max;
	const struct pipe_buf_operations *ops;
	void (*spd_release)(struct splice_pipe_desc *, unsigned int);
};

struct rchan_percpu_buf_dispatcher {
	struct rchan_buf *buf;
	struct dentry *dentry;
};

enum {
	TASKSTATS_TYPE_UNSPEC = 0,
	TASKSTATS_TYPE_PID = 1,
	TASKSTATS_TYPE_TGID = 2,
	TASKSTATS_TYPE_STATS = 3,
	TASKSTATS_TYPE_AGGR_PID = 4,
	TASKSTATS_TYPE_AGGR_TGID = 5,
	TASKSTATS_TYPE_NULL = 6,
	__TASKSTATS_TYPE_MAX = 7,
};

enum {
	TASKSTATS_CMD_ATTR_UNSPEC = 0,
	TASKSTATS_CMD_ATTR_PID = 1,
	TASKSTATS_CMD_ATTR_TGID = 2,
	TASKSTATS_CMD_ATTR_REGISTER_CPUMASK = 3,
	TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK = 4,
	__TASKSTATS_CMD_ATTR_MAX = 5,
};

enum {
	CGROUPSTATS_CMD_UNSPEC = 3,
	CGROUPSTATS_CMD_GET = 4,
	CGROUPSTATS_CMD_NEW = 5,
	__CGROUPSTATS_CMD_MAX = 6,
};

enum {
	CGROUPSTATS_TYPE_UNSPEC = 0,
	CGROUPSTATS_TYPE_CGROUP_STATS = 1,
	__CGROUPSTATS_TYPE_MAX = 2,
};

enum {
	CGROUPSTATS_CMD_ATTR_UNSPEC = 0,
	CGROUPSTATS_CMD_ATTR_FD = 1,
	__CGROUPSTATS_CMD_ATTR_MAX = 2,
};

struct genlmsghdr {
	__u8 cmd;
	__u8 version;
	__u16 reserved;
};

enum {
	NLA_UNSPEC = 0,
	NLA_U8 = 1,
	NLA_U16 = 2,
	NLA_U32 = 3,
	NLA_U64 = 4,
	NLA_STRING = 5,
	NLA_FLAG = 6,
	NLA_MSECS = 7,
	NLA_NESTED = 8,
	NLA_NESTED_ARRAY = 9,
	NLA_NUL_STRING = 10,
	NLA_BINARY = 11,
	NLA_S8 = 12,
	NLA_S16 = 13,
	NLA_S32 = 14,
	NLA_S64 = 15,
	NLA_BITFIELD32 = 16,
	NLA_REJECT = 17,
	NLA_EXACT_LEN = 18,
	NLA_MIN_LEN = 19,
	__NLA_TYPE_MAX = 20,
};

enum netlink_validation {
	NL_VALIDATE_LIBERAL = 0,
	NL_VALIDATE_TRAILING = 1,
	NL_VALIDATE_MAXTYPE = 2,
	NL_VALIDATE_UNSPEC = 4,
	NL_VALIDATE_STRICT_ATTRS = 8,
	NL_VALIDATE_NESTED = 16,
};

struct genl_multicast_group {
	char name[16];
};

struct genl_ops;

struct genl_info;

struct genl_family {
	int id;
	unsigned int hdrsize;
	char name[16];
	unsigned int version;
	unsigned int maxattr;
	bool netnsok;
	bool parallel_ops;
	const struct nla_policy *policy;
	int (*pre_doit)(const struct genl_ops *, struct sk_buff *, struct genl_info *);
	void (*post_doit)(const struct genl_ops *, struct sk_buff *, struct genl_info *);
	const struct genl_ops *ops;
	const struct genl_multicast_group *mcgrps;
	unsigned int n_ops;
	unsigned int n_mcgrps;
	unsigned int mcgrp_offset;
	struct module *module;
};

struct genl_ops {
	int (*doit)(struct sk_buff *, struct genl_info *);
	int (*start)(struct netlink_callback *);
	int (*dumpit)(struct sk_buff *, struct netlink_callback *);
	int (*done)(struct netlink_callback *);
	u8 cmd;
	u8 internal_flags;
	u8 flags;
	u8 validate;
};

struct genl_info {
	u32 snd_seq;
	u32 snd_portid;
	struct nlmsghdr *nlhdr;
	struct genlmsghdr *genlhdr;
	void *userhdr;
	struct nlattr **attrs;
	possible_net_t _net;
	void *user_ptr[2];
	struct netlink_ext_ack *extack;
};

enum genl_validate_flags {
	GENL_DONT_VALIDATE_STRICT = 1,
	GENL_DONT_VALIDATE_DUMP = 2,
	GENL_DONT_VALIDATE_DUMP_STRICT = 4,
};

struct listener {
	struct list_head list;
	pid_t pid;
	char valid;
};

struct listener_list {
	struct rw_semaphore sem;
	struct list_head list;
};

enum actions {
	REGISTER = 0,
	DEREGISTER = 1,
	CPU_DONT_CARE = 2,
};

struct tp_module {
	struct list_head list;
	struct module *mod;
};

struct tp_probes {
	struct callback_head rcu;
	struct tracepoint_func probes[0];
};

enum ring_buffer_type {
	RINGBUF_TYPE_DATA_TYPE_LEN_MAX = 28,
	RINGBUF_TYPE_PADDING = 29,
	RINGBUF_TYPE_TIME_EXTEND = 30,
	RINGBUF_TYPE_TIME_STAMP = 31,
};

enum ring_buffer_flags {
	RB_FL_OVERWRITE = 1,
};

struct ring_buffer_per_cpu;

struct buffer_page;

struct ring_buffer_iter {
	struct ring_buffer_per_cpu *cpu_buffer;
	long unsigned int head;
	long unsigned int next_event;
	struct buffer_page *head_page;
	struct buffer_page *cache_reader_page;
	long unsigned int cache_read;
	u64 read_stamp;
	u64 page_stamp;
	struct ring_buffer_event *event;
	int missed_events;
};

struct rb_irq_work {
	struct irq_work work;
	wait_queue_head_t waiters;
	wait_queue_head_t full_waiters;
	bool waiters_pending;
	bool full_waiters_pending;
	bool wakeup_full;
};

struct trace_buffer___2 {
	unsigned int flags;
	int cpus;
	atomic_t record_disabled;
	cpumask_var_t cpumask;
	struct lock_class_key *reader_lock_key;
	struct mutex mutex;
	struct ring_buffer_per_cpu **buffers;
	struct hlist_node node;
	u64 (*clock)();
	struct rb_irq_work irq_work;
	bool time_stamp_abs;
};

enum {
	RB_LEN_TIME_EXTEND = 8,
	RB_LEN_TIME_STAMP = 8,
};

struct buffer_data_page {
	u64 time_stamp;
	local_t commit;
	unsigned char data[0];
};

struct buffer_page {
	struct list_head list;
	local_t write;
	unsigned int read;
	local_t entries;
	long unsigned int real_end;
	struct buffer_data_page *page;
};

struct rb_event_info {
	u64 ts;
	u64 delta;
	long unsigned int length;
	struct buffer_page *tail_page;
	int add_timestamp;
};

enum {
	RB_CTX_NMI = 0,
	RB_CTX_IRQ = 1,
	RB_CTX_SOFTIRQ = 2,
	RB_CTX_NORMAL = 3,
	RB_CTX_MAX = 4,
};

struct ring_buffer_per_cpu {
	int cpu;
	atomic_t record_disabled;
	atomic_t resize_disabled;
	struct trace_buffer___2 *buffer;
	raw_spinlock_t reader_lock;
	arch_spinlock_t lock;
	struct lock_class_key lock_key;
	struct buffer_data_page *free_page;
	long unsigned int nr_pages;
	unsigned int current_context;
	struct list_head *pages;
	struct buffer_page *head_page;
	struct buffer_page *tail_page;
	struct buffer_page *commit_page;
	struct buffer_page *reader_page;
	long unsigned int lost_events;
	long unsigned int last_overrun;
	long unsigned int nest;
	local_t entries_bytes;
	local_t entries;
	local_t overrun;
	local_t commit_overrun;
	local_t dropped_events;
	local_t committing;
	local_t commits;
	local_t pages_touched;
	local_t pages_read;
	long int last_pages_touch;
	size_t shortest_full;
	long unsigned int read;
	long unsigned int read_bytes;
	u64 write_stamp;
	u64 read_stamp;
	long int nr_pages_to_update;
	struct list_head new_pages;
	struct work_struct update_pages_work;
	struct completion update_done;
	struct rb_irq_work irq_work;
};

struct trace_export {
	struct trace_export *next;
	void (*write)(struct trace_export *, const void *, unsigned int);
};

struct prog_entry;

struct event_filter {
	struct prog_entry *prog;
	char *filter_string;
};

struct trace_array_cpu;

struct array_buffer {
	struct trace_array *tr;
	struct trace_buffer *buffer;
	struct trace_array_cpu *data;
	u64 time_start;
	int cpu;
};

struct trace_pid_list;

struct trace_options;

struct trace_array {
	struct list_head list;
	char *name;
	struct array_buffer array_buffer;
	struct trace_pid_list *filtered_pids;
	struct trace_pid_list *filtered_no_pids;
	arch_spinlock_t max_lock;
	int buffer_disabled;
	int stop_count;
	int clock_id;
	int nr_topts;
	bool clear_trace;
	int buffer_percent;
	unsigned int n_err_log_entries;
	struct tracer *current_trace;
	unsigned int trace_flags;
	unsigned char trace_flags_index[32];
	unsigned int flags;
	raw_spinlock_t start_lock;
	struct list_head err_log;
	struct dentry *dir;
	struct dentry *options;
	struct dentry *percpu_dir;
	struct dentry *event_dir;
	struct trace_options *topts;
	struct list_head systems;
	struct list_head events;
	struct trace_event_file *trace_marker_file;
	cpumask_var_t tracing_cpumask;
	int ref;
	int time_stamp_abs_ref;
	struct list_head hist_vars;
};

struct tracer_flags;

struct tracer {
	const char *name;
	int (*init)(struct trace_array *);
	void (*reset)(struct trace_array *);
	void (*start)(struct trace_array *);
	void (*stop)(struct trace_array *);
	int (*update_thresh)(struct trace_array *);
	void (*open)(struct trace_iterator *);
	void (*pipe_open)(struct trace_iterator *);
	void (*close)(struct trace_iterator *);
	void (*pipe_close)(struct trace_iterator *);
	ssize_t (*read)(struct trace_iterator *, struct file *, char *, size_t, loff_t *);
	ssize_t (*splice_read)(struct trace_iterator *, struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	void (*print_header)(struct seq_file *);
	enum print_line_t (*print_line)(struct trace_iterator *);
	int (*set_flag)(struct trace_array *, u32, u32, int);
	int (*flag_changed)(struct trace_array *, u32, int);
	struct tracer *next;
	struct tracer_flags *flags;
	int enabled;
	int ref;
	bool print_max;
	bool allow_instances;
	bool noboot;
};

enum trace_iter_flags {
	TRACE_FILE_LAT_FMT = 1,
	TRACE_FILE_ANNOTATE = 2,
	TRACE_FILE_TIME_IN_NS = 4,
};

struct event_subsystem;

struct trace_subsystem_dir {
	struct list_head list;
	struct event_subsystem *subsystem;
	struct trace_array *tr;
	struct dentry *entry;
	int ref_count;
	int nr_events;
};

enum event_trigger_type {
	ETT_NONE = 0,
	ETT_TRACE_ONOFF = 1,
	ETT_SNAPSHOT = 2,
	ETT_STACKTRACE = 4,
	ETT_EVENT_ENABLE = 8,
	ETT_EVENT_HIST = 16,
	ETT_HIST_ENABLE = 32,
};

enum trace_type {
	__TRACE_FIRST_TYPE = 0,
	TRACE_FN = 1,
	TRACE_CTX = 2,
	TRACE_WAKE = 3,
	TRACE_STACK = 4,
	TRACE_PRINT = 5,
	TRACE_BPRINT = 6,
	TRACE_MMIO_RW = 7,
	TRACE_MMIO_MAP = 8,
	TRACE_BRANCH = 9,
	TRACE_GRAPH_RET = 10,
	TRACE_GRAPH_ENT = 11,
	TRACE_USER_STACK = 12,
	TRACE_BLK = 13,
	TRACE_BPUTS = 14,
	TRACE_HWLAT = 15,
	TRACE_RAW_DATA = 16,
	__TRACE_LAST_TYPE = 17,
};

struct ftrace_entry {
	struct trace_entry ent;
	long unsigned int ip;
	long unsigned int parent_ip;
};

struct stack_entry {
	struct trace_entry ent;
	int size;
	long unsigned int caller[8];
};

struct userstack_entry {
	struct trace_entry ent;
	unsigned int tgid;
	long unsigned int caller[8];
};

struct bprint_entry {
	struct trace_entry ent;
	long unsigned int ip;
	const char *fmt;
	u32 buf[0];
};

struct print_entry {
	struct trace_entry ent;
	long unsigned int ip;
	char buf[0];
};

struct raw_data_entry {
	struct trace_entry ent;
	unsigned int id;
	char buf[0];
};

struct bputs_entry {
	struct trace_entry ent;
	long unsigned int ip;
	const char *str;
};

enum trace_flag_type {
	TRACE_FLAG_IRQS_OFF = 1,
	TRACE_FLAG_IRQS_NOSUPPORT = 2,
	TRACE_FLAG_NEED_RESCHED = 4,
	TRACE_FLAG_HARDIRQ = 8,
	TRACE_FLAG_SOFTIRQ = 16,
	TRACE_FLAG_PREEMPT_RESCHED = 32,
	TRACE_FLAG_NMI = 64,
};

struct trace_array_cpu {
	atomic_t disabled;
	void *buffer_page;
	long unsigned int entries;
	long unsigned int saved_latency;
	long unsigned int critical_start;
	long unsigned int critical_end;
	long unsigned int critical_sequence;
	long unsigned int nice;
	long unsigned int policy;
	long unsigned int rt_priority;
	long unsigned int skipped_entries;
	u64 preempt_timestamp;
	pid_t pid;
	kuid_t uid;
	char comm[16];
	bool ignore_pid;
};

struct trace_option_dentry;

struct trace_options {
	struct tracer *tracer;
	struct trace_option_dentry *topts;
};

struct tracer_opt;

struct trace_option_dentry {
	struct tracer_opt *opt;
	struct tracer_flags *flags;
	struct trace_array *tr;
	struct dentry *entry;
};

struct trace_pid_list {
	int pid_max;
	long unsigned int *pids;
};

typedef bool (*cond_update_fn_t)(struct trace_array *, void *);

enum {
	TRACE_ARRAY_FL_GLOBAL = 1,
};

struct tracer_opt {
	const char *name;
	u32 bit;
};

struct tracer_flags {
	u32 val;
	struct tracer_opt *opts;
	struct tracer *trace;
};

struct trace_parser {
	bool cont;
	char *buffer;
	unsigned int idx;
	unsigned int size;
};

enum trace_iterator_bits {
	TRACE_ITER_PRINT_PARENT_BIT = 0,
	TRACE_ITER_SYM_OFFSET_BIT = 1,
	TRACE_ITER_SYM_ADDR_BIT = 2,
	TRACE_ITER_VERBOSE_BIT = 3,
	TRACE_ITER_RAW_BIT = 4,
	TRACE_ITER_HEX_BIT = 5,
	TRACE_ITER_BIN_BIT = 6,
	TRACE_ITER_BLOCK_BIT = 7,
	TRACE_ITER_PRINTK_BIT = 8,
	TRACE_ITER_ANNOTATE_BIT = 9,
	TRACE_ITER_USERSTACKTRACE_BIT = 10,
	TRACE_ITER_SYM_USEROBJ_BIT = 11,
	TRACE_ITER_PRINTK_MSGONLY_BIT = 12,
	TRACE_ITER_CONTEXT_INFO_BIT = 13,
	TRACE_ITER_LATENCY_FMT_BIT = 14,
	TRACE_ITER_RECORD_CMD_BIT = 15,
	TRACE_ITER_RECORD_TGID_BIT = 16,
	TRACE_ITER_OVERWRITE_BIT = 17,
	TRACE_ITER_STOP_ON_FREE_BIT = 18,
	TRACE_ITER_IRQ_INFO_BIT = 19,
	TRACE_ITER_MARKERS_BIT = 20,
	TRACE_ITER_EVENT_FORK_BIT = 21,
	TRACE_ITER_PAUSE_ON_TRACE_BIT = 22,
	TRACE_ITER_STACKTRACE_BIT = 23,
	TRACE_ITER_LAST_BIT = 24,
};

enum trace_iterator_flags {
	TRACE_ITER_PRINT_PARENT = 1,
	TRACE_ITER_SYM_OFFSET = 2,
	TRACE_ITER_SYM_ADDR = 4,
	TRACE_ITER_VERBOSE = 8,
	TRACE_ITER_RAW = 16,
	TRACE_ITER_HEX = 32,
	TRACE_ITER_BIN = 64,
	TRACE_ITER_BLOCK = 128,
	TRACE_ITER_PRINTK = 256,
	TRACE_ITER_ANNOTATE = 512,
	TRACE_ITER_USERSTACKTRACE = 1024,
	TRACE_ITER_SYM_USEROBJ = 2048,
	TRACE_ITER_PRINTK_MSGONLY = 4096,
	TRACE_ITER_CONTEXT_INFO = 8192,
	TRACE_ITER_LATENCY_FMT = 16384,
	TRACE_ITER_RECORD_CMD = 32768,
	TRACE_ITER_RECORD_TGID = 65536,
	TRACE_ITER_OVERWRITE = 131072,
	TRACE_ITER_STOP_ON_FREE = 262144,
	TRACE_ITER_IRQ_INFO = 524288,
	TRACE_ITER_MARKERS = 1048576,
	TRACE_ITER_EVENT_FORK = 2097152,
	TRACE_ITER_PAUSE_ON_TRACE = 4194304,
	TRACE_ITER_STACKTRACE = 8388608,
};

struct event_subsystem {
	struct list_head list;
	const char *name;
	struct event_filter *filter;
	int ref_count;
};

struct saved_cmdlines_buffer {
	unsigned int map_pid_to_cmdline[32769];
	unsigned int *map_cmdline_to_pid;
	unsigned int cmdline_num;
	int cmdline_idx;
	char *saved_cmdlines;
};

struct ftrace_stack {
	long unsigned int calls[1024];
};

struct ftrace_stacks {
	struct ftrace_stack stacks[4];
};

struct trace_buffer_struct {
	int nesting;
	char buffer[4096];
};

struct ftrace_buffer_info {
	struct trace_iterator iter;
	void *spare;
	unsigned int spare_cpu;
	unsigned int read;
};

struct err_info {
	const char **errs;
	u8 type;
	u8 pos;
	u64 ts;
};

struct tracing_log_err {
	struct list_head list;
	struct err_info info;
	char loc[128];
	char cmd[256];
};

struct buffer_ref {
	struct trace_buffer *buffer;
	void *page;
	int cpu;
	refcount_t refcount;
};

struct ctx_switch_entry {
	struct trace_entry ent;
	unsigned int prev_pid;
	unsigned int next_pid;
	unsigned int next_cpu;
	unsigned char prev_prio;
	unsigned char prev_state;
	unsigned char next_prio;
	unsigned char next_state;
};

struct hwlat_entry {
	struct trace_entry ent;
	u64 duration;
	u64 outer_duration;
	u64 nmi_total_ts;
	struct timespec64 timestamp;
	unsigned int nmi_count;
	unsigned int seqnum;
	unsigned int count;
};

struct trace_mark {
	long long unsigned int val;
	char sym;
};

struct tracer_stat {
	const char *name;
	void * (*stat_start)(struct tracer_stat *);
	void * (*stat_next)(void *, int);
	cmp_func_t stat_cmp;
	int (*stat_show)(struct seq_file *, void *);
	void (*stat_release)(void *);
	int (*stat_headers)(struct seq_file *);
};

struct stat_node {
	struct rb_node node;
	void *stat;
};

struct stat_session {
	struct list_head session_list;
	struct tracer_stat *ts;
	struct rb_root stat_root;
	struct mutex stat_mutex;
	struct dentry *file;
};

struct trace_bprintk_fmt {
	struct list_head list;
	const char *fmt;
};

enum {
	TRACE_NOP_OPT_ACCEPT = 1,
	TRACE_NOP_OPT_REFUSE = 2,
};

typedef __u32 blk_mq_req_flags_t;

struct disk_stats {
	u64 nsecs[4];
	long unsigned int sectors[4];
	long unsigned int ios[4];
	long unsigned int merges[4];
	long unsigned int io_ticks;
	local_t in_flight[2];
};

struct blk_mq_ctxs;

struct blk_mq_ctx {
	struct {
		spinlock_t lock;
		struct list_head rq_lists[3];
		long: 64;
	};
	unsigned int cpu;
	short unsigned int index_hw[3];
	struct blk_mq_hw_ctx *hctxs[3];
	long unsigned int rq_dispatched[2];
	long unsigned int rq_merged;
	long unsigned int rq_completed[2];
	struct request_queue *queue;
	struct blk_mq_ctxs *ctxs;
	struct kobject kobj;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct sbitmap_word;

struct sbitmap {
	unsigned int depth;
	unsigned int shift;
	unsigned int map_nr;
	struct sbitmap_word *map;
};

struct blk_mq_tags;

struct blk_mq_hw_ctx {
	struct {
		spinlock_t lock;
		struct list_head dispatch;
		long unsigned int state;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	};
	struct delayed_work run_work;
	cpumask_var_t cpumask;
	int next_cpu;
	int next_cpu_batch;
	long unsigned int flags;
	void *sched_data;
	struct request_queue *queue;
	struct blk_flush_queue *fq;
	void *driver_data;
	struct sbitmap ctx_map;
	struct blk_mq_ctx *dispatch_from;
	unsigned int dispatch_busy;
	short unsigned int type;
	short unsigned int nr_ctx;
	struct blk_mq_ctx **ctxs;
	spinlock_t dispatch_wait_lock;
	wait_queue_entry_t dispatch_wait;
	atomic_t wait_index;
	struct blk_mq_tags *tags;
	struct blk_mq_tags *sched_tags;
	long unsigned int queued;
	long unsigned int run;
	long unsigned int dispatched[7];
	unsigned int numa_node;
	unsigned int queue_num;
	atomic_t nr_active;
	struct hlist_node cpuhp_online;
	struct hlist_node cpuhp_dead;
	struct kobject kobj;
	long unsigned int poll_considered;
	long unsigned int poll_invoked;
	long unsigned int poll_success;
	struct dentry *debugfs_dir;
	struct dentry *sched_debugfs_dir;
	struct list_head hctx_list;
	struct srcu_struct srcu[0];
	long: 64;
};

struct blk_mq_alloc_data {
	struct request_queue *q;
	blk_mq_req_flags_t flags;
	unsigned int shallow_depth;
	unsigned int cmd_flags;
	struct blk_mq_ctx *ctx;
	struct blk_mq_hw_ctx *hctx;
};

struct blk_stat_callback {
	struct list_head list;
	struct timer_list timer;
	struct blk_rq_stat *cpu_stat;
	int (*bucket_fn)(const struct request *);
	unsigned int buckets;
	struct blk_rq_stat *stat;
	void (*timer_fn)(struct blk_stat_callback *);
	void *data;
	struct callback_head rcu;
};

struct blk_trace {
	int trace_state;
	struct rchan *rchan;
	long unsigned int *sequence;
	unsigned char *msg_data;
	u16 act_mask;
	u64 start_lba;
	u64 end_lba;
	u32 pid;
	u32 dev;
	struct dentry *dir;
	struct dentry *dropped_file;
	struct dentry *msg_file;
	struct list_head running_list;
	atomic_t dropped;
};

struct blk_flush_queue {
	unsigned int flush_pending_idx: 1;
	unsigned int flush_running_idx: 1;
	blk_status_t rq_status;
	long unsigned int flush_pending_since;
	struct list_head flush_queue[2];
	struct list_head flush_data_in_flight;
	struct request *flush_rq;
	struct request *orig_rq;
	struct lock_class_key key;
	spinlock_t mq_flush_lock;
};

struct blk_mq_queue_map {
	unsigned int *mq_map;
	unsigned int nr_queues;
	unsigned int queue_offset;
};

struct blk_mq_tag_set {
	struct blk_mq_queue_map map[3];
	unsigned int nr_maps;
	const struct blk_mq_ops *ops;
	unsigned int nr_hw_queues;
	unsigned int queue_depth;
	unsigned int reserved_tags;
	unsigned int cmd_size;
	int numa_node;
	unsigned int timeout;
	unsigned int flags;
	void *driver_data;
	struct blk_mq_tags **tags;
	struct mutex tag_list_lock;
	struct list_head tag_list;
};

typedef u64 compat_u64;

enum blktrace_cat {
	BLK_TC_READ = 1,
	BLK_TC_WRITE = 2,
	BLK_TC_FLUSH = 4,
	BLK_TC_SYNC = 8,
	BLK_TC_SYNCIO = 8,
	BLK_TC_QUEUE = 16,
	BLK_TC_REQUEUE = 32,
	BLK_TC_ISSUE = 64,
	BLK_TC_COMPLETE = 128,
	BLK_TC_FS = 256,
	BLK_TC_PC = 512,
	BLK_TC_NOTIFY = 1024,
	BLK_TC_AHEAD = 2048,
	BLK_TC_META = 4096,
	BLK_TC_DISCARD = 8192,
	BLK_TC_DRV_DATA = 16384,
	BLK_TC_FUA = 32768,
	BLK_TC_END = 32768,
};

enum blktrace_act {
	__BLK_TA_QUEUE = 1,
	__BLK_TA_BACKMERGE = 2,
	__BLK_TA_FRONTMERGE = 3,
	__BLK_TA_GETRQ = 4,
	__BLK_TA_SLEEPRQ = 5,
	__BLK_TA_REQUEUE = 6,
	__BLK_TA_ISSUE = 7,
	__BLK_TA_COMPLETE = 8,
	__BLK_TA_PLUG = 9,
	__BLK_TA_UNPLUG_IO = 10,
	__BLK_TA_UNPLUG_TIMER = 11,
	__BLK_TA_INSERT = 12,
	__BLK_TA_SPLIT = 13,
	__BLK_TA_BOUNCE = 14,
	__BLK_TA_REMAP = 15,
	__BLK_TA_ABORT = 16,
	__BLK_TA_DRV_DATA = 17,
	__BLK_TA_CGROUP = 256,
};

enum blktrace_notify {
	__BLK_TN_PROCESS = 0,
	__BLK_TN_TIMESTAMP = 1,
	__BLK_TN_MESSAGE = 2,
	__BLK_TN_CGROUP = 256,
};

struct blk_io_trace {
	__u32 magic;
	__u32 sequence;
	__u64 time;
	__u64 sector;
	__u32 bytes;
	__u32 action;
	__u32 pid;
	__u32 device;
	__u32 cpu;
	__u16 error;
	__u16 pdu_len;
};

struct blk_io_trace_remap {
	__be32 device_from;
	__be32 device_to;
	__be64 sector_from;
};

enum {
	Blktrace_setup = 1,
	Blktrace_running = 2,
	Blktrace_stopped = 3,
};

struct blk_user_trace_setup {
	char name[32];
	__u16 act_mask;
	__u32 buf_size;
	__u32 buf_nr;
	__u64 start_lba;
	__u64 end_lba;
	__u32 pid;
};

struct compat_blk_user_trace_setup {
	char name[32];
	u16 act_mask;
	short: 16;
	u32 buf_size;
	u32 buf_nr;
	compat_u64 start_lba;
	compat_u64 end_lba;
	u32 pid;
} __attribute__((packed));

struct blkcg {};

struct sbitmap_word {
	long unsigned int depth;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int word;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int cleared;
	spinlock_t swap_lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct sbq_wait_state {
	atomic_t wait_cnt;
	wait_queue_head_t wait;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct sbitmap_queue {
	struct sbitmap sb;
	unsigned int *alloc_hint;
	unsigned int wake_batch;
	atomic_t wake_index;
	struct sbq_wait_state *ws;
	atomic_t ws_active;
	bool round_robin;
	unsigned int min_shallow_depth;
};

struct blk_mq_tags {
	unsigned int nr_tags;
	unsigned int nr_reserved_tags;
	atomic_t active_queues;
	struct sbitmap_queue bitmap_tags;
	struct sbitmap_queue breserved_tags;
	struct request **rqs;
	struct request **static_rqs;
	struct list_head page_list;
};

struct blk_mq_queue_data {
	struct request *rq;
	bool last;
};

struct blk_crypto_mode {
	const char *cipher_str;
	unsigned int keysize;
	unsigned int ivsize;
};

struct blk_mq_ctxs {
	struct kobject kobj;
	struct blk_mq_ctx *queue_ctx;
};

typedef void blk_log_action_t(struct trace_iterator *, const char *, bool);

enum {
	TRACE_PIDS = 1,
	TRACE_NO_PIDS = 2,
};

struct ftrace_event_field {
	struct list_head link;
	const char *name;
	const char *type;
	int filter_type;
	int offset;
	int size;
	int is_signed;
};

enum {
	FORMAT_HEADER = 1,
	FORMAT_FIELD_SEPERATOR = 2,
	FORMAT_PRINTFMT = 3,
};

typedef long unsigned int perf_trace_t[256];

struct filter_pred;

struct prog_entry {
	int target;
	int when_to_branch;
	struct filter_pred *pred;
};

typedef int (*filter_pred_fn_t)(struct filter_pred *, void *);

struct regex;

typedef int (*regex_match_func)(char *, struct regex *, int);

struct regex {
	char pattern[256];
	int len;
	int field_len;
	regex_match_func match;
};

struct filter_pred {
	filter_pred_fn_t fn;
	u64 val;
	struct regex regex;
	short unsigned int *ops;
	struct ftrace_event_field *field;
	int offset;
	int not;
	int op;
};

enum regex_type {
	MATCH_FULL = 0,
	MATCH_FRONT_ONLY = 1,
	MATCH_MIDDLE_ONLY = 2,
	MATCH_END_ONLY = 3,
	MATCH_GLOB = 4,
	MATCH_INDEX = 5,
};

enum filter_op_ids {
	OP_GLOB = 0,
	OP_NE = 1,
	OP_EQ = 2,
	OP_LE = 3,
	OP_LT = 4,
	OP_GE = 5,
	OP_GT = 6,
	OP_BAND = 7,
	OP_MAX = 8,
};

enum {
	FILT_ERR_NONE = 0,
	FILT_ERR_INVALID_OP = 1,
	FILT_ERR_TOO_MANY_OPEN = 2,
	FILT_ERR_TOO_MANY_CLOSE = 3,
	FILT_ERR_MISSING_QUOTE = 4,
	FILT_ERR_OPERAND_TOO_LONG = 5,
	FILT_ERR_EXPECT_STRING = 6,
	FILT_ERR_EXPECT_DIGIT = 7,
	FILT_ERR_ILLEGAL_FIELD_OP = 8,
	FILT_ERR_FIELD_NOT_FOUND = 9,
	FILT_ERR_ILLEGAL_INTVAL = 10,
	FILT_ERR_BAD_SUBSYS_FILTER = 11,
	FILT_ERR_TOO_MANY_PREDS = 12,
	FILT_ERR_INVALID_FILTER = 13,
	FILT_ERR_IP_FIELD_ONLY = 14,
	FILT_ERR_INVALID_VALUE = 15,
	FILT_ERR_ERRNO = 16,
	FILT_ERR_NO_FILTER = 17,
};

struct filter_parse_error {
	int lasterr;
	int lasterr_pos;
};

typedef int (*parse_pred_fn)(const char *, void *, int, struct filter_parse_error *, struct filter_pred **);

enum {
	INVERT = 1,
	PROCESS_AND = 2,
	PROCESS_OR = 4,
};

enum {
	TOO_MANY_CLOSE = 4294967295,
	TOO_MANY_OPEN = 4294967294,
	MISSING_QUOTE = 4294967293,
};

struct filter_list {
	struct list_head list;
	struct event_filter *filter;
};

struct event_trigger_ops;

struct event_command;

struct event_trigger_data {
	long unsigned int count;
	int ref;
	struct event_trigger_ops *ops;
	struct event_command *cmd_ops;
	struct event_filter *filter;
	char *filter_str;
	void *private_data;
	bool paused;
	bool paused_tmp;
	struct list_head list;
	char *name;
	struct list_head named_list;
	struct event_trigger_data *named_data;
};

struct event_trigger_ops {
	void (*func)(struct event_trigger_data *, void *, struct ring_buffer_event *);
	int (*init)(struct event_trigger_ops *, struct event_trigger_data *);
	void (*free)(struct event_trigger_ops *, struct event_trigger_data *);
	int (*print)(struct seq_file *, struct event_trigger_ops *, struct event_trigger_data *);
};

struct event_command {
	struct list_head list;
	char *name;
	enum event_trigger_type trigger_type;
	int flags;
	int (*func)(struct event_command *, struct trace_event_file *, char *, char *, char *);
	int (*reg)(char *, struct event_trigger_ops *, struct event_trigger_data *, struct trace_event_file *);
	void (*unreg)(char *, struct event_trigger_ops *, struct event_trigger_data *, struct trace_event_file *);
	void (*unreg_all)(struct trace_event_file *);
	int (*set_filter)(char *, struct event_trigger_data *, struct trace_event_file *);
	struct event_trigger_ops * (*get_trigger_ops)(char *, char *);
};

struct enable_trigger_data {
	struct trace_event_file *file;
	bool enable;
	bool hist;
};

enum event_command_flags {
	EVENT_CMD_FL_POST_TRIGGER = 1,
	EVENT_CMD_FL_NEEDS_REC = 2,
};

enum {
	BPF_F_INDEX_MASK = 4294967295,
	BPF_F_CURRENT_CPU = 4294967295,
	BPF_F_CTXLEN_MASK = 0,
};

enum {
	BPF_F_GET_BRANCH_RECORDS_SIZE = 1,
};

struct bpf_perf_event_value {
	__u64 counter;
	__u64 enabled;
	__u64 running;
};

struct bpf_raw_tracepoint_args {
	__u64 args[0];
};

enum bpf_task_fd_type {
	BPF_FD_TYPE_RAW_TRACEPOINT = 0,
	BPF_FD_TYPE_TRACEPOINT = 1,
	BPF_FD_TYPE_KPROBE = 2,
	BPF_FD_TYPE_KRETPROBE = 3,
	BPF_FD_TYPE_UPROBE = 4,
	BPF_FD_TYPE_URETPROBE = 5,
};

struct bpf_event_entry {
	struct perf_event *event;
	struct file *perf_file;
	struct file *map_file;
	struct callback_head rcu;
};

typedef long unsigned int (*bpf_ctx_copy_t)(void *, const void *, long unsigned int, long unsigned int);

typedef struct pt_regs bpf_user_pt_regs_t;

struct bpf_perf_event_data {
	bpf_user_pt_regs_t regs;
	__u64 sample_period;
	__u64 addr;
};

struct perf_event_query_bpf {
	__u32 ids_len;
	__u32 prog_cnt;
	__u32 ids[0];
};

struct bpf_perf_event_data_kern {
	bpf_user_pt_regs_t *regs;
	struct perf_sample_data *data;
	struct perf_event *event;
};

struct bpf_trace_module {
	struct module *module;
	struct list_head list;
};

typedef u64 (*btf_bpf_override_return)(struct pt_regs *, long unsigned int);

typedef u64 (*btf_bpf_probe_read_user)(void *, u32, const void *);

typedef u64 (*btf_bpf_probe_read_user_str)(void *, u32, const void *);

typedef u64 (*btf_bpf_probe_read_kernel)(void *, u32, const void *);

typedef u64 (*btf_bpf_probe_read_kernel_str)(void *, u32, const void *);

typedef u64 (*btf_bpf_probe_read_compat)(void *, u32, const void *);

typedef u64 (*btf_bpf_probe_read_compat_str)(void *, u32, const void *);

typedef u64 (*btf_bpf_probe_write_user)(void *, const void *, u32);

typedef u64 (*btf_bpf_trace_printk)(char *, u32, u64, u64, u64);

struct bpf_seq_printf_buf {
	char buf[768];
};

typedef u64 (*btf_bpf_seq_printf)(struct seq_file *, char *, u32, const void *, u32);

typedef u64 (*btf_bpf_seq_write)(struct seq_file *, const void *, u32);

typedef u64 (*btf_bpf_perf_event_read)(struct bpf_map *, u64);

typedef u64 (*btf_bpf_perf_event_read_value)(struct bpf_map *, u64, struct bpf_perf_event_value *, u32);

struct bpf_trace_sample_data {
	struct perf_sample_data sds[3];
};

typedef u64 (*btf_bpf_perf_event_output)(struct pt_regs *, struct bpf_map *, u64, void *, u64);

struct bpf_nested_pt_regs {
	struct pt_regs regs[3];
};

typedef u64 (*btf_bpf_get_current_task)();

typedef u64 (*btf_bpf_current_task_under_cgroup)(struct bpf_map *, u32);

struct send_signal_irq_work {
	struct irq_work irq_work;
	struct task_struct *task;
	u32 sig;
	enum pid_type type;
};

typedef u64 (*btf_bpf_send_signal)(u32);

typedef u64 (*btf_bpf_send_signal_thread)(u32);

typedef u64 (*btf_bpf_perf_event_output_tp)(void *, struct bpf_map *, u64, void *, u64);

typedef u64 (*btf_bpf_get_stackid_tp)(void *, struct bpf_map *, u64);

typedef u64 (*btf_bpf_get_stack_tp)(void *, void *, u32, u64);

typedef u64 (*btf_bpf_perf_prog_read_value)(struct bpf_perf_event_data_kern *, struct bpf_perf_event_value *, u32);

typedef u64 (*btf_bpf_read_branch_records)(struct bpf_perf_event_data_kern *, void *, u32, u64);

struct bpf_raw_tp_regs {
	struct pt_regs regs[3];
};

typedef u64 (*btf_bpf_perf_event_output_raw_tp)(struct bpf_raw_tracepoint_args *, struct bpf_map *, u64, void *, u64);

typedef u64 (*btf_bpf_get_stackid_raw_tp)(struct bpf_raw_tracepoint_args *, struct bpf_map *, u64);

typedef u64 (*btf_bpf_get_stack_raw_tp)(struct bpf_raw_tracepoint_args *, void *, u32, u64);

typedef struct bpf_cgroup_storage *pto_T_____20;

enum dynevent_type {
	DYNEVENT_TYPE_SYNTH = 1,
	DYNEVENT_TYPE_KPROBE = 2,
	DYNEVENT_TYPE_NONE = 3,
};

struct dynevent_cmd;

typedef int (*dynevent_create_fn_t)(struct dynevent_cmd *);

struct dynevent_cmd {
	struct seq_buf seq;
	const char *event_name;
	unsigned int n_fields;
	enum dynevent_type type;
	dynevent_create_fn_t run_command;
	void *private_data;
};

struct kprobe_trace_entry_head {
	struct trace_entry ent;
	long unsigned int ip;
};

struct kretprobe_trace_entry_head {
	struct trace_entry ent;
	long unsigned int func;
	long unsigned int ret_ip;
};

struct dyn_event;

struct dyn_event_operations {
	struct list_head list;
	int (*create)(int, const char **);
	int (*show)(struct seq_file *, struct dyn_event *);
	bool (*is_busy)(struct dyn_event *);
	int (*free)(struct dyn_event *);
	bool (*match)(const char *, const char *, int, const char **, struct dyn_event *);
};

struct dyn_event {
	struct list_head list;
	struct dyn_event_operations *ops;
};

struct dynevent_arg {
	const char *str;
	char separator;
};

typedef int (*print_type_func_t)(struct trace_seq *, void *, void *);

enum fetch_op {
	FETCH_OP_NOP = 0,
	FETCH_OP_REG = 1,
	FETCH_OP_STACK = 2,
	FETCH_OP_STACKP = 3,
	FETCH_OP_RETVAL = 4,
	FETCH_OP_IMM = 5,
	FETCH_OP_COMM = 6,
	FETCH_OP_ARG = 7,
	FETCH_OP_FOFFS = 8,
	FETCH_OP_DATA = 9,
	FETCH_OP_DEREF = 10,
	FETCH_OP_UDEREF = 11,
	FETCH_OP_ST_RAW = 12,
	FETCH_OP_ST_MEM = 13,
	FETCH_OP_ST_UMEM = 14,
	FETCH_OP_ST_STRING = 15,
	FETCH_OP_ST_USTRING = 16,
	FETCH_OP_MOD_BF = 17,
	FETCH_OP_LP_ARRAY = 18,
	FETCH_OP_END = 19,
	FETCH_NOP_SYMBOL = 20,
};

struct fetch_insn {
	enum fetch_op op;
	union {
		unsigned int param;
		struct {
			unsigned int size;
			int offset;
		};
		struct {
			unsigned char basesize;
			unsigned char lshift;
			unsigned char rshift;
		};
		long unsigned int immediate;
		void *data;
	};
};

struct fetch_type {
	const char *name;
	size_t size;
	int is_signed;
	print_type_func_t print;
	const char *fmt;
	const char *fmttype;
};

struct probe_arg {
	struct fetch_insn *code;
	bool dynamic;
	unsigned int offset;
	unsigned int count;
	const char *name;
	const char *comm;
	char *fmt;
	const struct fetch_type *type;
};

struct trace_uprobe_filter {
	rwlock_t rwlock;
	int nr_systemwide;
	struct list_head perf_events;
};

struct trace_probe_event {
	unsigned int flags;
	struct trace_event_class class;
	struct trace_event_call call;
	struct list_head files;
	struct list_head probes;
	struct trace_uprobe_filter filter[0];
};

struct trace_probe {
	struct list_head list;
	struct trace_probe_event *event;
	ssize_t size;
	unsigned int nr_args;
	struct probe_arg args[0];
};

struct event_file_link {
	struct trace_event_file *file;
	struct list_head list;
};

enum {
	TP_ERR_FILE_NOT_FOUND = 0,
	TP_ERR_NO_REGULAR_FILE = 1,
	TP_ERR_BAD_REFCNT = 2,
	TP_ERR_REFCNT_OPEN_BRACE = 3,
	TP_ERR_BAD_REFCNT_SUFFIX = 4,
	TP_ERR_BAD_UPROBE_OFFS = 5,
	TP_ERR_MAXACT_NO_KPROBE = 6,
	TP_ERR_BAD_MAXACT = 7,
	TP_ERR_MAXACT_TOO_BIG = 8,
	TP_ERR_BAD_PROBE_ADDR = 9,
	TP_ERR_BAD_RETPROBE = 10,
	TP_ERR_NO_GROUP_NAME = 11,
	TP_ERR_GROUP_TOO_LONG = 12,
	TP_ERR_BAD_GROUP_NAME = 13,
	TP_ERR_NO_EVENT_NAME = 14,
	TP_ERR_EVENT_TOO_LONG = 15,
	TP_ERR_BAD_EVENT_NAME = 16,
	TP_ERR_RETVAL_ON_PROBE = 17,
	TP_ERR_BAD_STACK_NUM = 18,
	TP_ERR_BAD_ARG_NUM = 19,
	TP_ERR_BAD_VAR = 20,
	TP_ERR_BAD_REG_NAME = 21,
	TP_ERR_BAD_MEM_ADDR = 22,
	TP_ERR_BAD_IMM = 23,
	TP_ERR_IMMSTR_NO_CLOSE = 24,
	TP_ERR_FILE_ON_KPROBE = 25,
	TP_ERR_BAD_FILE_OFFS = 26,
	TP_ERR_SYM_ON_UPROBE = 27,
	TP_ERR_TOO_MANY_OPS = 28,
	TP_ERR_DEREF_NEED_BRACE = 29,
	TP_ERR_BAD_DEREF_OFFS = 30,
	TP_ERR_DEREF_OPEN_BRACE = 31,
	TP_ERR_COMM_CANT_DEREF = 32,
	TP_ERR_BAD_FETCH_ARG = 33,
	TP_ERR_ARRAY_NO_CLOSE = 34,
	TP_ERR_BAD_ARRAY_SUFFIX = 35,
	TP_ERR_BAD_ARRAY_NUM = 36,
	TP_ERR_ARRAY_TOO_BIG = 37,
	TP_ERR_BAD_TYPE = 38,
	TP_ERR_BAD_STRING = 39,
	TP_ERR_BAD_BITFIELD = 40,
	TP_ERR_ARG_NAME_TOO_LONG = 41,
	TP_ERR_NO_ARG_NAME = 42,
	TP_ERR_BAD_ARG_NAME = 43,
	TP_ERR_USED_ARG_NAME = 44,
	TP_ERR_ARG_TOO_LONG = 45,
	TP_ERR_NO_ARG_BODY = 46,
	TP_ERR_BAD_INSN_BNDRY = 47,
	TP_ERR_FAIL_REG_PROBE = 48,
	TP_ERR_DIFF_PROBE_TYPE = 49,
	TP_ERR_DIFF_ARG_TYPE = 50,
	TP_ERR_SAME_PROBE = 51,
};

struct trace_kprobe {
	struct dyn_event devent;
	struct kretprobe rp;
	long unsigned int *nhit;
	const char *symbol;
	struct trace_probe tp;
};

struct trace_event_raw_cpu {
	struct trace_entry ent;
	u32 state;
	u32 cpu_id;
	char __data[0];
};

struct trace_event_raw_powernv_throttle {
	struct trace_entry ent;
	int chip_id;
	u32 __data_loc_reason;
	int pmax;
	char __data[0];
};

struct trace_event_raw_pstate_sample {
	struct trace_entry ent;
	u32 core_busy;
	u32 scaled_busy;
	u32 from;
	u32 to;
	u64 mperf;
	u64 aperf;
	u64 tsc;
	u32 freq;
	u32 io_boost;
	char __data[0];
};

struct trace_event_raw_cpu_frequency_limits {
	struct trace_entry ent;
	u32 min_freq;
	u32 max_freq;
	u32 cpu_id;
	char __data[0];
};

struct trace_event_raw_device_pm_callback_start {
	struct trace_entry ent;
	u32 __data_loc_device;
	u32 __data_loc_driver;
	u32 __data_loc_parent;
	u32 __data_loc_pm_ops;
	int event;
	char __data[0];
};

struct trace_event_raw_device_pm_callback_end {
	struct trace_entry ent;
	u32 __data_loc_device;
	u32 __data_loc_driver;
	int error;
	char __data[0];
};

struct trace_event_raw_suspend_resume {
	struct trace_entry ent;
	const char *action;
	int val;
	bool start;
	char __data[0];
};

struct trace_event_raw_wakeup_source {
	struct trace_entry ent;
	u32 __data_loc_name;
	u64 state;
	char __data[0];
};

struct trace_event_raw_clock {
	struct trace_entry ent;
	u32 __data_loc_name;
	u64 state;
	u64 cpu_id;
	char __data[0];
};

struct trace_event_raw_power_domain {
	struct trace_entry ent;
	u32 __data_loc_name;
	u64 state;
	u64 cpu_id;
	char __data[0];
};

struct trace_event_raw_cpu_latency_qos_request {
	struct trace_entry ent;
	s32 value;
	char __data[0];
};

struct trace_event_raw_pm_qos_update {
	struct trace_entry ent;
	enum pm_qos_req_action action;
	int prev_value;
	int curr_value;
	char __data[0];
};

struct trace_event_raw_dev_pm_qos_request {
	struct trace_entry ent;
	u32 __data_loc_name;
	enum dev_pm_qos_req_type type;
	s32 new_value;
	char __data[0];
};

struct trace_event_data_offsets_cpu {};

struct trace_event_data_offsets_powernv_throttle {
	u32 reason;
};

struct trace_event_data_offsets_pstate_sample {};

struct trace_event_data_offsets_cpu_frequency_limits {};

struct trace_event_data_offsets_device_pm_callback_start {
	u32 device;
	u32 driver;
	u32 parent;
	u32 pm_ops;
};

struct trace_event_data_offsets_device_pm_callback_end {
	u32 device;
	u32 driver;
};

struct trace_event_data_offsets_suspend_resume {};

struct trace_event_data_offsets_wakeup_source {
	u32 name;
};

struct trace_event_data_offsets_clock {
	u32 name;
};

struct trace_event_data_offsets_power_domain {
	u32 name;
};

struct trace_event_data_offsets_cpu_latency_qos_request {};

struct trace_event_data_offsets_pm_qos_update {};

struct trace_event_data_offsets_dev_pm_qos_request {
	u32 name;
};

typedef void (*btf_trace_cpu_idle)(void *, unsigned int, unsigned int);

typedef void (*btf_trace_powernv_throttle)(void *, int, const char *, int);

typedef void (*btf_trace_pstate_sample)(void *, u32, u32, u32, u32, u64, u64, u64, u32, u32);

typedef void (*btf_trace_cpu_frequency)(void *, unsigned int, unsigned int);

typedef void (*btf_trace_cpu_frequency_limits)(void *, struct cpufreq_policy *);

typedef void (*btf_trace_device_pm_callback_start)(void *, struct device *, const char *, int);

typedef void (*btf_trace_device_pm_callback_end)(void *, struct device *, int);

typedef void (*btf_trace_suspend_resume)(void *, const char *, int, bool);

typedef void (*btf_trace_wakeup_source_activate)(void *, const char *, unsigned int);

typedef void (*btf_trace_wakeup_source_deactivate)(void *, const char *, unsigned int);

typedef void (*btf_trace_clock_enable)(void *, const char *, unsigned int, unsigned int);

typedef void (*btf_trace_clock_disable)(void *, const char *, unsigned int, unsigned int);

typedef void (*btf_trace_clock_set_rate)(void *, const char *, unsigned int, unsigned int);

typedef void (*btf_trace_power_domain_target)(void *, const char *, unsigned int, unsigned int);

typedef void (*btf_trace_pm_qos_add_request)(void *, s32);

typedef void (*btf_trace_pm_qos_update_request)(void *, s32);

typedef void (*btf_trace_pm_qos_remove_request)(void *, s32);

typedef void (*btf_trace_pm_qos_update_target)(void *, enum pm_qos_req_action, int, int);

typedef void (*btf_trace_pm_qos_update_flags)(void *, enum pm_qos_req_action, int, int);

typedef void (*btf_trace_dev_pm_qos_add_request)(void *, const char *, enum dev_pm_qos_req_type, s32);

typedef void (*btf_trace_dev_pm_qos_update_request)(void *, const char *, enum dev_pm_qos_req_type, s32);

typedef void (*btf_trace_dev_pm_qos_remove_request)(void *, const char *, enum dev_pm_qos_req_type, s32);

struct trace_event_raw_rpm_internal {
	struct trace_entry ent;
	u32 __data_loc_name;
	int flags;
	int usage_count;
	int disable_depth;
	int runtime_auto;
	int request_pending;
	int irq_safe;
	int child_count;
	char __data[0];
};

struct trace_event_raw_rpm_return_int {
	struct trace_entry ent;
	u32 __data_loc_name;
	long unsigned int ip;
	int ret;
	char __data[0];
};

struct trace_event_data_offsets_rpm_internal {
	u32 name;
};

struct trace_event_data_offsets_rpm_return_int {
	u32 name;
};

typedef void (*btf_trace_rpm_suspend)(void *, struct device *, int);

typedef void (*btf_trace_rpm_resume)(void *, struct device *, int);

typedef void (*btf_trace_rpm_idle)(void *, struct device *, int);

typedef void (*btf_trace_rpm_usage)(void *, struct device *, int);

typedef void (*btf_trace_rpm_return_int)(void *, struct device *, long unsigned int, int);

typedef int (*dynevent_check_arg_fn_t)(void *);

struct dynevent_arg_pair {
	const char *lhs;
	const char *rhs;
	char operator;
	char separator;
};

struct trace_probe_log {
	const char *subsystem;
	const char **argv;
	int argc;
	int index;
};

enum uprobe_filter_ctx {
	UPROBE_FILTER_REGISTER = 0,
	UPROBE_FILTER_UNREGISTER = 1,
	UPROBE_FILTER_MMAP = 2,
};

struct uprobe_consumer {
	int (*handler)(struct uprobe_consumer *, struct pt_regs *);
	int (*ret_handler)(struct uprobe_consumer *, long unsigned int, struct pt_regs *);
	bool (*filter)(struct uprobe_consumer *, enum uprobe_filter_ctx, struct mm_struct *);
	struct uprobe_consumer *next;
};

struct uprobe_trace_entry_head {
	struct trace_entry ent;
	long unsigned int vaddr[0];
};

struct trace_uprobe {
	struct dyn_event devent;
	struct uprobe_consumer consumer;
	struct path path;
	struct inode *inode;
	char *filename;
	long unsigned int offset;
	long unsigned int ref_ctr_offset;
	long unsigned int nhit;
	struct trace_probe tp;
};

struct uprobe_dispatch_data {
	struct trace_uprobe *tu;
	long unsigned int bp_addr;
};

struct uprobe_cpu_buffer {
	struct mutex mutex;
	void *buf;
};

typedef bool (*filter_func_t)(struct uprobe_consumer *, enum uprobe_filter_ctx, struct mm_struct *);

typedef __u32 __le32;

typedef __u64 __le64;

struct rhash_lock_head;

struct bucket_table {
	unsigned int size;
	unsigned int nest;
	u32 hash_rnd;
	struct list_head walkers;
	struct callback_head rcu;
	struct bucket_table *future_tbl;
	struct lockdep_map dep_map;
	long: 64;
	struct rhash_lock_head *buckets[0];
};

enum xdp_action {
	XDP_ABORTED = 0,
	XDP_DROP = 1,
	XDP_PASS = 2,
	XDP_TX = 3,
	XDP_REDIRECT = 4,
};

enum xdp_mem_type {
	MEM_TYPE_PAGE_SHARED = 0,
	MEM_TYPE_PAGE_ORDER0 = 1,
	MEM_TYPE_PAGE_POOL = 2,
	MEM_TYPE_XSK_BUFF_POOL = 3,
	MEM_TYPE_MAX = 4,
};

typedef void (*bpf_jit_fill_hole_t)(void *, unsigned int);

struct bpf_prog_dummy {
	struct bpf_prog prog;
};

typedef u64 (*btf_bpf_user_rnd_u32)();

typedef u64 (*btf_bpf_get_raw_cpu_id)();

struct _bpf_dtab_netdev {
	struct net_device *dev;
};

struct rhash_lock_head {};

struct zero_copy_allocator;

struct page_pool;

struct xdp_mem_allocator {
	struct xdp_mem_info mem;
	union {
		void *allocator;
		struct page_pool *page_pool;
		struct zero_copy_allocator *zc_alloc;
	};
	struct rhash_head node;
	struct callback_head rcu;
};

struct trace_event_raw_xdp_exception {
	struct trace_entry ent;
	int prog_id;
	u32 act;
	int ifindex;
	char __data[0];
};

struct trace_event_raw_xdp_bulk_tx {
	struct trace_entry ent;
	int ifindex;
	u32 act;
	int drops;
	int sent;
	int err;
	char __data[0];
};

struct trace_event_raw_xdp_redirect_template {
	struct trace_entry ent;
	int prog_id;
	u32 act;
	int ifindex;
	int err;
	int to_ifindex;
	u32 map_id;
	int map_index;
	char __data[0];
};

struct trace_event_raw_xdp_cpumap_kthread {
	struct trace_entry ent;
	int map_id;
	u32 act;
	int cpu;
	unsigned int drops;
	unsigned int processed;
	int sched;
	char __data[0];
};

struct trace_event_raw_xdp_cpumap_enqueue {
	struct trace_entry ent;
	int map_id;
	u32 act;
	int cpu;
	unsigned int drops;
	unsigned int processed;
	int to_cpu;
	char __data[0];
};

struct trace_event_raw_xdp_devmap_xmit {
	struct trace_entry ent;
	int from_ifindex;
	u32 act;
	int to_ifindex;
	int drops;
	int sent;
	int err;
	char __data[0];
};

struct trace_event_raw_mem_disconnect {
	struct trace_entry ent;
	const struct xdp_mem_allocator *xa;
	u32 mem_id;
	u32 mem_type;
	const void *allocator;
	char __data[0];
};

struct trace_event_raw_mem_connect {
	struct trace_entry ent;
	const struct xdp_mem_allocator *xa;
	u32 mem_id;
	u32 mem_type;
	const void *allocator;
	const struct xdp_rxq_info *rxq;
	int ifindex;
	char __data[0];
};

struct trace_event_raw_mem_return_failed {
	struct trace_entry ent;
	const struct page *page;
	u32 mem_id;
	u32 mem_type;
	char __data[0];
};

struct trace_event_data_offsets_xdp_exception {};

struct trace_event_data_offsets_xdp_bulk_tx {};

struct trace_event_data_offsets_xdp_redirect_template {};

struct trace_event_data_offsets_xdp_cpumap_kthread {};

struct trace_event_data_offsets_xdp_cpumap_enqueue {};

struct trace_event_data_offsets_xdp_devmap_xmit {};

struct trace_event_data_offsets_mem_disconnect {};

struct trace_event_data_offsets_mem_connect {};

struct trace_event_data_offsets_mem_return_failed {};

typedef void (*btf_trace_xdp_exception)(void *, const struct net_device *, const struct bpf_prog *, u32);

typedef void (*btf_trace_xdp_bulk_tx)(void *, const struct net_device *, int, int, int);

typedef void (*btf_trace_xdp_redirect)(void *, const struct net_device *, const struct bpf_prog *, const void *, int, const struct bpf_map *, u32);

typedef void (*btf_trace_xdp_redirect_err)(void *, const struct net_device *, const struct bpf_prog *, const void *, int, const struct bpf_map *, u32);

typedef void (*btf_trace_xdp_redirect_map)(void *, const struct net_device *, const struct bpf_prog *, const void *, int, const struct bpf_map *, u32);

typedef void (*btf_trace_xdp_redirect_map_err)(void *, const struct net_device *, const struct bpf_prog *, const void *, int, const struct bpf_map *, u32);

typedef void (*btf_trace_xdp_cpumap_kthread)(void *, int, unsigned int, unsigned int, int);

typedef void (*btf_trace_xdp_cpumap_enqueue)(void *, int, unsigned int, unsigned int, int);

typedef void (*btf_trace_xdp_devmap_xmit)(void *, const struct net_device *, const struct net_device *, int, int, int);

typedef void (*btf_trace_mem_disconnect)(void *, const struct xdp_mem_allocator *);

typedef void (*btf_trace_mem_connect)(void *, const struct xdp_mem_allocator *, const struct xdp_rxq_info *);

typedef void (*btf_trace_mem_return_failed)(void *, const struct xdp_mem_info *, const struct page *);

enum bpf_cmd {
	BPF_MAP_CREATE = 0,
	BPF_MAP_LOOKUP_ELEM = 1,
	BPF_MAP_UPDATE_ELEM = 2,
	BPF_MAP_DELETE_ELEM = 3,
	BPF_MAP_GET_NEXT_KEY = 4,
	BPF_PROG_LOAD = 5,
	BPF_OBJ_PIN = 6,
	BPF_OBJ_GET = 7,
	BPF_PROG_ATTACH = 8,
	BPF_PROG_DETACH = 9,
	BPF_PROG_TEST_RUN = 10,
	BPF_PROG_GET_NEXT_ID = 11,
	BPF_MAP_GET_NEXT_ID = 12,
	BPF_PROG_GET_FD_BY_ID = 13,
	BPF_MAP_GET_FD_BY_ID = 14,
	BPF_OBJ_GET_INFO_BY_FD = 15,
	BPF_PROG_QUERY = 16,
	BPF_RAW_TRACEPOINT_OPEN = 17,
	BPF_BTF_LOAD = 18,
	BPF_BTF_GET_FD_BY_ID = 19,
	BPF_TASK_FD_QUERY = 20,
	BPF_MAP_LOOKUP_AND_DELETE_ELEM = 21,
	BPF_MAP_FREEZE = 22,
	BPF_BTF_GET_NEXT_ID = 23,
	BPF_MAP_LOOKUP_BATCH = 24,
	BPF_MAP_LOOKUP_AND_DELETE_BATCH = 25,
	BPF_MAP_UPDATE_BATCH = 26,
	BPF_MAP_DELETE_BATCH = 27,
	BPF_LINK_CREATE = 28,
	BPF_LINK_UPDATE = 29,
	BPF_LINK_GET_FD_BY_ID = 30,
	BPF_LINK_GET_NEXT_ID = 31,
	BPF_ENABLE_STATS = 32,
	BPF_ITER_CREATE = 33,
};

enum {
	BPF_ANY = 0,
	BPF_NOEXIST = 1,
	BPF_EXIST = 2,
	BPF_F_LOCK = 4,
};

enum {
	BPF_F_NO_PREALLOC = 1,
	BPF_F_NO_COMMON_LRU = 2,
	BPF_F_NUMA_NODE = 4,
	BPF_F_RDONLY = 8,
	BPF_F_WRONLY = 16,
	BPF_F_STACK_BUILD_ID = 32,
	BPF_F_ZERO_SEED = 64,
	BPF_F_RDONLY_PROG = 128,
	BPF_F_WRONLY_PROG = 256,
	BPF_F_CLONE = 512,
	BPF_F_MMAPABLE = 1024,
};

enum bpf_stats_type {
	BPF_STATS_RUN_TIME = 0,
};

struct bpf_prog_info {
	__u32 type;
	__u32 id;
	__u8 tag[8];
	__u32 jited_prog_len;
	__u32 xlated_prog_len;
	__u64 jited_prog_insns;
	__u64 xlated_prog_insns;
	__u64 load_time;
	__u32 created_by_uid;
	__u32 nr_map_ids;
	__u64 map_ids;
	char name[16];
	__u32 ifindex;
	__u32 gpl_compatible: 1;
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 nr_jited_ksyms;
	__u32 nr_jited_func_lens;
	__u64 jited_ksyms;
	__u64 jited_func_lens;
	__u32 btf_id;
	__u32 func_info_rec_size;
	__u64 func_info;
	__u32 nr_func_info;
	__u32 nr_line_info;
	__u64 line_info;
	__u64 jited_line_info;
	__u32 nr_jited_line_info;
	__u32 line_info_rec_size;
	__u32 jited_line_info_rec_size;
	__u32 nr_prog_tags;
	__u64 prog_tags;
	__u64 run_time_ns;
	__u64 run_cnt;
};

struct bpf_map_info {
	__u32 type;
	__u32 id;
	__u32 key_size;
	__u32 value_size;
	__u32 max_entries;
	__u32 map_flags;
	char name[16];
	__u32 ifindex;
	__u32 btf_vmlinux_value_type_id;
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 btf_id;
	__u32 btf_key_type_id;
	__u32 btf_value_type_id;
};

struct bpf_btf_info {
	__u64 btf;
	__u32 btf_size;
	__u32 id;
};

struct bpf_spin_lock {
	__u32 val;
};

struct bpf_link_primer {
	struct bpf_link *link;
	struct file *file;
	int fd;
	u32 id;
};

enum perf_bpf_event_type {
	PERF_BPF_EVENT_UNKNOWN = 0,
	PERF_BPF_EVENT_PROG_LOAD = 1,
	PERF_BPF_EVENT_PROG_UNLOAD = 2,
	PERF_BPF_EVENT_MAX = 3,
};

struct security_hook_heads {
	struct hlist_head binder_set_context_mgr;
	struct hlist_head binder_transaction;
	struct hlist_head binder_transfer_binder;
	struct hlist_head binder_transfer_file;
	struct hlist_head ptrace_access_check;
	struct hlist_head ptrace_traceme;
	struct hlist_head capget;
	struct hlist_head capset;
	struct hlist_head capable;
	struct hlist_head quotactl;
	struct hlist_head quota_on;
	struct hlist_head syslog;
	struct hlist_head settime;
	struct hlist_head vm_enough_memory;
	struct hlist_head bprm_creds_for_exec;
	struct hlist_head bprm_creds_from_file;
	struct hlist_head bprm_check_security;
	struct hlist_head bprm_committing_creds;
	struct hlist_head bprm_committed_creds;
	struct hlist_head fs_context_dup;
	struct hlist_head fs_context_parse_param;
	struct hlist_head sb_alloc_security;
	struct hlist_head sb_free_security;
	struct hlist_head sb_free_mnt_opts;
	struct hlist_head sb_eat_lsm_opts;
	struct hlist_head sb_remount;
	struct hlist_head sb_kern_mount;
	struct hlist_head sb_show_options;
	struct hlist_head sb_statfs;
	struct hlist_head sb_mount;
	struct hlist_head sb_umount;
	struct hlist_head sb_pivotroot;
	struct hlist_head sb_set_mnt_opts;
	struct hlist_head sb_clone_mnt_opts;
	struct hlist_head sb_add_mnt_opt;
	struct hlist_head move_mount;
	struct hlist_head dentry_init_security;
	struct hlist_head dentry_create_files_as;
	struct hlist_head path_notify;
	struct hlist_head inode_alloc_security;
	struct hlist_head inode_free_security;
	struct hlist_head inode_init_security;
	struct hlist_head inode_create;
	struct hlist_head inode_link;
	struct hlist_head inode_unlink;
	struct hlist_head inode_symlink;
	struct hlist_head inode_mkdir;
	struct hlist_head inode_rmdir;
	struct hlist_head inode_mknod;
	struct hlist_head inode_rename;
	struct hlist_head inode_readlink;
	struct hlist_head inode_follow_link;
	struct hlist_head inode_permission;
	struct hlist_head inode_setattr;
	struct hlist_head inode_getattr;
	struct hlist_head inode_setxattr;
	struct hlist_head inode_post_setxattr;
	struct hlist_head inode_getxattr;
	struct hlist_head inode_listxattr;
	struct hlist_head inode_removexattr;
	struct hlist_head inode_need_killpriv;
	struct hlist_head inode_killpriv;
	struct hlist_head inode_getsecurity;
	struct hlist_head inode_setsecurity;
	struct hlist_head inode_listsecurity;
	struct hlist_head inode_getsecid;
	struct hlist_head inode_copy_up;
	struct hlist_head inode_copy_up_xattr;
	struct hlist_head kernfs_init_security;
	struct hlist_head file_permission;
	struct hlist_head file_alloc_security;
	struct hlist_head file_free_security;
	struct hlist_head file_ioctl;
	struct hlist_head mmap_addr;
	struct hlist_head mmap_file;
	struct hlist_head file_mprotect;
	struct hlist_head file_lock;
	struct hlist_head file_fcntl;
	struct hlist_head file_set_fowner;
	struct hlist_head file_send_sigiotask;
	struct hlist_head file_receive;
	struct hlist_head file_open;
	struct hlist_head task_alloc;
	struct hlist_head task_free;
	struct hlist_head cred_alloc_blank;
	struct hlist_head cred_free;
	struct hlist_head cred_prepare;
	struct hlist_head cred_transfer;
	struct hlist_head cred_getsecid;
	struct hlist_head kernel_act_as;
	struct hlist_head kernel_create_files_as;
	struct hlist_head kernel_module_request;
	struct hlist_head kernel_load_data;
	struct hlist_head kernel_read_file;
	struct hlist_head kernel_post_read_file;
	struct hlist_head task_fix_setuid;
	struct hlist_head task_fix_setgid;
	struct hlist_head task_setpgid;
	struct hlist_head task_getpgid;
	struct hlist_head task_getsid;
	struct hlist_head task_getsecid;
	struct hlist_head task_setnice;
	struct hlist_head task_setioprio;
	struct hlist_head task_getioprio;
	struct hlist_head task_prlimit;
	struct hlist_head task_setrlimit;
	struct hlist_head task_setscheduler;
	struct hlist_head task_getscheduler;
	struct hlist_head task_movememory;
	struct hlist_head task_kill;
	struct hlist_head task_prctl;
	struct hlist_head task_to_inode;
	struct hlist_head ipc_permission;
	struct hlist_head ipc_getsecid;
	struct hlist_head msg_msg_alloc_security;
	struct hlist_head msg_msg_free_security;
	struct hlist_head msg_queue_alloc_security;
	struct hlist_head msg_queue_free_security;
	struct hlist_head msg_queue_associate;
	struct hlist_head msg_queue_msgctl;
	struct hlist_head msg_queue_msgsnd;
	struct hlist_head msg_queue_msgrcv;
	struct hlist_head shm_alloc_security;
	struct hlist_head shm_free_security;
	struct hlist_head shm_associate;
	struct hlist_head shm_shmctl;
	struct hlist_head shm_shmat;
	struct hlist_head sem_alloc_security;
	struct hlist_head sem_free_security;
	struct hlist_head sem_associate;
	struct hlist_head sem_semctl;
	struct hlist_head sem_semop;
	struct hlist_head netlink_send;
	struct hlist_head d_instantiate;
	struct hlist_head getprocattr;
	struct hlist_head setprocattr;
	struct hlist_head ismaclabel;
	struct hlist_head secid_to_secctx;
	struct hlist_head secctx_to_secid;
	struct hlist_head release_secctx;
	struct hlist_head inode_invalidate_secctx;
	struct hlist_head inode_notifysecctx;
	struct hlist_head inode_setsecctx;
	struct hlist_head inode_getsecctx;
	struct hlist_head unix_stream_connect;
	struct hlist_head unix_may_send;
	struct hlist_head socket_create;
	struct hlist_head socket_post_create;
	struct hlist_head socket_socketpair;
	struct hlist_head socket_bind;
	struct hlist_head socket_connect;
	struct hlist_head socket_listen;
	struct hlist_head socket_accept;
	struct hlist_head socket_sendmsg;
	struct hlist_head socket_recvmsg;
	struct hlist_head socket_getsockname;
	struct hlist_head socket_getpeername;
	struct hlist_head socket_getsockopt;
	struct hlist_head socket_setsockopt;
	struct hlist_head socket_shutdown;
	struct hlist_head socket_sock_rcv_skb;
	struct hlist_head socket_getpeersec_stream;
	struct hlist_head socket_getpeersec_dgram;
	struct hlist_head sk_alloc_security;
	struct hlist_head sk_free_security;
	struct hlist_head sk_clone_security;
	struct hlist_head sk_getsecid;
	struct hlist_head sock_graft;
	struct hlist_head inet_conn_request;
	struct hlist_head inet_csk_clone;
	struct hlist_head inet_conn_established;
	struct hlist_head secmark_relabel_packet;
	struct hlist_head secmark_refcount_inc;
	struct hlist_head secmark_refcount_dec;
	struct hlist_head req_classify_flow;
	struct hlist_head tun_dev_alloc_security;
	struct hlist_head tun_dev_free_security;
	struct hlist_head tun_dev_create;
	struct hlist_head tun_dev_attach_queue;
	struct hlist_head tun_dev_attach;
	struct hlist_head tun_dev_open;
	struct hlist_head sctp_assoc_request;
	struct hlist_head sctp_bind_connect;
	struct hlist_head sctp_sk_clone;
	struct hlist_head key_alloc;
	struct hlist_head key_free;
	struct hlist_head key_permission;
	struct hlist_head key_getsecurity;
	struct hlist_head audit_rule_init;
	struct hlist_head audit_rule_known;
	struct hlist_head audit_rule_match;
	struct hlist_head audit_rule_free;
	struct hlist_head bpf;
	struct hlist_head bpf_map;
	struct hlist_head bpf_prog;
	struct hlist_head bpf_map_alloc_security;
	struct hlist_head bpf_map_free_security;
	struct hlist_head bpf_prog_alloc_security;
	struct hlist_head bpf_prog_free_security;
	struct hlist_head locked_down;
	struct hlist_head perf_event_open;
	struct hlist_head perf_event_alloc;
	struct hlist_head perf_event_free;
	struct hlist_head perf_event_read;
	struct hlist_head perf_event_write;
};

struct lsm_blob_sizes {
	int lbs_cred;
	int lbs_file;
	int lbs_inode;
	int lbs_ipc;
	int lbs_msg_msg;
	int lbs_task;
};

enum lsm_order {
	LSM_ORDER_FIRST = 4294967295,
	LSM_ORDER_MUTABLE = 0,
};

struct lsm_info {
	const char *name;
	enum lsm_order order;
	long unsigned int flags;
	int *enabled;
	int (*init)();
	struct lsm_blob_sizes *blobs;
};

enum bpf_audit {
	BPF_AUDIT_LOAD = 0,
	BPF_AUDIT_UNLOAD = 1,
	BPF_AUDIT_MAX = 2,
};

struct bpf_tracing_link {
	struct bpf_link link;
	enum bpf_attach_type attach_type;
};

struct bpf_raw_tp_link {
	struct bpf_link link;
	struct bpf_raw_event_map *btp;
};

struct btf_member {
	__u32 name_off;
	__u32 type;
	__u32 offset;
};

enum btf_func_linkage {
	BTF_FUNC_STATIC = 0,
	BTF_FUNC_GLOBAL = 1,
	BTF_FUNC_EXTERN = 2,
};

struct bpf_verifier_log {
	u32 level;
	char kbuf[1024];
	char *ubuf;
	u32 len_used;
	u32 len_total;
};

struct bpf_subprog_info {
	u32 start;
	u32 linfo_idx;
	u16 stack_depth;
};

struct bpf_verifier_stack_elem;

struct bpf_verifier_state;

struct bpf_verifier_state_list;

struct bpf_insn_aux_data;

struct bpf_verifier_env {
	u32 insn_idx;
	u32 prev_insn_idx;
	struct bpf_prog *prog;
	const struct bpf_verifier_ops *ops;
	struct bpf_verifier_stack_elem *head;
	int stack_size;
	bool strict_alignment;
	bool test_state_freq;
	struct bpf_verifier_state *cur_state;
	struct bpf_verifier_state_list **explored_states;
	struct bpf_verifier_state_list *free_list;
	struct bpf_map *used_maps[64];
	u32 used_map_cnt;
	u32 id_gen;
	bool allow_ptr_leaks;
	bool bpf_capable;
	bool bypass_spec_v1;
	bool bypass_spec_v4;
	bool seen_direct_write;
	struct bpf_insn_aux_data *insn_aux_data;
	const struct bpf_line_info *prev_linfo;
	struct bpf_verifier_log log;
	struct bpf_subprog_info subprog_info[257];
	struct {
		int *insn_state;
		int *insn_stack;
		int cur_stack;
	} cfg;
	u32 pass_cnt;
	u32 subprog_cnt;
	u32 prev_insn_processed;
	u32 insn_processed;
	u32 prev_jmps_processed;
	u32 jmps_processed;
	u64 verification_time;
	u32 max_states_per_insn;
	u32 total_states;
	u32 peak_states;
	u32 longest_mark_read_walk;
};

struct bpf_struct_ops {
	const struct bpf_verifier_ops *verifier_ops;
	int (*init)(struct btf *);
	int (*check_member)(const struct btf_type *, const struct btf_member *);
	int (*init_member)(const struct btf_type *, const struct btf_member *, void *, const void *);
	int (*reg)(void *);
	void (*unreg)(void *);
	const struct btf_type *type;
	const struct btf_type *value_type;
	const char *name;
	struct btf_func_model func_models[64];
	u32 type_id;
	u32 value_id;
};

typedef u32 (*bpf_convert_ctx_access_t)(enum bpf_access_type, const struct bpf_insn *, struct bpf_insn *, struct bpf_prog *, u32 *);

struct tnum {
	u64 value;
	u64 mask;
};

enum bpf_reg_liveness {
	REG_LIVE_NONE = 0,
	REG_LIVE_READ32 = 1,
	REG_LIVE_READ64 = 2,
	REG_LIVE_READ = 3,
	REG_LIVE_WRITTEN = 4,
	REG_LIVE_DONE = 8,
};

struct bpf_reg_state {
	enum bpf_reg_type type;
	union {
		u16 range;
		struct bpf_map *map_ptr;
		u32 btf_id;
		u32 mem_size;
		long unsigned int raw;
	};
	s32 off;
	u32 id;
	u32 ref_obj_id;
	struct tnum var_off;
	s64 smin_value;
	s64 smax_value;
	u64 umin_value;
	u64 umax_value;
	s32 s32_min_value;
	s32 s32_max_value;
	u32 u32_min_value;
	u32 u32_max_value;
	struct bpf_reg_state *parent;
	u32 frameno;
	s32 subreg_def;
	enum bpf_reg_liveness live;
	bool precise;
};

enum bpf_stack_slot_type {
	STACK_INVALID = 0,
	STACK_SPILL = 1,
	STACK_MISC = 2,
	STACK_ZERO = 3,
};

struct bpf_stack_state {
	struct bpf_reg_state spilled_ptr;
	u8 slot_type[8];
};

struct bpf_reference_state {
	int id;
	int insn_idx;
};

struct bpf_func_state {
	struct bpf_reg_state regs[11];
	int callsite;
	u32 frameno;
	u32 subprogno;
	int acquired_refs;
	struct bpf_reference_state *refs;
	int allocated_stack;
	struct bpf_stack_state *stack;
};

struct bpf_idx_pair {
	u32 prev_idx;
	u32 idx;
};

struct bpf_verifier_state {
	struct bpf_func_state *frame[8];
	struct bpf_verifier_state *parent;
	u32 branches;
	u32 insn_idx;
	u32 curframe;
	u32 active_spin_lock;
	bool speculative;
	u32 first_insn_idx;
	u32 last_insn_idx;
	struct bpf_idx_pair *jmp_history;
	u32 jmp_history_cnt;
};

struct bpf_verifier_state_list {
	struct bpf_verifier_state state;
	struct bpf_verifier_state_list *next;
	int miss_cnt;
	int hit_cnt;
};

struct bpf_insn_aux_data {
	union {
		enum bpf_reg_type ptr_type;
		long unsigned int map_ptr_state;
		s32 call_imm;
		u32 alu_limit;
		struct {
			u32 map_index;
			u32 map_off;
		};
	};
	u64 map_key_state;
	int ctx_field_size;
	int sanitize_stack_off;
	u32 seen;
	bool zext_dst;
	u8 alu_state;
	unsigned int orig_idx;
	bool prune_point;
};

struct bpf_verifier_stack_elem {
	struct bpf_verifier_state st;
	int insn_idx;
	int prev_insn_idx;
	struct bpf_verifier_stack_elem *next;
	u32 log_pos;
};

typedef void (*bpf_insn_print_t)(void *, const char *, ...);

typedef const char * (*bpf_insn_revmap_call_t)(void *, const struct bpf_insn *);

typedef const char * (*bpf_insn_print_imm_t)(void *, const struct bpf_insn *, __u64);

struct bpf_insn_cbs {
	bpf_insn_print_t cb_print;
	bpf_insn_revmap_call_t cb_call;
	bpf_insn_print_imm_t cb_imm;
	void *private_data;
};

struct bpf_call_arg_meta {
	struct bpf_map *map_ptr;
	bool raw_mode;
	bool pkt_access;
	int regno;
	int access_size;
	int mem_size;
	u64 msize_max_value;
	int ref_obj_id;
	int func_id;
	u32 btf_id;
};

enum reg_arg_type {
	SRC_OP = 0,
	DST_OP = 1,
	DST_OP_NO_MARK = 2,
};

enum {
	DISCOVERED = 16,
	EXPLORED = 32,
	FALLTHROUGH = 1,
	BRANCH = 2,
};

struct idpair {
	u32 old;
	u32 cur;
};

struct tree_descr {
	const char *name;
	const struct file_operations *ops;
	int mode;
};

enum bpf_type {
	BPF_TYPE_UNSPEC = 0,
	BPF_TYPE_PROG = 1,
	BPF_TYPE_MAP = 2,
	BPF_TYPE_LINK = 3,
};

struct map_iter {
	void *key;
	bool done;
};

enum {
	OPT_MODE = 0,
};

struct bpf_mount_opts {
	umode_t mode;
};

struct bpf_pidns_info {
	__u32 pid;
	__u32 tgid;
};

typedef u64 (*btf_bpf_map_lookup_elem)(struct bpf_map *, void *);

typedef u64 (*btf_bpf_map_update_elem)(struct bpf_map *, void *, void *, u64);

typedef u64 (*btf_bpf_map_delete_elem)(struct bpf_map *, void *);

typedef u64 (*btf_bpf_map_push_elem)(struct bpf_map *, void *, u64);

typedef u64 (*btf_bpf_map_pop_elem)(struct bpf_map *, void *);

typedef u64 (*btf_bpf_map_peek_elem)(struct bpf_map *, void *);

typedef u64 (*btf_bpf_get_smp_processor_id)();

typedef u64 (*btf_bpf_get_numa_node_id)();

typedef u64 (*btf_bpf_ktime_get_ns)();

typedef u64 (*btf_bpf_ktime_get_boot_ns)();

typedef u64 (*btf_bpf_get_current_pid_tgid)();

typedef u64 (*btf_bpf_get_current_uid_gid)();

typedef u64 (*btf_bpf_get_current_comm)(char *, u32);

typedef u64 (*btf_bpf_spin_lock)(struct bpf_spin_lock *);

typedef u64 (*btf_bpf_spin_unlock)(struct bpf_spin_lock *);

typedef u64 (*btf_bpf_jiffies64)();

typedef u64 (*btf_bpf_get_current_cgroup_id)();

typedef u64 (*btf_bpf_get_current_ancestor_cgroup_id)(int);

typedef u64 (*btf_bpf_get_local_storage)(struct bpf_map *, u64);

typedef u64 (*btf_bpf_strtol)(const char *, size_t, u64, long int *);

typedef u64 (*btf_bpf_strtoul)(const char *, size_t, u64, long unsigned int *);

typedef u64 (*btf_bpf_get_ns_current_pid_tgid)(u64, u64, struct bpf_pidns_info *, u32);

typedef u64 (*btf_bpf_event_output_data)(void *, struct bpf_map *, u64, void *, u64);

typedef int (*bpf_iter_init_seq_priv_t)(void *);

typedef void (*bpf_iter_fini_seq_priv_t)(void *);

struct bpf_iter_reg {
	const char *target;
	const struct seq_operations *seq_ops;
	bpf_iter_init_seq_priv_t init_seq_private;
	bpf_iter_fini_seq_priv_t fini_seq_private;
	u32 seq_priv_size;
	u32 ctx_arg_info_size;
	struct bpf_ctx_arg_aux ctx_arg_info[2];
};

struct bpf_iter_meta {
	union {
		struct seq_file *seq;
	};
	u64 session_id;
	u64 seq_num;
};

struct bpf_iter_target_info {
	struct list_head list;
	const struct bpf_iter_reg *reg_info;
	u32 btf_id;
};

struct bpf_iter_link {
	struct bpf_link link;
	struct bpf_iter_target_info *tinfo;
};

struct bpf_iter_priv_data {
	struct bpf_iter_target_info *tinfo;
	struct bpf_prog *prog;
	u64 session_id;
	u64 seq_num;
	bool done_stop;
	long: 56;
	u8 target_private[0];
};

struct bpf_iter_seq_map_info {
	u32 mid;
};

struct bpf_iter__bpf_map {
	union {
		struct bpf_iter_meta *meta;
	};
	union {
		struct bpf_map *map;
	};
};

struct bpf_iter_seq_task_common {
	struct pid_namespace *ns;
};

struct bpf_iter_seq_task_info {
	struct bpf_iter_seq_task_common common;
	u32 tid;
};

struct bpf_iter__task {
	union {
		struct bpf_iter_meta *meta;
	};
	union {
		struct task_struct *task;
	};
};

struct bpf_iter_seq_task_file_info {
	struct bpf_iter_seq_task_common common;
	struct task_struct *task;
	struct files_struct *files;
	u32 tid;
	u32 fd;
};

struct bpf_iter__task_file {
	union {
		struct bpf_iter_meta *meta;
	};
	union {
		struct task_struct *task;
	};
	u32 fd;
	union {
		struct file *file;
	};
};

struct pcpu_freelist_node;

struct pcpu_freelist_head {
	struct pcpu_freelist_node *first;
	raw_spinlock_t lock;
};

struct pcpu_freelist_node {
	struct pcpu_freelist_node *next;
};

struct pcpu_freelist {
	struct pcpu_freelist_head *freelist;
};

struct bpf_lru_node {
	struct list_head list;
	u16 cpu;
	u8 type;
	u8 ref;
};

struct bpf_lru_list {
	struct list_head lists[3];
	unsigned int counts[2];
	struct list_head *next_inactive_rotation;
	raw_spinlock_t lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_lru_locallist {
	struct list_head lists[2];
	u16 next_steal;
	raw_spinlock_t lock;
};

struct bpf_common_lru {
	struct bpf_lru_list lru_list;
	struct bpf_lru_locallist *local_list;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

typedef bool (*del_from_htab_func)(void *, struct bpf_lru_node *);

struct bpf_lru {
	union {
		struct bpf_common_lru common_lru;
		struct bpf_lru_list *percpu_lru;
	};
	del_from_htab_func del_from_htab;
	void *del_arg;
	unsigned int hash_offset;
	unsigned int nr_scans;
	bool percpu;
	long: 56;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct bucket {
	struct hlist_nulls_head head;
	union {
		raw_spinlock_t raw_lock;
		spinlock_t lock;
	};
};

struct htab_elem;

struct bpf_htab {
	struct bpf_map map;
	struct bucket *buckets;
	void *elems;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	union {
		struct pcpu_freelist freelist;
		struct bpf_lru lru;
	};
	struct htab_elem **extra_elems;
	atomic_t count;
	u32 n_buckets;
	u32 elem_size;
	u32 hashrnd;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct htab_elem {
	union {
		struct hlist_nulls_node hash_node;
		struct {
			void *padding;
			union {
				struct bpf_htab *htab;
				struct pcpu_freelist_node fnode;
				struct htab_elem *batch_flink;
			};
		};
	};
	union {
		struct callback_head rcu;
		struct bpf_lru_node lru_node;
	};
	u32 hash;
	int: 32;
	char key[0];
};

struct prog_poke_elem {
	struct list_head list;
	struct bpf_prog_aux *aux;
};

enum bpf_lru_list_type {
	BPF_LRU_LIST_T_ACTIVE = 0,
	BPF_LRU_LIST_T_INACTIVE = 1,
	BPF_LRU_LIST_T_FREE = 2,
	BPF_LRU_LOCAL_LIST_T_FREE = 3,
	BPF_LRU_LOCAL_LIST_T_PENDING = 4,
};

struct bpf_lpm_trie_key {
	__u32 prefixlen;
	__u8 data[0];
};

struct lpm_trie_node {
	struct callback_head rcu;
	struct lpm_trie_node *child[2];
	u32 prefixlen;
	u32 flags;
	u8 data[0];
};

struct lpm_trie {
	struct bpf_map map;
	struct lpm_trie_node *root;
	size_t n_entries;
	size_t max_prefixlen;
	size_t data_size;
	spinlock_t lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_cgroup_storage_map {
	struct bpf_map map;
	spinlock_t lock;
	struct bpf_prog_aux *aux;
	struct rb_root root;
	struct list_head list;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_queue_stack {
	struct bpf_map map;
	raw_spinlock_t lock;
	u32 head;
	u32 tail;
	u32 size;
	char elements[0];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum {
	BPF_RB_NO_WAKEUP = 1,
	BPF_RB_FORCE_WAKEUP = 2,
};

enum {
	BPF_RB_AVAIL_DATA = 0,
	BPF_RB_RING_SIZE = 1,
	BPF_RB_CONS_POS = 2,
	BPF_RB_PROD_POS = 3,
};

enum {
	BPF_RINGBUF_BUSY_BIT = 2147483648,
	BPF_RINGBUF_DISCARD_BIT = 1073741824,
	BPF_RINGBUF_HDR_SZ = 8,
};

struct bpf_ringbuf {
	wait_queue_head_t waitq;
	struct irq_work work;
	u64 mask;
	struct page **pages;
	int nr_pages;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t spinlock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int consumer_pos;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int producer_pos;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	char data[0];
};

struct bpf_ringbuf_map {
	struct bpf_map map;
	struct bpf_map_memory memory;
	struct bpf_ringbuf *rb;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_ringbuf_hdr {
	u32 len;
	u32 pg_off;
};

typedef u64 (*btf_bpf_ringbuf_reserve)(struct bpf_map *, u64, u64);

typedef u64 (*btf_bpf_ringbuf_submit)(void *, u64);

typedef u64 (*btf_bpf_ringbuf_discard)(void *, u64);

typedef u64 (*btf_bpf_ringbuf_output)(struct bpf_map *, void *, u64, u64);

typedef u64 (*btf_bpf_ringbuf_query)(struct bpf_map *, u64);

enum perf_record_ksymbol_type {
	PERF_RECORD_KSYMBOL_TYPE_UNKNOWN = 0,
	PERF_RECORD_KSYMBOL_TYPE_BPF = 1,
	PERF_RECORD_KSYMBOL_TYPE_MAX = 2,
};

struct btf_enum {
	__u32 name_off;
	__s32 val;
};

struct btf_array {
	__u32 type;
	__u32 index_type;
	__u32 nelems;
};

struct btf_param {
	__u32 name_off;
	__u32 type;
};

enum {
	BTF_VAR_STATIC = 0,
	BTF_VAR_GLOBAL_ALLOCATED = 1,
	BTF_VAR_GLOBAL_EXTERN = 2,
};

struct btf_var {
	__u32 linkage;
};

struct btf_var_secinfo {
	__u32 type;
	__u32 offset;
	__u32 size;
};

struct bpf_flow_keys {
	__u16 nhoff;
	__u16 thoff;
	__u16 addr_proto;
	__u8 is_frag;
	__u8 is_first_frag;
	__u8 is_encap;
	__u8 ip_proto;
	__be16 n_proto;
	__be16 sport;
	__be16 dport;
	union {
		struct {
			__be32 ipv4_src;
			__be32 ipv4_dst;
		};
		struct {
			__u32 ipv6_src[4];
			__u32 ipv6_dst[4];
		};
	};
	__u32 flags;
	__be32 flow_label;
};

struct bpf_sock {
	__u32 bound_dev_if;
	__u32 family;
	__u32 type;
	__u32 protocol;
	__u32 mark;
	__u32 priority;
	__u32 src_ip4;
	__u32 src_ip6[4];
	__u32 src_port;
	__u32 dst_port;
	__u32 dst_ip4;
	__u32 dst_ip6[4];
	__u32 state;
	__s32 rx_queue_mapping;
};

struct __sk_buff {
	__u32 len;
	__u32 pkt_type;
	__u32 mark;
	__u32 queue_mapping;
	__u32 protocol;
	__u32 vlan_present;
	__u32 vlan_tci;
	__u32 vlan_proto;
	__u32 priority;
	__u32 ingress_ifindex;
	__u32 ifindex;
	__u32 tc_index;
	__u32 cb[5];
	__u32 hash;
	__u32 tc_classid;
	__u32 data;
	__u32 data_end;
	__u32 napi_id;
	__u32 family;
	__u32 remote_ip4;
	__u32 local_ip4;
	__u32 remote_ip6[4];
	__u32 local_ip6[4];
	__u32 remote_port;
	__u32 local_port;
	__u32 data_meta;
	union {
		struct bpf_flow_keys *flow_keys;
	};
	__u64 tstamp;
	__u32 wire_len;
	__u32 gso_segs;
	union {
		struct bpf_sock *sk;
	};
	__u32 gso_size;
};

struct xdp_md {
	__u32 data;
	__u32 data_end;
	__u32 data_meta;
	__u32 ingress_ifindex;
	__u32 rx_queue_index;
	__u32 egress_ifindex;
};

struct sk_msg_md {
	union {
		void *data;
	};
	union {
		void *data_end;
	};
	__u32 family;
	__u32 remote_ip4;
	__u32 local_ip4;
	__u32 remote_ip6[4];
	__u32 local_ip6[4];
	__u32 remote_port;
	__u32 local_port;
	__u32 size;
	union {
		struct bpf_sock *sk;
	};
};

struct sk_reuseport_md {
	union {
		void *data;
	};
	union {
		void *data_end;
	};
	__u32 len;
	__u32 eth_protocol;
	__u32 ip_protocol;
	__u32 bind_inany;
	__u32 hash;
};

struct bpf_sock_addr {
	__u32 user_family;
	__u32 user_ip4;
	__u32 user_ip6[4];
	__u32 user_port;
	__u32 family;
	__u32 type;
	__u32 protocol;
	__u32 msg_src_ip4;
	__u32 msg_src_ip6[4];
	union {
		struct bpf_sock *sk;
	};
};

struct bpf_sock_ops {
	__u32 op;
	union {
		__u32 args[4];
		__u32 reply;
		__u32 replylong[4];
	};
	__u32 family;
	__u32 remote_ip4;
	__u32 local_ip4;
	__u32 remote_ip6[4];
	__u32 local_ip6[4];
	__u32 remote_port;
	__u32 local_port;
	__u32 is_fullsock;
	__u32 snd_cwnd;
	__u32 srtt_us;
	__u32 bpf_sock_ops_cb_flags;
	__u32 state;
	__u32 rtt_min;
	__u32 snd_ssthresh;
	__u32 rcv_nxt;
	__u32 snd_nxt;
	__u32 snd_una;
	__u32 mss_cache;
	__u32 ecn_flags;
	__u32 rate_delivered;
	__u32 rate_interval_us;
	__u32 packets_out;
	__u32 retrans_out;
	__u32 total_retrans;
	__u32 segs_in;
	__u32 data_segs_in;
	__u32 segs_out;
	__u32 data_segs_out;
	__u32 lost_out;
	__u32 sacked_out;
	__u32 sk_txhash;
	__u64 bytes_received;
	__u64 bytes_acked;
	union {
		struct bpf_sock *sk;
	};
};

struct bpf_cgroup_dev_ctx {
	__u32 access_type;
	__u32 major;
	__u32 minor;
};

struct bpf_sysctl {
	__u32 write;
	__u32 file_pos;
};

struct bpf_sockopt {
	union {
		struct bpf_sock *sk;
	};
	union {
		void *optval;
	};
	union {
		void *optval_end;
	};
	__s32 level;
	__s32 optname;
	__s32 optlen;
	__s32 retval;
};

struct sk_reuseport_kern {
	struct sk_buff *skb;
	struct sock *sk;
	struct sock *selected_sk;
	void *data_end;
	u32 hash;
	u32 reuseport_id;
	bool bind_inany;
};

struct bpf_flow_dissector {
	struct bpf_flow_keys *flow_keys;
	const struct sk_buff *skb;
	void *data;
	void *data_end;
};

struct inet_listen_hashbucket {
	spinlock_t lock;
	unsigned int count;
	union {
		struct hlist_head head;
		struct hlist_nulls_head nulls_head;
	};
};

struct inet_ehash_bucket;

struct inet_bind_hashbucket;

struct inet_hashinfo {
	struct inet_ehash_bucket *ehash;
	spinlock_t *ehash_locks;
	unsigned int ehash_mask;
	unsigned int ehash_locks_mask;
	struct kmem_cache *bind_bucket_cachep;
	struct inet_bind_hashbucket *bhash;
	unsigned int bhash_size;
	unsigned int lhash2_mask;
	struct inet_listen_hashbucket *lhash2;
	long: 64;
	struct inet_listen_hashbucket listening_hash[32];
};

struct ip_ra_chain {
	struct ip_ra_chain *next;
	struct sock *sk;
	union {
		void (*destructor)(struct sock *);
		struct sock *saved_sk;
	};
	struct callback_head rcu;
};

struct fib_table {
	struct hlist_node tb_hlist;
	u32 tb_id;
	int tb_num_default;
	struct callback_head rcu;
	long unsigned int *tb_data;
	long unsigned int __data[0];
};

struct inet_peer_base {
	struct rb_root rb_root;
	seqlock_t lock;
	int total;
};

struct tcp_fastopen_context {
	siphash_key_t key[2];
	int num;
	struct callback_head rcu;
};

struct in_addr {
	__be32 s_addr;
};

struct xdp_txq_info {
	struct net_device *dev;
};

struct xdp_buff {
	void *data;
	void *data_end;
	void *data_meta;
	void *data_hard_start;
	struct xdp_rxq_info *rxq;
	struct xdp_txq_info *txq;
	u32 frame_sz;
};

struct bpf_sock_addr_kern {
	struct sock *sk;
	struct sockaddr *uaddr;
	u64 tmp_reg;
	void *t_ctx;
};

struct bpf_sock_ops_kern {
	struct sock *sk;
	u32 op;
	union {
		u32 args[4];
		u32 reply;
		u32 replylong[4];
	};
	u32 is_fullsock;
	u64 temp;
};

struct bpf_sysctl_kern {
	struct ctl_table_header *head;
	struct ctl_table *table;
	void *cur_val;
	size_t cur_len;
	void *new_val;
	size_t new_len;
	int new_updated;
	int write;
	loff_t *ppos;
	u64 tmp_reg;
};

struct bpf_sockopt_kern {
	struct sock *sk;
	u8 *optval;
	u8 *optval_end;
	s32 level;
	s32 optname;
	s32 optlen;
	s32 retval;
};

struct sock_reuseport {
	struct callback_head rcu;
	u16 max_socks;
	u16 num_socks;
	unsigned int synq_overflow_ts;
	unsigned int reuseport_id;
	unsigned int bind_inany: 1;
	unsigned int has_conns: 1;
	struct bpf_prog *prog;
	struct sock *socks[0];
};

struct tcp_fastopen_cookie {
	__le64 val[2];
	s8 len;
	bool exp;
};

enum tcp_synack_type {
	TCP_SYNACK_NORMAL = 0,
	TCP_SYNACK_FASTOPEN = 1,
	TCP_SYNACK_COOKIE = 2,
};

struct tcp_md5sig_key;

struct tcp_request_sock_ops {
	u16 mss_clamp;
	struct tcp_md5sig_key * (*req_md5_lookup)(const struct sock *, const struct sock *);
	int (*calc_md5_hash)(char *, const struct tcp_md5sig_key *, const struct sock *, const struct sk_buff *);
	void (*init_req)(struct request_sock *, const struct sock *, struct sk_buff *);
	__u32 (*cookie_init_seq)(const struct sk_buff *, __u16 *);
	struct dst_entry * (*route_req)(const struct sock *, struct flowi *, const struct request_sock *);
	u32 (*init_seq)(const struct sk_buff *);
	u32 (*init_ts_off)(const struct net *, const struct sk_buff *);
	int (*send_synack)(const struct sock *, struct dst_entry *, struct flowi *, struct request_sock *, struct tcp_fastopen_cookie *, enum tcp_synack_type);
};

union tcp_md5_addr {
	struct in_addr a4;
	struct in6_addr a6;
};

struct tcp_md5sig_key {
	struct hlist_node node;
	u8 keylen;
	u8 family;
	u8 prefixlen;
	union tcp_md5_addr addr;
	int l3index;
	u8 key[80];
	struct callback_head rcu;
};

struct ip_rt_acct {
	__u32 o_bytes;
	__u32 o_packets;
	__u32 i_bytes;
	__u32 i_packets;
};

struct inet_ehash_bucket {
	struct hlist_nulls_head chain;
};

struct inet_bind_hashbucket {
	spinlock_t lock;
	struct hlist_head chain;
};

struct ack_sample {
	u32 pkts_acked;
	s32 rtt_us;
	u32 in_flight;
};

struct rate_sample {
	u64 prior_mstamp;
	u32 prior_delivered;
	s32 delivered;
	long int interval_us;
	u32 snd_interval_us;
	u32 rcv_interval_us;
	long int rtt_us;
	int losses;
	u32 acked_sacked;
	u32 prior_in_flight;
	bool is_app_limited;
	bool is_retrans;
	bool is_ack_delayed;
};

struct sk_msg_sg {
	u32 start;
	u32 curr;
	u32 end;
	u32 size;
	u32 copybreak;
	long unsigned int copy;
	struct scatterlist data[19];
};

struct sk_msg {
	struct sk_msg_sg sg;
	void *data;
	void *data_end;
	u32 apply_bytes;
	u32 cork_bytes;
	u32 flags;
	struct sk_buff *skb;
	struct sock *sk_redir;
	struct sock *sk;
	struct list_head list;
};

enum verifier_phase {
	CHECK_META = 0,
	CHECK_TYPE = 1,
};

struct resolve_vertex {
	const struct btf_type *t;
	u32 type_id;
	u16 next_member;
};

enum visit_state {
	NOT_VISITED = 0,
	VISITED = 1,
	RESOLVED = 2,
};

enum resolve_mode {
	RESOLVE_TBD = 0,
	RESOLVE_PTR = 1,
	RESOLVE_STRUCT_OR_ARRAY = 2,
};

struct btf_sec_info {
	u32 off;
	u32 len;
};

struct btf_verifier_env {
	struct btf *btf;
	u8 *visit_states;
	struct resolve_vertex stack[32];
	struct bpf_verifier_log log;
	u32 log_type_id;
	u32 top_stack;
	enum verifier_phase phase;
	enum resolve_mode resolve_mode;
};

struct btf_kind_operations {
	s32 (*check_meta)(struct btf_verifier_env *, const struct btf_type *, u32);
	int (*resolve)(struct btf_verifier_env *, const struct resolve_vertex *);
	int (*check_member)(struct btf_verifier_env *, const struct btf_type *, const struct btf_member *, const struct btf_type *);
	int (*check_kflag_member)(struct btf_verifier_env *, const struct btf_type *, const struct btf_member *, const struct btf_type *);
	void (*log_details)(struct btf_verifier_env *, const struct btf_type *);
	void (*seq_show)(const struct btf *, const struct btf_type *, u32, void *, u8, struct seq_file *);
};

struct bpf_ctx_convert {
	struct __sk_buff BPF_PROG_TYPE_SOCKET_FILTER_prog;
	struct sk_buff BPF_PROG_TYPE_SOCKET_FILTER_kern;
	struct __sk_buff BPF_PROG_TYPE_SCHED_CLS_prog;
	struct sk_buff BPF_PROG_TYPE_SCHED_CLS_kern;
	struct __sk_buff BPF_PROG_TYPE_SCHED_ACT_prog;
	struct sk_buff BPF_PROG_TYPE_SCHED_ACT_kern;
	struct xdp_md BPF_PROG_TYPE_XDP_prog;
	struct xdp_buff BPF_PROG_TYPE_XDP_kern;
	struct __sk_buff BPF_PROG_TYPE_CGROUP_SKB_prog;
	struct sk_buff BPF_PROG_TYPE_CGROUP_SKB_kern;
	struct bpf_sock BPF_PROG_TYPE_CGROUP_SOCK_prog;
	struct sock BPF_PROG_TYPE_CGROUP_SOCK_kern;
	struct bpf_sock_addr BPF_PROG_TYPE_CGROUP_SOCK_ADDR_prog;
	struct bpf_sock_addr_kern BPF_PROG_TYPE_CGROUP_SOCK_ADDR_kern;
	struct __sk_buff BPF_PROG_TYPE_LWT_IN_prog;
	struct sk_buff BPF_PROG_TYPE_LWT_IN_kern;
	struct __sk_buff BPF_PROG_TYPE_LWT_OUT_prog;
	struct sk_buff BPF_PROG_TYPE_LWT_OUT_kern;
	struct __sk_buff BPF_PROG_TYPE_LWT_XMIT_prog;
	struct sk_buff BPF_PROG_TYPE_LWT_XMIT_kern;
	struct __sk_buff BPF_PROG_TYPE_LWT_SEG6LOCAL_prog;
	struct sk_buff BPF_PROG_TYPE_LWT_SEG6LOCAL_kern;
	struct bpf_sock_ops BPF_PROG_TYPE_SOCK_OPS_prog;
	struct bpf_sock_ops_kern BPF_PROG_TYPE_SOCK_OPS_kern;
	struct __sk_buff BPF_PROG_TYPE_SK_SKB_prog;
	struct sk_buff BPF_PROG_TYPE_SK_SKB_kern;
	struct sk_msg_md BPF_PROG_TYPE_SK_MSG_prog;
	struct sk_msg BPF_PROG_TYPE_SK_MSG_kern;
	struct __sk_buff BPF_PROG_TYPE_FLOW_DISSECTOR_prog;
	struct bpf_flow_dissector BPF_PROG_TYPE_FLOW_DISSECTOR_kern;
	bpf_user_pt_regs_t BPF_PROG_TYPE_KPROBE_prog;
	struct pt_regs BPF_PROG_TYPE_KPROBE_kern;
	__u64 BPF_PROG_TYPE_TRACEPOINT_prog;
	u64 BPF_PROG_TYPE_TRACEPOINT_kern;
	struct bpf_perf_event_data BPF_PROG_TYPE_PERF_EVENT_prog;
	struct bpf_perf_event_data_kern BPF_PROG_TYPE_PERF_EVENT_kern;
	struct bpf_raw_tracepoint_args BPF_PROG_TYPE_RAW_TRACEPOINT_prog;
	u64 BPF_PROG_TYPE_RAW_TRACEPOINT_kern;
	struct bpf_raw_tracepoint_args BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE_prog;
	u64 BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE_kern;
	void *BPF_PROG_TYPE_TRACING_prog;
	void *BPF_PROG_TYPE_TRACING_kern;
	struct bpf_cgroup_dev_ctx BPF_PROG_TYPE_CGROUP_DEVICE_prog;
	struct bpf_cgroup_dev_ctx BPF_PROG_TYPE_CGROUP_DEVICE_kern;
	struct bpf_sysctl BPF_PROG_TYPE_CGROUP_SYSCTL_prog;
	struct bpf_sysctl_kern BPF_PROG_TYPE_CGROUP_SYSCTL_kern;
	struct bpf_sockopt BPF_PROG_TYPE_CGROUP_SOCKOPT_prog;
	struct bpf_sockopt_kern BPF_PROG_TYPE_CGROUP_SOCKOPT_kern;
	struct sk_reuseport_md BPF_PROG_TYPE_SK_REUSEPORT_prog;
	struct sk_reuseport_kern BPF_PROG_TYPE_SK_REUSEPORT_kern;
	void *BPF_PROG_TYPE_STRUCT_OPS_prog;
	void *BPF_PROG_TYPE_STRUCT_OPS_kern;
	void *BPF_PROG_TYPE_EXT_prog;
	void *BPF_PROG_TYPE_EXT_kern;
};

enum {
	__ctx_convertBPF_PROG_TYPE_SOCKET_FILTER = 0,
	__ctx_convertBPF_PROG_TYPE_SCHED_CLS = 1,
	__ctx_convertBPF_PROG_TYPE_SCHED_ACT = 2,
	__ctx_convertBPF_PROG_TYPE_XDP = 3,
	__ctx_convertBPF_PROG_TYPE_CGROUP_SKB = 4,
	__ctx_convertBPF_PROG_TYPE_CGROUP_SOCK = 5,
	__ctx_convertBPF_PROG_TYPE_CGROUP_SOCK_ADDR = 6,
	__ctx_convertBPF_PROG_TYPE_LWT_IN = 7,
	__ctx_convertBPF_PROG_TYPE_LWT_OUT = 8,
	__ctx_convertBPF_PROG_TYPE_LWT_XMIT = 9,
	__ctx_convertBPF_PROG_TYPE_LWT_SEG6LOCAL = 10,
	__ctx_convertBPF_PROG_TYPE_SOCK_OPS = 11,
	__ctx_convertBPF_PROG_TYPE_SK_SKB = 12,
	__ctx_convertBPF_PROG_TYPE_SK_MSG = 13,
	__ctx_convertBPF_PROG_TYPE_FLOW_DISSECTOR = 14,
	__ctx_convertBPF_PROG_TYPE_KPROBE = 15,
	__ctx_convertBPF_PROG_TYPE_TRACEPOINT = 16,
	__ctx_convertBPF_PROG_TYPE_PERF_EVENT = 17,
	__ctx_convertBPF_PROG_TYPE_RAW_TRACEPOINT = 18,
	__ctx_convertBPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE = 19,
	__ctx_convertBPF_PROG_TYPE_TRACING = 20,
	__ctx_convertBPF_PROG_TYPE_CGROUP_DEVICE = 21,
	__ctx_convertBPF_PROG_TYPE_CGROUP_SYSCTL = 22,
	__ctx_convertBPF_PROG_TYPE_CGROUP_SOCKOPT = 23,
	__ctx_convertBPF_PROG_TYPE_SK_REUSEPORT = 24,
	__ctx_convertBPF_PROG_TYPE_STRUCT_OPS = 25,
	__ctx_convertBPF_PROG_TYPE_EXT = 26,
	__ctx_convert_unused = 27,
};

struct bpf_devmap_val {
	__u32 ifindex;
	union {
		int fd;
		__u32 id;
	} bpf_prog;
};

enum net_device_flags {
	IFF_UP = 1,
	IFF_BROADCAST = 2,
	IFF_DEBUG = 4,
	IFF_LOOPBACK = 8,
	IFF_POINTOPOINT = 16,
	IFF_NOTRAILERS = 32,
	IFF_RUNNING = 64,
	IFF_NOARP = 128,
	IFF_PROMISC = 256,
	IFF_ALLMULTI = 512,
	IFF_MASTER = 1024,
	IFF_SLAVE = 2048,
	IFF_MULTICAST = 4096,
	IFF_PORTSEL = 8192,
	IFF_AUTOMEDIA = 16384,
	IFF_DYNAMIC = 32768,
	IFF_LOWER_UP = 65536,
	IFF_DORMANT = 131072,
	IFF_ECHO = 262144,
};

struct xdp_dev_bulk_queue {
	struct xdp_frame *q[16];
	struct list_head flush_node;
	struct net_device *dev;
	struct net_device *dev_rx;
	unsigned int count;
};

enum netdev_cmd {
	NETDEV_UP = 1,
	NETDEV_DOWN = 2,
	NETDEV_REBOOT = 3,
	NETDEV_CHANGE = 4,
	NETDEV_REGISTER = 5,
	NETDEV_UNREGISTER = 6,
	NETDEV_CHANGEMTU = 7,
	NETDEV_CHANGEADDR = 8,
	NETDEV_PRE_CHANGEADDR = 9,
	NETDEV_GOING_DOWN = 10,
	NETDEV_CHANGENAME = 11,
	NETDEV_FEAT_CHANGE = 12,
	NETDEV_BONDING_FAILOVER = 13,
	NETDEV_PRE_UP = 14,
	NETDEV_PRE_TYPE_CHANGE = 15,
	NETDEV_POST_TYPE_CHANGE = 16,
	NETDEV_POST_INIT = 17,
	NETDEV_RELEASE = 18,
	NETDEV_NOTIFY_PEERS = 19,
	NETDEV_JOIN = 20,
	NETDEV_CHANGEUPPER = 21,
	NETDEV_RESEND_IGMP = 22,
	NETDEV_PRECHANGEMTU = 23,
	NETDEV_CHANGEINFODATA = 24,
	NETDEV_BONDING_INFO = 25,
	NETDEV_PRECHANGEUPPER = 26,
	NETDEV_CHANGELOWERSTATE = 27,
	NETDEV_UDP_TUNNEL_PUSH_INFO = 28,
	NETDEV_UDP_TUNNEL_DROP_INFO = 29,
	NETDEV_CHANGE_TX_QUEUE_LEN = 30,
	NETDEV_CVLAN_FILTER_PUSH_INFO = 31,
	NETDEV_CVLAN_FILTER_DROP_INFO = 32,
	NETDEV_SVLAN_FILTER_PUSH_INFO = 33,
	NETDEV_SVLAN_FILTER_DROP_INFO = 34,
};

struct netdev_notifier_info {
	struct net_device *dev;
	struct netlink_ext_ack *extack;
};

struct bpf_dtab;

struct bpf_dtab_netdev {
	struct net_device *dev;
	struct hlist_node index_hlist;
	struct bpf_dtab *dtab;
	struct bpf_prog *xdp_prog;
	struct callback_head rcu;
	unsigned int idx;
	struct bpf_devmap_val val;
};

struct bpf_dtab {
	struct bpf_map map;
	struct bpf_dtab_netdev **netdev_map;
	struct list_head list;
	struct hlist_head *dev_index_head;
	spinlock_t index_lock;
	unsigned int items;
	u32 n_buckets;
	long: 32;
	long: 64;
	long: 64;
};

typedef struct bio_vec skb_frag_t;

struct skb_shared_hwtstamps {
	ktime_t hwtstamp;
};

struct skb_shared_info {
	__u8 __unused;
	__u8 meta_len;
	__u8 nr_frags;
	__u8 tx_flags;
	short unsigned int gso_size;
	short unsigned int gso_segs;
	struct sk_buff *frag_list;
	struct skb_shared_hwtstamps hwtstamps;
	unsigned int gso_type;
	u32 tskey;
	atomic_t dataref;
	void *destructor_arg;
	skb_frag_t frags[17];
};

struct ptr_ring {
	int producer;
	spinlock_t producer_lock;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	int consumer_head;
	int consumer_tail;
	spinlock_t consumer_lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	int size;
	int batch;
	void **queue;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_cpu_map_entry;

struct xdp_bulk_queue {
	void *q[8];
	struct list_head flush_node;
	struct bpf_cpu_map_entry *obj;
	unsigned int count;
};

struct bpf_cpu_map;

struct bpf_cpu_map_entry {
	u32 cpu;
	int map_id;
	u32 qsize;
	struct xdp_bulk_queue *bulkq;
	struct bpf_cpu_map *cmap;
	struct ptr_ring *queue;
	struct task_struct *kthread;
	struct work_struct kthread_stop_wq;
	atomic_t refcnt;
	struct callback_head rcu;
};

struct bpf_cpu_map {
	struct bpf_map map;
	struct bpf_cpu_map_entry **cpu_map;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct rhlist_head {
	struct rhash_head rhead;
	struct rhlist_head *next;
};

struct bpf_prog_offload_ops {
	int (*insn_hook)(struct bpf_verifier_env *, int, int);
	int (*finalize)(struct bpf_verifier_env *);
	int (*replace_insn)(struct bpf_verifier_env *, u32, struct bpf_insn *);
	int (*remove_insns)(struct bpf_verifier_env *, u32, u32);
	int (*prepare)(struct bpf_prog *);
	int (*translate)(struct bpf_prog *);
	void (*destroy)(struct bpf_prog *);
};

struct bpf_offload_dev {
	const struct bpf_prog_offload_ops *ops;
	struct list_head netdevs;
	void *priv;
};

struct bpf_offload_netdev {
	struct rhash_head l;
	struct net_device *netdev;
	struct bpf_offload_dev *offdev;
	struct list_head progs;
	struct list_head maps;
	struct list_head offdev_netdevs;
};

struct ns_get_path_bpf_prog_args {
	struct bpf_prog *prog;
	struct bpf_prog_info *info;
};

struct ns_get_path_bpf_map_args {
	struct bpf_offloaded_map *offmap;
	struct bpf_map_info *info;
};

struct bpf_netns_link {
	struct bpf_link link;
	enum bpf_attach_type type;
	enum netns_bpf_attach_type netns_type;
	struct net *net;
	struct list_head node;
};

enum bpf_stack_build_id_status {
	BPF_STACK_BUILD_ID_EMPTY = 0,
	BPF_STACK_BUILD_ID_VALID = 1,
	BPF_STACK_BUILD_ID_IP = 2,
};

struct bpf_stack_build_id {
	__s32 status;
	unsigned char build_id[20];
	union {
		__u64 offset;
		__u64 ip;
	};
};

enum {
	BPF_F_SKIP_FIELD_MASK = 255,
	BPF_F_USER_STACK = 256,
	BPF_F_FAST_STACK_CMP = 512,
	BPF_F_REUSE_STACKID = 1024,
	BPF_F_USER_BUILD_ID = 2048,
};

typedef __u32 Elf32_Addr;

typedef __u16 Elf32_Half;

typedef __u32 Elf32_Off;

struct elf32_hdr {
	unsigned char e_ident[16];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
};

typedef struct elf32_hdr Elf32_Ehdr;

struct elf32_phdr {
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;
};

typedef struct elf32_phdr Elf32_Phdr;

struct elf64_phdr {
	Elf64_Word p_type;
	Elf64_Word p_flags;
	Elf64_Off p_offset;
	Elf64_Addr p_vaddr;
	Elf64_Addr p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
};

typedef struct elf64_phdr Elf64_Phdr;

typedef struct elf32_note Elf32_Nhdr;

struct stack_map_bucket {
	struct pcpu_freelist_node fnode;
	u32 hash;
	u32 nr;
	u64 data[0];
};

struct bpf_stack_map {
	struct bpf_map map;
	void *elems;
	struct pcpu_freelist freelist;
	u32 n_buckets;
	struct stack_map_bucket *buckets[0];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct stack_map_irq_work {
	struct irq_work irq_work;
	struct mm_struct *mm;
};

typedef u64 (*btf_bpf_get_stackid)(struct pt_regs *, struct bpf_map *, u64);

typedef u64 (*btf_bpf_get_stack)(struct pt_regs *, void *, u32, u64);

enum {
	BPF_F_SYSCTL_BASE_NAME = 1,
};

struct bpf_prog_list {
	struct list_head node;
	struct bpf_prog *prog;
	struct bpf_cgroup_link *link;
	struct bpf_cgroup_storage *storage[2];
};

struct qdisc_skb_cb {
	struct {
		unsigned int pkt_len;
		u16 slave_dev_queue_mapping;
		u16 tc_classid;
	};
	unsigned char data[20];
};

struct bpf_skb_data_end {
	struct qdisc_skb_cb qdisc_cb;
	void *data_meta;
	void *data_end;
};

enum {
	TCPF_ESTABLISHED = 2,
	TCPF_SYN_SENT = 4,
	TCPF_SYN_RECV = 8,
	TCPF_FIN_WAIT1 = 16,
	TCPF_FIN_WAIT2 = 32,
	TCPF_TIME_WAIT = 64,
	TCPF_CLOSE = 128,
	TCPF_CLOSE_WAIT = 256,
	TCPF_LAST_ACK = 512,
	TCPF_LISTEN = 1024,
	TCPF_CLOSING = 2048,
	TCPF_NEW_SYN_RECV = 4096,
};

typedef u64 (*btf_bpf_sysctl_get_name)(struct bpf_sysctl_kern *, char *, size_t, u64);

typedef u64 (*btf_bpf_sysctl_get_current_value)(struct bpf_sysctl_kern *, char *, size_t);

typedef u64 (*btf_bpf_sysctl_get_new_value)(struct bpf_sysctl_kern *, char *, size_t);

typedef u64 (*btf_bpf_sysctl_set_new_value)(struct bpf_sysctl_kern *, const char *, size_t);

enum sock_type {
	SOCK_STREAM = 1,
	SOCK_DGRAM = 2,
	SOCK_RAW = 3,
	SOCK_RDM = 4,
	SOCK_SEQPACKET = 5,
	SOCK_DCCP = 6,
	SOCK_PACKET = 10,
};

enum {
	IPPROTO_IP = 0,
	IPPROTO_ICMP = 1,
	IPPROTO_IGMP = 2,
	IPPROTO_IPIP = 4,
	IPPROTO_TCP = 6,
	IPPROTO_EGP = 8,
	IPPROTO_PUP = 12,
	IPPROTO_UDP = 17,
	IPPROTO_IDP = 22,
	IPPROTO_TP = 29,
	IPPROTO_DCCP = 33,
	IPPROTO_IPV6 = 41,
	IPPROTO_RSVP = 46,
	IPPROTO_GRE = 47,
	IPPROTO_ESP = 50,
	IPPROTO_AH = 51,
	IPPROTO_MTP = 92,
	IPPROTO_BEETPH = 94,
	IPPROTO_ENCAP = 98,
	IPPROTO_PIM = 103,
	IPPROTO_COMP = 108,
	IPPROTO_SCTP = 132,
	IPPROTO_UDPLITE = 136,
	IPPROTO_MPLS = 137,
	IPPROTO_ETHERNET = 143,
	IPPROTO_RAW = 255,
	IPPROTO_MPTCP = 262,
	IPPROTO_MAX = 263,
};

enum sock_flags {
	SOCK_DEAD = 0,
	SOCK_DONE = 1,
	SOCK_URGINLINE = 2,
	SOCK_KEEPOPEN = 3,
	SOCK_LINGER = 4,
	SOCK_DESTROY = 5,
	SOCK_BROADCAST = 6,
	SOCK_TIMESTAMP = 7,
	SOCK_ZAPPED = 8,
	SOCK_USE_WRITE_QUEUE = 9,
	SOCK_DBG = 10,
	SOCK_RCVTSTAMP = 11,
	SOCK_RCVTSTAMPNS = 12,
	SOCK_LOCALROUTE = 13,
	SOCK_QUEUE_SHRUNK = 14,
	SOCK_MEMALLOC = 15,
	SOCK_TIMESTAMPING_RX_SOFTWARE = 16,
	SOCK_FASYNC = 17,
	SOCK_RXQ_OVFL = 18,
	SOCK_ZEROCOPY = 19,
	SOCK_WIFI_STATUS = 20,
	SOCK_NOFCS = 21,
	SOCK_FILTER_LOCKED = 22,
	SOCK_SELECT_ERR_QUEUE = 23,
	SOCK_RCU_FREE = 24,
	SOCK_TXTIME = 25,
	SOCK_XDP = 26,
	SOCK_TSTAMP_NEW = 27,
};

struct reuseport_array {
	struct bpf_map map;
	struct sock *ptrs[0];
};

enum bpf_struct_ops_state {
	BPF_STRUCT_OPS_STATE_INIT = 0,
	BPF_STRUCT_OPS_STATE_INUSE = 1,
	BPF_STRUCT_OPS_STATE_TOBEFREE = 2,
};

struct bpf_struct_ops_value {
	refcount_t refcnt;
	enum bpf_struct_ops_state state;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	char data[0];
};

struct bpf_struct_ops_map {
	struct bpf_map map;
	const struct bpf_struct_ops *st_ops;
	struct mutex lock;
	struct bpf_prog **progs;
	void *image;
	struct bpf_struct_ops_value *uvalue;
	struct bpf_struct_ops_value kvalue;
};

struct bpf_struct_ops_tcp_congestion_ops {
	refcount_t refcnt;
	enum bpf_struct_ops_state state;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct tcp_congestion_ops data;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum perf_event_read_format {
	PERF_FORMAT_TOTAL_TIME_ENABLED = 1,
	PERF_FORMAT_TOTAL_TIME_RUNNING = 2,
	PERF_FORMAT_ID = 4,
	PERF_FORMAT_GROUP = 8,
	PERF_FORMAT_MAX = 16,
};

enum perf_event_ioc_flags {
	PERF_IOC_FLAG_GROUP = 1,
};

struct perf_ns_link_info {
	__u64 dev;
	__u64 ino;
};

enum {
	NET_NS_INDEX = 0,
	UTS_NS_INDEX = 1,
	IPC_NS_INDEX = 2,
	PID_NS_INDEX = 3,
	USER_NS_INDEX = 4,
	MNT_NS_INDEX = 5,
	CGROUP_NS_INDEX = 6,
	NR_NAMESPACES = 7,
};

enum perf_event_type {
	PERF_RECORD_MMAP = 1,
	PERF_RECORD_LOST = 2,
	PERF_RECORD_COMM = 3,
	PERF_RECORD_EXIT = 4,
	PERF_RECORD_THROTTLE = 5,
	PERF_RECORD_UNTHROTTLE = 6,
	PERF_RECORD_FORK = 7,
	PERF_RECORD_READ = 8,
	PERF_RECORD_SAMPLE = 9,
	PERF_RECORD_MMAP2 = 10,
	PERF_RECORD_AUX = 11,
	PERF_RECORD_ITRACE_START = 12,
	PERF_RECORD_LOST_SAMPLES = 13,
	PERF_RECORD_SWITCH = 14,
	PERF_RECORD_SWITCH_CPU_WIDE = 15,
	PERF_RECORD_NAMESPACES = 16,
	PERF_RECORD_KSYMBOL = 17,
	PERF_RECORD_BPF_EVENT = 18,
	PERF_RECORD_CGROUP = 19,
	PERF_RECORD_MAX = 20,
};

struct swevent_hlist {
	struct hlist_head heads[256];
	struct callback_head callback_head;
};

struct pmu_event_list {
	raw_spinlock_t lock;
	struct list_head list;
};

struct perf_buffer {
	refcount_t refcount;
	struct callback_head callback_head;
	int nr_pages;
	int overwrite;
	int paused;
	atomic_t poll;
	local_t head;
	unsigned int nest;
	local_t events;
	local_t wakeup;
	local_t lost;
	long int watermark;
	long int aux_watermark;
	spinlock_t event_lock;
	struct list_head event_list;
	atomic_t mmap_count;
	long unsigned int mmap_locked;
	struct user_struct *mmap_user;
	long int aux_head;
	unsigned int aux_nest;
	long int aux_wakeup;
	long unsigned int aux_pgoff;
	int aux_nr_pages;
	int aux_overwrite;
	atomic_t aux_mmap_count;
	long unsigned int aux_mmap_locked;
	void (*free_aux)(void *);
	refcount_t aux_refcount;
	int aux_in_sampling;
	void **aux_pages;
	void *aux_priv;
	struct perf_event_mmap_page *user_page;
	void *data_pages[0];
};

struct match_token {
	int token;
	const char *pattern;
};

enum {
	MAX_OPT_ARGS = 3,
};

typedef struct {
	char *from;
	char *to;
} substring_t;

struct min_heap {
	void *data;
	int nr;
	int size;
};

struct min_heap_callbacks {
	int elem_size;
	bool (*less)(const void *, const void *);
	void (*swp)(void *, void *);
};

typedef int (*remote_function_f)(void *);

struct remote_function_call {
	struct task_struct *p;
	remote_function_f func;
	void *info;
	int ret;
};

typedef void (*event_f)(struct perf_event *, struct perf_cpu_context *, struct perf_event_context *, void *);

struct event_function_struct {
	struct perf_event *event;
	event_f func;
	void *data;
};

enum event_type_t {
	EVENT_FLEXIBLE = 1,
	EVENT_PINNED = 2,
	EVENT_TIME = 4,
	EVENT_CPU = 8,
	EVENT_ALL = 3,
};

struct stop_event_data {
	struct perf_event *event;
	unsigned int restart;
};

struct perf_read_data {
	struct perf_event *event;
	bool group;
	int ret;
};

struct perf_read_event {
	struct perf_event_header header;
	u32 pid;
	u32 tid;
};

typedef void perf_iterate_f(struct perf_event *, void *);

struct remote_output {
	struct perf_buffer *rb;
	int err;
};

struct perf_task_event {
	struct task_struct *task;
	struct perf_event_context *task_ctx;
	struct {
		struct perf_event_header header;
		u32 pid;
		u32 ppid;
		u32 tid;
		u32 ptid;
		u64 time;
	} event_id;
};

struct perf_comm_event {
	struct task_struct *task;
	char *comm;
	int comm_size;
	struct {
		struct perf_event_header header;
		u32 pid;
		u32 tid;
	} event_id;
};

struct perf_namespaces_event {
	struct task_struct *task;
	struct {
		struct perf_event_header header;
		u32 pid;
		u32 tid;
		u64 nr_namespaces;
		struct perf_ns_link_info link_info[7];
	} event_id;
};

struct perf_mmap_event {
	struct vm_area_struct *vma;
	const char *file_name;
	int file_size;
	int maj;
	int min;
	u64 ino;
	u64 ino_generation;
	u32 prot;
	u32 flags;
	struct {
		struct perf_event_header header;
		u32 pid;
		u32 tid;
		u64 start;
		u64 len;
		u64 pgoff;
	} event_id;
};

struct perf_switch_event {
	struct task_struct *task;
	struct task_struct *next_prev;
	struct {
		struct perf_event_header header;
		u32 next_prev_pid;
		u32 next_prev_tid;
	} event_id;
};

struct perf_ksymbol_event {
	const char *name;
	int name_len;
	struct {
		struct perf_event_header header;
		u64 addr;
		u32 len;
		u16 ksym_type;
		u16 flags;
	} event_id;
};

struct perf_bpf_event {
	struct bpf_prog *prog;
	struct {
		struct perf_event_header header;
		u16 type;
		u16 flags;
		u32 id;
		u8 tag[8];
	} event_id;
};

struct swevent_htable {
	struct swevent_hlist *swevent_hlist;
	struct mutex hlist_mutex;
	int hlist_refcount;
	int recursion[4];
};

enum perf_probe_config {
	PERF_PROBE_CONFIG_IS_RETPROBE = 1,
	PERF_UPROBE_REF_CTR_OFFSET_BITS = 32,
	PERF_UPROBE_REF_CTR_OFFSET_SHIFT = 32,
};

enum {
	IF_ACT_NONE = 4294967295,
	IF_ACT_FILTER = 0,
	IF_ACT_START = 1,
	IF_ACT_STOP = 2,
	IF_SRC_FILE = 3,
	IF_SRC_KERNEL = 4,
	IF_SRC_FILEADDR = 5,
	IF_SRC_KERNELADDR = 6,
};

enum {
	IF_STATE_ACTION = 0,
	IF_STATE_SOURCE = 1,
	IF_STATE_END = 2,
};

struct perf_aux_event {
	struct perf_event_header header;
	u32 pid;
	u32 tid;
};

struct perf_aux_event___2 {
	struct perf_event_header header;
	u64 offset;
	u64 size;
	u64 flags;
};

enum perf_callchain_context {
	PERF_CONTEXT_HV = 4294967264,
	PERF_CONTEXT_KERNEL = 4294967168,
	PERF_CONTEXT_USER = 4294966784,
	PERF_CONTEXT_GUEST = 4294965248,
	PERF_CONTEXT_GUEST_KERNEL = 4294965120,
	PERF_CONTEXT_GUEST_USER = 4294964736,
	PERF_CONTEXT_MAX = 4294963201,
};

struct callchain_cpus_entries {
	struct callback_head callback_head;
	struct perf_callchain_entry *cpu_entries[0];
};

enum bp_type_idx {
	TYPE_INST = 0,
	TYPE_DATA = 0,
	TYPE_MAX = 1,
};

struct bp_cpuinfo {
	unsigned int cpu_pinned;
	unsigned int *tsk_pinned;
	unsigned int flexible;
};

struct bp_busy_slots {
	unsigned int pinned;
	unsigned int flexible;
};

typedef u8 uprobe_opcode_t;

struct uprobe {
	struct rb_node rb_node;
	refcount_t ref;
	struct rw_semaphore register_rwsem;
	struct rw_semaphore consumer_rwsem;
	struct list_head pending_list;
	struct uprobe_consumer *consumers;
	struct inode *inode;
	loff_t offset;
	loff_t ref_ctr_offset;
	long unsigned int flags;
	struct arch_uprobe arch;
};

struct xol_area {
	wait_queue_head_t wq;
	atomic_t slot_count;
	long unsigned int *bitmap;
	struct vm_special_mapping xol_mapping;
	struct page *pages[2];
	long unsigned int vaddr;
};

typedef long unsigned int vm_flags_t;

struct compact_control;

struct capture_control {
	struct compact_control *cc;
	struct page *page;
};

struct page_vma_mapped_walk {
	struct page *page;
	struct vm_area_struct *vma;
	long unsigned int address;
	pmd_t *pmd;
	pte_t *pte;
	spinlock_t *ptl;
	unsigned int flags;
};

enum mmu_notifier_event {
	MMU_NOTIFY_UNMAP = 0,
	MMU_NOTIFY_CLEAR = 1,
	MMU_NOTIFY_PROTECTION_VMA = 2,
	MMU_NOTIFY_PROTECTION_PAGE = 3,
	MMU_NOTIFY_SOFT_DIRTY = 4,
	MMU_NOTIFY_RELEASE = 5,
};

struct mmu_notifier_range {
	struct vm_area_struct *vma;
	struct mm_struct *mm;
	long unsigned int start;
	long unsigned int end;
	unsigned int flags;
	enum mmu_notifier_event event;
};

struct compact_control {
	struct list_head freepages;
	struct list_head migratepages;
	unsigned int nr_freepages;
	unsigned int nr_migratepages;
	long unsigned int free_pfn;
	long unsigned int migrate_pfn;
	long unsigned int fast_start_pfn;
	struct zone *zone;
	long unsigned int total_migrate_scanned;
	long unsigned int total_free_scanned;
	short unsigned int fast_search_fail;
	short int search_order;
	const gfp_t gfp_mask;
	int order;
	int migratetype;
	const unsigned int alloc_flags;
	const int highest_zoneidx;
	enum migrate_mode mode;
	bool ignore_skip_hint;
	bool no_set_skip_hint;
	bool ignore_block_suitable;
	bool direct_compaction;
	bool whole_zone;
	bool contended;
	bool rescan;
	bool alloc_contig;
};

struct delayed_uprobe {
	struct list_head list;
	struct uprobe *uprobe;
	struct mm_struct *mm;
};

struct map_info {
	struct map_info *next;
	struct mm_struct *mm;
	long unsigned int vaddr;
};

struct static_key_mod {
	struct static_key_mod *next;
	struct jump_entry *entries;
	struct module *mod;
};

struct static_key_deferred {
	struct static_key key;
	long unsigned int timeout;
	struct delayed_work work;
};

enum rseq_cpu_id_state {
	RSEQ_CPU_ID_UNINITIALIZED = 4294967295,
	RSEQ_CPU_ID_REGISTRATION_FAILED = 4294967294,
};

enum rseq_flags {
	RSEQ_FLAG_UNREGISTER = 1,
};

enum rseq_cs_flags {
	RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT = 1,
	RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL = 2,
	RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE = 4,
};

struct rseq_cs {
	__u32 version;
	__u32 flags;
	__u64 start_ip;
	__u64 post_commit_offset;
	__u64 abort_ip;
};

struct trace_event_raw_rseq_update {
	struct trace_entry ent;
	s32 cpu_id;
	char __data[0];
};

struct trace_event_raw_rseq_ip_fixup {
	struct trace_entry ent;
	long unsigned int regs_ip;
	long unsigned int start_ip;
	long unsigned int post_commit_offset;
	long unsigned int abort_ip;
	char __data[0];
};

struct trace_event_data_offsets_rseq_update {};

struct trace_event_data_offsets_rseq_ip_fixup {};

typedef void (*btf_trace_rseq_update)(void *, struct task_struct *);

typedef void (*btf_trace_rseq_ip_fixup)(void *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);

struct __key_reference_with_attributes;

typedef struct __key_reference_with_attributes *key_ref_t;

enum key_being_used_for {
	VERIFYING_MODULE_SIGNATURE = 0,
	VERIFYING_FIRMWARE_SIGNATURE = 1,
	VERIFYING_KEXEC_PE_SIGNATURE = 2,
	VERIFYING_KEY_SIGNATURE = 3,
	VERIFYING_KEY_SELF_SIGNATURE = 4,
	VERIFYING_UNSPECIFIED_SIGNATURE = 5,
	NR__KEY_BEING_USED_FOR = 6,
};

struct key_preparsed_payload {
	char *description;
	union key_payload payload;
	const void *data;
	size_t datalen;
	size_t quotalen;
	time64_t expiry;
};

struct key_match_data {
	bool (*cmp)(const struct key *, const struct key_match_data *);
	const void *raw_data;
	void *preparsed;
	unsigned int lookup_type;
};

enum kernel_pkey_operation {
	kernel_pkey_encrypt = 0,
	kernel_pkey_decrypt = 1,
	kernel_pkey_sign = 2,
	kernel_pkey_verify = 3,
};

struct kernel_pkey_params {
	struct key *key;
	const char *encoding;
	const char *hash_algo;
	char *info;
	__u32 in_len;
	union {
		__u32 out_len;
		__u32 in2_len;
	};
	enum kernel_pkey_operation op: 8;
};

struct kernel_pkey_query {
	__u32 supported_ops;
	__u32 key_size;
	__u16 max_data_size;
	__u16 max_sig_size;
	__u16 max_enc_size;
	__u16 max_dec_size;
};

struct asymmetric_key_subtype;

struct pkcs7_message;

typedef struct pglist_data pg_data_t;

typedef void (*xa_update_node_t)(struct xa_node *);

struct xa_state {
	struct xarray *xa;
	long unsigned int xa_index;
	unsigned char xa_shift;
	unsigned char xa_sibs;
	unsigned char xa_offset;
	unsigned char xa_pad;
	struct xa_node *xa_node;
	struct xa_node *xa_alloc;
	xa_update_node_t xa_update;
};

enum positive_aop_returns {
	AOP_WRITEPAGE_ACTIVATE = 524288,
	AOP_TRUNCATED_PAGE = 524289,
};

enum mapping_flags {
	AS_EIO = 0,
	AS_ENOSPC = 1,
	AS_MM_ALL_LOCKS = 2,
	AS_UNEVICTABLE = 3,
	AS_EXITING = 4,
	AS_NO_WRITEBACK_TAGS = 5,
};

enum iter_type {
	ITER_IOVEC = 4,
	ITER_KVEC = 8,
	ITER_BVEC = 16,
	ITER_PIPE = 32,
	ITER_DISCARD = 64,
};

struct pagevec {
	unsigned char nr;
	bool percpu_pvec_drained;
	struct page *pages[15];
};

struct fid {
	union {
		struct {
			u32 ino;
			u32 gen;
			u32 parent_ino;
			u32 parent_gen;
		} i32;
		struct {
			u32 block;
			u16 partref;
			u16 parent_partref;
			u32 generation;
			u32 parent_block;
			u32 parent_generation;
		} udf;
		__u32 raw[0];
	};
};

struct trace_event_raw_mm_filemap_op_page_cache {
	struct trace_entry ent;
	long unsigned int pfn;
	long unsigned int i_ino;
	long unsigned int index;
	dev_t s_dev;
	char __data[0];
};

struct trace_event_raw_filemap_set_wb_err {
	struct trace_entry ent;
	long unsigned int i_ino;
	dev_t s_dev;
	errseq_t errseq;
	char __data[0];
};

struct trace_event_raw_file_check_and_advance_wb_err {
	struct trace_entry ent;
	struct file *file;
	long unsigned int i_ino;
	dev_t s_dev;
	errseq_t old;
	errseq_t new;
	char __data[0];
};

struct trace_event_data_offsets_mm_filemap_op_page_cache {};

struct trace_event_data_offsets_filemap_set_wb_err {};

struct trace_event_data_offsets_file_check_and_advance_wb_err {};

typedef void (*btf_trace_mm_filemap_delete_from_page_cache)(void *, struct page *);

typedef void (*btf_trace_mm_filemap_add_to_page_cache)(void *, struct page *);

typedef void (*btf_trace_filemap_set_wb_err)(void *, struct address_space *, errseq_t);

typedef void (*btf_trace_file_check_and_advance_wb_err)(void *, struct file *, errseq_t);

struct wait_page_key {
	struct page *page;
	int bit_nr;
	int page_match;
};

struct wait_page_queue {
	struct page *page;
	int bit_nr;
	wait_queue_entry_t wait;
};

enum behavior {
	EXCLUSIVE = 0,
	SHARED = 1,
	DROP = 2,
};

struct kmem_cache_order_objects {
	unsigned int x;
};

struct kmem_cache_cpu;

struct kmem_cache_node;

struct kmem_cache {
	struct kmem_cache_cpu *cpu_slab;
	slab_flags_t flags;
	long unsigned int min_partial;
	unsigned int size;
	unsigned int object_size;
	unsigned int offset;
	unsigned int cpu_partial;
	struct kmem_cache_order_objects oo;
	struct kmem_cache_order_objects max;
	struct kmem_cache_order_objects min;
	gfp_t allocflags;
	int refcount;
	void (*ctor)(void *);
	unsigned int inuse;
	unsigned int align;
	unsigned int red_left_pad;
	const char *name;
	struct list_head list;
	struct kobject kobj;
	struct work_struct kobj_remove_work;
	unsigned int remote_node_defrag_ratio;
	unsigned int useroffset;
	unsigned int usersize;
	struct kmem_cache_node *node[64];
};

struct kmem_cache_cpu {
	void **freelist;
	long unsigned int tid;
	struct page *page;
	struct page *partial;
};

struct kmem_cache_node {
	spinlock_t list_lock;
	long unsigned int nr_partial;
	struct list_head partial;
	atomic_long_t nr_slabs;
	atomic_long_t total_objects;
	struct list_head full;
};

enum slab_state {
	DOWN = 0,
	PARTIAL = 1,
	PARTIAL_NODE = 2,
	UP = 3,
	FULL = 4,
};

struct kmalloc_info_struct {
	const char *name[3];
	unsigned int size;
};

enum oom_constraint {
	CONSTRAINT_NONE = 0,
	CONSTRAINT_CPUSET = 1,
	CONSTRAINT_MEMORY_POLICY = 2,
	CONSTRAINT_MEMCG = 3,
};

struct oom_control {
	struct zonelist *zonelist;
	nodemask_t *nodemask;
	struct mem_cgroup *memcg;
	const gfp_t gfp_mask;
	const int order;
	long unsigned int totalpages;
	struct task_struct *chosen;
	long unsigned int chosen_points;
	enum oom_constraint constraint;
};

enum memcg_memory_event {
	MEMCG_LOW = 0,
	MEMCG_HIGH = 1,
	MEMCG_MAX = 2,
	MEMCG_OOM = 3,
	MEMCG_OOM_KILL = 4,
	MEMCG_SWAP_HIGH = 5,
	MEMCG_SWAP_MAX = 6,
	MEMCG_SWAP_FAIL = 7,
	MEMCG_NR_MEMORY_EVENTS = 8,
};

enum compact_priority {
	COMPACT_PRIO_SYNC_FULL = 0,
	MIN_COMPACT_PRIORITY = 0,
	COMPACT_PRIO_SYNC_LIGHT = 1,
	MIN_COMPACT_COSTLY_PRIORITY = 1,
	DEF_COMPACT_PRIORITY = 1,
	COMPACT_PRIO_ASYNC = 2,
	INIT_COMPACT_PRIORITY = 2,
};

enum compact_result {
	COMPACT_NOT_SUITABLE_ZONE = 0,
	COMPACT_SKIPPED = 1,
	COMPACT_DEFERRED = 2,
	COMPACT_INACTIVE = 2,
	COMPACT_NO_SUITABLE_PAGE = 3,
	COMPACT_CONTINUE = 4,
	COMPACT_COMPLETE = 5,
	COMPACT_PARTIAL_SKIPPED = 6,
	COMPACT_CONTENDED = 7,
	COMPACT_SUCCESS = 8,
};

struct trace_event_raw_oom_score_adj_update {
	struct trace_entry ent;
	pid_t pid;
	char comm[16];
	short int oom_score_adj;
	char __data[0];
};

struct trace_event_raw_reclaim_retry_zone {
	struct trace_entry ent;
	int node;
	int zone_idx;
	int order;
	long unsigned int reclaimable;
	long unsigned int available;
	long unsigned int min_wmark;
	int no_progress_loops;
	bool wmark_check;
	char __data[0];
};

struct trace_event_raw_mark_victim {
	struct trace_entry ent;
	int pid;
	char __data[0];
};

struct trace_event_raw_wake_reaper {
	struct trace_entry ent;
	int pid;
	char __data[0];
};

struct trace_event_raw_start_task_reaping {
	struct trace_entry ent;
	int pid;
	char __data[0];
};

struct trace_event_raw_finish_task_reaping {
	struct trace_entry ent;
	int pid;
	char __data[0];
};

struct trace_event_raw_skip_task_reaping {
	struct trace_entry ent;
	int pid;
	char __data[0];
};

struct trace_event_raw_compact_retry {
	struct trace_entry ent;
	int order;
	int priority;
	int result;
	int retries;
	int max_retries;
	bool ret;
	char __data[0];
};

struct trace_event_data_offsets_oom_score_adj_update {};

struct trace_event_data_offsets_reclaim_retry_zone {};

struct trace_event_data_offsets_mark_victim {};

struct trace_event_data_offsets_wake_reaper {};

struct trace_event_data_offsets_start_task_reaping {};

struct trace_event_data_offsets_finish_task_reaping {};

struct trace_event_data_offsets_skip_task_reaping {};

struct trace_event_data_offsets_compact_retry {};

typedef void (*btf_trace_oom_score_adj_update)(void *, struct task_struct *);

typedef void (*btf_trace_reclaim_retry_zone)(void *, struct zoneref *, int, long unsigned int, long unsigned int, long unsigned int, int, bool);

typedef void (*btf_trace_mark_victim)(void *, int);

typedef void (*btf_trace_wake_reaper)(void *, int);

typedef void (*btf_trace_start_task_reaping)(void *, int);

typedef void (*btf_trace_finish_task_reaping)(void *, int);

typedef void (*btf_trace_skip_task_reaping)(void *, int);

typedef void (*btf_trace_compact_retry)(void *, int, enum compact_priority, enum compact_result, int, int, bool);

enum wb_congested_state {
	WB_async_congested = 0,
	WB_sync_congested = 1,
};

enum {
	XA_CHECK_SCHED = 4096,
};

enum wb_state {
	WB_registered = 0,
	WB_writeback_running = 1,
	WB_has_dirty_io = 2,
	WB_start_all = 3,
};

enum {
	BLK_RW_ASYNC = 0,
	BLK_RW_SYNC = 1,
};

struct wb_lock_cookie {
	bool locked;
	long unsigned int flags;
};

typedef int (*writepage_t)(struct page *, struct writeback_control *, void *);

struct dirty_throttle_control {
	struct bdi_writeback *wb;
	struct fprop_local_percpu *wb_completions;
	long unsigned int avail;
	long unsigned int dirty;
	long unsigned int thresh;
	long unsigned int bg_thresh;
	long unsigned int wb_dirty;
	long unsigned int wb_thresh;
	long unsigned int wb_bg_thresh;
	long unsigned int pos_ratio;
};

struct trace_event_raw_mm_lru_insertion {
	struct trace_entry ent;
	struct page *page;
	long unsigned int pfn;
	int lru;
	long unsigned int flags;
	char __data[0];
};

struct trace_event_raw_mm_lru_activate {
	struct trace_entry ent;
	struct page *page;
	long unsigned int pfn;
	char __data[0];
};

struct trace_event_data_offsets_mm_lru_insertion {};

struct trace_event_data_offsets_mm_lru_activate {};

typedef void (*btf_trace_mm_lru_insertion)(void *, struct page *, int);

typedef void (*btf_trace_mm_lru_activate)(void *, struct page *);

struct lru_rotate {
	local_lock_t lock;
	struct pagevec pvec;
};

struct lru_pvecs {
	local_lock_t lock;
	struct pagevec lru_add;
	struct pagevec lru_deactivate_file;
	struct pagevec lru_deactivate;
	struct pagevec lru_lazyfree;
	struct pagevec activate_page;
};

enum lruvec_flags {
	LRUVEC_CONGESTED = 0,
};

enum pgdat_flags {
	PGDAT_DIRTY = 0,
	PGDAT_WRITEBACK = 1,
	PGDAT_RECLAIM_LOCKED = 2,
};

struct reclaim_stat {
	unsigned int nr_dirty;
	unsigned int nr_unqueued_dirty;
	unsigned int nr_congested;
	unsigned int nr_writeback;
	unsigned int nr_immediate;
	unsigned int nr_pageout;
	unsigned int nr_activate[2];
	unsigned int nr_ref_keep;
	unsigned int nr_unmap_fail;
	unsigned int nr_lazyfree_fail;
};

enum mem_cgroup_protection {
	MEMCG_PROT_NONE = 0,
	MEMCG_PROT_LOW = 1,
	MEMCG_PROT_MIN = 2,
};

struct mem_cgroup_reclaim_cookie {
	pg_data_t *pgdat;
	unsigned int generation;
};

enum ttu_flags {
	TTU_MIGRATION = 1,
	TTU_MUNLOCK = 2,
	TTU_SPLIT_HUGE_PMD = 4,
	TTU_IGNORE_MLOCK = 8,
	TTU_IGNORE_ACCESS = 16,
	TTU_IGNORE_HWPOISON = 32,
	TTU_BATCH_FLUSH = 64,
	TTU_RMAP_LOCKED = 128,
	TTU_SPLIT_FREEZE = 256,
};

struct trace_event_raw_mm_vmscan_kswapd_sleep {
	struct trace_entry ent;
	int nid;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_kswapd_wake {
	struct trace_entry ent;
	int nid;
	int zid;
	int order;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_wakeup_kswapd {
	struct trace_entry ent;
	int nid;
	int zid;
	int order;
	gfp_t gfp_flags;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_direct_reclaim_begin_template {
	struct trace_entry ent;
	int order;
	gfp_t gfp_flags;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_direct_reclaim_end_template {
	struct trace_entry ent;
	long unsigned int nr_reclaimed;
	char __data[0];
};

struct trace_event_raw_mm_shrink_slab_start {
	struct trace_entry ent;
	struct shrinker *shr;
	void *shrink;
	int nid;
	long int nr_objects_to_shrink;
	gfp_t gfp_flags;
	long unsigned int cache_items;
	long long unsigned int delta;
	long unsigned int total_scan;
	int priority;
	char __data[0];
};

struct trace_event_raw_mm_shrink_slab_end {
	struct trace_entry ent;
	struct shrinker *shr;
	int nid;
	void *shrink;
	long int unused_scan;
	long int new_scan;
	int retval;
	long int total_scan;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_lru_isolate {
	struct trace_entry ent;
	int highest_zoneidx;
	int order;
	long unsigned int nr_requested;
	long unsigned int nr_scanned;
	long unsigned int nr_skipped;
	long unsigned int nr_taken;
	isolate_mode_t isolate_mode;
	int lru;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_writepage {
	struct trace_entry ent;
	long unsigned int pfn;
	int reclaim_flags;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_lru_shrink_inactive {
	struct trace_entry ent;
	int nid;
	long unsigned int nr_scanned;
	long unsigned int nr_reclaimed;
	long unsigned int nr_dirty;
	long unsigned int nr_writeback;
	long unsigned int nr_congested;
	long unsigned int nr_immediate;
	unsigned int nr_activate0;
	unsigned int nr_activate1;
	long unsigned int nr_ref_keep;
	long unsigned int nr_unmap_fail;
	int priority;
	int reclaim_flags;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_lru_shrink_active {
	struct trace_entry ent;
	int nid;
	long unsigned int nr_taken;
	long unsigned int nr_active;
	long unsigned int nr_deactivated;
	long unsigned int nr_referenced;
	int priority;
	int reclaim_flags;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_inactive_list_is_low {
	struct trace_entry ent;
	int nid;
	int reclaim_idx;
	long unsigned int total_inactive;
	long unsigned int inactive;
	long unsigned int total_active;
	long unsigned int active;
	long unsigned int ratio;
	int reclaim_flags;
	char __data[0];
};

struct trace_event_raw_mm_vmscan_node_reclaim_begin {
	struct trace_entry ent;
	int nid;
	int order;
	gfp_t gfp_flags;
	char __data[0];
};

struct trace_event_data_offsets_mm_vmscan_kswapd_sleep {};

struct trace_event_data_offsets_mm_vmscan_kswapd_wake {};

struct trace_event_data_offsets_mm_vmscan_wakeup_kswapd {};

struct trace_event_data_offsets_mm_vmscan_direct_reclaim_begin_template {};

struct trace_event_data_offsets_mm_vmscan_direct_reclaim_end_template {};

struct trace_event_data_offsets_mm_shrink_slab_start {};

struct trace_event_data_offsets_mm_shrink_slab_end {};

struct trace_event_data_offsets_mm_vmscan_lru_isolate {};

struct trace_event_data_offsets_mm_vmscan_writepage {};

struct trace_event_data_offsets_mm_vmscan_lru_shrink_inactive {};

struct trace_event_data_offsets_mm_vmscan_lru_shrink_active {};

struct trace_event_data_offsets_mm_vmscan_inactive_list_is_low {};

struct trace_event_data_offsets_mm_vmscan_node_reclaim_begin {};

typedef void (*btf_trace_mm_vmscan_kswapd_sleep)(void *, int);

typedef void (*btf_trace_mm_vmscan_kswapd_wake)(void *, int, int, int);

typedef void (*btf_trace_mm_vmscan_wakeup_kswapd)(void *, int, int, int, gfp_t);

typedef void (*btf_trace_mm_vmscan_direct_reclaim_begin)(void *, int, gfp_t);

typedef void (*btf_trace_mm_vmscan_direct_reclaim_end)(void *, long unsigned int);

typedef void (*btf_trace_mm_shrink_slab_start)(void *, struct shrinker *, struct shrink_control *, long int, long unsigned int, long long unsigned int, long unsigned int, int);

typedef void (*btf_trace_mm_shrink_slab_end)(void *, struct shrinker *, int, int, long int, long int, long int);

typedef void (*btf_trace_mm_vmscan_lru_isolate)(void *, int, int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, isolate_mode_t, int);

typedef void (*btf_trace_mm_vmscan_writepage)(void *, struct page *);

typedef void (*btf_trace_mm_vmscan_lru_shrink_inactive)(void *, int, long unsigned int, long unsigned int, struct reclaim_stat *, int, int);

typedef void (*btf_trace_mm_vmscan_lru_shrink_active)(void *, int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, int, int);

typedef void (*btf_trace_mm_vmscan_inactive_list_is_low)(void *, int, int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, int);

typedef void (*btf_trace_mm_vmscan_node_reclaim_begin)(void *, int, int, gfp_t);

typedef void (*btf_trace_mm_vmscan_node_reclaim_end)(void *, long unsigned int);

struct scan_control {
	long unsigned int nr_to_reclaim;
	nodemask_t *nodemask;
	struct mem_cgroup *target_mem_cgroup;
	long unsigned int anon_cost;
	long unsigned int file_cost;
	unsigned int may_deactivate: 2;
	unsigned int force_deactivate: 1;
	unsigned int skipped_deactivate: 1;
	unsigned int may_writepage: 1;
	unsigned int may_unmap: 1;
	unsigned int may_swap: 1;
	unsigned int memcg_low_reclaim: 1;
	unsigned int memcg_low_skipped: 1;
	unsigned int hibernation_mode: 1;
	unsigned int compaction_ready: 1;
	unsigned int cache_trim_mode: 1;
	unsigned int file_is_tiny: 1;
	s8 order;
	s8 priority;
	s8 reclaim_idx;
	gfp_t gfp_mask;
	long unsigned int nr_scanned;
	long unsigned int nr_reclaimed;
	struct {
		unsigned int dirty;
		unsigned int unqueued_dirty;
		unsigned int congested;
		unsigned int writeback;
		unsigned int immediate;
		unsigned int file_taken;
		unsigned int taken;
	} nr;
	struct reclaim_state reclaim_state;
};

typedef enum {
	PAGE_KEEP = 0,
	PAGE_ACTIVATE = 1,
	PAGE_SUCCESS = 2,
	PAGE_CLEAN = 3,
} pageout_t;

enum page_references {
	PAGEREF_RECLAIM = 0,
	PAGEREF_RECLAIM_CLEAN = 1,
	PAGEREF_KEEP = 2,
	PAGEREF_ACTIVATE = 3,
};

enum scan_balance {
	SCAN_EQUAL = 0,
	SCAN_FRACT = 1,
	SCAN_ANON = 2,
	SCAN_FILE = 3,
};

struct xattr {
	const char *name;
	void *value;
	size_t value_len;
};

struct constant_table {
	const char *name;
	int value;
};

enum {
	MPOL_DEFAULT = 0,
	MPOL_PREFERRED = 1,
	MPOL_BIND = 2,
	MPOL_INTERLEAVE = 3,
	MPOL_LOCAL = 4,
	MPOL_MAX = 5,
};

struct shared_policy {
	struct rb_root root;
	rwlock_t lock;
};

struct simple_xattrs {
	struct list_head head;
	spinlock_t lock;
};

struct simple_xattr {
	struct list_head list;
	char *name;
	size_t size;
	char value[0];
};

enum fid_type {
	FILEID_ROOT = 0,
	FILEID_INO32_GEN = 1,
	FILEID_INO32_GEN_PARENT = 2,
	FILEID_BTRFS_WITHOUT_PARENT = 77,
	FILEID_BTRFS_WITH_PARENT = 78,
	FILEID_BTRFS_WITH_PARENT_ROOT = 79,
	FILEID_UDF_WITHOUT_PARENT = 81,
	FILEID_UDF_WITH_PARENT = 82,
	FILEID_NILFS_WITHOUT_PARENT = 97,
	FILEID_NILFS_WITH_PARENT = 98,
	FILEID_FAT_WITHOUT_PARENT = 113,
	FILEID_FAT_WITH_PARENT = 114,
	FILEID_LUSTRE = 151,
	FILEID_KERNFS = 254,
	FILEID_INVALID = 255,
};

struct shmem_inode_info {
	spinlock_t lock;
	unsigned int seals;
	long unsigned int flags;
	long unsigned int alloced;
	long unsigned int swapped;
	struct list_head shrinklist;
	struct list_head swaplist;
	struct shared_policy policy;
	struct simple_xattrs xattrs;
	atomic_t stop_eviction;
	struct inode vfs_inode;
};

struct shmem_sb_info {
	long unsigned int max_blocks;
	struct percpu_counter used_blocks;
	long unsigned int max_inodes;
	long unsigned int free_inodes;
	spinlock_t stat_lock;
	umode_t mode;
	unsigned char huge;
	kuid_t uid;
	kgid_t gid;
	struct mempolicy *mpol;
	spinlock_t shrinklist_lock;
	struct list_head shrinklist;
	long unsigned int shrinklist_len;
};

enum sgp_type {
	SGP_READ = 0,
	SGP_CACHE = 1,
	SGP_NOHUGE = 2,
	SGP_HUGE = 3,
	SGP_WRITE = 4,
	SGP_FALLOC = 5,
};

struct shmem_falloc {
	wait_queue_head_t *waitq;
	long unsigned int start;
	long unsigned int next;
	long unsigned int nr_falloced;
	long unsigned int nr_unswapped;
};

struct shmem_options {
	long long unsigned int blocks;
	long long unsigned int inodes;
	struct mempolicy *mpol;
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
	int huge;
	int seen;
};

enum shmem_param {
	Opt_gid = 0,
	Opt_huge = 1,
	Opt_mode = 2,
	Opt_mpol = 3,
	Opt_nr_blocks = 4,
	Opt_nr_inodes = 5,
	Opt_size = 6,
	Opt_uid = 7,
};

enum pageblock_bits {
	PB_migrate = 0,
	PB_migrate_end = 2,
	PB_migrate_skip = 3,
	NR_PAGEBLOCK_BITS = 4,
};

enum writeback_stat_item {
	NR_DIRTY_THRESHOLD = 0,
	NR_DIRTY_BG_THRESHOLD = 1,
	NR_VM_WRITEBACK_STAT_ITEMS = 2,
};

struct contig_page_info {
	long unsigned int free_pages;
	long unsigned int free_blocks_total;
	long unsigned int free_blocks_suitable;
};

typedef s8 pto_T_____21;

enum mminit_level {
	MMINIT_WARNING = 0,
	MMINIT_VERIFY = 1,
	MMINIT_TRACE = 2,
};

struct pcpu_group_info {
	int nr_units;
	long unsigned int base_offset;
	unsigned int *cpu_map;
};

struct pcpu_alloc_info {
	size_t static_size;
	size_t reserved_size;
	size_t dyn_size;
	size_t unit_size;
	size_t atom_size;
	size_t alloc_size;
	size_t __ai_size;
	int nr_groups;
	struct pcpu_group_info groups[0];
};

typedef void * (*pcpu_fc_alloc_fn_t)(unsigned int, size_t, size_t);

typedef void (*pcpu_fc_free_fn_t)(void *, size_t);

typedef void (*pcpu_fc_populate_pte_fn_t)(long unsigned int);

typedef int pcpu_fc_cpu_distance_fn_t(unsigned int, unsigned int);

struct trace_event_raw_percpu_alloc_percpu {
	struct trace_entry ent;
	bool reserved;
	bool is_atomic;
	size_t size;
	size_t align;
	void *base_addr;
	int off;
	void *ptr;
	char __data[0];
};

struct trace_event_raw_percpu_free_percpu {
	struct trace_entry ent;
	void *base_addr;
	int off;
	void *ptr;
	char __data[0];
};

struct trace_event_raw_percpu_alloc_percpu_fail {
	struct trace_entry ent;
	bool reserved;
	bool is_atomic;
	size_t size;
	size_t align;
	char __data[0];
};

struct trace_event_raw_percpu_create_chunk {
	struct trace_entry ent;
	void *base_addr;
	char __data[0];
};

struct trace_event_raw_percpu_destroy_chunk {
	struct trace_entry ent;
	void *base_addr;
	char __data[0];
};

struct trace_event_data_offsets_percpu_alloc_percpu {};

struct trace_event_data_offsets_percpu_free_percpu {};

struct trace_event_data_offsets_percpu_alloc_percpu_fail {};

struct trace_event_data_offsets_percpu_create_chunk {};

struct trace_event_data_offsets_percpu_destroy_chunk {};

typedef void (*btf_trace_percpu_alloc_percpu)(void *, bool, bool, size_t, size_t, void *, int, void *);

typedef void (*btf_trace_percpu_free_percpu)(void *, void *, int, void *);

typedef void (*btf_trace_percpu_alloc_percpu_fail)(void *, bool, bool, size_t, size_t);

typedef void (*btf_trace_percpu_create_chunk)(void *, void *);

typedef void (*btf_trace_percpu_destroy_chunk)(void *, void *);

struct pcpu_block_md {
	int scan_hint;
	int scan_hint_start;
	int contig_hint;
	int contig_hint_start;
	int left_free;
	int right_free;
	int first_free;
	int nr_bits;
};

struct pcpu_chunk {
	struct list_head list;
	int free_bytes;
	struct pcpu_block_md chunk_md;
	void *base_addr;
	long unsigned int *alloc_map;
	long unsigned int *bound_map;
	struct pcpu_block_md *md_blocks;
	void *data;
	bool immutable;
	int start_offset;
	int end_offset;
	int nr_pages;
	int nr_populated;
	int nr_empty_pop_pages;
	long unsigned int populated[0];
};

struct trace_event_raw_kmem_alloc {
	struct trace_entry ent;
	long unsigned int call_site;
	const void *ptr;
	size_t bytes_req;
	size_t bytes_alloc;
	gfp_t gfp_flags;
	char __data[0];
};

struct trace_event_raw_kmem_alloc_node {
	struct trace_entry ent;
	long unsigned int call_site;
	const void *ptr;
	size_t bytes_req;
	size_t bytes_alloc;
	gfp_t gfp_flags;
	int node;
	char __data[0];
};

struct trace_event_raw_kmem_free {
	struct trace_entry ent;
	long unsigned int call_site;
	const void *ptr;
	char __data[0];
};

struct trace_event_raw_mm_page_free {
	struct trace_entry ent;
	long unsigned int pfn;
	unsigned int order;
	char __data[0];
};

struct trace_event_raw_mm_page_free_batched {
	struct trace_entry ent;
	long unsigned int pfn;
	char __data[0];
};

struct trace_event_raw_mm_page_alloc {
	struct trace_entry ent;
	long unsigned int pfn;
	unsigned int order;
	gfp_t gfp_flags;
	int migratetype;
	char __data[0];
};

struct trace_event_raw_mm_page {
	struct trace_entry ent;
	long unsigned int pfn;
	unsigned int order;
	int migratetype;
	char __data[0];
};

struct trace_event_raw_mm_page_pcpu_drain {
	struct trace_entry ent;
	long unsigned int pfn;
	unsigned int order;
	int migratetype;
	char __data[0];
};

struct trace_event_raw_mm_page_alloc_extfrag {
	struct trace_entry ent;
	long unsigned int pfn;
	int alloc_order;
	int fallback_order;
	int alloc_migratetype;
	int fallback_migratetype;
	int change_ownership;
	char __data[0];
};

struct trace_event_raw_rss_stat {
	struct trace_entry ent;
	unsigned int mm_id;
	unsigned int curr;
	int member;
	long int size;
	char __data[0];
};

struct trace_event_data_offsets_kmem_alloc {};

struct trace_event_data_offsets_kmem_alloc_node {};

struct trace_event_data_offsets_kmem_free {};

struct trace_event_data_offsets_mm_page_free {};

struct trace_event_data_offsets_mm_page_free_batched {};

struct trace_event_data_offsets_mm_page_alloc {};

struct trace_event_data_offsets_mm_page {};

struct trace_event_data_offsets_mm_page_pcpu_drain {};

struct trace_event_data_offsets_mm_page_alloc_extfrag {};

struct trace_event_data_offsets_rss_stat {};

typedef void (*btf_trace_kmalloc)(void *, long unsigned int, const void *, size_t, size_t, gfp_t);

typedef void (*btf_trace_kmem_cache_alloc)(void *, long unsigned int, const void *, size_t, size_t, gfp_t);

typedef void (*btf_trace_kmalloc_node)(void *, long unsigned int, const void *, size_t, size_t, gfp_t, int);

typedef void (*btf_trace_kmem_cache_alloc_node)(void *, long unsigned int, const void *, size_t, size_t, gfp_t, int);

typedef void (*btf_trace_kfree)(void *, long unsigned int, const void *);

typedef void (*btf_trace_kmem_cache_free)(void *, long unsigned int, const void *);

typedef void (*btf_trace_mm_page_free)(void *, struct page *, unsigned int);

typedef void (*btf_trace_mm_page_free_batched)(void *, struct page *);

typedef void (*btf_trace_mm_page_alloc)(void *, struct page *, unsigned int, gfp_t, int);

typedef void (*btf_trace_mm_page_alloc_zone_locked)(void *, struct page *, unsigned int, int);

typedef void (*btf_trace_mm_page_pcpu_drain)(void *, struct page *, unsigned int, int);

typedef void (*btf_trace_mm_page_alloc_extfrag)(void *, struct page *, int, int, int, int);

typedef void (*btf_trace_rss_stat)(void *, struct mm_struct *, int, long int);

struct slabinfo {
	long unsigned int active_objs;
	long unsigned int num_objs;
	long unsigned int active_slabs;
	long unsigned int num_slabs;
	long unsigned int shared_avail;
	unsigned int limit;
	unsigned int batchcount;
	unsigned int shared;
	unsigned int objects_per_slab;
	unsigned int cache_order;
};

struct alloc_context {
	struct zonelist *zonelist;
	nodemask_t *nodemask;
	struct zoneref *preferred_zoneref;
	int migratetype;
	enum zone_type highest_zoneidx;
	bool spread_dirty_pages;
};

struct trace_event_raw_mm_compaction_isolate_template {
	struct trace_entry ent;
	long unsigned int start_pfn;
	long unsigned int end_pfn;
	long unsigned int nr_scanned;
	long unsigned int nr_taken;
	char __data[0];
};

struct trace_event_raw_mm_compaction_migratepages {
	struct trace_entry ent;
	long unsigned int nr_migrated;
	long unsigned int nr_failed;
	char __data[0];
};

struct trace_event_raw_mm_compaction_begin {
	struct trace_entry ent;
	long unsigned int zone_start;
	long unsigned int migrate_pfn;
	long unsigned int free_pfn;
	long unsigned int zone_end;
	bool sync;
	char __data[0];
};

struct trace_event_raw_mm_compaction_end {
	struct trace_entry ent;
	long unsigned int zone_start;
	long unsigned int migrate_pfn;
	long unsigned int free_pfn;
	long unsigned int zone_end;
	bool sync;
	int status;
	char __data[0];
};

struct trace_event_raw_mm_compaction_try_to_compact_pages {
	struct trace_entry ent;
	int order;
	gfp_t gfp_mask;
	int prio;
	char __data[0];
};

struct trace_event_raw_mm_compaction_suitable_template {
	struct trace_entry ent;
	int nid;
	enum zone_type idx;
	int order;
	int ret;
	char __data[0];
};

struct trace_event_raw_mm_compaction_defer_template {
	struct trace_entry ent;
	int nid;
	enum zone_type idx;
	int order;
	unsigned int considered;
	unsigned int defer_shift;
	int order_failed;
	char __data[0];
};

struct trace_event_raw_mm_compaction_kcompactd_sleep {
	struct trace_entry ent;
	int nid;
	char __data[0];
};

struct trace_event_raw_kcompactd_wake_template {
	struct trace_entry ent;
	int nid;
	int order;
	enum zone_type highest_zoneidx;
	char __data[0];
};

struct trace_event_data_offsets_mm_compaction_isolate_template {};

struct trace_event_data_offsets_mm_compaction_migratepages {};

struct trace_event_data_offsets_mm_compaction_begin {};

struct trace_event_data_offsets_mm_compaction_end {};

struct trace_event_data_offsets_mm_compaction_try_to_compact_pages {};

struct trace_event_data_offsets_mm_compaction_suitable_template {};

struct trace_event_data_offsets_mm_compaction_defer_template {};

struct trace_event_data_offsets_mm_compaction_kcompactd_sleep {};

struct trace_event_data_offsets_kcompactd_wake_template {};

typedef void (*btf_trace_mm_compaction_isolate_migratepages)(void *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);

typedef void (*btf_trace_mm_compaction_isolate_freepages)(void *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);

typedef void (*btf_trace_mm_compaction_migratepages)(void *, long unsigned int, int, struct list_head *);

typedef void (*btf_trace_mm_compaction_begin)(void *, long unsigned int, long unsigned int, long unsigned int, long unsigned int, bool);

typedef void (*btf_trace_mm_compaction_end)(void *, long unsigned int, long unsigned int, long unsigned int, long unsigned int, bool, int);

typedef void (*btf_trace_mm_compaction_try_to_compact_pages)(void *, int, gfp_t, int);

typedef void (*btf_trace_mm_compaction_finished)(void *, struct zone *, int, int);

typedef void (*btf_trace_mm_compaction_suitable)(void *, struct zone *, int, int);

typedef void (*btf_trace_mm_compaction_deferred)(void *, struct zone *, int);

typedef void (*btf_trace_mm_compaction_defer_compaction)(void *, struct zone *, int);

typedef void (*btf_trace_mm_compaction_defer_reset)(void *, struct zone *, int);

typedef void (*btf_trace_mm_compaction_kcompactd_sleep)(void *, int);

typedef void (*btf_trace_mm_compaction_wakeup_kcompactd)(void *, int, int, enum zone_type);

typedef void (*btf_trace_mm_compaction_kcompactd_wake)(void *, int, int, enum zone_type);

typedef enum {
	ISOLATE_ABORT = 0,
	ISOLATE_NONE = 1,
	ISOLATE_SUCCESS = 2,
} isolate_migrate_t;

struct anon_vma_chain {
	struct vm_area_struct *vma;
	struct anon_vma *anon_vma;
	struct list_head same_vma;
	struct rb_node rb;
	long unsigned int rb_subtree_last;
};

enum lru_status {
	LRU_REMOVED = 0,
	LRU_REMOVED_RETRY = 1,
	LRU_ROTATE = 2,
	LRU_SKIP = 3,
	LRU_RETRY = 4,
};

typedef enum lru_status (*list_lru_walk_cb)(struct list_head *, struct list_lru_one *, spinlock_t *, void *);

typedef struct {
	long unsigned int pd;
} hugepd_t;

struct follow_page_context {
	struct dev_pagemap *pgmap;
	unsigned int page_mask;
};

struct zap_details {
	struct address_space *check_mapping;
	long unsigned int first_index;
	long unsigned int last_index;
};

typedef int (*pte_fn_t)(pte_t *, long unsigned int, void *);

enum {
	SWP_USED = 1,
	SWP_WRITEOK = 2,
	SWP_DISCARDABLE = 4,
	SWP_DISCARDING = 8,
	SWP_SOLIDSTATE = 16,
	SWP_CONTINUED = 32,
	SWP_BLKDEV = 64,
	SWP_ACTIVATED = 128,
	SWP_FS = 256,
	SWP_AREA_DISCARD = 512,
	SWP_PAGE_DISCARD = 1024,
	SWP_STABLE_WRITES = 2048,
	SWP_SYNCHRONOUS_IO = 4096,
	SWP_VALID = 8192,
	SWP_SCANNING = 16384,
};

struct copy_subpage_arg {
	struct page *dst;
	struct page *src;
	struct vm_area_struct *vma;
};

struct mm_walk;

struct mm_walk_ops {
	int (*pgd_entry)(pgd_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*p4d_entry)(p4d_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pud_entry)(pud_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pmd_entry)(pmd_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pte_entry)(pte_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pte_hole)(long unsigned int, long unsigned int, int, struct mm_walk *);
	int (*hugetlb_entry)(pte_t *, long unsigned int, long unsigned int, long unsigned int, struct mm_walk *);
	int (*test_walk)(long unsigned int, long unsigned int, struct mm_walk *);
	int (*pre_vma)(long unsigned int, long unsigned int, struct mm_walk *);
	void (*post_vma)(struct mm_walk *);
};

enum page_walk_action {
	ACTION_SUBTREE = 0,
	ACTION_CONTINUE = 1,
	ACTION_AGAIN = 2,
};

struct mm_walk {
	const struct mm_walk_ops *ops;
	struct mm_struct *mm;
	pgd_t *pgd;
	struct vm_area_struct *vma;
	enum page_walk_action action;
	bool no_vma;
	void *private;
};

enum {
	HUGETLB_SHMFS_INODE = 1,
	HUGETLB_ANONHUGE_INODE = 2,
};

struct trace_event_raw_vm_unmapped_area {
	struct trace_entry ent;
	long unsigned int addr;
	long unsigned int total_vm;
	long unsigned int flags;
	long unsigned int length;
	long unsigned int low_limit;
	long unsigned int high_limit;
	long unsigned int align_mask;
	long unsigned int align_offset;
	char __data[0];
};

struct trace_event_data_offsets_vm_unmapped_area {};

typedef void (*btf_trace_vm_unmapped_area)(void *, long unsigned int, struct vm_unmapped_area_info *);

struct rmap_walk_control {
	void *arg;
	bool (*rmap_one)(struct page *, struct vm_area_struct *, long unsigned int, void *);
	int (*done)(struct page *);
	struct anon_vma * (*anon_lock)(struct page *);
	bool (*invalid_vma)(struct vm_area_struct *, void *);
};

struct page_referenced_arg {
	int mapcount;
	int referenced;
	long unsigned int vm_flags;
	struct mem_cgroup *memcg;
};

struct vmap_area {
	long unsigned int va_start;
	long unsigned int va_end;
	struct rb_node rb_node;
	struct list_head list;
	union {
		long unsigned int subtree_max_size;
		struct vm_struct *vm;
		struct llist_node purge_list;
	};
};

typedef unsigned int pgtbl_mod_mask;

struct vfree_deferred {
	struct llist_head list;
	struct work_struct wq;
};

enum fit_type {
	NOTHING_FIT = 0,
	FL_FIT_TYPE = 1,
	LE_FIT_TYPE = 2,
	RE_FIT_TYPE = 3,
	NE_FIT_TYPE = 4,
};

struct vmap_block_queue {
	spinlock_t lock;
	struct list_head free;
};

struct vmap_block {
	spinlock_t lock;
	struct vmap_area *va;
	long unsigned int free;
	long unsigned int dirty;
	long unsigned int dirty_min;
	long unsigned int dirty_max;
	struct list_head free_list;
	struct callback_head callback_head;
	struct list_head purge;
};

typedef struct vmap_area *pto_T_____22;

struct page_frag_cache {
	void *va;
	__u16 offset;
	__u16 size;
	unsigned int pagecnt_bias;
	bool pfmemalloc;
};

enum zone_flags {
	ZONE_BOOSTED_WATERMARK = 0,
};

enum memmap_context {
	MEMMAP_EARLY = 0,
	MEMMAP_HOTPLUG = 1,
};

struct mminit_pfnnid_cache {
	long unsigned int last_start;
	long unsigned int last_end;
	int last_nid;
};

struct pcpu_drain {
	struct zone *zone;
	struct work_struct work;
};

struct madvise_walk_private {
	struct mmu_gather *tlb;
	bool pageout;
};

struct vma_swap_readahead {
	short unsigned int win;
	short unsigned int offset;
	short unsigned int nr_pte;
	pte_t *ptes;
};

union swap_header {
	struct {
		char reserved[4086];
		char magic[10];
	} magic;
	struct {
		char bootbits[1024];
		__u32 version;
		__u32 last_page;
		__u32 nr_badpages;
		unsigned char sws_uuid[16];
		unsigned char sws_volume[16];
		__u32 padding[117];
		__u32 badpages[1];
	} info;
};

struct swap_extent {
	struct rb_node rb_node;
	long unsigned int start_page;
	long unsigned int nr_pages;
	sector_t start_block;
};

struct swap_slots_cache {
	bool lock_initialized;
	struct mutex alloc_lock;
	swp_entry_t *slots;
	int nr;
	int cur;
	spinlock_t free_lock;
	swp_entry_t *slots_ret;
	int n_ret;
};

struct dma_pool {
	struct list_head page_list;
	spinlock_t lock;
	size_t size;
	struct device *dev;
	size_t allocation;
	size_t boundary;
	char name[32];
	struct list_head pools;
};

struct dma_page {
	struct list_head page_list;
	void *vaddr;
	dma_addr_t dma;
	unsigned int in_use;
	unsigned int offset;
};

enum string_size_units {
	STRING_UNITS_10 = 0,
	STRING_UNITS_2 = 1,
};

struct resv_map {
	struct kref refs;
	spinlock_t lock;
	struct list_head regions;
	long int adds_in_progress;
	struct list_head region_cache;
	long int region_cache_count;
};

struct file_region {
	struct list_head link;
	long int from;
	long int to;
};

struct huge_bootmem_page {
	struct list_head list;
	struct hstate *hstate;
};

enum vma_resv_mode {
	VMA_NEEDS_RESV = 0,
	VMA_COMMIT_RESV = 1,
	VMA_END_RESV = 2,
	VMA_ADD_RESV = 3,
};

struct node_hstate {
	struct kobject *hugepages_kobj;
	struct kobject *hstate_kobjs[2];
};

struct hugetlb_cgroup;

struct nodemask_scratch {
	nodemask_t mask1;
	nodemask_t mask2;
};

struct sp_node {
	struct rb_node nd;
	long unsigned int start;
	long unsigned int end;
	struct mempolicy *policy;
};

struct mempolicy_operations {
	int (*create)(struct mempolicy *, const nodemask_t *);
	void (*rebind)(struct mempolicy *, const nodemask_t *);
};

struct queue_pages {
	struct list_head *pagelist;
	long unsigned int flags;
	nodemask_t *nmask;
	long unsigned int start;
	long unsigned int end;
	struct vm_area_struct *first;
};

struct mmu_notifier_subscriptions {
	struct hlist_head list;
	bool has_itree;
	spinlock_t lock;
	long unsigned int invalidate_seq;
	long unsigned int active_invalidate_ranges;
	struct rb_root_cached itree;
	wait_queue_head_t wq;
	struct hlist_head deferred_list;
};

struct interval_tree_node {
	struct rb_node rb;
	long unsigned int start;
	long unsigned int last;
	long unsigned int __subtree_last;
};

struct mmu_notifier;

struct mmu_notifier_ops {
	void (*release)(struct mmu_notifier *, struct mm_struct *);
	int (*clear_flush_young)(struct mmu_notifier *, struct mm_struct *, long unsigned int, long unsigned int);
	int (*clear_young)(struct mmu_notifier *, struct mm_struct *, long unsigned int, long unsigned int);
	int (*test_young)(struct mmu_notifier *, struct mm_struct *, long unsigned int);
	void (*change_pte)(struct mmu_notifier *, struct mm_struct *, long unsigned int, pte_t);
	int (*invalidate_range_start)(struct mmu_notifier *, const struct mmu_notifier_range *);
	void (*invalidate_range_end)(struct mmu_notifier *, const struct mmu_notifier_range *);
	void (*invalidate_range)(struct mmu_notifier *, struct mm_struct *, long unsigned int, long unsigned int);
	struct mmu_notifier * (*alloc_notifier)(struct mm_struct *);
	void (*free_notifier)(struct mmu_notifier *);
};

struct mmu_notifier {
	struct hlist_node hlist;
	const struct mmu_notifier_ops *ops;
	struct mm_struct *mm;
	struct callback_head rcu;
	unsigned int users;
};

struct mmu_interval_notifier;

struct mmu_interval_notifier_ops {
	bool (*invalidate)(struct mmu_interval_notifier *, const struct mmu_notifier_range *, long unsigned int);
};

struct mmu_interval_notifier {
	struct interval_tree_node interval_tree;
	const struct mmu_interval_notifier_ops *ops;
	struct mm_struct *mm;
	struct hlist_node deferred_item;
	long unsigned int invalidate_seq;
};

enum stat_item {
	ALLOC_FASTPATH = 0,
	ALLOC_SLOWPATH = 1,
	FREE_FASTPATH = 2,
	FREE_SLOWPATH = 3,
	FREE_FROZEN = 4,
	FREE_ADD_PARTIAL = 5,
	FREE_REMOVE_PARTIAL = 6,
	ALLOC_FROM_PARTIAL = 7,
	ALLOC_SLAB = 8,
	ALLOC_REFILL = 9,
	ALLOC_NODE_MISMATCH = 10,
	FREE_SLAB = 11,
	CPUSLAB_FLUSH = 12,
	DEACTIVATE_FULL = 13,
	DEACTIVATE_EMPTY = 14,
	DEACTIVATE_TO_HEAD = 15,
	DEACTIVATE_TO_TAIL = 16,
	DEACTIVATE_REMOTE_FREES = 17,
	DEACTIVATE_BYPASS = 18,
	ORDER_FALLBACK = 19,
	CMPXCHG_DOUBLE_CPU_FAIL = 20,
	CMPXCHG_DOUBLE_FAIL = 21,
	CPU_PARTIAL_ALLOC = 22,
	CPU_PARTIAL_FREE = 23,
	CPU_PARTIAL_NODE = 24,
	CPU_PARTIAL_DRAIN = 25,
	NR_SLUB_STAT_ITEMS = 26,
};

struct track {
	long unsigned int addr;
	long unsigned int addrs[16];
	int cpu;
	int pid;
	long unsigned int when;
};

enum track_item {
	TRACK_ALLOC = 0,
	TRACK_FREE = 1,
};

struct detached_freelist {
	struct page *page;
	void *tail;
	void *freelist;
	int cnt;
	struct kmem_cache *s;
};

struct location {
	long unsigned int count;
	long unsigned int addr;
	long long int sum_time;
	long int min_time;
	long int max_time;
	long int min_pid;
	long int max_pid;
	long unsigned int cpus[1];
	nodemask_t nodes;
};

struct loc_track {
	long unsigned int max;
	long unsigned int count;
	struct location *loc;
};

enum slab_stat_type {
	SL_ALL = 0,
	SL_PARTIAL = 1,
	SL_CPU = 2,
	SL_OBJECTS = 3,
	SL_TOTAL = 4,
};

struct slab_attribute {
	struct attribute attr;
	ssize_t (*show)(struct kmem_cache *, char *);
	ssize_t (*store)(struct kmem_cache *, const char *, size_t);
};

struct saved_alias {
	struct kmem_cache *s;
	const char *name;
	struct saved_alias *next;
};

enum slab_modes {
	M_NONE = 0,
	M_PARTIAL = 1,
	M_FULL = 2,
	M_FREE = 3,
};

struct buffer_head;

typedef void bh_end_io_t(struct buffer_head *, int);

struct buffer_head {
	long unsigned int b_state;
	struct buffer_head *b_this_page;
	struct page *b_page;
	sector_t b_blocknr;
	size_t b_size;
	char *b_data;
	struct block_device *b_bdev;
	bh_end_io_t *b_end_io;
	void *b_private;
	struct list_head b_assoc_buffers;
	struct address_space *b_assoc_map;
	atomic_t b_count;
	spinlock_t b_uptodate_lock;
};

typedef struct page *new_page_t(struct page *, long unsigned int);

typedef void free_page_t(struct page *, long unsigned int);

enum bh_state_bits {
	BH_Uptodate = 0,
	BH_Dirty = 1,
	BH_Lock = 2,
	BH_Req = 3,
	BH_Mapped = 4,
	BH_New = 5,
	BH_Async_Read = 6,
	BH_Async_Write = 7,
	BH_Delay = 8,
	BH_Boundary = 9,
	BH_Write_EIO = 10,
	BH_Unwritten = 11,
	BH_Quiet = 12,
	BH_Meta = 13,
	BH_Prio = 14,
	BH_Defer_Completion = 15,
	BH_PrivateStart = 16,
};

struct trace_event_raw_mm_migrate_pages {
	struct trace_entry ent;
	long unsigned int succeeded;
	long unsigned int failed;
	enum migrate_mode mode;
	int reason;
	char __data[0];
};

struct trace_event_data_offsets_mm_migrate_pages {};

typedef void (*btf_trace_mm_migrate_pages)(void *, long unsigned int, long unsigned int, enum migrate_mode, int);

struct hugetlbfs_inode_info {
	struct shared_policy policy;
	struct inode vfs_inode;
	unsigned int seals;
};

struct open_how {
	__u64 flags;
	__u64 mode;
	__u64 resolve;
};

typedef s32 compat_off_t;

struct fs_context_operations___2;

struct open_flags {
	int open_flag;
	umode_t mode;
	int acc_mode;
	int intent;
	int lookup_flags;
};

typedef __kernel_long_t __kernel_off_t;

typedef __kernel_off_t off_t;

struct file_dedupe_range_info {
	__s64 dest_fd;
	__u64 dest_offset;
	__u64 bytes_deduped;
	__s32 status;
	__u32 reserved;
};

struct file_dedupe_range {
	__u64 src_offset;
	__u64 src_length;
	__u16 dest_count;
	__u16 reserved1;
	__u32 reserved2;
	struct file_dedupe_range_info info[0];
};

typedef int __kernel_rwf_t;

typedef __kernel_rwf_t rwf_t;

typedef s32 compat_ssize_t;

enum vfs_get_super_keying {
	vfs_get_single_super = 0,
	vfs_get_single_reconf_super = 1,
	vfs_get_keyed_super = 2,
	vfs_get_independent_super = 3,
};

struct kobj_map;

struct char_device_struct {
	struct char_device_struct *next;
	unsigned int major;
	unsigned int baseminor;
	int minorct;
	char name[64];
	struct cdev *cdev;
};

struct stat {
	__kernel_ulong_t st_dev;
	__kernel_ulong_t st_ino;
	__kernel_ulong_t st_nlink;
	unsigned int st_mode;
	unsigned int st_uid;
	unsigned int st_gid;
	unsigned int __pad0;
	__kernel_ulong_t st_rdev;
	__kernel_long_t st_size;
	__kernel_long_t st_blksize;
	__kernel_long_t st_blocks;
	__kernel_ulong_t st_atime;
	__kernel_ulong_t st_atime_nsec;
	__kernel_ulong_t st_mtime;
	__kernel_ulong_t st_mtime_nsec;
	__kernel_ulong_t st_ctime;
	__kernel_ulong_t st_ctime_nsec;
	__kernel_long_t __unused[3];
};

struct __old_kernel_stat {
	short unsigned int st_dev;
	short unsigned int st_ino;
	short unsigned int st_mode;
	short unsigned int st_nlink;
	short unsigned int st_uid;
	short unsigned int st_gid;
	short unsigned int st_rdev;
	unsigned int st_size;
	unsigned int st_atime;
	unsigned int st_mtime;
	unsigned int st_ctime;
};

struct statx_timestamp {
	__s64 tv_sec;
	__u32 tv_nsec;
	__s32 __reserved;
};

struct statx {
	__u32 stx_mask;
	__u32 stx_blksize;
	__u64 stx_attributes;
	__u32 stx_nlink;
	__u32 stx_uid;
	__u32 stx_gid;
	__u16 stx_mode;
	__u16 __spare0[1];
	__u64 stx_ino;
	__u64 stx_size;
	__u64 stx_blocks;
	__u64 stx_attributes_mask;
	struct statx_timestamp stx_atime;
	struct statx_timestamp stx_btime;
	struct statx_timestamp stx_ctime;
	struct statx_timestamp stx_mtime;
	__u32 stx_rdev_major;
	__u32 stx_rdev_minor;
	__u32 stx_dev_major;
	__u32 stx_dev_minor;
	__u64 stx_mnt_id;
	__u64 __spare2;
	__u64 __spare3[12];
};

struct mount;

struct mnt_namespace {
	atomic_t count;
	struct ns_common ns;
	struct mount *root;
	struct list_head list;
	spinlock_t ns_lock;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	u64 seq;
	wait_queue_head_t poll;
	u64 event;
	unsigned int mounts;
	unsigned int pending_mounts;
};

typedef u32 compat_ino_t;

typedef u16 __compat_uid_t;

typedef u16 __compat_gid_t;

typedef u16 compat_mode_t;

typedef u16 compat_dev_t;

typedef u16 compat_nlink_t;

struct compat_stat {
	compat_dev_t st_dev;
	u16 __pad1;
	compat_ino_t st_ino;
	compat_mode_t st_mode;
	compat_nlink_t st_nlink;
	__compat_uid_t st_uid;
	__compat_gid_t st_gid;
	compat_dev_t st_rdev;
	u16 __pad2;
	u32 st_size;
	u32 st_blksize;
	u32 st_blocks;
	u32 st_atime;
	u32 st_atime_nsec;
	u32 st_mtime;
	u32 st_mtime_nsec;
	u32 st_ctime;
	u32 st_ctime_nsec;
	u32 __unused4;
	u32 __unused5;
};

struct mnt_pcp;

struct mountpoint;

struct mount {
	struct hlist_node mnt_hash;
	struct mount *mnt_parent;
	struct dentry *mnt_mountpoint;
	struct vfsmount mnt;
	union {
		struct callback_head mnt_rcu;
		struct llist_node mnt_llist;
	};
	struct mnt_pcp *mnt_pcp;
	struct list_head mnt_mounts;
	struct list_head mnt_child;
	struct list_head mnt_instance;
	const char *mnt_devname;
	struct list_head mnt_list;
	struct list_head mnt_expire;
	struct list_head mnt_share;
	struct list_head mnt_slave_list;
	struct list_head mnt_slave;
	struct mount *mnt_master;
	struct mnt_namespace *mnt_ns;
	struct mountpoint *mnt_mp;
	union {
		struct hlist_node mnt_mp_list;
		struct hlist_node mnt_umount;
	};
	struct list_head mnt_umounting;
	struct fsnotify_mark_connector *mnt_fsnotify_marks;
	__u32 mnt_fsnotify_mask;
	int mnt_id;
	int mnt_group_id;
	int mnt_expiry_mark;
	struct hlist_head mnt_pins;
	struct hlist_head mnt_stuck_children;
};

struct mnt_pcp {
	int mnt_count;
	int mnt_writers;
};

struct mountpoint {
	struct hlist_node m_hash;
	struct dentry *m_dentry;
	struct hlist_head m_list;
	int m_count;
};

typedef short unsigned int ushort;

struct user_arg_ptr {
	bool is_compat;
	union {
		const char * const *native;
		const compat_uptr_t *compat;
	} ptr;
};

enum inode_i_mutex_lock_class {
	I_MUTEX_NORMAL = 0,
	I_MUTEX_PARENT = 1,
	I_MUTEX_CHILD = 2,
	I_MUTEX_XATTR = 3,
	I_MUTEX_NONDIR2 = 4,
	I_MUTEX_PARENT2 = 5,
};

struct pseudo_fs_context {
	const struct super_operations *ops;
	const struct xattr_handler **xattr;
	const struct dentry_operations *dops;
	long unsigned int magic;
};

struct name_snapshot {
	struct qstr name;
	unsigned char inline_name[32];
};

struct saved {
	struct path link;
	struct delayed_call done;
	const char *name;
	unsigned int seq;
};

struct nameidata {
	struct path path;
	struct qstr last;
	struct path root;
	struct inode *inode;
	unsigned int flags;
	unsigned int seq;
	unsigned int m_seq;
	unsigned int r_seq;
	int last_type;
	unsigned int depth;
	int total_link_count;
	struct saved *stack;
	struct saved internal[2];
	struct filename *name;
	struct nameidata *saved;
	unsigned int root_seq;
	int dfd;
	kuid_t dir_uid;
	umode_t dir_mode;
};

enum {
	LAST_NORM = 0,
	LAST_ROOT = 1,
	LAST_DOT = 2,
	LAST_DOTDOT = 3,
};

enum {
	WALK_TRAILING = 1,
	WALK_MORE = 2,
	WALK_NOFOLLOW = 4,
};

struct word_at_a_time {
	const long unsigned int one_bits;
	const long unsigned int high_bits;
};

struct f_owner_ex {
	int type;
	__kernel_pid_t pid;
};

struct flock {
	short int l_type;
	short int l_whence;
	__kernel_off_t l_start;
	__kernel_off_t l_len;
	__kernel_pid_t l_pid;
};

struct compat_flock {
	short int l_type;
	short int l_whence;
	compat_off_t l_start;
	compat_off_t l_len;
	compat_pid_t l_pid;
};

struct compat_flock64 {
	short int l_type;
	short int l_whence;
	compat_loff_t l_start;
	compat_loff_t l_len;
	compat_pid_t l_pid;
} __attribute__((packed));

struct file_clone_range {
	__s64 src_fd;
	__u64 src_offset;
	__u64 src_length;
	__u64 dest_offset;
};

typedef int get_block_t(struct inode *, sector_t, struct buffer_head *, int);

struct fiemap_extent;

struct fiemap_extent_info {
	unsigned int fi_flags;
	unsigned int fi_extents_mapped;
	unsigned int fi_extents_max;
	struct fiemap_extent *fi_extents_start;
};

struct space_resv {
	__s16 l_type;
	__s16 l_whence;
	__s64 l_start;
	__s64 l_len;
	__s32 l_sysid;
	__u32 l_pid;
	__s32 l_pad[4];
};

struct space_resv_32 {
	__s16 l_type;
	__s16 l_whence;
	__s64 l_start;
	__s64 l_len;
	__s32 l_sysid;
	__u32 l_pid;
	__s32 l_pad[4];
} __attribute__((packed));

struct fiemap_extent {
	__u64 fe_logical;
	__u64 fe_physical;
	__u64 fe_length;
	__u64 fe_reserved64[2];
	__u32 fe_flags;
	__u32 fe_reserved[3];
};

struct fiemap {
	__u64 fm_start;
	__u64 fm_length;
	__u32 fm_flags;
	__u32 fm_mapped_extents;
	__u32 fm_extent_count;
	__u32 fm_reserved;
	struct fiemap_extent fm_extents[0];
};

struct linux_dirent64 {
	u64 d_ino;
	s64 d_off;
	short unsigned int d_reclen;
	unsigned char d_type;
	char d_name[0];
};

struct old_linux_dirent {
	long unsigned int d_ino;
	long unsigned int d_offset;
	short unsigned int d_namlen;
	char d_name[1];
};

struct readdir_callback {
	struct dir_context ctx;
	struct old_linux_dirent *dirent;
	int result;
};

struct linux_dirent {
	long unsigned int d_ino;
	long unsigned int d_off;
	short unsigned int d_reclen;
	char d_name[1];
};

struct getdents_callback {
	struct dir_context ctx;
	struct linux_dirent *current_dir;
	int prev_reclen;
	int count;
	int error;
};

struct getdents_callback64 {
	struct dir_context ctx;
	struct linux_dirent64 *current_dir;
	int prev_reclen;
	int count;
	int error;
};

struct compat_old_linux_dirent {
	compat_ulong_t d_ino;
	compat_ulong_t d_offset;
	short unsigned int d_namlen;
	char d_name[1];
};

struct compat_readdir_callback {
	struct dir_context ctx;
	struct compat_old_linux_dirent *dirent;
	int result;
};

struct compat_linux_dirent {
	compat_ulong_t d_ino;
	compat_ulong_t d_off;
	short unsigned int d_reclen;
	char d_name[1];
};

struct compat_getdents_callback {
	struct dir_context ctx;
	struct compat_linux_dirent *current_dir;
	int prev_reclen;
	int count;
	int error;
};

typedef struct {
	long unsigned int fds_bits[16];
} __kernel_fd_set;

typedef __kernel_fd_set fd_set;

struct poll_table_entry {
	struct file *filp;
	__poll_t key;
	wait_queue_entry_t wait;
	wait_queue_head_t *wait_address;
};

struct poll_table_page;

struct poll_wqueues {
	poll_table pt;
	struct poll_table_page *table;
	struct task_struct *polling_task;
	int triggered;
	int error;
	int inline_index;
	struct poll_table_entry inline_entries[9];
};

struct poll_table_page {
	struct poll_table_page *next;
	struct poll_table_entry *entry;
	struct poll_table_entry entries[0];
};

enum poll_time_type {
	PT_TIMEVAL = 0,
	PT_OLD_TIMEVAL = 1,
	PT_TIMESPEC = 2,
	PT_OLD_TIMESPEC = 3,
};

typedef struct {
	long unsigned int *in;
	long unsigned int *out;
	long unsigned int *ex;
	long unsigned int *res_in;
	long unsigned int *res_out;
	long unsigned int *res_ex;
} fd_set_bits;

struct sigset_argpack {
	sigset_t *p;
	size_t size;
};

struct poll_list {
	struct poll_list *next;
	int len;
	struct pollfd entries[0];
};

struct compat_sel_arg_struct {
	compat_ulong_t n;
	compat_uptr_t inp;
	compat_uptr_t outp;
	compat_uptr_t exp;
	compat_uptr_t tvp;
};

struct compat_sigset_argpack {
	compat_uptr_t p;
	compat_size_t size;
};

enum dentry_d_lock_class {
	DENTRY_D_LOCK_NORMAL = 0,
	DENTRY_D_LOCK_NESTED = 1,
};

struct external_name {
	union {
		atomic_t count;
		struct callback_head head;
	} u;
	unsigned char name[0];
};

enum d_walk_ret {
	D_WALK_CONTINUE = 0,
	D_WALK_QUIT = 1,
	D_WALK_NORETRY = 2,
	D_WALK_SKIP = 3,
};

struct check_mount {
	struct vfsmount *mnt;
	unsigned int mounted;
};

struct select_data {
	struct dentry *start;
	union {
		long int found;
		struct dentry *victim;
	};
	struct list_head dispose;
};

typedef long int pao_T_____6;

struct fsxattr {
	__u32 fsx_xflags;
	__u32 fsx_extsize;
	__u32 fsx_nextents;
	__u32 fsx_projid;
	__u32 fsx_cowextsize;
	unsigned char fsx_pad[8];
};

enum file_time_flags {
	S_ATIME = 1,
	S_MTIME = 2,
	S_CTIME = 4,
	S_VERSION = 8,
};

struct proc_mounts {
	struct mnt_namespace *ns;
	struct path root;
	int (*show)(struct seq_file *, struct vfsmount *);
	struct mount cursor;
};

enum umount_tree_flags {
	UMOUNT_SYNC = 1,
	UMOUNT_PROPAGATE = 2,
	UMOUNT_CONNECTED = 4,
};

struct simple_transaction_argresp {
	ssize_t size;
	char data[0];
};

struct simple_attr {
	int (*get)(void *, u64 *);
	int (*set)(void *, u64);
	char get_buf[24];
	char set_buf[24];
	void *data;
	const char *fmt;
	struct mutex mutex;
};

struct wb_completion {
	atomic_t cnt;
	wait_queue_head_t *waitq;
};

struct wb_writeback_work {
	long int nr_pages;
	struct super_block *sb;
	long unsigned int *older_than_this;
	enum writeback_sync_modes sync_mode;
	unsigned int tagged_writepages: 1;
	unsigned int for_kupdate: 1;
	unsigned int range_cyclic: 1;
	unsigned int for_background: 1;
	unsigned int for_sync: 1;
	unsigned int auto_free: 1;
	enum wb_reason reason;
	struct list_head list;
	struct wb_completion *done;
};

struct trace_event_raw_writeback_page_template {
	struct trace_entry ent;
	char name[32];
	ino_t ino;
	long unsigned int index;
	char __data[0];
};

struct trace_event_raw_writeback_dirty_inode_template {
	struct trace_entry ent;
	char name[32];
	ino_t ino;
	long unsigned int state;
	long unsigned int flags;
	char __data[0];
};

struct trace_event_raw_writeback_write_inode_template {
	struct trace_entry ent;
	char name[32];
	ino_t ino;
	int sync_mode;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_work_class {
	struct trace_entry ent;
	char name[32];
	long int nr_pages;
	dev_t sb_dev;
	int sync_mode;
	int for_kupdate;
	int range_cyclic;
	int for_background;
	int reason;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_pages_written {
	struct trace_entry ent;
	long int pages;
	char __data[0];
};

struct trace_event_raw_writeback_class {
	struct trace_entry ent;
	char name[32];
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_bdi_register {
	struct trace_entry ent;
	char name[32];
	char __data[0];
};

struct trace_event_raw_wbc_class {
	struct trace_entry ent;
	char name[32];
	long int nr_to_write;
	long int pages_skipped;
	int sync_mode;
	int for_kupdate;
	int for_background;
	int for_reclaim;
	int range_cyclic;
	long int range_start;
	long int range_end;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_queue_io {
	struct trace_entry ent;
	char name[32];
	long unsigned int older;
	long int age;
	int moved;
	int reason;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_global_dirty_state {
	struct trace_entry ent;
	long unsigned int nr_dirty;
	long unsigned int nr_writeback;
	long unsigned int background_thresh;
	long unsigned int dirty_thresh;
	long unsigned int dirty_limit;
	long unsigned int nr_dirtied;
	long unsigned int nr_written;
	char __data[0];
};

struct trace_event_raw_bdi_dirty_ratelimit {
	struct trace_entry ent;
	char bdi[32];
	long unsigned int write_bw;
	long unsigned int avg_write_bw;
	long unsigned int dirty_rate;
	long unsigned int dirty_ratelimit;
	long unsigned int task_ratelimit;
	long unsigned int balanced_dirty_ratelimit;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_balance_dirty_pages {
	struct trace_entry ent;
	char bdi[32];
	long unsigned int limit;
	long unsigned int setpoint;
	long unsigned int dirty;
	long unsigned int bdi_setpoint;
	long unsigned int bdi_dirty;
	long unsigned int dirty_ratelimit;
	long unsigned int task_ratelimit;
	unsigned int dirtied;
	unsigned int dirtied_pause;
	long unsigned int paused;
	long int pause;
	long unsigned int period;
	long int think;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_sb_inodes_requeue {
	struct trace_entry ent;
	char name[32];
	ino_t ino;
	long unsigned int state;
	long unsigned int dirtied_when;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_congest_waited_template {
	struct trace_entry ent;
	unsigned int usec_timeout;
	unsigned int usec_delayed;
	char __data[0];
};

struct trace_event_raw_writeback_single_inode_template {
	struct trace_entry ent;
	char name[32];
	ino_t ino;
	long unsigned int state;
	long unsigned int dirtied_when;
	long unsigned int writeback_index;
	long int nr_to_write;
	long unsigned int wrote;
	ino_t cgroup_ino;
	char __data[0];
};

struct trace_event_raw_writeback_inode_template {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	long unsigned int state;
	__u16 mode;
	long unsigned int dirtied_when;
	char __data[0];
};

struct trace_event_data_offsets_writeback_page_template {};

struct trace_event_data_offsets_writeback_dirty_inode_template {};

struct trace_event_data_offsets_writeback_write_inode_template {};

struct trace_event_data_offsets_writeback_work_class {};

struct trace_event_data_offsets_writeback_pages_written {};

struct trace_event_data_offsets_writeback_class {};

struct trace_event_data_offsets_writeback_bdi_register {};

struct trace_event_data_offsets_wbc_class {};

struct trace_event_data_offsets_writeback_queue_io {};

struct trace_event_data_offsets_global_dirty_state {};

struct trace_event_data_offsets_bdi_dirty_ratelimit {};

struct trace_event_data_offsets_balance_dirty_pages {};

struct trace_event_data_offsets_writeback_sb_inodes_requeue {};

struct trace_event_data_offsets_writeback_congest_waited_template {};

struct trace_event_data_offsets_writeback_single_inode_template {};

struct trace_event_data_offsets_writeback_inode_template {};

typedef void (*btf_trace_writeback_dirty_page)(void *, struct page *, struct address_space *);

typedef void (*btf_trace_wait_on_page_writeback)(void *, struct page *, struct address_space *);

typedef void (*btf_trace_writeback_mark_inode_dirty)(void *, struct inode *, int);

typedef void (*btf_trace_writeback_dirty_inode_start)(void *, struct inode *, int);

typedef void (*btf_trace_writeback_dirty_inode)(void *, struct inode *, int);

typedef void (*btf_trace_writeback_write_inode_start)(void *, struct inode *, struct writeback_control *);

typedef void (*btf_trace_writeback_write_inode)(void *, struct inode *, struct writeback_control *);

typedef void (*btf_trace_writeback_queue)(void *, struct bdi_writeback *, struct wb_writeback_work *);

typedef void (*btf_trace_writeback_exec)(void *, struct bdi_writeback *, struct wb_writeback_work *);

typedef void (*btf_trace_writeback_start)(void *, struct bdi_writeback *, struct wb_writeback_work *);

typedef void (*btf_trace_writeback_written)(void *, struct bdi_writeback *, struct wb_writeback_work *);

typedef void (*btf_trace_writeback_wait)(void *, struct bdi_writeback *, struct wb_writeback_work *);

typedef void (*btf_trace_writeback_pages_written)(void *, long int);

typedef void (*btf_trace_writeback_wake_background)(void *, struct bdi_writeback *);

typedef void (*btf_trace_writeback_bdi_register)(void *, struct backing_dev_info *);

typedef void (*btf_trace_wbc_writepage)(void *, struct writeback_control *, struct backing_dev_info *);

typedef void (*btf_trace_writeback_queue_io)(void *, struct bdi_writeback *, struct wb_writeback_work *, int);

typedef void (*btf_trace_global_dirty_state)(void *, long unsigned int, long unsigned int);

typedef void (*btf_trace_bdi_dirty_ratelimit)(void *, struct bdi_writeback *, long unsigned int, long unsigned int);

typedef void (*btf_trace_balance_dirty_pages)(void *, struct bdi_writeback *, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long int, long unsigned int);

typedef void (*btf_trace_writeback_sb_inodes_requeue)(void *, struct inode *);

typedef void (*btf_trace_writeback_congestion_wait)(void *, unsigned int, unsigned int);

typedef void (*btf_trace_writeback_wait_iff_congested)(void *, unsigned int, unsigned int);

typedef void (*btf_trace_writeback_single_inode_start)(void *, struct inode *, struct writeback_control *, long unsigned int);

typedef void (*btf_trace_writeback_single_inode)(void *, struct inode *, struct writeback_control *, long unsigned int);

typedef void (*btf_trace_writeback_lazytime)(void *, struct inode *);

typedef void (*btf_trace_writeback_lazytime_iput)(void *, struct inode *);

typedef void (*btf_trace_writeback_dirty_inode_enqueue)(void *, struct inode *);

typedef void (*btf_trace_sb_mark_inode_writeback)(void *, struct inode *);

typedef void (*btf_trace_sb_clear_inode_writeback)(void *, struct inode *);

struct splice_desc {
	size_t total_len;
	unsigned int len;
	unsigned int flags;
	union {
		void *userptr;
		struct file *file;
		void *data;
	} u;
	loff_t pos;
	loff_t *opos;
	size_t num_spliced;
	bool need_wakeup;
};

typedef int splice_actor(struct pipe_inode_info *, struct pipe_buffer *, struct splice_desc *);

typedef int splice_direct_actor(struct pipe_inode_info *, struct splice_desc *);

struct old_utimbuf32 {
	old_time32_t actime;
	old_time32_t modtime;
};

struct utimbuf {
	__kernel_old_time_t actime;
	__kernel_old_time_t modtime;
};

typedef int __kernel_daddr_t;

struct ustat {
	__kernel_daddr_t f_tfree;
	__kernel_ino_t f_tinode;
	char f_fname[6];
	char f_fpack[6];
};

struct statfs {
	__kernel_long_t f_type;
	__kernel_long_t f_bsize;
	__kernel_long_t f_blocks;
	__kernel_long_t f_bfree;
	__kernel_long_t f_bavail;
	__kernel_long_t f_files;
	__kernel_long_t f_ffree;
	__kernel_fsid_t f_fsid;
	__kernel_long_t f_namelen;
	__kernel_long_t f_frsize;
	__kernel_long_t f_flags;
	__kernel_long_t f_spare[4];
};

struct statfs64 {
	__kernel_long_t f_type;
	__kernel_long_t f_bsize;
	__u64 f_blocks;
	__u64 f_bfree;
	__u64 f_bavail;
	__u64 f_files;
	__u64 f_ffree;
	__kernel_fsid_t f_fsid;
	__kernel_long_t f_namelen;
	__kernel_long_t f_frsize;
	__kernel_long_t f_flags;
	__kernel_long_t f_spare[4];
};

struct compat_statfs64 {
	__u32 f_type;
	__u32 f_bsize;
	__u64 f_blocks;
	__u64 f_bfree;
	__u64 f_bavail;
	__u64 f_files;
	__u64 f_ffree;
	__kernel_fsid_t f_fsid;
	__u32 f_namelen;
	__u32 f_frsize;
	__u32 f_flags;
	__u32 f_spare[4];
} __attribute__((packed));

typedef s32 compat_daddr_t;

typedef __kernel_fsid_t compat_fsid_t;

struct compat_statfs {
	int f_type;
	int f_bsize;
	int f_blocks;
	int f_bfree;
	int f_bavail;
	int f_files;
	int f_ffree;
	compat_fsid_t f_fsid;
	int f_namelen;
	int f_frsize;
	int f_flags;
	int f_spare[4];
};

struct compat_ustat {
	compat_daddr_t f_tfree;
	compat_ino_t f_tinode;
	char f_fname[6];
	char f_fpack[6];
};

typedef struct ns_common *ns_get_path_helper_t(void *);

struct ns_get_path_task_args {
	const struct proc_ns_operations *ns_ops;
	struct task_struct *task;
};

enum legacy_fs_param {
	LEGACY_FS_UNSET_PARAMS = 0,
	LEGACY_FS_MONOLITHIC_PARAMS = 1,
	LEGACY_FS_INDIVIDUAL_PARAMS = 2,
};

struct legacy_fs_context {
	char *legacy_data;
	size_t data_size;
	enum legacy_fs_param param_type;
};

enum fsconfig_command {
	FSCONFIG_SET_FLAG = 0,
	FSCONFIG_SET_STRING = 1,
	FSCONFIG_SET_BINARY = 2,
	FSCONFIG_SET_PATH = 3,
	FSCONFIG_SET_PATH_EMPTY = 4,
	FSCONFIG_SET_FD = 5,
	FSCONFIG_CMD_CREATE = 6,
	FSCONFIG_CMD_RECONFIGURE = 7,
};

struct dax_device;

struct iomap_page_ops;

struct iomap___2 {
	u64 addr;
	loff_t offset;
	u64 length;
	u16 type;
	u16 flags;
	struct block_device *bdev;
	struct dax_device *dax_dev;
	void *inline_data;
	void *private;
	const struct iomap_page_ops *page_ops;
};

struct iomap_page_ops {
	int (*page_prepare)(struct inode *, loff_t, unsigned int, struct iomap___2 *);
	void (*page_done)(struct inode *, loff_t, unsigned int, struct page *, struct iomap___2 *);
};

struct decrypt_bh_ctx {
	struct work_struct work;
	struct buffer_head *bh;
};

struct bh_lru {
	struct buffer_head *bhs[16];
};

struct bh_accounting {
	int nr;
	int ratelimit;
};

typedef struct buffer_head *pto_T_____23;

enum {
	DISK_EVENT_MEDIA_CHANGE = 1,
	DISK_EVENT_EJECT_REQUEST = 2,
};

struct blk_integrity_profile;

struct blk_integrity {
	const struct blk_integrity_profile *profile;
	unsigned char flags;
	unsigned char tuple_size;
	unsigned char interval_exp;
	unsigned char tag_size;
};

enum {
	BIOSET_NEED_BVECS = 1,
	BIOSET_NEED_RESCUER = 2,
};

struct bdev_inode {
	struct block_device bdev;
	struct inode vfs_inode;
};

struct blkdev_dio {
	union {
		struct kiocb *iocb;
		struct task_struct *waiter;
	};
	size_t size;
	atomic_t ref;
	bool multi_bio: 1;
	bool should_dirty: 1;
	bool is_sync: 1;
	struct bio bio;
};

struct bd_holder_disk {
	struct list_head list;
	struct gendisk *disk;
	int refcnt;
};

typedef int dio_iodone_t(struct kiocb *, loff_t, ssize_t, void *);

typedef void dio_submit_t(struct bio *, struct inode *, loff_t);

enum {
	DIO_LOCKING = 1,
	DIO_SKIP_HOLES = 2,
};

struct dio_submit {
	struct bio *bio;
	unsigned int blkbits;
	unsigned int blkfactor;
	unsigned int start_zero_done;
	int pages_in_io;
	sector_t block_in_file;
	unsigned int blocks_available;
	int reap_counter;
	sector_t final_block_in_request;
	int boundary;
	get_block_t *get_block;
	dio_submit_t *submit_io;
	loff_t logical_offset_in_bio;
	sector_t final_block_in_bio;
	sector_t next_block_for_io;
	struct page *cur_page;
	unsigned int cur_page_offset;
	unsigned int cur_page_len;
	sector_t cur_page_block;
	loff_t cur_page_fs_offset;
	struct iov_iter *iter;
	unsigned int head;
	unsigned int tail;
	size_t from;
	size_t to;
};

struct dio {
	int flags;
	int op;
	int op_flags;
	blk_qc_t bio_cookie;
	struct gendisk *bio_disk;
	struct inode *inode;
	loff_t i_size;
	dio_iodone_t *end_io;
	void *private;
	spinlock_t bio_lock;
	int page_errors;
	int is_async;
	bool defer_completion;
	bool should_dirty;
	int io_error;
	long unsigned int refcount;
	struct bio *bio_list;
	struct task_struct *waiter;
	struct kiocb *iocb;
	ssize_t result;
	union {
		struct page *pages[64];
		struct work_struct complete_work;
	};
	long: 64;
};

struct bvec_iter_all {
	struct bio_vec bv;
	int idx;
	unsigned int done;
};

struct mpage_readpage_args {
	struct bio *bio;
	struct page *page;
	unsigned int nr_pages;
	bool is_readahead;
	sector_t last_block_in_bio;
	struct buffer_head map_bh;
	long unsigned int first_logical_block;
	get_block_t *get_block;
};

struct mpage_data {
	struct bio *bio;
	sector_t last_block_in_bio;
	get_block_t *get_block;
	unsigned int use_writepage;
};

typedef u32 nlink_t;

typedef int (*proc_write_t)(struct file *, char *, size_t);

struct proc_dir_entry {
	atomic_t in_use;
	refcount_t refcnt;
	struct list_head pde_openers;
	spinlock_t pde_unload_lock;
	struct completion *pde_unload_completion;
	const struct inode_operations *proc_iops;
	union {
		const struct proc_ops *proc_ops;
		const struct file_operations *proc_dir_ops;
	};
	const struct dentry_operations *proc_dops;
	union {
		const struct seq_operations *seq_ops;
		int (*single_show)(struct seq_file *, void *);
	};
	proc_write_t write;
	void *data;
	unsigned int state_size;
	unsigned int low_ino;
	nlink_t nlink;
	kuid_t uid;
	kgid_t gid;
	loff_t size;
	struct proc_dir_entry *parent;
	struct rb_root subdir;
	struct rb_node subdir_node;
	char *name;
	umode_t mode;
	u8 flags;
	u8 namelen;
	char inline_name[0];
};

union proc_op {
	int (*proc_get_link)(struct dentry *, struct path *);
	int (*proc_show)(struct seq_file *, struct pid_namespace *, struct pid *, struct task_struct *);
	const char *lsm;
};

struct proc_inode {
	struct pid *pid;
	unsigned int fd;
	union proc_op op;
	struct proc_dir_entry *pde;
	struct ctl_table_header *sysctl;
	struct ctl_table *sysctl_entry;
	struct hlist_node sibling_inodes;
	const struct proc_ns_operations *ns_ops;
	struct inode vfs_inode;
};

struct proc_fs_opts {
	int flag;
	const char *str;
};

struct file_handle {
	__u32 handle_bytes;
	int handle_type;
	unsigned char f_handle[0];
};

struct inotify_inode_mark {
	struct fsnotify_mark fsn_mark;
	int wd;
};

struct dnotify_struct {
	struct dnotify_struct *dn_next;
	__u32 dn_mask;
	int dn_fd;
	struct file *dn_filp;
	fl_owner_t dn_owner;
};

struct dnotify_mark {
	struct fsnotify_mark fsn_mark;
	struct dnotify_struct *dn;
};

struct inotify_event_info {
	struct fsnotify_event fse;
	u32 mask;
	int wd;
	u32 sync_cookie;
	int name_len;
	char name[0];
};

struct inotify_event {
	__s32 wd;
	__u32 mask;
	__u32 cookie;
	__u32 len;
	char name[0];
};

struct epoll_event {
	__poll_t events;
	__u64 data;
} __attribute__((packed));

struct epoll_filefd {
	struct file *file;
	int fd;
} __attribute__((packed));

struct nested_call_node {
	struct list_head llink;
	void *cookie;
	void *ctx;
};

struct nested_calls {
	struct list_head tasks_call_list;
	spinlock_t lock;
};

struct eventpoll;

struct epitem {
	union {
		struct rb_node rbn;
		struct callback_head rcu;
	};
	struct list_head rdllink;
	struct epitem *next;
	struct epoll_filefd ffd;
	int nwait;
	struct list_head pwqlist;
	struct eventpoll *ep;
	struct list_head fllink;
	struct wakeup_source *ws;
	struct epoll_event event;
};

struct eventpoll {
	struct mutex mtx;
	wait_queue_head_t wq;
	wait_queue_head_t poll_wait;
	struct list_head rdllist;
	rwlock_t lock;
	struct rb_root_cached rbr;
	struct epitem *ovflist;
	struct wakeup_source *ws;
	struct user_struct *user;
	struct file *file;
	struct list_head visited_list_link;
	int visited;
	unsigned int napi_id;
};

struct eppoll_entry {
	struct list_head llink;
	struct epitem *base;
	wait_queue_entry_t wait;
	wait_queue_head_t *whead;
};

struct ep_pqueue {
	poll_table pt;
	struct epitem *epi;
};

struct ep_send_events_data {
	int maxevents;
	struct epoll_event *events;
	int res;
};

struct signalfd_siginfo {
	__u32 ssi_signo;
	__s32 ssi_errno;
	__s32 ssi_code;
	__u32 ssi_pid;
	__u32 ssi_uid;
	__s32 ssi_fd;
	__u32 ssi_tid;
	__u32 ssi_band;
	__u32 ssi_overrun;
	__u32 ssi_trapno;
	__s32 ssi_status;
	__s32 ssi_int;
	__u64 ssi_ptr;
	__u64 ssi_utime;
	__u64 ssi_stime;
	__u64 ssi_addr;
	__u16 ssi_addr_lsb;
	__u16 __pad2;
	__s32 ssi_syscall;
	__u64 ssi_call_addr;
	__u32 ssi_arch;
	__u8 __pad[28];
};

struct signalfd_ctx {
	sigset_t sigmask;
};

struct timerfd_ctx {
	union {
		struct hrtimer tmr;
		struct alarm alarm;
	} t;
	ktime_t tintv;
	ktime_t moffs;
	wait_queue_head_t wqh;
	u64 ticks;
	int clockid;
	short unsigned int expired;
	short unsigned int settime_flags;
	struct callback_head rcu;
	struct list_head clist;
	spinlock_t cancel_lock;
	bool might_cancel;
};

struct eventfd_ctx {
	struct kref kref;
	wait_queue_head_t wqh;
	__u64 count;
	unsigned int flags;
	int id;
};

struct kioctx;

struct kioctx_table {
	struct callback_head rcu;
	unsigned int nr;
	struct kioctx *table[0];
};

typedef __kernel_ulong_t aio_context_t;

enum {
	IOCB_CMD_PREAD = 0,
	IOCB_CMD_PWRITE = 1,
	IOCB_CMD_FSYNC = 2,
	IOCB_CMD_FDSYNC = 3,
	IOCB_CMD_POLL = 5,
	IOCB_CMD_NOOP = 6,
	IOCB_CMD_PREADV = 7,
	IOCB_CMD_PWRITEV = 8,
};

struct io_event {
	__u64 data;
	__u64 obj;
	__s64 res;
	__s64 res2;
};

struct iocb {
	__u64 aio_data;
	__u32 aio_key;
	__kernel_rwf_t aio_rw_flags;
	__u16 aio_lio_opcode;
	__s16 aio_reqprio;
	__u32 aio_fildes;
	__u64 aio_buf;
	__u64 aio_nbytes;
	__s64 aio_offset;
	__u64 aio_reserved2;
	__u32 aio_flags;
	__u32 aio_resfd;
};

typedef int kiocb_cancel_fn(struct kiocb *);

typedef u32 compat_aio_context_t;

struct aio_ring {
	unsigned int id;
	unsigned int nr;
	unsigned int head;
	unsigned int tail;
	unsigned int magic;
	unsigned int compat_features;
	unsigned int incompat_features;
	unsigned int header_length;
	struct io_event io_events[0];
};

struct kioctx_cpu;

struct ctx_rq_wait;

struct kioctx {
	struct percpu_ref users;
	atomic_t dead;
	struct percpu_ref reqs;
	long unsigned int user_id;
	struct kioctx_cpu *cpu;
	unsigned int req_batch;
	unsigned int max_reqs;
	unsigned int nr_events;
	long unsigned int mmap_base;
	long unsigned int mmap_size;
	struct page **ring_pages;
	long int nr_pages;
	struct rcu_work free_rwork;
	struct ctx_rq_wait *rq_wait;
	long: 64;
	struct {
		atomic_t reqs_available;
		long: 32;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	};
	struct {
		spinlock_t ctx_lock;
		struct list_head active_reqs;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	};
	struct {
		struct mutex ring_lock;
		wait_queue_head_t wait;
		long: 64;
	};
	struct {
		unsigned int tail;
		unsigned int completed_events;
		spinlock_t completion_lock;
		long: 32;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	};
	struct page *internal_pages[8];
	struct file *aio_ring_file;
	unsigned int id;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct kioctx_cpu {
	unsigned int reqs_available;
};

struct ctx_rq_wait {
	struct completion comp;
	atomic_t count;
};

struct fsync_iocb {
	struct file *file;
	struct work_struct work;
	bool datasync;
	struct cred *creds;
};

struct poll_iocb {
	struct file *file;
	struct wait_queue_head *head;
	__poll_t events;
	bool done;
	bool cancelled;
	struct wait_queue_entry wait;
	struct work_struct work;
};

struct eventfd_ctx___2;

struct aio_kiocb {
	union {
		struct file *ki_filp;
		struct kiocb rw;
		struct fsync_iocb fsync;
		struct poll_iocb poll;
	};
	struct kioctx *ki_ctx;
	kiocb_cancel_fn *ki_cancel;
	struct io_event ki_res;
	struct list_head ki_list;
	refcount_t ki_refcnt;
	struct eventfd_ctx___2 *ki_eventfd;
};

struct aio_poll_table {
	struct poll_table_struct pt;
	struct aio_kiocb *iocb;
	int error;
};

struct __aio_sigset {
	const sigset_t *sigmask;
	size_t sigsetsize;
};

struct __compat_aio_sigset {
	compat_uptr_t sigmask;
	compat_size_t sigsetsize;
};

enum {
	PERCPU_REF_INIT_ATOMIC = 1,
	PERCPU_REF_INIT_DEAD = 2,
	PERCPU_REF_ALLOW_REINIT = 4,
};

struct user_msghdr {
	void *msg_name;
	int msg_namelen;
	struct iovec *msg_iov;
	__kernel_size_t msg_iovlen;
	void *msg_control;
	__kernel_size_t msg_controllen;
	unsigned int msg_flags;
};

struct compat_msghdr {
	compat_uptr_t msg_name;
	compat_int_t msg_namelen;
	compat_uptr_t msg_iov;
	compat_size_t msg_iovlen;
	compat_uptr_t msg_control;
	compat_size_t msg_controllen;
	compat_uint_t msg_flags;
};

struct scm_fp_list {
	short int count;
	short int max;
	struct user_struct *user;
	struct file *fp[253];
};

struct unix_skb_parms {
	struct pid *pid;
	kuid_t uid;
	kgid_t gid;
	struct scm_fp_list *fp;
	u32 secid;
	u32 consumed;
};

struct trace_event_raw_io_uring_create {
	struct trace_entry ent;
	int fd;
	void *ctx;
	u32 sq_entries;
	u32 cq_entries;
	u32 flags;
	char __data[0];
};

struct trace_event_raw_io_uring_register {
	struct trace_entry ent;
	void *ctx;
	unsigned int opcode;
	unsigned int nr_files;
	unsigned int nr_bufs;
	bool eventfd;
	long int ret;
	char __data[0];
};

struct trace_event_raw_io_uring_file_get {
	struct trace_entry ent;
	void *ctx;
	int fd;
	char __data[0];
};

struct io_wq_work;

struct trace_event_raw_io_uring_queue_async_work {
	struct trace_entry ent;
	void *ctx;
	int rw;
	void *req;
	struct io_wq_work *work;
	unsigned int flags;
	char __data[0];
};

struct io_wq_work_node {
	struct io_wq_work_node *next;
};

struct io_wq_work {
	struct io_wq_work_node list;
	struct files_struct *files;
	struct mm_struct *mm;
	const struct cred *creds;
	struct fs_struct *fs;
	unsigned int flags;
};

struct trace_event_raw_io_uring_defer {
	struct trace_entry ent;
	void *ctx;
	void *req;
	long long unsigned int data;
	char __data[0];
};

struct trace_event_raw_io_uring_link {
	struct trace_entry ent;
	void *ctx;
	void *req;
	void *target_req;
	char __data[0];
};

struct trace_event_raw_io_uring_cqring_wait {
	struct trace_entry ent;
	void *ctx;
	int min_events;
	char __data[0];
};

struct trace_event_raw_io_uring_fail_link {
	struct trace_entry ent;
	void *req;
	void *link;
	char __data[0];
};

struct trace_event_raw_io_uring_complete {
	struct trace_entry ent;
	void *ctx;
	u64 user_data;
	long int res;
	char __data[0];
};

struct trace_event_raw_io_uring_submit_sqe {
	struct trace_entry ent;
	void *ctx;
	u8 opcode;
	u64 user_data;
	bool force_nonblock;
	bool sq_thread;
	char __data[0];
};

struct trace_event_raw_io_uring_poll_arm {
	struct trace_entry ent;
	void *ctx;
	u8 opcode;
	u64 user_data;
	int mask;
	int events;
	char __data[0];
};

struct trace_event_raw_io_uring_poll_wake {
	struct trace_entry ent;
	void *ctx;
	u8 opcode;
	u64 user_data;
	int mask;
	char __data[0];
};

struct trace_event_raw_io_uring_task_add {
	struct trace_entry ent;
	void *ctx;
	u8 opcode;
	u64 user_data;
	int mask;
	char __data[0];
};

struct trace_event_raw_io_uring_task_run {
	struct trace_entry ent;
	void *ctx;
	u8 opcode;
	u64 user_data;
	char __data[0];
};

struct trace_event_data_offsets_io_uring_create {};

struct trace_event_data_offsets_io_uring_register {};

struct trace_event_data_offsets_io_uring_file_get {};

struct trace_event_data_offsets_io_uring_queue_async_work {};

struct trace_event_data_offsets_io_uring_defer {};

struct trace_event_data_offsets_io_uring_link {};

struct trace_event_data_offsets_io_uring_cqring_wait {};

struct trace_event_data_offsets_io_uring_fail_link {};

struct trace_event_data_offsets_io_uring_complete {};

struct trace_event_data_offsets_io_uring_submit_sqe {};

struct trace_event_data_offsets_io_uring_poll_arm {};

struct trace_event_data_offsets_io_uring_poll_wake {};

struct trace_event_data_offsets_io_uring_task_add {};

struct trace_event_data_offsets_io_uring_task_run {};

typedef void (*btf_trace_io_uring_create)(void *, int, void *, u32, u32, u32);

typedef void (*btf_trace_io_uring_register)(void *, void *, unsigned int, unsigned int, unsigned int, bool, long int);

typedef void (*btf_trace_io_uring_file_get)(void *, void *, int);

typedef void (*btf_trace_io_uring_queue_async_work)(void *, void *, int, void *, struct io_wq_work *, unsigned int);

typedef void (*btf_trace_io_uring_defer)(void *, void *, void *, long long unsigned int);

typedef void (*btf_trace_io_uring_link)(void *, void *, void *, void *);

typedef void (*btf_trace_io_uring_cqring_wait)(void *, void *, int);

typedef void (*btf_trace_io_uring_fail_link)(void *, void *, void *);

typedef void (*btf_trace_io_uring_complete)(void *, void *, u64, long int);

typedef void (*btf_trace_io_uring_submit_sqe)(void *, void *, u8, u64, bool, bool);

typedef void (*btf_trace_io_uring_poll_arm)(void *, void *, u8, u64, int, int);

typedef void (*btf_trace_io_uring_poll_wake)(void *, void *, u8, u64, int);

typedef void (*btf_trace_io_uring_task_add)(void *, void *, u8, u64, int);

typedef void (*btf_trace_io_uring_task_run)(void *, void *, u8, u64);

struct io_uring_sqe {
	__u8 opcode;
	__u8 flags;
	__u16 ioprio;
	__s32 fd;
	union {
		__u64 off;
		__u64 addr2;
	};
	union {
		__u64 addr;
		__u64 splice_off_in;
	};
	__u32 len;
	union {
		__kernel_rwf_t rw_flags;
		__u32 fsync_flags;
		__u16 poll_events;
		__u32 sync_range_flags;
		__u32 msg_flags;
		__u32 timeout_flags;
		__u32 accept_flags;
		__u32 cancel_flags;
		__u32 open_flags;
		__u32 statx_flags;
		__u32 fadvise_advice;
		__u32 splice_flags;
	};
	__u64 user_data;
	union {
		struct {
			union {
				__u16 buf_index;
				__u16 buf_group;
			};
			__u16 personality;
			__s32 splice_fd_in;
		};
		__u64 __pad2[3];
	};
};

enum {
	IOSQE_FIXED_FILE_BIT = 0,
	IOSQE_IO_DRAIN_BIT = 1,
	IOSQE_IO_LINK_BIT = 2,
	IOSQE_IO_HARDLINK_BIT = 3,
	IOSQE_ASYNC_BIT = 4,
	IOSQE_BUFFER_SELECT_BIT = 5,
};

enum {
	IORING_OP_NOP = 0,
	IORING_OP_READV = 1,
	IORING_OP_WRITEV = 2,
	IORING_OP_FSYNC = 3,
	IORING_OP_READ_FIXED = 4,
	IORING_OP_WRITE_FIXED = 5,
	IORING_OP_POLL_ADD = 6,
	IORING_OP_POLL_REMOVE = 7,
	IORING_OP_SYNC_FILE_RANGE = 8,
	IORING_OP_SENDMSG = 9,
	IORING_OP_RECVMSG = 10,
	IORING_OP_TIMEOUT = 11,
	IORING_OP_TIMEOUT_REMOVE = 12,
	IORING_OP_ACCEPT = 13,
	IORING_OP_ASYNC_CANCEL = 14,
	IORING_OP_LINK_TIMEOUT = 15,
	IORING_OP_CONNECT = 16,
	IORING_OP_FALLOCATE = 17,
	IORING_OP_OPENAT = 18,
	IORING_OP_CLOSE = 19,
	IORING_OP_FILES_UPDATE = 20,
	IORING_OP_STATX = 21,
	IORING_OP_READ = 22,
	IORING_OP_WRITE = 23,
	IORING_OP_FADVISE = 24,
	IORING_OP_MADVISE = 25,
	IORING_OP_SEND = 26,
	IORING_OP_RECV = 27,
	IORING_OP_OPENAT2 = 28,
	IORING_OP_EPOLL_CTL = 29,
	IORING_OP_SPLICE = 30,
	IORING_OP_PROVIDE_BUFFERS = 31,
	IORING_OP_REMOVE_BUFFERS = 32,
	IORING_OP_TEE = 33,
	IORING_OP_LAST = 34,
};

struct io_uring_cqe {
	__u64 user_data;
	__s32 res;
	__u32 flags;
};

enum {
	IORING_CQE_BUFFER_SHIFT = 16,
};

struct io_sqring_offsets {
	__u32 head;
	__u32 tail;
	__u32 ring_mask;
	__u32 ring_entries;
	__u32 flags;
	__u32 dropped;
	__u32 array;
	__u32 resv1;
	__u64 resv2;
};

struct io_cqring_offsets {
	__u32 head;
	__u32 tail;
	__u32 ring_mask;
	__u32 ring_entries;
	__u32 overflow;
	__u32 cqes;
	__u32 flags;
	__u32 resv1;
	__u64 resv2;
};

struct io_uring_params {
	__u32 sq_entries;
	__u32 cq_entries;
	__u32 flags;
	__u32 sq_thread_cpu;
	__u32 sq_thread_idle;
	__u32 features;
	__u32 wq_fd;
	__u32 resv[3];
	struct io_sqring_offsets sq_off;
	struct io_cqring_offsets cq_off;
};

struct io_uring_files_update {
	__u32 offset;
	__u32 resv;
	__u64 fds;
};

struct io_uring_probe_op {
	__u8 op;
	__u8 resv;
	__u16 flags;
	__u32 resv2;
};

struct io_uring_probe {
	__u8 last_op;
	__u8 ops_len;
	__u16 resv;
	__u32 resv2[3];
	struct io_uring_probe_op ops[0];
};

enum {
	IO_WQ_WORK_CANCEL = 1,
	IO_WQ_WORK_HASHED = 4,
	IO_WQ_WORK_UNBOUND = 32,
	IO_WQ_WORK_NO_CANCEL = 256,
	IO_WQ_WORK_CONCURRENT = 512,
	IO_WQ_HASH_SHIFT = 24,
};

enum io_wq_cancel {
	IO_WQ_CANCEL_OK = 0,
	IO_WQ_CANCEL_RUNNING = 1,
	IO_WQ_CANCEL_NOTFOUND = 2,
};

typedef void free_work_fn(struct io_wq_work *);

typedef void io_wq_work_fn(struct io_wq_work **);

struct io_wq_data {
	struct user_struct *user;
	io_wq_work_fn *do_work;
	free_work_fn *free_work;
};

struct io_uring {
	u32 head;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	u32 tail;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct io_rings {
	struct io_uring sq;
	struct io_uring cq;
	u32 sq_ring_mask;
	u32 cq_ring_mask;
	u32 sq_ring_entries;
	u32 cq_ring_entries;
	u32 sq_dropped;
	u32 sq_flags;
	u32 cq_flags;
	u32 cq_overflow;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct io_uring_cqe cqes[0];
};

struct io_mapped_ubuf {
	u64 ubuf;
	size_t len;
	struct bio_vec *bvec;
	unsigned int nr_bvecs;
};

struct fixed_file_table {
	struct file **files;
};

struct fixed_file_data;

struct fixed_file_ref_node {
	struct percpu_ref refs;
	struct list_head node;
	struct list_head file_list;
	struct fixed_file_data *file_data;
	struct llist_node llist;
};

struct io_ring_ctx;

struct fixed_file_data {
	struct fixed_file_table *table;
	struct io_ring_ctx *ctx;
	struct percpu_ref *cur_refs;
	struct percpu_ref refs;
	struct completion done;
	struct list_head ref_list;
	spinlock_t lock;
};

struct io_wq;

struct io_kiocb;

struct io_ring_ctx {
	struct {
		struct percpu_ref refs;
		long: 64;
	};
	struct {
		unsigned int flags;
		unsigned int compat: 1;
		unsigned int account_mem: 1;
		unsigned int cq_overflow_flushed: 1;
		unsigned int drain_next: 1;
		unsigned int eventfd_async: 1;
		u32 *sq_array;
		unsigned int cached_sq_head;
		unsigned int sq_entries;
		unsigned int sq_mask;
		unsigned int sq_thread_idle;
		unsigned int cached_sq_dropped;
		atomic_t cached_cq_overflow;
		long unsigned int sq_check_overflow;
		struct list_head defer_list;
		struct list_head timeout_list;
		struct list_head cq_overflow_list;
		wait_queue_head_t inflight_wait;
		struct io_uring_sqe *sq_sqes;
	};
	struct io_rings *rings;
	struct io_wq *io_wq;
	struct task_struct *sqo_thread;
	struct mm_struct *sqo_mm;
	wait_queue_head_t sqo_wait;
	struct fixed_file_data *file_data;
	unsigned int nr_user_files;
	int ring_fd;
	struct file *ring_file;
	unsigned int nr_user_bufs;
	struct io_mapped_ubuf *user_bufs;
	struct user_struct *user;
	const struct cred *creds;
	struct completion ref_comp;
	struct completion sq_thread_comp;
	struct io_kiocb *fallback_req;
	struct socket *ring_sock;
	struct idr io_buffer_idr;
	struct idr personality_idr;
	long: 64;
	long: 64;
	struct {
		unsigned int cached_cq_tail;
		unsigned int cq_entries;
		unsigned int cq_mask;
		atomic_t cq_timeouts;
		long unsigned int cq_check_overflow;
		struct wait_queue_head cq_wait;
		struct fasync_struct *cq_fasync;
		struct eventfd_ctx___2 *cq_ev_fd;
	};
	struct {
		struct mutex uring_lock;
		wait_queue_head_t wait;
		long: 64;
	};
	struct {
		spinlock_t completion_lock;
		struct list_head poll_list;
		struct hlist_head *cancel_hash;
		unsigned int cancel_hash_bits;
		bool poll_multi_file;
		spinlock_t inflight_lock;
		struct list_head inflight_list;
	};
	struct delayed_work file_put_work;
	struct llist_head file_put_llist;
	struct work_struct exit_work;
};

struct io_buffer {
	struct list_head list;
	__u64 addr;
	__s32 len;
	__u16 bid;
};

struct io_rw {
	struct kiocb kiocb;
	u64 addr;
	u64 len;
};

struct io_poll_iocb {
	struct file *file;
	union {
		struct wait_queue_head *head;
		u64 addr;
	};
	__poll_t events;
	bool done;
	bool canceled;
	struct wait_queue_entry wait;
};

struct io_accept {
	struct file *file;
	struct sockaddr *addr;
	int *addr_len;
	int flags;
	long unsigned int nofile;
};

struct io_sync {
	struct file *file;
	loff_t len;
	loff_t off;
	int flags;
	int mode;
};

struct io_cancel {
	struct file *file;
	u64 addr;
};

struct io_timeout {
	struct file *file;
	u64 addr;
	int flags;
	u32 off;
	u32 target_seq;
};

struct io_connect {
	struct file *file;
	struct sockaddr *addr;
	int addr_len;
};

struct io_sr_msg {
	struct file *file;
	union {
		struct user_msghdr *msg;
		void *buf;
	};
	int msg_flags;
	int bgid;
	size_t len;
	struct io_buffer *kbuf;
};

struct io_open {
	struct file *file;
	int dfd;
	struct filename *filename;
	struct open_how how;
	long unsigned int nofile;
};

struct io_close {
	struct file *file;
	struct file *put_file;
	int fd;
};

struct io_files_update {
	struct file *file;
	u64 arg;
	u32 nr_args;
	u32 offset;
};

struct io_fadvise {
	struct file *file;
	u64 offset;
	u32 len;
	u32 advice;
};

struct io_madvise {
	struct file *file;
	u64 addr;
	u32 len;
	u32 advice;
};

struct io_epoll {
	struct file *file;
	int epfd;
	int op;
	int fd;
	struct epoll_event event;
} __attribute__((packed));

struct io_splice {
	struct file *file_out;
	struct file *file_in;
	loff_t off_out;
	loff_t off_in;
	u64 len;
	unsigned int flags;
};

struct io_provide_buf {
	struct file *file;
	__u64 addr;
	__s32 len;
	__u32 bgid;
	__u16 nbufs;
	__u16 bid;
};

struct io_statx {
	struct file *file;
	int dfd;
	unsigned int mask;
	unsigned int flags;
	const char *filename;
	struct statx *buffer;
};

struct io_async_ctx;

struct async_poll;

struct io_kiocb {
	union {
		struct file *file;
		struct io_rw rw;
		struct io_poll_iocb poll;
		struct io_accept accept;
		struct io_sync sync;
		struct io_cancel cancel;
		struct io_timeout timeout;
		struct io_connect connect;
		struct io_sr_msg sr_msg;
		struct io_open open;
		struct io_close close;
		struct io_files_update files_update;
		struct io_fadvise fadvise;
		struct io_madvise madvise;
		struct io_epoll epoll;
		struct io_splice splice;
		struct io_provide_buf pbuf;
		struct io_statx statx;
	};
	struct io_async_ctx *io;
	int cflags;
	u8 opcode;
	u8 iopoll_completed;
	u16 buf_index;
	struct io_ring_ctx *ctx;
	struct list_head list;
	unsigned int flags;
	refcount_t refs;
	struct task_struct *task;
	long unsigned int fsize;
	u64 user_data;
	u32 result;
	u32 sequence;
	struct list_head link_list;
	struct list_head inflight_entry;
	struct percpu_ref *fixed_file_refs;
	union {
		struct {
			struct callback_head task_work;
			struct hlist_node hash_node;
			struct async_poll *apoll;
		};
		struct io_wq_work work;
	};
};

struct io_timeout_data {
	struct io_kiocb *req;
	struct hrtimer timer;
	struct timespec64 ts;
	enum hrtimer_mode mode;
};

struct io_async_connect {
	struct __kernel_sockaddr_storage address;
};

struct io_async_msghdr {
	struct iovec fast_iov[8];
	struct iovec *iov;
	struct sockaddr *uaddr;
	struct msghdr msg;
	struct __kernel_sockaddr_storage addr;
};

struct io_async_rw {
	struct iovec fast_iov[8];
	struct iovec *iov;
	ssize_t nr_segs;
	ssize_t size;
};

struct io_async_ctx {
	union {
		struct io_async_rw rw;
		struct io_async_msghdr msg;
		struct io_async_connect connect;
		struct io_timeout_data timeout;
	};
};

enum {
	REQ_F_FIXED_FILE_BIT = 0,
	REQ_F_IO_DRAIN_BIT = 1,
	REQ_F_LINK_BIT = 2,
	REQ_F_HARDLINK_BIT = 3,
	REQ_F_FORCE_ASYNC_BIT = 4,
	REQ_F_BUFFER_SELECT_BIT = 5,
	REQ_F_LINK_HEAD_BIT = 6,
	REQ_F_LINK_NEXT_BIT = 7,
	REQ_F_FAIL_LINK_BIT = 8,
	REQ_F_INFLIGHT_BIT = 9,
	REQ_F_CUR_POS_BIT = 10,
	REQ_F_NOWAIT_BIT = 11,
	REQ_F_LINK_TIMEOUT_BIT = 12,
	REQ_F_TIMEOUT_BIT = 13,
	REQ_F_ISREG_BIT = 14,
	REQ_F_MUST_PUNT_BIT = 15,
	REQ_F_TIMEOUT_NOSEQ_BIT = 16,
	REQ_F_COMP_LOCKED_BIT = 17,
	REQ_F_NEED_CLEANUP_BIT = 18,
	REQ_F_OVERFLOW_BIT = 19,
	REQ_F_POLLED_BIT = 20,
	REQ_F_BUFFER_SELECTED_BIT = 21,
	REQ_F_NO_FILE_TABLE_BIT = 22,
	REQ_F_QUEUE_TIMEOUT_BIT = 23,
	REQ_F_WORK_INITIALIZED_BIT = 24,
	REQ_F_TASK_PINNED_BIT = 25,
	__REQ_F_LAST_BIT = 26,
};

enum {
	REQ_F_FIXED_FILE = 1,
	REQ_F_IO_DRAIN = 2,
	REQ_F_LINK = 4,
	REQ_F_HARDLINK = 8,
	REQ_F_FORCE_ASYNC = 16,
	REQ_F_BUFFER_SELECT = 32,
	REQ_F_LINK_HEAD = 64,
	REQ_F_LINK_NEXT = 128,
	REQ_F_FAIL_LINK = 256,
	REQ_F_INFLIGHT = 512,
	REQ_F_CUR_POS = 1024,
	REQ_F_NOWAIT = 2048,
	REQ_F_LINK_TIMEOUT = 4096,
	REQ_F_TIMEOUT = 8192,
	REQ_F_ISREG = 16384,
	REQ_F_MUST_PUNT = 32768,
	REQ_F_TIMEOUT_NOSEQ = 65536,
	REQ_F_COMP_LOCKED = 131072,
	REQ_F_NEED_CLEANUP = 262144,
	REQ_F_OVERFLOW = 524288,
	REQ_F_POLLED = 1048576,
	REQ_F_BUFFER_SELECTED = 2097152,
	REQ_F_NO_FILE_TABLE = 4194304,
	REQ_F_QUEUE_TIMEOUT = 8388608,
	REQ_F_WORK_INITIALIZED = 16777216,
	REQ_F_TASK_PINNED = 33554432,
};

struct async_poll {
	struct io_poll_iocb poll;
	struct io_poll_iocb *double_poll;
	struct io_wq_work work;
};

struct io_submit_state {
	struct blk_plug plug;
	void *reqs[8];
	unsigned int free_reqs;
	struct file *file;
	unsigned int fd;
	unsigned int has_refs;
	unsigned int used_refs;
	unsigned int ios_left;
};

struct io_op_def {
	unsigned int async_ctx: 1;
	unsigned int needs_mm: 1;
	unsigned int needs_file: 1;
	unsigned int needs_file_no_error: 1;
	unsigned int hash_reg_file: 1;
	unsigned int unbound_nonreg_file: 1;
	unsigned int not_supported: 1;
	unsigned int file_table: 1;
	unsigned int needs_fs: 1;
	unsigned int pollin: 1;
	unsigned int pollout: 1;
	unsigned int buffer_select: 1;
};

struct req_batch {
	void *reqs[8];
	int to_free;
	int need_iter;
};

struct io_poll_table {
	struct poll_table_struct pt;
	struct io_kiocb *req;
	int error;
};

struct io_wait_queue {
	struct wait_queue_entry wq;
	struct io_ring_ctx *ctx;
	unsigned int to_wait;
	unsigned int nr_timeouts;
};

struct io_file_put {
	struct list_head list;
	struct file *file;
};

struct io_wq_work_list {
	struct io_wq_work_node *first;
	struct io_wq_work_node *last;
};

typedef bool work_cancel_fn(struct io_wq_work *, void *);

enum {
	IO_WORKER_F_UP = 1,
	IO_WORKER_F_RUNNING = 2,
	IO_WORKER_F_FREE = 4,
	IO_WORKER_F_EXITING = 8,
	IO_WORKER_F_FIXED = 16,
	IO_WORKER_F_BOUND = 32,
};

enum {
	IO_WQ_BIT_EXIT = 0,
	IO_WQ_BIT_CANCEL = 1,
	IO_WQ_BIT_ERROR = 2,
};

enum {
	IO_WQE_FLAG_STALLED = 1,
};

struct io_wqe;

struct io_worker {
	refcount_t ref;
	unsigned int flags;
	struct hlist_nulls_node nulls_node;
	struct list_head all_list;
	struct task_struct *task;
	struct io_wqe *wqe;
	struct io_wq_work *cur_work;
	spinlock_t lock;
	struct callback_head rcu;
	struct mm_struct *mm;
	const struct cred *cur_creds;
	const struct cred *saved_creds;
	struct files_struct *restore_files;
	struct fs_struct *restore_fs;
};

struct io_wqe_acct {
	unsigned int nr_workers;
	unsigned int max_workers;
	atomic_t nr_running;
};

struct io_wq___2;

struct io_wqe {
	struct {
		spinlock_t lock;
		struct io_wq_work_list work_list;
		long unsigned int hash_map;
		unsigned int flags;
		long: 32;
		long: 64;
		long: 64;
		long: 64;
	};
	int node;
	struct io_wqe_acct acct[2];
	struct hlist_nulls_head free_list;
	struct list_head all_list;
	struct io_wq___2 *wq;
	struct io_wq_work *hash_tail[64];
};

enum {
	IO_WQ_ACCT_BOUND = 0,
	IO_WQ_ACCT_UNBOUND = 1,
};

struct io_wq___2 {
	struct io_wqe **wqes;
	long unsigned int state;
	free_work_fn *free_work;
	io_wq_work_fn *do_work;
	struct task_struct *manager;
	struct user_struct *user;
	refcount_t refs;
	struct completion done;
	refcount_t use_refs;
};

struct io_cb_cancel_data {
	work_cancel_fn *fn;
	void *data;
	int nr_running;
	int nr_pending;
	bool cancel_all;
};

struct flock64 {
	short int l_type;
	short int l_whence;
	__kernel_loff_t l_start;
	__kernel_loff_t l_len;
	__kernel_pid_t l_pid;
};

struct trace_event_raw_locks_get_lock_context {
	struct trace_entry ent;
	long unsigned int i_ino;
	dev_t s_dev;
	unsigned char type;
	struct file_lock_context *ctx;
	char __data[0];
};

struct trace_event_raw_filelock_lock {
	struct trace_entry ent;
	struct file_lock *fl;
	long unsigned int i_ino;
	dev_t s_dev;
	struct file_lock *fl_blocker;
	fl_owner_t fl_owner;
	unsigned int fl_pid;
	unsigned int fl_flags;
	unsigned char fl_type;
	loff_t fl_start;
	loff_t fl_end;
	int ret;
	char __data[0];
};

struct trace_event_raw_filelock_lease {
	struct trace_entry ent;
	struct file_lock *fl;
	long unsigned int i_ino;
	dev_t s_dev;
	struct file_lock *fl_blocker;
	fl_owner_t fl_owner;
	unsigned int fl_flags;
	unsigned char fl_type;
	long unsigned int fl_break_time;
	long unsigned int fl_downgrade_time;
	char __data[0];
};

struct trace_event_raw_generic_add_lease {
	struct trace_entry ent;
	long unsigned int i_ino;
	int wcount;
	int rcount;
	int icount;
	dev_t s_dev;
	fl_owner_t fl_owner;
	unsigned int fl_flags;
	unsigned char fl_type;
	char __data[0];
};

struct trace_event_raw_leases_conflict {
	struct trace_entry ent;
	void *lease;
	void *breaker;
	unsigned int l_fl_flags;
	unsigned int b_fl_flags;
	unsigned char l_fl_type;
	unsigned char b_fl_type;
	bool conflict;
	char __data[0];
};

struct trace_event_data_offsets_locks_get_lock_context {};

struct trace_event_data_offsets_filelock_lock {};

struct trace_event_data_offsets_filelock_lease {};

struct trace_event_data_offsets_generic_add_lease {};

struct trace_event_data_offsets_leases_conflict {};

typedef void (*btf_trace_locks_get_lock_context)(void *, struct inode *, int, struct file_lock_context *);

typedef void (*btf_trace_posix_lock_inode)(void *, struct inode *, struct file_lock *, int);

typedef void (*btf_trace_fcntl_setlk)(void *, struct inode *, struct file_lock *, int);

typedef void (*btf_trace_locks_remove_posix)(void *, struct inode *, struct file_lock *, int);

typedef void (*btf_trace_flock_lock_inode)(void *, struct inode *, struct file_lock *, int);

typedef void (*btf_trace_break_lease_noblock)(void *, struct inode *, struct file_lock *);

typedef void (*btf_trace_break_lease_block)(void *, struct inode *, struct file_lock *);

typedef void (*btf_trace_break_lease_unblock)(void *, struct inode *, struct file_lock *);

typedef void (*btf_trace_generic_delete_lease)(void *, struct inode *, struct file_lock *);

typedef void (*btf_trace_time_out_leases)(void *, struct inode *, struct file_lock *);

typedef void (*btf_trace_generic_add_lease)(void *, struct inode *, struct file_lock *);

typedef void (*btf_trace_leases_conflict)(void *, bool, struct file_lock *, struct file_lock *);

struct file_lock_list_struct {
	spinlock_t lock;
	struct hlist_head hlist;
};

struct locks_iterator {
	int li_cpu;
	loff_t li_pos;
};

struct nfs_string {
	unsigned int len;
	const char *data;
};

struct nfs4_mount_data {
	int version;
	int flags;
	int rsize;
	int wsize;
	int timeo;
	int retrans;
	int acregmin;
	int acregmax;
	int acdirmin;
	int acdirmax;
	struct nfs_string client_addr;
	struct nfs_string mnt_path;
	struct nfs_string hostname;
	unsigned int host_addrlen;
	struct sockaddr *host_addr;
	int proto;
	int auth_flavourlen;
	int *auth_flavours;
};

struct compat_nfs_string {
	compat_uint_t len;
	compat_uptr_t data;
};

struct compat_nfs4_mount_data_v1 {
	compat_int_t version;
	compat_int_t flags;
	compat_int_t rsize;
	compat_int_t wsize;
	compat_int_t timeo;
	compat_int_t retrans;
	compat_int_t acregmin;
	compat_int_t acregmax;
	compat_int_t acdirmin;
	compat_int_t acdirmax;
	struct compat_nfs_string client_addr;
	struct compat_nfs_string mnt_path;
	struct compat_nfs_string hostname;
	compat_uint_t host_addrlen;
	compat_uptr_t host_addr;
	compat_int_t proto;
	compat_int_t auth_flavourlen;
	compat_uptr_t auth_flavours;
};

enum {
	VERBOSE_STATUS = 1,
};

enum {
	Enabled = 0,
	Magic = 1,
};

typedef struct {
	struct list_head list;
	long unsigned int flags;
	int offset;
	int size;
	char *magic;
	char *mask;
	const char *interpreter;
	char *name;
	struct dentry *dentry;
	struct file *interp_file;
} Node;

typedef unsigned int __kernel_uid_t;

typedef unsigned int __kernel_gid_t;

struct elf_prpsinfo {
	char pr_state;
	char pr_sname;
	char pr_zomb;
	char pr_nice;
	long unsigned int pr_flag;
	__kernel_uid_t pr_uid;
	__kernel_gid_t pr_gid;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgrp;
	pid_t pr_sid;
	char pr_fname[16];
	char pr_psargs[80];
};

struct arch_elf_state {};

struct memelfnote {
	const char *name;
	int type;
	unsigned int datasz;
	void *data;
};

struct elf_thread_core_info {
	struct elf_thread_core_info *next;
	struct task_struct *task;
	struct elf_prstatus prstatus;
	struct memelfnote notes[0];
};

struct elf_note_info {
	struct elf_thread_core_info *thread;
	struct memelfnote psinfo;
	struct memelfnote signote;
	struct memelfnote auxv;
	struct memelfnote files;
	siginfo_t csigdata;
	size_t size;
	int thread_notes;
};

struct elf32_shdr {
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
};

typedef struct user_regs_struct compat_elf_gregset_t;

struct compat_elf_siginfo {
	compat_int_t si_signo;
	compat_int_t si_code;
	compat_int_t si_errno;
};

struct compat_elf_prstatus {
	struct compat_elf_siginfo pr_info;
	short int pr_cursig;
	compat_ulong_t pr_sigpend;
	compat_ulong_t pr_sighold;
	compat_pid_t pr_pid;
	compat_pid_t pr_ppid;
	compat_pid_t pr_pgrp;
	compat_pid_t pr_sid;
	struct old_timeval32 pr_utime;
	struct old_timeval32 pr_stime;
	struct old_timeval32 pr_cutime;
	struct old_timeval32 pr_cstime;
	compat_elf_gregset_t pr_reg;
	compat_int_t pr_fpvalid;
};

struct compat_elf_prpsinfo {
	char pr_state;
	char pr_sname;
	char pr_zomb;
	char pr_nice;
	compat_ulong_t pr_flag;
	__compat_uid_t pr_uid;
	__compat_gid_t pr_gid;
	compat_pid_t pr_pid;
	compat_pid_t pr_ppid;
	compat_pid_t pr_pgrp;
	compat_pid_t pr_sid;
	char pr_fname[16];
	char pr_psargs[80];
};

struct elf_thread_core_info___2 {
	struct elf_thread_core_info___2 *next;
	struct task_struct *task;
	struct compat_elf_prstatus prstatus;
	struct memelfnote notes[0];
};

struct elf_note_info___2 {
	struct elf_thread_core_info___2 *thread;
	struct memelfnote psinfo;
	struct memelfnote signote;
	struct memelfnote auxv;
	struct memelfnote files;
	compat_siginfo_t csigdata;
	size_t size;
	int thread_notes;
};

struct mb_cache_entry {
	struct list_head e_list;
	struct hlist_bl_node e_hash_list;
	atomic_t e_refcnt;
	u32 e_key;
	u32 e_referenced: 1;
	u32 e_reusable: 1;
	u64 e_value;
};

struct mb_cache {
	struct hlist_bl_head *c_hash;
	int c_bucket_bits;
	long unsigned int c_max_entries;
	spinlock_t c_list_lock;
	struct list_head c_list;
	long unsigned int c_entry_count;
	struct shrinker c_shrink;
	struct work_struct c_shrink_work;
};

struct posix_acl_xattr_entry {
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
};

struct posix_acl_xattr_header {
	__le32 a_version;
};

struct xdr_array2_desc;

typedef int (*xdr_xcode_elem_t)(struct xdr_array2_desc *, void *);

struct xdr_array2_desc {
	unsigned int elem_size;
	unsigned int array_len;
	unsigned int array_maxlen;
	xdr_xcode_elem_t xcode;
};

struct nfsacl_encode_desc {
	struct xdr_array2_desc desc;
	unsigned int count;
	struct posix_acl *acl;
	int typeflag;
	kuid_t uid;
	kgid_t gid;
};

struct nfsacl_simple_acl {
	struct posix_acl acl;
	struct posix_acl_entry ace[4];
};

struct nfsacl_decode_desc {
	struct xdr_array2_desc desc;
	unsigned int count;
	struct posix_acl *acl;
};

struct lock_manager {
	struct list_head list;
	bool block_opens;
};

struct core_name {
	char *corename;
	int used;
	int size;
};

struct trace_event_raw_iomap_readpage_class {
	struct trace_entry ent;
	dev_t dev;
	u64 ino;
	int nr_pages;
	char __data[0];
};

struct trace_event_raw_iomap_range_class {
	struct trace_entry ent;
	dev_t dev;
	u64 ino;
	loff_t size;
	long unsigned int offset;
	unsigned int length;
	char __data[0];
};

struct trace_event_raw_iomap_class {
	struct trace_entry ent;
	dev_t dev;
	u64 ino;
	u64 addr;
	loff_t offset;
	u64 length;
	u16 type;
	u16 flags;
	dev_t bdev;
	char __data[0];
};

struct trace_event_raw_iomap_apply {
	struct trace_entry ent;
	dev_t dev;
	u64 ino;
	loff_t pos;
	loff_t length;
	unsigned int flags;
	const void *ops;
	void *actor;
	long unsigned int caller;
	char __data[0];
};

struct trace_event_data_offsets_iomap_readpage_class {};

struct trace_event_data_offsets_iomap_range_class {};

struct trace_event_data_offsets_iomap_class {};

struct trace_event_data_offsets_iomap_apply {};

typedef void (*btf_trace_iomap_readpage)(void *, struct inode *, int);

typedef void (*btf_trace_iomap_readahead)(void *, struct inode *, int);

typedef void (*btf_trace_iomap_writepage)(void *, struct inode *, long unsigned int, unsigned int);

typedef void (*btf_trace_iomap_releasepage)(void *, struct inode *, long unsigned int, unsigned int);

typedef void (*btf_trace_iomap_invalidatepage)(void *, struct inode *, long unsigned int, unsigned int);

typedef void (*btf_trace_iomap_apply_dstmap)(void *, struct inode *, struct iomap___2 *);

typedef void (*btf_trace_iomap_apply_srcmap)(void *, struct inode *, struct iomap___2 *);

typedef void (*btf_trace_iomap_apply)(void *, struct inode *, loff_t, loff_t, unsigned int, const void *, void *, long unsigned int);

struct iomap_ops {
	int (*iomap_begin)(struct inode *, loff_t, loff_t, unsigned int, struct iomap___2 *, struct iomap___2 *);
	int (*iomap_end)(struct inode *, loff_t, loff_t, ssize_t, unsigned int, struct iomap___2 *);
};

typedef loff_t (*iomap_actor_t)(struct inode *, loff_t, loff_t, void *, struct iomap___2 *, struct iomap___2 *);

struct iomap_ioend {
	struct list_head io_list;
	u16 io_type;
	u16 io_flags;
	struct inode *io_inode;
	size_t io_size;
	loff_t io_offset;
	void *io_private;
	struct bio *io_bio;
	struct bio io_inline_bio;
};

struct iomap_writepage_ctx;

struct iomap_writeback_ops {
	int (*map_blocks)(struct iomap_writepage_ctx *, struct inode *, loff_t);
	int (*prepare_ioend)(struct iomap_ioend *, int);
	void (*discard_page)(struct page *);
};

struct iomap_writepage_ctx {
	struct iomap___2 iomap;
	struct iomap_ioend *ioend;
	const struct iomap_writeback_ops *ops;
};

struct iomap_page {
	atomic_t read_count;
	atomic_t write_count;
	spinlock_t uptodate_lock;
	long unsigned int uptodate[1];
};

struct iomap_readpage_ctx {
	struct page *cur_page;
	bool cur_page_in_bio;
	struct bio *bio;
	struct readahead_control *rac;
};

enum {
	IOMAP_WRITE_F_UNSHARE = 1,
};

struct iomap_dio_ops {
	int (*end_io)(struct kiocb *, ssize_t, int, unsigned int);
	blk_qc_t (*submit_io)(struct inode *, struct iomap___2 *, struct bio *, loff_t);
};

struct iomap_dio {
	struct kiocb *iocb;
	const struct iomap_dio_ops *dops;
	loff_t i_size;
	loff_t size;
	atomic_t ref;
	unsigned int flags;
	int error;
	bool wait_for_completion;
	union {
		struct {
			struct iov_iter *iter;
			struct task_struct *waiter;
			struct request_queue *last_queue;
			blk_qc_t cookie;
		} submit;
		struct {
			struct work_struct work;
		} aio;
	};
};

struct fiemap_ctx {
	struct fiemap_extent_info *fi;
	struct iomap___2 prev;
};

struct iomap_swapfile_info {
	struct iomap___2 iomap;
	struct swap_info_struct *sis;
	uint64_t lowest_ppage;
	uint64_t highest_ppage;
	long unsigned int nr_pages;
	int nr_extents;
};

enum {
	QIF_BLIMITS_B = 0,
	QIF_SPACE_B = 1,
	QIF_ILIMITS_B = 2,
	QIF_INODES_B = 3,
	QIF_BTIME_B = 4,
	QIF_ITIME_B = 5,
};

enum {
	DQF_ROOT_SQUASH_B = 0,
	DQF_SYS_FILE_B = 16,
	DQF_PRIVATE = 17,
};

typedef __kernel_uid32_t qid_t;

enum {
	DQF_INFO_DIRTY_B = 17,
};

enum {
	DQST_LOOKUPS = 0,
	DQST_DROPS = 1,
	DQST_READS = 2,
	DQST_WRITES = 3,
	DQST_CACHE_HITS = 4,
	DQST_ALLOC_DQUOTS = 5,
	DQST_FREE_DQUOTS = 6,
	DQST_SYNCS = 7,
	_DQST_DQSTAT_LAST = 8,
};

enum {
	_DQUOT_USAGE_ENABLED = 0,
	_DQUOT_LIMITS_ENABLED = 1,
	_DQUOT_SUSPENDED = 2,
	_DQUOT_STATE_FLAGS = 3,
};

struct quota_module_name {
	int qm_fmt_id;
	char *qm_mod_name;
};

struct dquot_warn {
	struct super_block *w_sb;
	struct kqid w_dq_id;
	short int w_type;
};

struct qtree_fmt_operations {
	void (*mem2disk_dqblk)(void *, struct dquot *);
	void (*disk2mem_dqblk)(struct dquot *, void *);
	int (*is_id)(void *, struct dquot *);
};

struct qtree_mem_dqinfo {
	struct super_block *dqi_sb;
	int dqi_type;
	unsigned int dqi_blocks;
	unsigned int dqi_free_blk;
	unsigned int dqi_free_entry;
	unsigned int dqi_blocksize_bits;
	unsigned int dqi_entry_size;
	unsigned int dqi_usable_bs;
	unsigned int dqi_qtree_depth;
	const struct qtree_fmt_operations *dqi_ops;
};

struct v2_disk_dqheader {
	__le32 dqh_magic;
	__le32 dqh_version;
};

struct v2r0_disk_dqblk {
	__le32 dqb_id;
	__le32 dqb_ihardlimit;
	__le32 dqb_isoftlimit;
	__le32 dqb_curinodes;
	__le32 dqb_bhardlimit;
	__le32 dqb_bsoftlimit;
	__le64 dqb_curspace;
	__le64 dqb_btime;
	__le64 dqb_itime;
};

struct v2r1_disk_dqblk {
	__le32 dqb_id;
	__le32 dqb_pad;
	__le64 dqb_ihardlimit;
	__le64 dqb_isoftlimit;
	__le64 dqb_curinodes;
	__le64 dqb_bhardlimit;
	__le64 dqb_bsoftlimit;
	__le64 dqb_curspace;
	__le64 dqb_btime;
	__le64 dqb_itime;
};

struct v2_disk_dqinfo {
	__le32 dqi_bgrace;
	__le32 dqi_igrace;
	__le32 dqi_flags;
	__le32 dqi_blocks;
	__le32 dqi_free_blk;
	__le32 dqi_free_entry;
};

struct qt_disk_dqdbheader {
	__le32 dqdh_next_free;
	__le32 dqdh_prev_free;
	__le16 dqdh_entries;
	__le16 dqdh_pad1;
	__le32 dqdh_pad2;
};

struct fs_disk_quota {
	__s8 d_version;
	__s8 d_flags;
	__u16 d_fieldmask;
	__u32 d_id;
	__u64 d_blk_hardlimit;
	__u64 d_blk_softlimit;
	__u64 d_ino_hardlimit;
	__u64 d_ino_softlimit;
	__u64 d_bcount;
	__u64 d_icount;
	__s32 d_itimer;
	__s32 d_btimer;
	__u16 d_iwarns;
	__u16 d_bwarns;
	__s32 d_padding2;
	__u64 d_rtb_hardlimit;
	__u64 d_rtb_softlimit;
	__u64 d_rtbcount;
	__s32 d_rtbtimer;
	__u16 d_rtbwarns;
	__s16 d_padding3;
	char d_padding4[8];
};

struct fs_qfilestat {
	__u64 qfs_ino;
	__u64 qfs_nblks;
	__u32 qfs_nextents;
};

typedef struct fs_qfilestat fs_qfilestat_t;

struct fs_quota_stat {
	__s8 qs_version;
	__u16 qs_flags;
	__s8 qs_pad;
	fs_qfilestat_t qs_uquota;
	fs_qfilestat_t qs_gquota;
	__u32 qs_incoredqs;
	__s32 qs_btimelimit;
	__s32 qs_itimelimit;
	__s32 qs_rtbtimelimit;
	__u16 qs_bwarnlimit;
	__u16 qs_iwarnlimit;
};

struct fs_qfilestatv {
	__u64 qfs_ino;
	__u64 qfs_nblks;
	__u32 qfs_nextents;
	__u32 qfs_pad;
};

struct fs_quota_statv {
	__s8 qs_version;
	__u8 qs_pad1;
	__u16 qs_flags;
	__u32 qs_incoredqs;
	struct fs_qfilestatv qs_uquota;
	struct fs_qfilestatv qs_gquota;
	struct fs_qfilestatv qs_pquota;
	__s32 qs_btimelimit;
	__s32 qs_itimelimit;
	__s32 qs_rtbtimelimit;
	__u16 qs_bwarnlimit;
	__u16 qs_iwarnlimit;
	__u64 qs_pad2[8];
};

struct if_dqblk {
	__u64 dqb_bhardlimit;
	__u64 dqb_bsoftlimit;
	__u64 dqb_curspace;
	__u64 dqb_ihardlimit;
	__u64 dqb_isoftlimit;
	__u64 dqb_curinodes;
	__u64 dqb_btime;
	__u64 dqb_itime;
	__u32 dqb_valid;
};

struct if_nextdqblk {
	__u64 dqb_bhardlimit;
	__u64 dqb_bsoftlimit;
	__u64 dqb_curspace;
	__u64 dqb_ihardlimit;
	__u64 dqb_isoftlimit;
	__u64 dqb_curinodes;
	__u64 dqb_btime;
	__u64 dqb_itime;
	__u32 dqb_valid;
	__u32 dqb_id;
};

struct if_dqinfo {
	__u64 dqi_bgrace;
	__u64 dqi_igrace;
	__u32 dqi_flags;
	__u32 dqi_valid;
};

struct compat_if_dqblk {
	compat_u64 dqb_bhardlimit;
	compat_u64 dqb_bsoftlimit;
	compat_u64 dqb_curspace;
	compat_u64 dqb_ihardlimit;
	compat_u64 dqb_isoftlimit;
	compat_u64 dqb_curinodes;
	compat_u64 dqb_btime;
	compat_u64 dqb_itime;
	compat_uint_t dqb_valid;
} __attribute__((packed));

struct compat_fs_qfilestat {
	compat_u64 dqb_bhardlimit;
	compat_u64 qfs_nblks;
	compat_uint_t qfs_nextents;
} __attribute__((packed));

struct compat_fs_quota_stat {
	__s8 qs_version;
	char: 8;
	__u16 qs_flags;
	__s8 qs_pad;
	int: 24;
	struct compat_fs_qfilestat qs_uquota;
	struct compat_fs_qfilestat qs_gquota;
	compat_uint_t qs_incoredqs;
	compat_int_t qs_btimelimit;
	compat_int_t qs_itimelimit;
	compat_int_t qs_rtbtimelimit;
	__u16 qs_bwarnlimit;
	__u16 qs_iwarnlimit;
} __attribute__((packed));

enum {
	QUOTA_NL_C_UNSPEC = 0,
	QUOTA_NL_C_WARNING = 1,
	__QUOTA_NL_C_MAX = 2,
};

enum {
	QUOTA_NL_A_UNSPEC = 0,
	QUOTA_NL_A_QTYPE = 1,
	QUOTA_NL_A_EXCESS_ID = 2,
	QUOTA_NL_A_WARNING = 3,
	QUOTA_NL_A_DEV_MAJOR = 4,
	QUOTA_NL_A_DEV_MINOR = 5,
	QUOTA_NL_A_CAUSED_ID = 6,
	QUOTA_NL_A_PAD = 7,
	__QUOTA_NL_A_MAX = 8,
};

struct proc_maps_private {
	struct inode *inode;
	struct task_struct *task;
	struct mm_struct *mm;
	struct vm_area_struct *tail_vma;
	struct mempolicy *task_mempolicy;
};

struct mem_size_stats {
	long unsigned int resident;
	long unsigned int shared_clean;
	long unsigned int shared_dirty;
	long unsigned int private_clean;
	long unsigned int private_dirty;
	long unsigned int referenced;
	long unsigned int anonymous;
	long unsigned int lazyfree;
	long unsigned int anonymous_thp;
	long unsigned int shmem_thp;
	long unsigned int file_thp;
	long unsigned int swap;
	long unsigned int shared_hugetlb;
	long unsigned int private_hugetlb;
	u64 pss;
	u64 pss_anon;
	u64 pss_file;
	u64 pss_shmem;
	u64 pss_locked;
	u64 swap_pss;
	bool check_shmem_swap;
};

enum clear_refs_types {
	CLEAR_REFS_ALL = 1,
	CLEAR_REFS_ANON = 2,
	CLEAR_REFS_MAPPED = 3,
	CLEAR_REFS_SOFT_DIRTY = 4,
	CLEAR_REFS_MM_HIWATER_RSS = 5,
	CLEAR_REFS_LAST = 6,
};

struct clear_refs_private {
	enum clear_refs_types type;
};

typedef struct {
	u64 pme;
} pagemap_entry_t;

struct pagemapread {
	int pos;
	int len;
	pagemap_entry_t *buffer;
	bool show_pfn;
};

struct numa_maps {
	long unsigned int pages;
	long unsigned int anon;
	long unsigned int active;
	long unsigned int writeback;
	long unsigned int mapcount_max;
	long unsigned int dirty;
	long unsigned int swapcache;
	long unsigned int node[64];
};

struct numa_maps_private {
	struct proc_maps_private proc_maps;
	struct numa_maps md;
};

struct pde_opener {
	struct list_head lh;
	struct file *file;
	bool closing;
	struct completion *c;
};

enum {
	BIAS = 2147483648,
};

struct proc_fs_context {
	struct pid_namespace *pid_ns;
	unsigned int mask;
	enum proc_hidepid hidepid;
	int gid;
	enum proc_pidonly pidonly;
};

enum proc_param {
	Opt_gid___2 = 0,
	Opt_hidepid = 1,
	Opt_subset = 2,
};

struct genradix_root;

struct __genradix {
	struct genradix_root *root;
};

struct syscall_info {
	__u64 sp;
	struct seccomp_data data;
};

typedef struct dentry *instantiate_t(struct dentry *, struct task_struct *, const void *);

struct pid_entry {
	const char *name;
	unsigned int len;
	umode_t mode;
	const struct inode_operations *iop;
	const struct file_operations *fop;
	union proc_op op;
};

struct limit_names {
	const char *name;
	const char *unit;
};

struct map_files_info {
	long unsigned int start;
	long unsigned int end;
	fmode_t mode;
};

struct tgid_iter {
	unsigned int tgid;
	struct task_struct *task;
};

struct fd_data {
	fmode_t mode;
	unsigned int fd;
};

struct sysctl_alias {
	const char *kernel_param;
	const char *sysctl_param;
};

struct seq_net_private {
	struct net *net;
};

struct vmcore {
	struct list_head list;
	long long unsigned int paddr;
	long long unsigned int size;
	loff_t offset;
};

typedef struct elf64_note Elf64_Nhdr;

struct kernfs_iattrs {
	kuid_t ia_uid;
	kgid_t ia_gid;
	struct timespec64 ia_atime;
	struct timespec64 ia_mtime;
	struct timespec64 ia_ctime;
	struct simple_xattrs xattrs;
	atomic_t nr_user_xattrs;
	atomic_t user_xattr_size;
};

struct kernfs_super_info {
	struct super_block *sb;
	struct kernfs_root *root;
	const void *ns;
	struct list_head node;
};

enum kernfs_node_flag {
	KERNFS_ACTIVATED = 16,
	KERNFS_NS = 32,
	KERNFS_HAS_SEQ_SHOW = 64,
	KERNFS_HAS_MMAP = 128,
	KERNFS_LOCKDEP = 256,
	KERNFS_SUICIDAL = 1024,
	KERNFS_SUICIDED = 2048,
	KERNFS_EMPTY_DIR = 4096,
	KERNFS_HAS_RELEASE = 8192,
};

struct kernfs_open_node {
	atomic_t refcnt;
	atomic_t event;
	wait_queue_head_t poll;
	struct list_head files;
};

struct pts_mount_opts {
	int setuid;
	int setgid;
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
	umode_t ptmxmode;
	int reserve;
	int max;
};

enum {
	Opt_uid___2 = 0,
	Opt_gid___3 = 1,
	Opt_mode___2 = 2,
	Opt_ptmxmode = 3,
	Opt_newinstance = 4,
	Opt_max = 5,
	Opt_err = 6,
};

struct pts_fs_info {
	struct ida allocated_ptys;
	struct pts_mount_opts mount_opts;
	struct super_block *sb;
	struct dentry *ptmx_dentry;
};

struct dcookie_struct {
	struct path path;
	struct list_head hash_list;
};

struct dcookie_user {
	struct list_head next;
};

typedef unsigned int tid_t;

struct transaction_chp_stats_s {
	long unsigned int cs_chp_time;
	__u32 cs_forced_to_close;
	__u32 cs_written;
	__u32 cs_dropped;
};

struct journal_s;

typedef struct journal_s journal_t;

struct journal_head;

struct transaction_s;

typedef struct transaction_s transaction_t;

struct transaction_s {
	journal_t *t_journal;
	tid_t t_tid;
	enum {
		T_RUNNING = 0,
		T_LOCKED = 1,
		T_SWITCH = 2,
		T_FLUSH = 3,
		T_COMMIT = 4,
		T_COMMIT_DFLUSH = 5,
		T_COMMIT_JFLUSH = 6,
		T_COMMIT_CALLBACK = 7,
		T_FINISHED = 8,
	} t_state;
	long unsigned int t_log_start;
	int t_nr_buffers;
	struct journal_head *t_reserved_list;
	struct journal_head *t_buffers;
	struct journal_head *t_forget;
	struct journal_head *t_checkpoint_list;
	struct journal_head *t_checkpoint_io_list;
	struct journal_head *t_shadow_list;
	struct list_head t_inode_list;
	spinlock_t t_handle_lock;
	long unsigned int t_max_wait;
	long unsigned int t_start;
	long unsigned int t_requested;
	struct transaction_chp_stats_s t_chp_stats;
	atomic_t t_updates;
	atomic_t t_outstanding_credits;
	atomic_t t_outstanding_revokes;
	atomic_t t_handle_count;
	transaction_t *t_cpnext;
	transaction_t *t_cpprev;
	long unsigned int t_expires;
	ktime_t t_start_time;
	unsigned int t_synchronous_commit: 1;
	int t_need_data_flush;
	struct list_head t_private_list;
};

struct jbd2_buffer_trigger_type;

struct journal_head {
	struct buffer_head *b_bh;
	spinlock_t b_state_lock;
	int b_jcount;
	unsigned int b_jlist;
	unsigned int b_modified;
	char *b_frozen_data;
	char *b_committed_data;
	transaction_t *b_transaction;
	transaction_t *b_next_transaction;
	struct journal_head *b_tnext;
	struct journal_head *b_tprev;
	transaction_t *b_cp_transaction;
	struct journal_head *b_cpnext;
	struct journal_head *b_cpprev;
	struct jbd2_buffer_trigger_type *b_triggers;
	struct jbd2_buffer_trigger_type *b_frozen_triggers;
};

struct jbd2_buffer_trigger_type {
	void (*t_frozen)(struct jbd2_buffer_trigger_type *, struct buffer_head *, void *, size_t);
	void (*t_abort)(struct jbd2_buffer_trigger_type *, struct buffer_head *);
};

struct crypto_alg;

struct crypto_tfm {
	u32 crt_flags;
	void (*exit)(struct crypto_tfm *);
	struct crypto_alg *__crt_alg;
	void *__crt_ctx[0];
};

struct cipher_alg {
	unsigned int cia_min_keysize;
	unsigned int cia_max_keysize;
	int (*cia_setkey)(struct crypto_tfm *, const u8 *, unsigned int);
	void (*cia_encrypt)(struct crypto_tfm *, u8 *, const u8 *);
	void (*cia_decrypt)(struct crypto_tfm *, u8 *, const u8 *);
};

struct compress_alg {
	int (*coa_compress)(struct crypto_tfm *, const u8 *, unsigned int, u8 *, unsigned int *);
	int (*coa_decompress)(struct crypto_tfm *, const u8 *, unsigned int, u8 *, unsigned int *);
};

struct crypto_type;

struct crypto_alg {
	struct list_head cra_list;
	struct list_head cra_users;
	u32 cra_flags;
	unsigned int cra_blocksize;
	unsigned int cra_ctxsize;
	unsigned int cra_alignmask;
	int cra_priority;
	refcount_t cra_refcnt;
	char cra_name[128];
	char cra_driver_name[128];
	const struct crypto_type *cra_type;
	union {
		struct cipher_alg cipher;
		struct compress_alg compress;
	} cra_u;
	int (*cra_init)(struct crypto_tfm *);
	void (*cra_exit)(struct crypto_tfm *);
	void (*cra_destroy)(struct crypto_alg *);
	struct module *cra_module;
};

struct crypto_instance;

struct crypto_type {
	unsigned int (*ctxsize)(struct crypto_alg *, u32, u32);
	unsigned int (*extsize)(struct crypto_alg *);
	int (*init)(struct crypto_tfm *, u32, u32);
	int (*init_tfm)(struct crypto_tfm *);
	void (*show)(struct seq_file *, struct crypto_alg *);
	int (*report)(struct sk_buff *, struct crypto_alg *);
	void (*free)(struct crypto_instance *);
	unsigned int type;
	unsigned int maskclear;
	unsigned int maskset;
	unsigned int tfmsize;
};

struct crypto_shash {
	unsigned int descsize;
	struct crypto_tfm base;
};

struct jbd2_journal_handle;

typedef struct jbd2_journal_handle handle_t;

struct jbd2_journal_handle {
	union {
		transaction_t *h_transaction;
		journal_t *h_journal;
	};
	handle_t *h_rsv_handle;
	int h_total_credits;
	int h_revoke_credits;
	int h_revoke_credits_requested;
	int h_ref;
	int h_err;
	unsigned int h_sync: 1;
	unsigned int h_jdata: 1;
	unsigned int h_reserved: 1;
	unsigned int h_aborted: 1;
	unsigned int h_type: 8;
	unsigned int h_line_no: 16;
	long unsigned int h_start_jiffies;
	unsigned int h_requested_credits;
	unsigned int saved_alloc_context;
};

struct transaction_run_stats_s {
	long unsigned int rs_wait;
	long unsigned int rs_request_delay;
	long unsigned int rs_running;
	long unsigned int rs_locked;
	long unsigned int rs_flushing;
	long unsigned int rs_logging;
	__u32 rs_handle_count;
	__u32 rs_blocks;
	__u32 rs_blocks_logged;
};

struct transaction_stats_s {
	long unsigned int ts_tid;
	long unsigned int ts_requested;
	struct transaction_run_stats_s run;
};

struct journal_superblock_s;

typedef struct journal_superblock_s journal_superblock_t;

struct jbd2_revoke_table_s;

struct journal_s {
	long unsigned int j_flags;
	int j_errno;
	struct mutex j_abort_mutex;
	struct buffer_head *j_sb_buffer;
	journal_superblock_t *j_superblock;
	int j_format_version;
	rwlock_t j_state_lock;
	int j_barrier_count;
	struct mutex j_barrier;
	transaction_t *j_running_transaction;
	transaction_t *j_committing_transaction;
	transaction_t *j_checkpoint_transactions;
	wait_queue_head_t j_wait_transaction_locked;
	wait_queue_head_t j_wait_done_commit;
	wait_queue_head_t j_wait_commit;
	wait_queue_head_t j_wait_updates;
	wait_queue_head_t j_wait_reserved;
	struct mutex j_checkpoint_mutex;
	struct buffer_head *j_chkpt_bhs[64];
	long unsigned int j_head;
	long unsigned int j_tail;
	long unsigned int j_free;
	long unsigned int j_first;
	long unsigned int j_last;
	struct block_device *j_dev;
	int j_blocksize;
	long long unsigned int j_blk_offset;
	char j_devname[56];
	struct block_device *j_fs_dev;
	unsigned int j_maxlen;
	atomic_t j_reserved_credits;
	spinlock_t j_list_lock;
	struct inode *j_inode;
	tid_t j_tail_sequence;
	tid_t j_transaction_sequence;
	tid_t j_commit_sequence;
	tid_t j_commit_request;
	__u8 j_uuid[16];
	struct task_struct *j_task;
	int j_max_transaction_buffers;
	int j_revoke_records_per_block;
	long unsigned int j_commit_interval;
	struct timer_list j_commit_timer;
	spinlock_t j_revoke_lock;
	struct jbd2_revoke_table_s *j_revoke;
	struct jbd2_revoke_table_s *j_revoke_table[2];
	struct buffer_head **j_wbuf;
	int j_wbufsize;
	pid_t j_last_sync_writer;
	u64 j_average_commit_time;
	u32 j_min_batch_time;
	u32 j_max_batch_time;
	void (*j_commit_callback)(journal_t *, transaction_t *);
	spinlock_t j_history_lock;
	struct proc_dir_entry *j_proc_entry;
	struct transaction_stats_s j_stats;
	unsigned int j_failed_commit;
	void *j_private;
	struct crypto_shash *j_chksum_driver;
	__u32 j_csum_seed;
};

struct journal_header_s {
	__be32 h_magic;
	__be32 h_blocktype;
	__be32 h_sequence;
};

typedef struct journal_header_s journal_header_t;

struct journal_superblock_s {
	journal_header_t s_header;
	__be32 s_blocksize;
	__be32 s_maxlen;
	__be32 s_first;
	__be32 s_sequence;
	__be32 s_start;
	__be32 s_errno;
	__be32 s_feature_compat;
	__be32 s_feature_incompat;
	__be32 s_feature_ro_compat;
	__u8 s_uuid[16];
	__be32 s_nr_users;
	__be32 s_dynsuper;
	__be32 s_max_transaction;
	__be32 s_max_trans_data;
	__u8 s_checksum_type;
	__u8 s_padding2[3];
	__u32 s_padding[42];
	__be32 s_checksum;
	__u8 s_users[768];
};

enum jbd_state_bits {
	BH_JBD = 16,
	BH_JWrite = 17,
	BH_Freed = 18,
	BH_Revoked = 19,
	BH_RevokeValid = 20,
	BH_JBDDirty = 21,
	BH_JournalHead = 22,
	BH_Shadow = 23,
	BH_Verified = 24,
	BH_JBDPrivateStart = 25,
};

struct jbd2_inode {
	transaction_t *i_transaction;
	transaction_t *i_next_transaction;
	struct list_head i_list;
	struct inode *i_vfs_inode;
	long unsigned int i_flags;
	loff_t i_dirty_start;
	loff_t i_dirty_end;
};

struct bgl_lock {
	spinlock_t lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct blockgroup_lock {
	struct bgl_lock locks[128];
};

struct fscrypt_dummy_context {};

struct fsverity_operations {
	int (*begin_enable_verity)(struct file *);
	int (*end_enable_verity)(struct file *, const void *, size_t, u64);
	int (*get_verity_descriptor)(struct inode *, void *, size_t);
	struct page * (*read_merkle_tree_page)(struct inode *, long unsigned int, long unsigned int);
	int (*write_merkle_tree_block)(struct inode *, const void *, u64, int);
};

typedef int ext4_grpblk_t;

typedef long long unsigned int ext4_fsblk_t;

typedef __u32 ext4_lblk_t;

typedef unsigned int ext4_group_t;

struct ext4_allocation_request {
	struct inode *inode;
	unsigned int len;
	ext4_lblk_t logical;
	ext4_lblk_t lleft;
	ext4_lblk_t lright;
	ext4_fsblk_t goal;
	ext4_fsblk_t pleft;
	ext4_fsblk_t pright;
	unsigned int flags;
};

struct ext4_system_blocks {
	struct rb_root root;
	struct callback_head rcu;
};

struct ext4_group_desc {
	__le32 bg_block_bitmap_lo;
	__le32 bg_inode_bitmap_lo;
	__le32 bg_inode_table_lo;
	__le16 bg_free_blocks_count_lo;
	__le16 bg_free_inodes_count_lo;
	__le16 bg_used_dirs_count_lo;
	__le16 bg_flags;
	__le32 bg_exclude_bitmap_lo;
	__le16 bg_block_bitmap_csum_lo;
	__le16 bg_inode_bitmap_csum_lo;
	__le16 bg_itable_unused_lo;
	__le16 bg_checksum;
	__le32 bg_block_bitmap_hi;
	__le32 bg_inode_bitmap_hi;
	__le32 bg_inode_table_hi;
	__le16 bg_free_blocks_count_hi;
	__le16 bg_free_inodes_count_hi;
	__le16 bg_used_dirs_count_hi;
	__le16 bg_itable_unused_hi;
	__le32 bg_exclude_bitmap_hi;
	__le16 bg_block_bitmap_csum_hi;
	__le16 bg_inode_bitmap_csum_hi;
	__u32 bg_reserved;
};

struct flex_groups {
	atomic64_t free_clusters;
	atomic_t free_inodes;
	atomic_t used_dirs;
};

struct extent_status {
	struct rb_node rb_node;
	ext4_lblk_t es_lblk;
	ext4_lblk_t es_len;
	ext4_fsblk_t es_pblk;
};

struct ext4_es_tree {
	struct rb_root root;
	struct extent_status *cache_es;
};

struct ext4_es_stats {
	long unsigned int es_stats_shrunk;
	struct percpu_counter es_stats_cache_hits;
	struct percpu_counter es_stats_cache_misses;
	u64 es_stats_scan_time;
	u64 es_stats_max_scan_time;
	struct percpu_counter es_stats_all_cnt;
	struct percpu_counter es_stats_shk_cnt;
};

struct ext4_pending_tree {
	struct rb_root root;
};

struct ext4_inode_info {
	__le32 i_data[15];
	__u32 i_dtime;
	ext4_fsblk_t i_file_acl;
	ext4_group_t i_block_group;
	ext4_lblk_t i_dir_start_lookup;
	long unsigned int i_flags;
	struct rw_semaphore xattr_sem;
	struct list_head i_orphan;
	loff_t i_disksize;
	struct rw_semaphore i_data_sem;
	struct rw_semaphore i_mmap_sem;
	struct inode vfs_inode;
	struct jbd2_inode *jinode;
	spinlock_t i_raw_lock;
	struct timespec64 i_crtime;
	struct list_head i_prealloc_list;
	spinlock_t i_prealloc_lock;
	struct ext4_es_tree i_es_tree;
	rwlock_t i_es_lock;
	struct list_head i_es_list;
	unsigned int i_es_all_nr;
	unsigned int i_es_shk_nr;
	ext4_lblk_t i_es_shrink_lblk;
	ext4_group_t i_last_alloc_group;
	unsigned int i_reserved_data_blocks;
	struct ext4_pending_tree i_pending_tree;
	__u16 i_extra_isize;
	u16 i_inline_off;
	u16 i_inline_size;
	qsize_t i_reserved_quota;
	spinlock_t i_completed_io_lock;
	struct list_head i_rsv_conversion_list;
	struct work_struct i_rsv_conversion_work;
	atomic_t i_unwritten;
	spinlock_t i_block_reservation_lock;
	tid_t i_sync_tid;
	tid_t i_datasync_tid;
	struct dquot *i_dquot[3];
	__u32 i_csum_seed;
	kprojid_t i_projid;
};

struct ext4_super_block {
	__le32 s_inodes_count;
	__le32 s_blocks_count_lo;
	__le32 s_r_blocks_count_lo;
	__le32 s_free_blocks_count_lo;
	__le32 s_free_inodes_count;
	__le32 s_first_data_block;
	__le32 s_log_block_size;
	__le32 s_log_cluster_size;
	__le32 s_blocks_per_group;
	__le32 s_clusters_per_group;
	__le32 s_inodes_per_group;
	__le32 s_mtime;
	__le32 s_wtime;
	__le16 s_mnt_count;
	__le16 s_max_mnt_count;
	__le16 s_magic;
	__le16 s_state;
	__le16 s_errors;
	__le16 s_minor_rev_level;
	__le32 s_lastcheck;
	__le32 s_checkinterval;
	__le32 s_creator_os;
	__le32 s_rev_level;
	__le16 s_def_resuid;
	__le16 s_def_resgid;
	__le32 s_first_ino;
	__le16 s_inode_size;
	__le16 s_block_group_nr;
	__le32 s_feature_compat;
	__le32 s_feature_incompat;
	__le32 s_feature_ro_compat;
	__u8 s_uuid[16];
	char s_volume_name[16];
	char s_last_mounted[64];
	__le32 s_algorithm_usage_bitmap;
	__u8 s_prealloc_blocks;
	__u8 s_prealloc_dir_blocks;
	__le16 s_reserved_gdt_blocks;
	__u8 s_journal_uuid[16];
	__le32 s_journal_inum;
	__le32 s_journal_dev;
	__le32 s_last_orphan;
	__le32 s_hash_seed[4];
	__u8 s_def_hash_version;
	__u8 s_jnl_backup_type;
	__le16 s_desc_size;
	__le32 s_default_mount_opts;
	__le32 s_first_meta_bg;
	__le32 s_mkfs_time;
	__le32 s_jnl_blocks[17];
	__le32 s_blocks_count_hi;
	__le32 s_r_blocks_count_hi;
	__le32 s_free_blocks_count_hi;
	__le16 s_min_extra_isize;
	__le16 s_want_extra_isize;
	__le32 s_flags;
	__le16 s_raid_stride;
	__le16 s_mmp_update_interval;
	__le64 s_mmp_block;
	__le32 s_raid_stripe_width;
	__u8 s_log_groups_per_flex;
	__u8 s_checksum_type;
	__u8 s_encryption_level;
	__u8 s_reserved_pad;
	__le64 s_kbytes_written;
	__le32 s_snapshot_inum;
	__le32 s_snapshot_id;
	__le64 s_snapshot_r_blocks_count;
	__le32 s_snapshot_list;
	__le32 s_error_count;
	__le32 s_first_error_time;
	__le32 s_first_error_ino;
	__le64 s_first_error_block;
	__u8 s_first_error_func[32];
	__le32 s_first_error_line;
	__le32 s_last_error_time;
	__le32 s_last_error_ino;
	__le32 s_last_error_line;
	__le64 s_last_error_block;
	__u8 s_last_error_func[32];
	__u8 s_mount_opts[64];
	__le32 s_usr_quota_inum;
	__le32 s_grp_quota_inum;
	__le32 s_overhead_clusters;
	__le32 s_backup_bgs[2];
	__u8 s_encrypt_algos[4];
	__u8 s_encrypt_pw_salt[16];
	__le32 s_lpf_ino;
	__le32 s_prj_quota_inum;
	__le32 s_checksum_seed;
	__u8 s_wtime_hi;
	__u8 s_mtime_hi;
	__u8 s_mkfs_time_hi;
	__u8 s_lastcheck_hi;
	__u8 s_first_error_time_hi;
	__u8 s_last_error_time_hi;
	__u8 s_first_error_errcode;
	__u8 s_last_error_errcode;
	__le16 s_encoding;
	__le16 s_encoding_flags;
	__le32 s_reserved[95];
	__le32 s_checksum;
};

struct mb_cache___2;

struct ext4_group_info;

struct ext4_locality_group;

struct ext4_li_request;

struct ext4_sb_info {
	long unsigned int s_desc_size;
	long unsigned int s_inodes_per_block;
	long unsigned int s_blocks_per_group;
	long unsigned int s_clusters_per_group;
	long unsigned int s_inodes_per_group;
	long unsigned int s_itb_per_group;
	long unsigned int s_gdb_count;
	long unsigned int s_desc_per_block;
	ext4_group_t s_groups_count;
	ext4_group_t s_blockfile_groups;
	long unsigned int s_overhead;
	unsigned int s_cluster_ratio;
	unsigned int s_cluster_bits;
	loff_t s_bitmap_maxbytes;
	struct buffer_head *s_sbh;
	struct ext4_super_block *s_es;
	struct buffer_head **s_group_desc;
	unsigned int s_mount_opt;
	unsigned int s_mount_opt2;
	unsigned int s_mount_flags;
	unsigned int s_def_mount_opt;
	ext4_fsblk_t s_sb_block;
	atomic64_t s_resv_clusters;
	kuid_t s_resuid;
	kgid_t s_resgid;
	short unsigned int s_mount_state;
	short unsigned int s_pad;
	int s_addr_per_block_bits;
	int s_desc_per_block_bits;
	int s_inode_size;
	int s_first_ino;
	unsigned int s_inode_readahead_blks;
	unsigned int s_inode_goal;
	u32 s_hash_seed[4];
	int s_def_hash_version;
	int s_hash_unsigned;
	struct percpu_counter s_freeclusters_counter;
	struct percpu_counter s_freeinodes_counter;
	struct percpu_counter s_dirs_counter;
	struct percpu_counter s_dirtyclusters_counter;
	struct blockgroup_lock *s_blockgroup_lock;
	struct proc_dir_entry *s_proc;
	struct kobject s_kobj;
	struct completion s_kobj_unregister;
	struct super_block *s_sb;
	struct journal_s *s_journal;
	struct list_head s_orphan;
	struct mutex s_orphan_lock;
	long unsigned int s_ext4_flags;
	long unsigned int s_commit_interval;
	u32 s_max_batch_time;
	u32 s_min_batch_time;
	struct block_device *journal_bdev;
	char *s_qf_names[3];
	int s_jquota_fmt;
	unsigned int s_want_extra_isize;
	struct ext4_system_blocks *system_blks;
	struct ext4_group_info ***s_group_info;
	struct inode *s_buddy_cache;
	spinlock_t s_md_lock;
	short unsigned int *s_mb_offsets;
	unsigned int *s_mb_maxs;
	unsigned int s_group_info_size;
	unsigned int s_mb_free_pending;
	struct list_head s_freed_data_list;
	long unsigned int s_stripe;
	unsigned int s_mb_stream_request;
	unsigned int s_mb_max_to_scan;
	unsigned int s_mb_min_to_scan;
	unsigned int s_mb_stats;
	unsigned int s_mb_order2_reqs;
	unsigned int s_mb_group_prealloc;
	unsigned int s_max_dir_size_kb;
	long unsigned int s_mb_last_group;
	long unsigned int s_mb_last_start;
	atomic_t s_bal_reqs;
	atomic_t s_bal_success;
	atomic_t s_bal_allocated;
	atomic_t s_bal_ex_scanned;
	atomic_t s_bal_goals;
	atomic_t s_bal_breaks;
	atomic_t s_bal_2orders;
	spinlock_t s_bal_lock;
	long unsigned int s_mb_buddies_generated;
	long long unsigned int s_mb_generation_time;
	atomic_t s_mb_lost_chunks;
	atomic_t s_mb_preallocated;
	atomic_t s_mb_discarded;
	atomic_t s_lock_busy;
	struct ext4_locality_group *s_locality_groups;
	long unsigned int s_sectors_written_start;
	u64 s_kbytes_written;
	unsigned int s_extent_max_zeroout_kb;
	unsigned int s_log_groups_per_flex;
	struct flex_groups **s_flex_groups;
	ext4_group_t s_flex_groups_allocated;
	struct workqueue_struct *rsv_conversion_wq;
	struct timer_list s_err_report;
	struct ext4_li_request *s_li_request;
	unsigned int s_li_wait_mult;
	struct task_struct *s_mmp_tsk;
	atomic_t s_last_trim_minblks;
	struct crypto_shash *s_chksum_driver;
	__u32 s_csum_seed;
	struct shrinker s_es_shrinker;
	struct list_head s_es_list;
	long int s_es_nr_inode;
	struct ext4_es_stats s_es_stats;
	struct mb_cache___2 *s_ea_block_cache;
	struct mb_cache___2 *s_ea_inode_cache;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t s_es_lock;
	struct ratelimit_state s_err_ratelimit_state;
	struct ratelimit_state s_warning_ratelimit_state;
	struct ratelimit_state s_msg_ratelimit_state;
	struct fscrypt_dummy_context s_dummy_enc_ctx;
	struct percpu_rw_semaphore s_writepages_rwsem;
	struct dax_device *s_daxdev;
	long: 64;
	long: 64;
	long: 64;
};

struct ext4_group_info {
	long unsigned int bb_state;
	struct rb_root bb_free_root;
	ext4_grpblk_t bb_first_free;
	ext4_grpblk_t bb_free;
	ext4_grpblk_t bb_fragments;
	ext4_grpblk_t bb_largest_free_order;
	struct list_head bb_prealloc_list;
	struct rw_semaphore alloc_sem;
	ext4_grpblk_t bb_counters[0];
};

struct ext4_locality_group {
	struct mutex lg_mutex;
	struct list_head lg_prealloc_list[10];
	spinlock_t lg_prealloc_lock;
};

struct ext4_li_request {
	struct super_block *lr_super;
	struct ext4_sb_info *lr_sbi;
	ext4_group_t lr_next_group;
	struct list_head lr_request;
	long unsigned int lr_next_sched;
	long unsigned int lr_timeout;
};

struct iomap_ops___2;

struct shash_desc {
	struct crypto_shash *tfm;
	void *__ctx[0];
};

struct ext4_map_blocks {
	ext4_fsblk_t m_pblk;
	ext4_lblk_t m_lblk;
	unsigned int m_len;
	unsigned int m_flags;
};

struct ext4_system_zone {
	struct rb_node node;
	ext4_fsblk_t start_blk;
	unsigned int count;
};

struct fscrypt_str {
	unsigned char *name;
	u32 len;
};

enum {
	EXT4_INODE_SECRM = 0,
	EXT4_INODE_UNRM = 1,
	EXT4_INODE_COMPR = 2,
	EXT4_INODE_SYNC = 3,
	EXT4_INODE_IMMUTABLE = 4,
	EXT4_INODE_APPEND = 5,
	EXT4_INODE_NODUMP = 6,
	EXT4_INODE_NOATIME = 7,
	EXT4_INODE_DIRTY = 8,
	EXT4_INODE_COMPRBLK = 9,
	EXT4_INODE_NOCOMPR = 10,
	EXT4_INODE_ENCRYPT = 11,
	EXT4_INODE_INDEX = 12,
	EXT4_INODE_IMAGIC = 13,
	EXT4_INODE_JOURNAL_DATA = 14,
	EXT4_INODE_NOTAIL = 15,
	EXT4_INODE_DIRSYNC = 16,
	EXT4_INODE_TOPDIR = 17,
	EXT4_INODE_HUGE_FILE = 18,
	EXT4_INODE_EXTENTS = 19,
	EXT4_INODE_VERITY = 20,
	EXT4_INODE_EA_INODE = 21,
	EXT4_INODE_DAX = 25,
	EXT4_INODE_INLINE_DATA = 28,
	EXT4_INODE_PROJINHERIT = 29,
	EXT4_INODE_CASEFOLD = 30,
	EXT4_INODE_RESERVED = 31,
};

struct ext4_dir_entry_2 {
	__le32 inode;
	__le16 rec_len;
	__u8 name_len;
	__u8 file_type;
	char name[255];
};

struct fname;

struct dir_private_info {
	struct rb_root root;
	struct rb_node *curr_node;
	struct fname *extra_fname;
	loff_t last_pos;
	__u32 curr_hash;
	__u32 curr_minor_hash;
	__u32 next_hash;
};

struct fname {
	__u32 hash;
	__u32 minor_hash;
	struct rb_node rb_hash;
	struct fname *next;
	__u32 inode;
	__u8 name_len;
	__u8 file_type;
	char name[0];
};

enum SHIFT_DIRECTION {
	SHIFT_LEFT = 0,
	SHIFT_RIGHT = 1,
};

struct ext4_io_end_vec {
	struct list_head list;
	loff_t offset;
	ssize_t size;
};

struct ext4_io_end {
	struct list_head list;
	handle_t *handle;
	struct inode *inode;
	struct bio *bio;
	unsigned int flag;
	atomic_t count;
	struct list_head list_vec;
};

typedef struct ext4_io_end ext4_io_end_t;

enum {
	ES_WRITTEN_B = 0,
	ES_UNWRITTEN_B = 1,
	ES_DELAYED_B = 2,
	ES_HOLE_B = 3,
	ES_REFERENCED_B = 4,
	ES_FLAGS = 5,
};

enum {
	EXT4_STATE_JDATA = 0,
	EXT4_STATE_NEW = 1,
	EXT4_STATE_XATTR = 2,
	EXT4_STATE_NO_EXPAND = 3,
	EXT4_STATE_DA_ALLOC_CLOSE = 4,
	EXT4_STATE_EXT_MIGRATE = 5,
	EXT4_STATE_NEWENTRY = 6,
	EXT4_STATE_MAY_INLINE_DATA = 7,
	EXT4_STATE_EXT_PRECACHED = 8,
	EXT4_STATE_LUSTRE_EA_INODE = 9,
	EXT4_STATE_VERITY_IN_PROGRESS = 10,
};

struct ext4_iloc {
	struct buffer_head *bh;
	long unsigned int offset;
	ext4_group_t block_group;
};

struct ext4_extent_tail {
	__le32 et_checksum;
};

struct ext4_extent {
	__le32 ee_block;
	__le16 ee_len;
	__le16 ee_start_hi;
	__le32 ee_start_lo;
};

struct ext4_extent_idx {
	__le32 ei_block;
	__le32 ei_leaf_lo;
	__le16 ei_leaf_hi;
	__u16 ei_unused;
};

struct ext4_extent_header {
	__le16 eh_magic;
	__le16 eh_entries;
	__le16 eh_max;
	__le16 eh_depth;
	__le32 eh_generation;
};

struct ext4_ext_path {
	ext4_fsblk_t p_block;
	__u16 p_depth;
	__u16 p_maxdepth;
	struct ext4_extent *p_ext;
	struct ext4_extent_idx *p_idx;
	struct ext4_extent_header *p_hdr;
	struct buffer_head *p_bh;
};

struct partial_cluster {
	ext4_fsblk_t pclu;
	ext4_lblk_t lblk;
	enum {
		initial = 0,
		tofree = 1,
		nofree = 2,
	} state;
};

struct pending_reservation {
	struct rb_node rb_node;
	ext4_lblk_t lclu;
};

struct rsvd_count {
	int ndelonly;
	bool first_do_lblk_found;
	ext4_lblk_t first_do_lblk;
	ext4_lblk_t last_do_lblk;
	struct extent_status *left_es;
	bool partial;
	ext4_lblk_t lclu;
};

struct fsverity_info;

struct fsmap {
	__u32 fmr_device;
	__u32 fmr_flags;
	__u64 fmr_physical;
	__u64 fmr_owner;
	__u64 fmr_offset;
	__u64 fmr_length;
	__u64 fmr_reserved[3];
};

struct ext4_fsmap {
	struct list_head fmr_list;
	dev_t fmr_device;
	uint32_t fmr_flags;
	uint64_t fmr_physical;
	uint64_t fmr_owner;
	uint64_t fmr_length;
};

struct ext4_fsmap_head {
	uint32_t fmh_iflags;
	uint32_t fmh_oflags;
	unsigned int fmh_count;
	unsigned int fmh_entries;
	struct ext4_fsmap fmh_keys[2];
};

typedef int (*ext4_fsmap_format_t)(struct ext4_fsmap *, void *);

struct ext4_getfsmap_info {
	struct ext4_fsmap_head *gfi_head;
	ext4_fsmap_format_t gfi_formatter;
	void *gfi_format_arg;
	ext4_fsblk_t gfi_next_fsblk;
	u32 gfi_dev;
	ext4_group_t gfi_agno;
	struct ext4_fsmap gfi_low;
	struct ext4_fsmap gfi_high;
	struct ext4_fsmap gfi_lastfree;
	struct list_head gfi_meta_list;
	bool gfi_last;
};

struct ext4_getfsmap_dev {
	int (*gfd_fn)(struct super_block *, struct ext4_fsmap *, struct ext4_getfsmap_info *);
	u32 gfd_dev;
};

struct dx_hash_info {
	u32 hash;
	u32 minor_hash;
	int hash_version;
	u32 *seed;
};

struct ext4_inode {
	__le16 i_mode;
	__le16 i_uid;
	__le32 i_size_lo;
	__le32 i_atime;
	__le32 i_ctime;
	__le32 i_mtime;
	__le32 i_dtime;
	__le16 i_gid;
	__le16 i_links_count;
	__le32 i_blocks_lo;
	__le32 i_flags;
	union {
		struct {
			__le32 l_i_version;
		} linux1;
		struct {
			__u32 h_i_translator;
		} hurd1;
		struct {
			__u32 m_i_reserved1;
		} masix1;
	} osd1;
	__le32 i_block[15];
	__le32 i_generation;
	__le32 i_file_acl_lo;
	__le32 i_size_high;
	__le32 i_obso_faddr;
	union {
		struct {
			__le16 l_i_blocks_high;
			__le16 l_i_file_acl_high;
			__le16 l_i_uid_high;
			__le16 l_i_gid_high;
			__le16 l_i_checksum_lo;
			__le16 l_i_reserved;
		} linux2;
		struct {
			__le16 h_i_reserved1;
			__u16 h_i_mode_high;
			__u16 h_i_uid_high;
			__u16 h_i_gid_high;
			__u32 h_i_author;
		} hurd2;
		struct {
			__le16 h_i_reserved1;
			__le16 m_i_file_acl_high;
			__u32 m_i_reserved2[2];
		} masix2;
	} osd2;
	__le16 i_extra_isize;
	__le16 i_checksum_hi;
	__le32 i_ctime_extra;
	__le32 i_mtime_extra;
	__le32 i_atime_extra;
	__le32 i_crtime;
	__le32 i_crtime_extra;
	__le32 i_version_hi;
	__le32 i_projid;
};

struct orlov_stats {
	__u64 free_clusters;
	__u32 free_inodes;
	__u32 used_dirs;
};

typedef struct {
	__le32 *p;
	__le32 key;
	struct buffer_head *bh;
} Indirect;

struct ext4_filename {
	const struct qstr *usr_fname;
	struct fscrypt_str disk_name;
	struct dx_hash_info hinfo;
};

struct ext4_xattr_ibody_header {
	__le32 h_magic;
};

struct ext4_xattr_entry {
	__u8 e_name_len;
	__u8 e_name_index;
	__le16 e_value_offs;
	__le32 e_value_inum;
	__le32 e_value_size;
	__le32 e_hash;
	char e_name[0];
};

struct ext4_xattr_info {
	const char *name;
	const void *value;
	size_t value_len;
	int name_index;
	int in_inode;
};

struct ext4_xattr_search {
	struct ext4_xattr_entry *first;
	void *base;
	void *end;
	struct ext4_xattr_entry *here;
	int not_found;
};

struct ext4_xattr_ibody_find {
	struct ext4_xattr_search s;
	struct ext4_iloc iloc;
};

typedef short unsigned int __kernel_uid16_t;

typedef short unsigned int __kernel_gid16_t;

typedef __kernel_uid16_t uid16_t;

typedef __kernel_gid16_t gid16_t;

struct ext4_io_submit {
	struct writeback_control *io_wbc;
	struct bio *io_bio;
	ext4_io_end_t *io_end;
	sector_t io_next_block;
};

typedef enum {
	EXT4_IGET_NORMAL = 0,
	EXT4_IGET_SPECIAL = 1,
	EXT4_IGET_HANDLE = 2,
} ext4_iget_flags;

struct ext4_xattr_inode_array {
	unsigned int count;
	struct inode *inodes[0];
};

struct mpage_da_data {
	struct inode *inode;
	struct writeback_control *wbc;
	long unsigned int first_page;
	long unsigned int next_page;
	long unsigned int last_page;
	struct ext4_map_blocks map;
	struct ext4_io_submit io_submit;
	unsigned int do_map: 1;
	unsigned int scanned_until_end: 1;
};

struct fstrim_range {
	__u64 start;
	__u64 len;
	__u64 minlen;
};

struct ext4_new_group_input {
	__u32 group;
	__u64 block_bitmap;
	__u64 inode_bitmap;
	__u64 inode_table;
	__u32 blocks_count;
	__u16 reserved_blocks;
	__u16 unused;
};

struct compat_ext4_new_group_input {
	u32 group;
	compat_u64 block_bitmap;
	compat_u64 inode_bitmap;
	compat_u64 inode_table;
	u32 blocks_count;
	u16 reserved_blocks;
	u16 unused;
} __attribute__((packed));

struct ext4_new_group_data {
	__u32 group;
	__u64 block_bitmap;
	__u64 inode_bitmap;
	__u64 inode_table;
	__u32 blocks_count;
	__u16 reserved_blocks;
	__u16 mdata_blocks;
	__u32 free_clusters_count;
};

struct move_extent {
	__u32 reserved;
	__u32 donor_fd;
	__u64 orig_start;
	__u64 donor_start;
	__u64 len;
	__u64 moved_len;
};

struct fsmap_head {
	__u32 fmh_iflags;
	__u32 fmh_oflags;
	__u32 fmh_count;
	__u32 fmh_entries;
	__u64 fmh_reserved[6];
	struct fsmap fmh_keys[2];
	struct fsmap fmh_recs[0];
};

struct getfsmap_info {
	struct super_block *gi_sb;
	struct fsmap_head *gi_data;
	unsigned int gi_idx;
	__u32 gi_last_flags;
};

struct ext4_free_data {
	struct list_head efd_list;
	struct rb_node efd_node;
	ext4_group_t efd_group;
	ext4_grpblk_t efd_start_cluster;
	ext4_grpblk_t efd_count;
	tid_t efd_tid;
};

struct ext4_prealloc_space {
	struct list_head pa_inode_list;
	struct list_head pa_group_list;
	union {
		struct list_head pa_tmp_list;
		struct callback_head pa_rcu;
	} u;
	spinlock_t pa_lock;
	atomic_t pa_count;
	unsigned int pa_deleted;
	ext4_fsblk_t pa_pstart;
	ext4_lblk_t pa_lstart;
	ext4_grpblk_t pa_len;
	ext4_grpblk_t pa_free;
	short unsigned int pa_type;
	spinlock_t *pa_obj_lock;
	struct inode *pa_inode;
};

enum {
	MB_INODE_PA = 0,
	MB_GROUP_PA = 1,
};

struct ext4_free_extent {
	ext4_lblk_t fe_logical;
	ext4_grpblk_t fe_start;
	ext4_group_t fe_group;
	ext4_grpblk_t fe_len;
};

struct ext4_allocation_context {
	struct inode *ac_inode;
	struct super_block *ac_sb;
	struct ext4_free_extent ac_o_ex;
	struct ext4_free_extent ac_g_ex;
	struct ext4_free_extent ac_b_ex;
	struct ext4_free_extent ac_f_ex;
	__u16 ac_groups_scanned;
	__u16 ac_found;
	__u16 ac_tail;
	__u16 ac_buddy;
	__u16 ac_flags;
	__u8 ac_status;
	__u8 ac_criteria;
	__u8 ac_2order;
	__u8 ac_op;
	struct page *ac_bitmap_page;
	struct page *ac_buddy_page;
	struct ext4_prealloc_space *ac_pa;
	struct ext4_locality_group *ac_lg;
};

struct ext4_buddy {
	struct page *bd_buddy_page;
	void *bd_buddy;
	struct page *bd_bitmap_page;
	void *bd_bitmap;
	struct ext4_group_info *bd_info;
	struct super_block *bd_sb;
	__u16 bd_blkbits;
	ext4_group_t bd_group;
};

typedef int (*ext4_mballoc_query_range_fn)(struct super_block *, ext4_group_t, ext4_grpblk_t, ext4_grpblk_t, void *);

struct sg {
	struct ext4_group_info info;
	ext4_grpblk_t counters[18];
};

struct migrate_struct {
	ext4_lblk_t first_block;
	ext4_lblk_t last_block;
	ext4_lblk_t curr_block;
	ext4_fsblk_t first_pblock;
	ext4_fsblk_t last_pblock;
};

struct mmp_struct {
	__le32 mmp_magic;
	__le32 mmp_seq;
	__le64 mmp_time;
	char mmp_nodename[64];
	char mmp_bdevname[32];
	__le16 mmp_check_interval;
	__le16 mmp_pad1;
	__le32 mmp_pad2[226];
	__le32 mmp_checksum;
};

struct mmpd_data {
	struct buffer_head *bh;
	struct super_block *sb;
};

struct fscrypt_name {
	const struct qstr *usr_fname;
	struct fscrypt_str disk_name;
	u32 hash;
	u32 minor_hash;
	struct fscrypt_str crypto_buf;
	bool is_ciphertext_name;
};

struct ext4_dir_entry {
	__le32 inode;
	__le16 rec_len;
	__le16 name_len;
	char name[255];
};

struct ext4_dir_entry_tail {
	__le32 det_reserved_zero1;
	__le16 det_rec_len;
	__u8 det_reserved_zero2;
	__u8 det_reserved_ft;
	__le32 det_checksum;
};

typedef enum {
	EITHER = 0,
	INDEX = 1,
	DIRENT = 2,
	DIRENT_HTREE = 3,
} dirblock_type_t;

struct fake_dirent {
	__le32 inode;
	__le16 rec_len;
	u8 name_len;
	u8 file_type;
};

struct dx_countlimit {
	__le16 limit;
	__le16 count;
};

struct dx_entry {
	__le32 hash;
	__le32 block;
};

struct dx_root_info {
	__le32 reserved_zero;
	u8 hash_version;
	u8 info_length;
	u8 indirect_levels;
	u8 unused_flags;
};

struct dx_root {
	struct fake_dirent dot;
	char dot_name[4];
	struct fake_dirent dotdot;
	char dotdot_name[4];
	struct dx_root_info info;
	struct dx_entry entries[0];
};

struct dx_node {
	struct fake_dirent fake;
	struct dx_entry entries[0];
};

struct dx_frame {
	struct buffer_head *bh;
	struct dx_entry *entries;
	struct dx_entry *at;
};

struct dx_map_entry {
	u32 hash;
	u16 offs;
	u16 size;
};

struct dx_tail {
	u32 dt_reserved;
	__le32 dt_checksum;
};

struct ext4_renament {
	struct inode *dir;
	struct dentry *dentry;
	struct inode *inode;
	bool is_dir;
	int dir_nlink_delta;
	struct buffer_head *bh;
	struct ext4_dir_entry_2 *de;
	int inlined;
	struct buffer_head *dir_bh;
	struct ext4_dir_entry_2 *parent_de;
	int dir_inlined;
};

union fscrypt_context;

enum bio_post_read_step {
	STEP_INITIAL = 0,
	STEP_DECRYPT = 1,
	STEP_VERITY = 2,
	STEP_MAX = 3,
};

struct bio_post_read_ctx {
	struct bio *bio;
	struct work_struct work;
	unsigned int cur_step;
	unsigned int enabled_steps;
};

enum {
	BLOCK_BITMAP = 0,
	INODE_BITMAP = 1,
	INODE_TABLE = 2,
	GROUP_TABLE_COUNT = 3,
};

struct ext4_rcu_ptr {
	struct callback_head rcu;
	void *ptr;
};

struct ext4_new_flex_group_data {
	struct ext4_new_group_data *groups;
	__u16 *bg_flags;
	ext4_group_t count;
};

enum stat_group {
	STAT_READ = 0,
	STAT_WRITE = 1,
	STAT_DISCARD = 2,
	STAT_FLUSH = 3,
	NR_STAT_GROUPS = 4,
};

enum {
	I_DATA_SEM_NORMAL = 0,
	I_DATA_SEM_OTHER = 1,
	I_DATA_SEM_QUOTA = 2,
};

struct ext4_lazy_init {
	long unsigned int li_state;
	struct list_head li_request_list;
	struct mutex li_list_mtx;
};

struct ext4_journal_cb_entry {
	struct list_head jce_list;
	void (*jce_func)(struct super_block *, struct ext4_journal_cb_entry *, int);
};

struct trace_event_raw_ext4_other_inode_update_time {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ino_t orig_ino;
	uid_t uid;
	gid_t gid;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_free_inode {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	uid_t uid;
	gid_t gid;
	__u64 blocks;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_request_inode {
	struct trace_entry ent;
	dev_t dev;
	ino_t dir;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_allocate_inode {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ino_t dir;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_evict_inode {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int nlink;
	char __data[0];
};

struct trace_event_raw_ext4_drop_inode {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int drop;
	char __data[0];
};

struct trace_event_raw_ext4_nfs_commit_metadata {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	char __data[0];
};

struct trace_event_raw_ext4_mark_inode_dirty {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	long unsigned int ip;
	char __data[0];
};

struct trace_event_raw_ext4_begin_ordered_truncate {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t new_size;
	char __data[0];
};

struct trace_event_raw_ext4__write_begin {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t pos;
	unsigned int len;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_ext4__write_end {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t pos;
	unsigned int len;
	unsigned int copied;
	char __data[0];
};

struct trace_event_raw_ext4_writepages {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	long int nr_to_write;
	long int pages_skipped;
	loff_t range_start;
	loff_t range_end;
	long unsigned int writeback_index;
	int sync_mode;
	char for_kupdate;
	char range_cyclic;
	char __data[0];
};

struct trace_event_raw_ext4_da_write_pages {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	long unsigned int first_page;
	long int nr_to_write;
	int sync_mode;
	char __data[0];
};

struct trace_event_raw_ext4_da_write_pages_extent {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 lblk;
	__u32 len;
	__u32 flags;
	char __data[0];
};

struct trace_event_raw_ext4_writepages_result {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int ret;
	int pages_written;
	long int pages_skipped;
	long unsigned int writeback_index;
	int sync_mode;
	char __data[0];
};

struct trace_event_raw_ext4__page_op {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	long unsigned int index;
	char __data[0];
};

struct trace_event_raw_ext4_invalidatepage_op {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	long unsigned int index;
	unsigned int offset;
	unsigned int length;
	char __data[0];
};

struct trace_event_raw_ext4_discard_blocks {
	struct trace_entry ent;
	dev_t dev;
	__u64 blk;
	__u64 count;
	char __data[0];
};

struct trace_event_raw_ext4__mb_new_pa {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 pa_pstart;
	__u64 pa_lstart;
	__u32 pa_len;
	char __data[0];
};

struct trace_event_raw_ext4_mb_release_inode_pa {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 block;
	__u32 count;
	char __data[0];
};

struct trace_event_raw_ext4_mb_release_group_pa {
	struct trace_entry ent;
	dev_t dev;
	__u64 pa_pstart;
	__u32 pa_len;
	char __data[0];
};

struct trace_event_raw_ext4_discard_preallocations {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	char __data[0];
};

struct trace_event_raw_ext4_mb_discard_preallocations {
	struct trace_entry ent;
	dev_t dev;
	int needed;
	char __data[0];
};

struct trace_event_raw_ext4_request_blocks {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	unsigned int len;
	__u32 logical;
	__u32 lleft;
	__u32 lright;
	__u64 goal;
	__u64 pleft;
	__u64 pright;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_ext4_allocate_blocks {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 block;
	unsigned int len;
	__u32 logical;
	__u32 lleft;
	__u32 lright;
	__u64 goal;
	__u64 pleft;
	__u64 pright;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_ext4_free_blocks {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 block;
	long unsigned int count;
	int flags;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_sync_file_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ino_t parent;
	int datasync;
	char __data[0];
};

struct trace_event_raw_ext4_sync_file_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4_sync_fs {
	struct trace_entry ent;
	dev_t dev;
	int wait;
	char __data[0];
};

struct trace_event_raw_ext4_alloc_da_blocks {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	unsigned int data_blocks;
	char __data[0];
};

struct trace_event_raw_ext4_mballoc_alloc {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u32 orig_logical;
	int orig_start;
	__u32 orig_group;
	int orig_len;
	__u32 goal_logical;
	int goal_start;
	__u32 goal_group;
	int goal_len;
	__u32 result_logical;
	int result_start;
	__u32 result_group;
	int result_len;
	__u16 found;
	__u16 groups;
	__u16 buddy;
	__u16 flags;
	__u16 tail;
	__u8 cr;
	char __data[0];
};

struct trace_event_raw_ext4_mballoc_prealloc {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u32 orig_logical;
	int orig_start;
	__u32 orig_group;
	int orig_len;
	__u32 result_logical;
	int result_start;
	__u32 result_group;
	int result_len;
	char __data[0];
};

struct trace_event_raw_ext4__mballoc {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int result_start;
	__u32 result_group;
	int result_len;
	char __data[0];
};

struct trace_event_raw_ext4_forget {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 block;
	int is_metadata;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_da_update_reserve_space {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 i_blocks;
	int used_blocks;
	int reserved_data_blocks;
	int quota_claim;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_da_reserve_space {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 i_blocks;
	int reserved_data_blocks;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4_da_release_space {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 i_blocks;
	int freed_blocks;
	int reserved_data_blocks;
	__u16 mode;
	char __data[0];
};

struct trace_event_raw_ext4__bitmap_load {
	struct trace_entry ent;
	dev_t dev;
	__u32 group;
	char __data[0];
};

struct trace_event_raw_ext4_direct_IO_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t pos;
	long unsigned int len;
	int rw;
	char __data[0];
};

struct trace_event_raw_ext4_direct_IO_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t pos;
	long unsigned int len;
	int rw;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4__fallocate_mode {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t offset;
	loff_t len;
	int mode;
	char __data[0];
};

struct trace_event_raw_ext4_fallocate_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t pos;
	unsigned int blocks;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4_unlink_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ino_t parent;
	loff_t size;
	char __data[0];
};

struct trace_event_raw_ext4_unlink_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4__truncate {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	__u64 blocks;
	char __data[0];
};

struct trace_event_raw_ext4_ext_convert_to_initialized_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t m_lblk;
	unsigned int m_len;
	ext4_lblk_t u_lblk;
	unsigned int u_len;
	ext4_fsblk_t u_pblk;
	char __data[0];
};

struct trace_event_raw_ext4_ext_convert_to_initialized_fastpath {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t m_lblk;
	unsigned int m_len;
	ext4_lblk_t u_lblk;
	unsigned int u_len;
	ext4_fsblk_t u_pblk;
	ext4_lblk_t i_lblk;
	unsigned int i_len;
	ext4_fsblk_t i_pblk;
	char __data[0];
};

struct trace_event_raw_ext4__map_blocks_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	unsigned int len;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_ext4__map_blocks_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	unsigned int flags;
	ext4_fsblk_t pblk;
	ext4_lblk_t lblk;
	unsigned int len;
	unsigned int mflags;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4_ext_load_extent {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_fsblk_t pblk;
	ext4_lblk_t lblk;
	char __data[0];
};

struct trace_event_raw_ext4_load_inode {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	char __data[0];
};

struct trace_event_raw_ext4_journal_start {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int ip;
	int blocks;
	int rsv_blocks;
	int revoke_creds;
	char __data[0];
};

struct trace_event_raw_ext4_journal_start_reserved {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int ip;
	int blocks;
	char __data[0];
};

struct trace_event_raw_ext4__trim {
	struct trace_entry ent;
	int dev_major;
	int dev_minor;
	__u32 group;
	int start;
	int len;
	char __data[0];
};

struct trace_event_raw_ext4_ext_handle_unwritten_extents {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	int flags;
	ext4_lblk_t lblk;
	ext4_fsblk_t pblk;
	unsigned int len;
	unsigned int allocated;
	ext4_fsblk_t newblk;
	char __data[0];
};

struct trace_event_raw_ext4_get_implied_cluster_alloc_exit {
	struct trace_entry ent;
	dev_t dev;
	unsigned int flags;
	ext4_lblk_t lblk;
	ext4_fsblk_t pblk;
	unsigned int len;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4_ext_put_in_cache {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	unsigned int len;
	ext4_fsblk_t start;
	char __data[0];
};

struct trace_event_raw_ext4_ext_in_cache {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	int ret;
	char __data[0];
};

struct trace_event_raw_ext4_find_delalloc_range {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t from;
	ext4_lblk_t to;
	int reverse;
	int found;
	ext4_lblk_t found_blk;
	char __data[0];
};

struct trace_event_raw_ext4_get_reserved_cluster_alloc {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	unsigned int len;
	char __data[0];
};

struct trace_event_raw_ext4_ext_show_extent {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_fsblk_t pblk;
	ext4_lblk_t lblk;
	short unsigned int len;
	char __data[0];
};

struct trace_event_raw_ext4_remove_blocks {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t from;
	ext4_lblk_t to;
	ext4_fsblk_t ee_pblk;
	ext4_lblk_t ee_lblk;
	short unsigned int ee_len;
	ext4_fsblk_t pc_pclu;
	ext4_lblk_t pc_lblk;
	int pc_state;
	char __data[0];
};

struct trace_event_raw_ext4_ext_rm_leaf {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t start;
	ext4_lblk_t ee_lblk;
	ext4_fsblk_t ee_pblk;
	short int ee_len;
	ext4_fsblk_t pc_pclu;
	ext4_lblk_t pc_lblk;
	int pc_state;
	char __data[0];
};

struct trace_event_raw_ext4_ext_rm_idx {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_fsblk_t pblk;
	char __data[0];
};

struct trace_event_raw_ext4_ext_remove_space {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t start;
	ext4_lblk_t end;
	int depth;
	char __data[0];
};

struct trace_event_raw_ext4_ext_remove_space_done {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t start;
	ext4_lblk_t end;
	int depth;
	ext4_fsblk_t pc_pclu;
	ext4_lblk_t pc_lblk;
	int pc_state;
	short unsigned int eh_entries;
	char __data[0];
};

struct trace_event_raw_ext4__es_extent {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	ext4_lblk_t len;
	ext4_fsblk_t pblk;
	char status;
	char __data[0];
};

struct trace_event_raw_ext4_es_remove_extent {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t lblk;
	loff_t len;
	char __data[0];
};

struct trace_event_raw_ext4_es_find_extent_range_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	char __data[0];
};

struct trace_event_raw_ext4_es_find_extent_range_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	ext4_lblk_t len;
	ext4_fsblk_t pblk;
	char status;
	char __data[0];
};

struct trace_event_raw_ext4_es_lookup_extent_enter {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	char __data[0];
};

struct trace_event_raw_ext4_es_lookup_extent_exit {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	ext4_lblk_t len;
	ext4_fsblk_t pblk;
	char status;
	int found;
	char __data[0];
};

struct trace_event_raw_ext4__es_shrink_enter {
	struct trace_entry ent;
	dev_t dev;
	int nr_to_scan;
	int cache_cnt;
	char __data[0];
};

struct trace_event_raw_ext4_es_shrink_scan_exit {
	struct trace_entry ent;
	dev_t dev;
	int nr_shrunk;
	int cache_cnt;
	char __data[0];
};

struct trace_event_raw_ext4_collapse_range {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t offset;
	loff_t len;
	char __data[0];
};

struct trace_event_raw_ext4_insert_range {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	loff_t offset;
	loff_t len;
	char __data[0];
};

struct trace_event_raw_ext4_es_shrink {
	struct trace_entry ent;
	dev_t dev;
	int nr_shrunk;
	long long unsigned int scan_time;
	int nr_skipped;
	int retried;
	char __data[0];
};

struct trace_event_raw_ext4_es_insert_delayed_block {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	ext4_lblk_t lblk;
	ext4_lblk_t len;
	ext4_fsblk_t pblk;
	char status;
	bool allocated;
	char __data[0];
};

struct trace_event_raw_ext4_fsmap_class {
	struct trace_entry ent;
	dev_t dev;
	dev_t keydev;
	u32 agno;
	u64 bno;
	u64 len;
	u64 owner;
	char __data[0];
};

struct trace_event_raw_ext4_getfsmap_class {
	struct trace_entry ent;
	dev_t dev;
	dev_t keydev;
	u64 block;
	u64 len;
	u64 owner;
	u64 flags;
	char __data[0];
};

struct trace_event_raw_ext4_shutdown {
	struct trace_entry ent;
	dev_t dev;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_ext4_error {
	struct trace_entry ent;
	dev_t dev;
	const char *function;
	unsigned int line;
	char __data[0];
};

struct trace_event_data_offsets_ext4_other_inode_update_time {};

struct trace_event_data_offsets_ext4_free_inode {};

struct trace_event_data_offsets_ext4_request_inode {};

struct trace_event_data_offsets_ext4_allocate_inode {};

struct trace_event_data_offsets_ext4_evict_inode {};

struct trace_event_data_offsets_ext4_drop_inode {};

struct trace_event_data_offsets_ext4_nfs_commit_metadata {};

struct trace_event_data_offsets_ext4_mark_inode_dirty {};

struct trace_event_data_offsets_ext4_begin_ordered_truncate {};

struct trace_event_data_offsets_ext4__write_begin {};

struct trace_event_data_offsets_ext4__write_end {};

struct trace_event_data_offsets_ext4_writepages {};

struct trace_event_data_offsets_ext4_da_write_pages {};

struct trace_event_data_offsets_ext4_da_write_pages_extent {};

struct trace_event_data_offsets_ext4_writepages_result {};

struct trace_event_data_offsets_ext4__page_op {};

struct trace_event_data_offsets_ext4_invalidatepage_op {};

struct trace_event_data_offsets_ext4_discard_blocks {};

struct trace_event_data_offsets_ext4__mb_new_pa {};

struct trace_event_data_offsets_ext4_mb_release_inode_pa {};

struct trace_event_data_offsets_ext4_mb_release_group_pa {};

struct trace_event_data_offsets_ext4_discard_preallocations {};

struct trace_event_data_offsets_ext4_mb_discard_preallocations {};

struct trace_event_data_offsets_ext4_request_blocks {};

struct trace_event_data_offsets_ext4_allocate_blocks {};

struct trace_event_data_offsets_ext4_free_blocks {};

struct trace_event_data_offsets_ext4_sync_file_enter {};

struct trace_event_data_offsets_ext4_sync_file_exit {};

struct trace_event_data_offsets_ext4_sync_fs {};

struct trace_event_data_offsets_ext4_alloc_da_blocks {};

struct trace_event_data_offsets_ext4_mballoc_alloc {};

struct trace_event_data_offsets_ext4_mballoc_prealloc {};

struct trace_event_data_offsets_ext4__mballoc {};

struct trace_event_data_offsets_ext4_forget {};

struct trace_event_data_offsets_ext4_da_update_reserve_space {};

struct trace_event_data_offsets_ext4_da_reserve_space {};

struct trace_event_data_offsets_ext4_da_release_space {};

struct trace_event_data_offsets_ext4__bitmap_load {};

struct trace_event_data_offsets_ext4_direct_IO_enter {};

struct trace_event_data_offsets_ext4_direct_IO_exit {};

struct trace_event_data_offsets_ext4__fallocate_mode {};

struct trace_event_data_offsets_ext4_fallocate_exit {};

struct trace_event_data_offsets_ext4_unlink_enter {};

struct trace_event_data_offsets_ext4_unlink_exit {};

struct trace_event_data_offsets_ext4__truncate {};

struct trace_event_data_offsets_ext4_ext_convert_to_initialized_enter {};

struct trace_event_data_offsets_ext4_ext_convert_to_initialized_fastpath {};

struct trace_event_data_offsets_ext4__map_blocks_enter {};

struct trace_event_data_offsets_ext4__map_blocks_exit {};

struct trace_event_data_offsets_ext4_ext_load_extent {};

struct trace_event_data_offsets_ext4_load_inode {};

struct trace_event_data_offsets_ext4_journal_start {};

struct trace_event_data_offsets_ext4_journal_start_reserved {};

struct trace_event_data_offsets_ext4__trim {};

struct trace_event_data_offsets_ext4_ext_handle_unwritten_extents {};

struct trace_event_data_offsets_ext4_get_implied_cluster_alloc_exit {};

struct trace_event_data_offsets_ext4_ext_put_in_cache {};

struct trace_event_data_offsets_ext4_ext_in_cache {};

struct trace_event_data_offsets_ext4_find_delalloc_range {};

struct trace_event_data_offsets_ext4_get_reserved_cluster_alloc {};

struct trace_event_data_offsets_ext4_ext_show_extent {};

struct trace_event_data_offsets_ext4_remove_blocks {};

struct trace_event_data_offsets_ext4_ext_rm_leaf {};

struct trace_event_data_offsets_ext4_ext_rm_idx {};

struct trace_event_data_offsets_ext4_ext_remove_space {};

struct trace_event_data_offsets_ext4_ext_remove_space_done {};

struct trace_event_data_offsets_ext4__es_extent {};

struct trace_event_data_offsets_ext4_es_remove_extent {};

struct trace_event_data_offsets_ext4_es_find_extent_range_enter {};

struct trace_event_data_offsets_ext4_es_find_extent_range_exit {};

struct trace_event_data_offsets_ext4_es_lookup_extent_enter {};

struct trace_event_data_offsets_ext4_es_lookup_extent_exit {};

struct trace_event_data_offsets_ext4__es_shrink_enter {};

struct trace_event_data_offsets_ext4_es_shrink_scan_exit {};

struct trace_event_data_offsets_ext4_collapse_range {};

struct trace_event_data_offsets_ext4_insert_range {};

struct trace_event_data_offsets_ext4_es_shrink {};

struct trace_event_data_offsets_ext4_es_insert_delayed_block {};

struct trace_event_data_offsets_ext4_fsmap_class {};

struct trace_event_data_offsets_ext4_getfsmap_class {};

struct trace_event_data_offsets_ext4_shutdown {};

struct trace_event_data_offsets_ext4_error {};

typedef void (*btf_trace_ext4_other_inode_update_time)(void *, struct inode *, ino_t);

typedef void (*btf_trace_ext4_free_inode)(void *, struct inode *);

typedef void (*btf_trace_ext4_request_inode)(void *, struct inode *, int);

typedef void (*btf_trace_ext4_allocate_inode)(void *, struct inode *, struct inode *, int);

typedef void (*btf_trace_ext4_evict_inode)(void *, struct inode *);

typedef void (*btf_trace_ext4_drop_inode)(void *, struct inode *, int);

typedef void (*btf_trace_ext4_nfs_commit_metadata)(void *, struct inode *);

typedef void (*btf_trace_ext4_mark_inode_dirty)(void *, struct inode *, long unsigned int);

typedef void (*btf_trace_ext4_begin_ordered_truncate)(void *, struct inode *, loff_t);

typedef void (*btf_trace_ext4_write_begin)(void *, struct inode *, loff_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_da_write_begin)(void *, struct inode *, loff_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_write_end)(void *, struct inode *, loff_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_journalled_write_end)(void *, struct inode *, loff_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_da_write_end)(void *, struct inode *, loff_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_writepages)(void *, struct inode *, struct writeback_control *);

typedef void (*btf_trace_ext4_da_write_pages)(void *, struct inode *, long unsigned int, struct writeback_control *);

typedef void (*btf_trace_ext4_da_write_pages_extent)(void *, struct inode *, struct ext4_map_blocks *);

typedef void (*btf_trace_ext4_writepages_result)(void *, struct inode *, struct writeback_control *, int, int);

typedef void (*btf_trace_ext4_writepage)(void *, struct page *);

typedef void (*btf_trace_ext4_readpage)(void *, struct page *);

typedef void (*btf_trace_ext4_releasepage)(void *, struct page *);

typedef void (*btf_trace_ext4_invalidatepage)(void *, struct page *, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_journalled_invalidatepage)(void *, struct page *, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_discard_blocks)(void *, struct super_block *, long long unsigned int, long long unsigned int);

typedef void (*btf_trace_ext4_mb_new_inode_pa)(void *, struct ext4_allocation_context *, struct ext4_prealloc_space *);

typedef void (*btf_trace_ext4_mb_new_group_pa)(void *, struct ext4_allocation_context *, struct ext4_prealloc_space *);

typedef void (*btf_trace_ext4_mb_release_inode_pa)(void *, struct ext4_prealloc_space *, long long unsigned int, unsigned int);

typedef void (*btf_trace_ext4_mb_release_group_pa)(void *, struct super_block *, struct ext4_prealloc_space *);

typedef void (*btf_trace_ext4_discard_preallocations)(void *, struct inode *);

typedef void (*btf_trace_ext4_mb_discard_preallocations)(void *, struct super_block *, int);

typedef void (*btf_trace_ext4_request_blocks)(void *, struct ext4_allocation_request *);

typedef void (*btf_trace_ext4_allocate_blocks)(void *, struct ext4_allocation_request *, long long unsigned int);

typedef void (*btf_trace_ext4_free_blocks)(void *, struct inode *, __u64, long unsigned int, int);

typedef void (*btf_trace_ext4_sync_file_enter)(void *, struct file *, int);

typedef void (*btf_trace_ext4_sync_file_exit)(void *, struct inode *, int);

typedef void (*btf_trace_ext4_sync_fs)(void *, struct super_block *, int);

typedef void (*btf_trace_ext4_alloc_da_blocks)(void *, struct inode *);

typedef void (*btf_trace_ext4_mballoc_alloc)(void *, struct ext4_allocation_context *);

typedef void (*btf_trace_ext4_mballoc_prealloc)(void *, struct ext4_allocation_context *);

typedef void (*btf_trace_ext4_mballoc_discard)(void *, struct super_block *, struct inode *, ext4_group_t, ext4_grpblk_t, ext4_grpblk_t);

typedef void (*btf_trace_ext4_mballoc_free)(void *, struct super_block *, struct inode *, ext4_group_t, ext4_grpblk_t, ext4_grpblk_t);

typedef void (*btf_trace_ext4_forget)(void *, struct inode *, int, __u64);

typedef void (*btf_trace_ext4_da_update_reserve_space)(void *, struct inode *, int, int);

typedef void (*btf_trace_ext4_da_reserve_space)(void *, struct inode *);

typedef void (*btf_trace_ext4_da_release_space)(void *, struct inode *, int);

typedef void (*btf_trace_ext4_mb_bitmap_load)(void *, struct super_block *, long unsigned int);

typedef void (*btf_trace_ext4_mb_buddy_bitmap_load)(void *, struct super_block *, long unsigned int);

typedef void (*btf_trace_ext4_read_block_bitmap_load)(void *, struct super_block *, long unsigned int);

typedef void (*btf_trace_ext4_load_inode_bitmap)(void *, struct super_block *, long unsigned int);

typedef void (*btf_trace_ext4_direct_IO_enter)(void *, struct inode *, loff_t, long unsigned int, int);

typedef void (*btf_trace_ext4_direct_IO_exit)(void *, struct inode *, loff_t, long unsigned int, int, int);

typedef void (*btf_trace_ext4_fallocate_enter)(void *, struct inode *, loff_t, loff_t, int);

typedef void (*btf_trace_ext4_punch_hole)(void *, struct inode *, loff_t, loff_t, int);

typedef void (*btf_trace_ext4_zero_range)(void *, struct inode *, loff_t, loff_t, int);

typedef void (*btf_trace_ext4_fallocate_exit)(void *, struct inode *, loff_t, unsigned int, int);

typedef void (*btf_trace_ext4_unlink_enter)(void *, struct inode *, struct dentry *);

typedef void (*btf_trace_ext4_unlink_exit)(void *, struct dentry *, int);

typedef void (*btf_trace_ext4_truncate_enter)(void *, struct inode *);

typedef void (*btf_trace_ext4_truncate_exit)(void *, struct inode *);

typedef void (*btf_trace_ext4_ext_convert_to_initialized_enter)(void *, struct inode *, struct ext4_map_blocks *, struct ext4_extent *);

typedef void (*btf_trace_ext4_ext_convert_to_initialized_fastpath)(void *, struct inode *, struct ext4_map_blocks *, struct ext4_extent *, struct ext4_extent *);

typedef void (*btf_trace_ext4_ext_map_blocks_enter)(void *, struct inode *, ext4_lblk_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_ind_map_blocks_enter)(void *, struct inode *, ext4_lblk_t, unsigned int, unsigned int);

typedef void (*btf_trace_ext4_ext_map_blocks_exit)(void *, struct inode *, unsigned int, struct ext4_map_blocks *, int);

typedef void (*btf_trace_ext4_ind_map_blocks_exit)(void *, struct inode *, unsigned int, struct ext4_map_blocks *, int);

typedef void (*btf_trace_ext4_ext_load_extent)(void *, struct inode *, ext4_lblk_t, ext4_fsblk_t);

typedef void (*btf_trace_ext4_load_inode)(void *, struct inode *);

typedef void (*btf_trace_ext4_journal_start)(void *, struct super_block *, int, int, int, long unsigned int);

typedef void (*btf_trace_ext4_journal_start_reserved)(void *, struct super_block *, int, long unsigned int);

typedef void (*btf_trace_ext4_trim_extent)(void *, struct super_block *, ext4_group_t, ext4_grpblk_t, ext4_grpblk_t);

typedef void (*btf_trace_ext4_trim_all_free)(void *, struct super_block *, ext4_group_t, ext4_grpblk_t, ext4_grpblk_t);

typedef void (*btf_trace_ext4_ext_handle_unwritten_extents)(void *, struct inode *, struct ext4_map_blocks *, int, unsigned int, ext4_fsblk_t);

typedef void (*btf_trace_ext4_get_implied_cluster_alloc_exit)(void *, struct super_block *, struct ext4_map_blocks *, int);

typedef void (*btf_trace_ext4_ext_put_in_cache)(void *, struct inode *, ext4_lblk_t, unsigned int, ext4_fsblk_t);

typedef void (*btf_trace_ext4_ext_in_cache)(void *, struct inode *, ext4_lblk_t, int);

typedef void (*btf_trace_ext4_find_delalloc_range)(void *, struct inode *, ext4_lblk_t, ext4_lblk_t, int, int, ext4_lblk_t);

typedef void (*btf_trace_ext4_get_reserved_cluster_alloc)(void *, struct inode *, ext4_lblk_t, unsigned int);

typedef void (*btf_trace_ext4_ext_show_extent)(void *, struct inode *, ext4_lblk_t, ext4_fsblk_t, short unsigned int);

typedef void (*btf_trace_ext4_remove_blocks)(void *, struct inode *, struct ext4_extent *, ext4_lblk_t, ext4_fsblk_t, struct partial_cluster *);

typedef void (*btf_trace_ext4_ext_rm_leaf)(void *, struct inode *, ext4_lblk_t, struct ext4_extent *, struct partial_cluster *);

typedef void (*btf_trace_ext4_ext_rm_idx)(void *, struct inode *, ext4_fsblk_t);

typedef void (*btf_trace_ext4_ext_remove_space)(void *, struct inode *, ext4_lblk_t, ext4_lblk_t, int);

typedef void (*btf_trace_ext4_ext_remove_space_done)(void *, struct inode *, ext4_lblk_t, ext4_lblk_t, int, struct partial_cluster *, __le16);

typedef void (*btf_trace_ext4_es_insert_extent)(void *, struct inode *, struct extent_status *);

typedef void (*btf_trace_ext4_es_cache_extent)(void *, struct inode *, struct extent_status *);

typedef void (*btf_trace_ext4_es_remove_extent)(void *, struct inode *, ext4_lblk_t, ext4_lblk_t);

typedef void (*btf_trace_ext4_es_find_extent_range_enter)(void *, struct inode *, ext4_lblk_t);

typedef void (*btf_trace_ext4_es_find_extent_range_exit)(void *, struct inode *, struct extent_status *);

typedef void (*btf_trace_ext4_es_lookup_extent_enter)(void *, struct inode *, ext4_lblk_t);

typedef void (*btf_trace_ext4_es_lookup_extent_exit)(void *, struct inode *, struct extent_status *, int);

typedef void (*btf_trace_ext4_es_shrink_count)(void *, struct super_block *, int, int);

typedef void (*btf_trace_ext4_es_shrink_scan_enter)(void *, struct super_block *, int, int);

typedef void (*btf_trace_ext4_es_shrink_scan_exit)(void *, struct super_block *, int, int);

typedef void (*btf_trace_ext4_collapse_range)(void *, struct inode *, loff_t, loff_t);

typedef void (*btf_trace_ext4_insert_range)(void *, struct inode *, loff_t, loff_t);

typedef void (*btf_trace_ext4_es_shrink)(void *, struct super_block *, int, u64, int, int);

typedef void (*btf_trace_ext4_es_insert_delayed_block)(void *, struct inode *, struct extent_status *, bool);

typedef void (*btf_trace_ext4_fsmap_low_key)(void *, struct super_block *, u32, u32, u64, u64, u64);

typedef void (*btf_trace_ext4_fsmap_high_key)(void *, struct super_block *, u32, u32, u64, u64, u64);

typedef void (*btf_trace_ext4_fsmap_mapping)(void *, struct super_block *, u32, u32, u64, u64, u64);

typedef void (*btf_trace_ext4_getfsmap_low_key)(void *, struct super_block *, struct ext4_fsmap *);

typedef void (*btf_trace_ext4_getfsmap_high_key)(void *, struct super_block *, struct ext4_fsmap *);

typedef void (*btf_trace_ext4_getfsmap_mapping)(void *, struct super_block *, struct ext4_fsmap *);

typedef void (*btf_trace_ext4_shutdown)(void *, struct super_block *, long unsigned int);

typedef void (*btf_trace_ext4_error)(void *, struct super_block *, const char *, unsigned int);

enum {
	Opt_bsd_df = 0,
	Opt_minix_df = 1,
	Opt_grpid = 2,
	Opt_nogrpid = 3,
	Opt_resgid = 4,
	Opt_resuid = 5,
	Opt_sb = 6,
	Opt_err_cont = 7,
	Opt_err_panic = 8,
	Opt_err_ro = 9,
	Opt_nouid32 = 10,
	Opt_debug = 11,
	Opt_removed = 12,
	Opt_user_xattr = 13,
	Opt_nouser_xattr = 14,
	Opt_acl = 15,
	Opt_noacl = 16,
	Opt_auto_da_alloc = 17,
	Opt_noauto_da_alloc = 18,
	Opt_noload = 19,
	Opt_commit = 20,
	Opt_min_batch_time = 21,
	Opt_max_batch_time = 22,
	Opt_journal_dev = 23,
	Opt_journal_path = 24,
	Opt_journal_checksum = 25,
	Opt_journal_async_commit = 26,
	Opt_abort = 27,
	Opt_data_journal = 28,
	Opt_data_ordered = 29,
	Opt_data_writeback = 30,
	Opt_data_err_abort = 31,
	Opt_data_err_ignore = 32,
	Opt_test_dummy_encryption = 33,
	Opt_usrjquota = 34,
	Opt_grpjquota = 35,
	Opt_offusrjquota = 36,
	Opt_offgrpjquota = 37,
	Opt_jqfmt_vfsold = 38,
	Opt_jqfmt_vfsv0 = 39,
	Opt_jqfmt_vfsv1 = 40,
	Opt_quota = 41,
	Opt_noquota = 42,
	Opt_barrier = 43,
	Opt_nobarrier = 44,
	Opt_err___2 = 45,
	Opt_usrquota = 46,
	Opt_grpquota = 47,
	Opt_prjquota = 48,
	Opt_i_version = 49,
	Opt_dax = 50,
	Opt_dax_always = 51,
	Opt_dax_inode = 52,
	Opt_dax_never = 53,
	Opt_stripe = 54,
	Opt_delalloc = 55,
	Opt_nodelalloc = 56,
	Opt_warn_on_error = 57,
	Opt_nowarn_on_error = 58,
	Opt_mblk_io_submit = 59,
	Opt_lazytime = 60,
	Opt_nolazytime = 61,
	Opt_debug_want_extra_isize = 62,
	Opt_nomblk_io_submit = 63,
	Opt_block_validity = 64,
	Opt_noblock_validity = 65,
	Opt_inode_readahead_blks = 66,
	Opt_journal_ioprio = 67,
	Opt_dioread_nolock = 68,
	Opt_dioread_lock = 69,
	Opt_discard = 70,
	Opt_nodiscard = 71,
	Opt_init_itable = 72,
	Opt_noinit_itable = 73,
	Opt_max_dir_size_kb = 74,
	Opt_nojournal_checksum = 75,
	Opt_nombcache = 76,
};

struct mount_opts {
	int token;
	int mount_opt;
	int flags;
};

struct ext4_mount_options {
	long unsigned int s_mount_opt;
	long unsigned int s_mount_opt2;
	kuid_t s_resuid;
	kgid_t s_resgid;
	long unsigned int s_commit_interval;
	u32 s_min_batch_time;
	u32 s_max_batch_time;
	int s_jquota_fmt;
	char *s_qf_names[3];
};

enum {
	attr_noop = 0,
	attr_delayed_allocation_blocks = 1,
	attr_session_write_kbytes = 2,
	attr_lifetime_write_kbytes = 3,
	attr_reserved_clusters = 4,
	attr_inode_readahead = 5,
	attr_trigger_test_error = 6,
	attr_first_error_time = 7,
	attr_last_error_time = 8,
	attr_feature = 9,
	attr_pointer_ui = 10,
	attr_pointer_ul = 11,
	attr_pointer_u64 = 12,
	attr_pointer_u8 = 13,
	attr_pointer_string = 14,
	attr_pointer_atomic = 15,
	attr_journal_task = 16,
};

enum {
	ptr_explicit = 0,
	ptr_ext4_sb_info_offset = 1,
	ptr_ext4_super_block_offset = 2,
};

struct ext4_attr {
	struct attribute attr;
	short int attr_id;
	short int attr_ptr;
	short unsigned int attr_size;
	union {
		int offset;
		void *explicit_ptr;
	} u;
};

struct ext4_xattr_header {
	__le32 h_magic;
	__le32 h_refcount;
	__le32 h_blocks;
	__le32 h_hash;
	__le32 h_checksum;
	__u32 h_reserved[3];
};

struct ext4_xattr_block_find {
	struct ext4_xattr_search s;
	struct buffer_head *bh;
};

typedef struct {
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
} ext4_acl_entry;

typedef struct {
	__le32 a_version;
} ext4_acl_header;

struct commit_header {
	__be32 h_magic;
	__be32 h_blocktype;
	__be32 h_sequence;
	unsigned char h_chksum_type;
	unsigned char h_chksum_size;
	unsigned char h_padding[2];
	__be32 h_chksum[8];
	__be64 h_commit_sec;
	__be32 h_commit_nsec;
};

struct journal_block_tag3_s {
	__be32 t_blocknr;
	__be32 t_flags;
	__be32 t_blocknr_high;
	__be32 t_checksum;
};

typedef struct journal_block_tag3_s journal_block_tag3_t;

struct journal_block_tag_s {
	__be32 t_blocknr;
	__be16 t_checksum;
	__be16 t_flags;
	__be32 t_blocknr_high;
};

typedef struct journal_block_tag_s journal_block_tag_t;

struct jbd2_journal_block_tail {
	__be32 t_checksum;
};

struct jbd2_journal_revoke_header_s {
	journal_header_t r_header;
	__be32 r_count;
};

typedef struct jbd2_journal_revoke_header_s jbd2_journal_revoke_header_t;

struct recovery_info {
	tid_t start_transaction;
	tid_t end_transaction;
	int nr_replays;
	int nr_revokes;
	int nr_revoke_hits;
};

enum passtype {
	PASS_SCAN = 0,
	PASS_REVOKE = 1,
	PASS_REPLAY = 2,
};

struct jbd2_revoke_table_s {
	int hash_size;
	int hash_shift;
	struct list_head *hash_table;
};

struct jbd2_revoke_record_s {
	struct list_head hash;
	tid_t sequence;
	long long unsigned int blocknr;
};

struct trace_event_raw_jbd2_checkpoint {
	struct trace_entry ent;
	dev_t dev;
	int result;
	char __data[0];
};

struct trace_event_raw_jbd2_commit {
	struct trace_entry ent;
	dev_t dev;
	char sync_commit;
	int transaction;
	char __data[0];
};

struct trace_event_raw_jbd2_end_commit {
	struct trace_entry ent;
	dev_t dev;
	char sync_commit;
	int transaction;
	int head;
	char __data[0];
};

struct trace_event_raw_jbd2_submit_inode_data {
	struct trace_entry ent;
	dev_t dev;
	ino_t ino;
	char __data[0];
};

struct trace_event_raw_jbd2_handle_start_class {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int tid;
	unsigned int type;
	unsigned int line_no;
	int requested_blocks;
	char __data[0];
};

struct trace_event_raw_jbd2_handle_extend {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int tid;
	unsigned int type;
	unsigned int line_no;
	int buffer_credits;
	int requested_blocks;
	char __data[0];
};

struct trace_event_raw_jbd2_handle_stats {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int tid;
	unsigned int type;
	unsigned int line_no;
	int interval;
	int sync;
	int requested_blocks;
	int dirtied_blocks;
	char __data[0];
};

struct trace_event_raw_jbd2_run_stats {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int tid;
	long unsigned int wait;
	long unsigned int request_delay;
	long unsigned int running;
	long unsigned int locked;
	long unsigned int flushing;
	long unsigned int logging;
	__u32 handle_count;
	__u32 blocks;
	__u32 blocks_logged;
	char __data[0];
};

struct trace_event_raw_jbd2_checkpoint_stats {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int tid;
	long unsigned int chp_time;
	__u32 forced_to_close;
	__u32 written;
	__u32 dropped;
	char __data[0];
};

struct trace_event_raw_jbd2_update_log_tail {
	struct trace_entry ent;
	dev_t dev;
	tid_t tail_sequence;
	tid_t first_tid;
	long unsigned int block_nr;
	long unsigned int freed;
	char __data[0];
};

struct trace_event_raw_jbd2_write_superblock {
	struct trace_entry ent;
	dev_t dev;
	int write_op;
	char __data[0];
};

struct trace_event_raw_jbd2_lock_buffer_stall {
	struct trace_entry ent;
	dev_t dev;
	long unsigned int stall_ms;
	char __data[0];
};

struct trace_event_data_offsets_jbd2_checkpoint {};

struct trace_event_data_offsets_jbd2_commit {};

struct trace_event_data_offsets_jbd2_end_commit {};

struct trace_event_data_offsets_jbd2_submit_inode_data {};

struct trace_event_data_offsets_jbd2_handle_start_class {};

struct trace_event_data_offsets_jbd2_handle_extend {};

struct trace_event_data_offsets_jbd2_handle_stats {};

struct trace_event_data_offsets_jbd2_run_stats {};

struct trace_event_data_offsets_jbd2_checkpoint_stats {};

struct trace_event_data_offsets_jbd2_update_log_tail {};

struct trace_event_data_offsets_jbd2_write_superblock {};

struct trace_event_data_offsets_jbd2_lock_buffer_stall {};

typedef void (*btf_trace_jbd2_checkpoint)(void *, journal_t *, int);

typedef void (*btf_trace_jbd2_start_commit)(void *, journal_t *, transaction_t *);

typedef void (*btf_trace_jbd2_commit_locking)(void *, journal_t *, transaction_t *);

typedef void (*btf_trace_jbd2_commit_flushing)(void *, journal_t *, transaction_t *);

typedef void (*btf_trace_jbd2_commit_logging)(void *, journal_t *, transaction_t *);

typedef void (*btf_trace_jbd2_drop_transaction)(void *, journal_t *, transaction_t *);

typedef void (*btf_trace_jbd2_end_commit)(void *, journal_t *, transaction_t *);

typedef void (*btf_trace_jbd2_submit_inode_data)(void *, struct inode *);

typedef void (*btf_trace_jbd2_handle_start)(void *, dev_t, long unsigned int, unsigned int, unsigned int, int);

typedef void (*btf_trace_jbd2_handle_restart)(void *, dev_t, long unsigned int, unsigned int, unsigned int, int);

typedef void (*btf_trace_jbd2_handle_extend)(void *, dev_t, long unsigned int, unsigned int, unsigned int, int, int);

typedef void (*btf_trace_jbd2_handle_stats)(void *, dev_t, long unsigned int, unsigned int, unsigned int, int, int, int, int);

typedef void (*btf_trace_jbd2_run_stats)(void *, dev_t, long unsigned int, struct transaction_run_stats_s *);

typedef void (*btf_trace_jbd2_checkpoint_stats)(void *, dev_t, long unsigned int, struct transaction_chp_stats_s *);

typedef void (*btf_trace_jbd2_update_log_tail)(void *, journal_t *, tid_t, long unsigned int, long unsigned int);

typedef void (*btf_trace_jbd2_write_superblock)(void *, journal_t *, int);

typedef void (*btf_trace_jbd2_lock_buffer_stall)(void *, dev_t, long unsigned int);

struct jbd2_stats_proc_session {
	journal_t *journal;
	struct transaction_stats_s *stats;
	int start;
	int max;
};

struct ramfs_mount_opts {
	umode_t mode;
};

struct ramfs_fs_info {
	struct ramfs_mount_opts mount_opts;
};

enum ramfs_param {
	Opt_mode___3 = 0,
};

enum hugetlbfs_size_type {
	NO_SIZE = 0,
	SIZE_STD = 1,
	SIZE_PERCENT = 2,
};

struct hugetlbfs_fs_context {
	struct hstate *hstate;
	long long unsigned int max_size_opt;
	long long unsigned int min_size_opt;
	long int max_hpages;
	long int nr_inodes;
	long int min_hpages;
	enum hugetlbfs_size_type max_val_type;
	enum hugetlbfs_size_type min_val_type;
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
};

enum hugetlb_param {
	Opt_gid___4 = 0,
	Opt_min_size = 1,
	Opt_mode___4 = 2,
	Opt_nr_inodes___2 = 3,
	Opt_pagesize = 4,
	Opt_size___2 = 5,
	Opt_uid___3 = 6,
};

typedef u16 wchar_t;

struct nls_table {
	const char *charset;
	const char *alias;
	int (*uni2char)(wchar_t, unsigned char *, int);
	int (*char2uni)(const unsigned char *, int, wchar_t *);
	const unsigned char *charset2lower;
	const unsigned char *charset2upper;
	struct module *owner;
	struct nls_table *next;
};

struct fat_mount_options {
	kuid_t fs_uid;
	kgid_t fs_gid;
	short unsigned int fs_fmask;
	short unsigned int fs_dmask;
	short unsigned int codepage;
	int time_offset;
	char *iocharset;
	short unsigned int shortname;
	unsigned char name_check;
	unsigned char errors;
	unsigned char nfs;
	short unsigned int allow_utime;
	unsigned int quiet: 1;
	unsigned int showexec: 1;
	unsigned int sys_immutable: 1;
	unsigned int dotsOK: 1;
	unsigned int isvfat: 1;
	unsigned int utf8: 1;
	unsigned int unicode_xlate: 1;
	unsigned int numtail: 1;
	unsigned int flush: 1;
	unsigned int nocase: 1;
	unsigned int usefree: 1;
	unsigned int tz_set: 1;
	unsigned int rodir: 1;
	unsigned int discard: 1;
	unsigned int dos1xfloppy: 1;
};

struct fatent_operations;

struct msdos_sb_info {
	short unsigned int sec_per_clus;
	short unsigned int cluster_bits;
	unsigned int cluster_size;
	unsigned char fats;
	unsigned char fat_bits;
	short unsigned int fat_start;
	long unsigned int fat_length;
	long unsigned int dir_start;
	short unsigned int dir_entries;
	long unsigned int data_start;
	long unsigned int max_cluster;
	long unsigned int root_cluster;
	long unsigned int fsinfo_sector;
	struct mutex fat_lock;
	struct mutex nfs_build_inode_lock;
	struct mutex s_lock;
	unsigned int prev_free;
	unsigned int free_clusters;
	unsigned int free_clus_valid;
	struct fat_mount_options options;
	struct nls_table *nls_disk;
	struct nls_table *nls_io;
	const void *dir_ops;
	int dir_per_block;
	int dir_per_block_bits;
	unsigned int vol_id;
	int fatent_shift;
	const struct fatent_operations *fatent_ops;
	struct inode *fat_inode;
	struct inode *fsinfo_inode;
	struct ratelimit_state ratelimit;
	spinlock_t inode_hash_lock;
	struct hlist_head inode_hashtable[256];
	spinlock_t dir_hash_lock;
	struct hlist_head dir_hashtable[256];
	unsigned int dirty;
	struct callback_head rcu;
};

struct fat_entry;

struct fatent_operations {
	void (*ent_blocknr)(struct super_block *, int, int *, sector_t *);
	void (*ent_set_ptr)(struct fat_entry *, int);
	int (*ent_bread)(struct super_block *, struct fat_entry *, int, sector_t);
	int (*ent_get)(struct fat_entry *);
	void (*ent_put)(struct fat_entry *, int);
	int (*ent_next)(struct fat_entry *);
};

struct msdos_inode_info {
	spinlock_t cache_lru_lock;
	struct list_head cache_lru;
	int nr_caches;
	unsigned int cache_valid_id;
	loff_t mmu_private;
	int i_start;
	int i_logstart;
	int i_attrs;
	loff_t i_pos;
	struct hlist_node i_fat_hash;
	struct hlist_node i_dir_hash;
	struct rw_semaphore truncate_lock;
	struct inode vfs_inode;
};

struct fat_entry {
	int entry;
	union {
		u8 *ent12_p[2];
		__le16 *ent16_p;
		__le32 *ent32_p;
	} u;
	int nr_bhs;
	struct buffer_head *bhs[2];
	struct inode *fat_inode;
};

struct fat_cache {
	struct list_head cache_list;
	int nr_contig;
	int fcluster;
	int dcluster;
};

struct fat_cache_id {
	unsigned int id;
	int nr_contig;
	int fcluster;
	int dcluster;
};

struct compat_dirent {
	u32 d_ino;
	compat_off_t d_off;
	u16 d_reclen;
	char d_name[256];
};

enum utf16_endian {
	UTF16_HOST_ENDIAN = 0,
	UTF16_LITTLE_ENDIAN = 1,
	UTF16_BIG_ENDIAN = 2,
};

struct __fat_dirent {
	long int d_ino;
	__kernel_off_t d_off;
	short unsigned int d_reclen;
	char d_name[256];
};

struct msdos_dir_entry {
	__u8 name[11];
	__u8 attr;
	__u8 lcase;
	__u8 ctime_cs;
	__le16 ctime;
	__le16 cdate;
	__le16 adate;
	__le16 starthi;
	__le16 time;
	__le16 date;
	__le16 start;
	__le32 size;
};

struct msdos_dir_slot {
	__u8 id;
	__u8 name0_4[10];
	__u8 attr;
	__u8 reserved;
	__u8 alias_checksum;
	__u8 name5_10[12];
	__le16 start;
	__u8 name11_12[4];
};

struct fat_slot_info {
	loff_t i_pos;
	loff_t slot_off;
	int nr_slots;
	struct msdos_dir_entry *de;
	struct buffer_head *bh;
};

typedef long long unsigned int llu;

enum {
	PARSE_INVALID = 1,
	PARSE_NOT_LONGNAME = 2,
	PARSE_EOF = 3,
};

struct fat_ioctl_filldir_callback {
	struct dir_context ctx;
	void *dirent;
	int result;
	const char *longname;
	int long_len;
	const char *shortname;
	int short_len;
};

struct fatent_ra {
	sector_t cur;
	sector_t limit;
	unsigned int ra_blocks;
	sector_t ra_advance;
	sector_t ra_next;
	sector_t ra_limit;
};

struct fat_boot_sector {
	__u8 ignored[3];
	__u8 system_id[8];
	__u8 sector_size[2];
	__u8 sec_per_clus;
	__le16 reserved;
	__u8 fats;
	__u8 dir_entries[2];
	__u8 sectors[2];
	__u8 media;
	__le16 fat_length;
	__le16 secs_track;
	__le16 heads;
	__le32 hidden;
	__le32 total_sect;
	union {
		struct {
			__u8 drive_number;
			__u8 state;
			__u8 signature;
			__u8 vol_id[4];
			__u8 vol_label[11];
			__u8 fs_type[8];
		} fat16;
		struct {
			__le32 length;
			__le16 flags;
			__u8 version[2];
			__le32 root_cluster;
			__le16 info_sector;
			__le16 backup_boot;
			__le16 reserved2[6];
			__u8 drive_number;
			__u8 state;
			__u8 signature;
			__u8 vol_id[4];
			__u8 vol_label[11];
			__u8 fs_type[8];
		} fat32;
	};
};

struct fat_boot_fsinfo {
	__le32 signature1;
	__le32 reserved1[120];
	__le32 signature2;
	__le32 free_clusters;
	__le32 next_cluster;
	__le32 reserved2[4];
};

struct fat_bios_param_block {
	u16 fat_sector_size;
	u8 fat_sec_per_clus;
	u16 fat_reserved;
	u8 fat_fats;
	u16 fat_dir_entries;
	u16 fat_sectors;
	u16 fat_fat_length;
	u32 fat_total_sect;
	u8 fat16_state;
	u32 fat16_vol_id;
	u32 fat32_length;
	u32 fat32_root_cluster;
	u16 fat32_info_sector;
	u8 fat32_state;
	u32 fat32_vol_id;
};

struct fat_floppy_defaults {
	unsigned int nr_sectors;
	unsigned int sec_per_clus;
	unsigned int dir_entries;
	unsigned int media;
	unsigned int fat_length;
};

enum {
	Opt_check_n = 0,
	Opt_check_r = 1,
	Opt_check_s = 2,
	Opt_uid___4 = 3,
	Opt_gid___5 = 4,
	Opt_umask = 5,
	Opt_dmask = 6,
	Opt_fmask = 7,
	Opt_allow_utime = 8,
	Opt_codepage = 9,
	Opt_usefree = 10,
	Opt_nocase = 11,
	Opt_quiet = 12,
	Opt_showexec = 13,
	Opt_debug___2 = 14,
	Opt_immutable = 15,
	Opt_dots = 16,
	Opt_nodots = 17,
	Opt_charset = 18,
	Opt_shortname_lower = 19,
	Opt_shortname_win95 = 20,
	Opt_shortname_winnt = 21,
	Opt_shortname_mixed = 22,
	Opt_utf8_no = 23,
	Opt_utf8_yes = 24,
	Opt_uni_xl_no = 25,
	Opt_uni_xl_yes = 26,
	Opt_nonumtail_no = 27,
	Opt_nonumtail_yes = 28,
	Opt_obsolete = 29,
	Opt_flush = 30,
	Opt_tz_utc = 31,
	Opt_rodir = 32,
	Opt_err_cont___2 = 33,
	Opt_err_panic___2 = 34,
	Opt_err_ro___2 = 35,
	Opt_discard___2 = 36,
	Opt_nfs = 37,
	Opt_time_offset = 38,
	Opt_nfs_stale_rw = 39,
	Opt_nfs_nostale_ro = 40,
	Opt_err___3 = 41,
	Opt_dos1xfloppy = 42,
};

struct fat_fid {
	u32 i_gen;
	u32 i_pos_low;
	u16 i_pos_hi;
	u16 parent_i_pos_hi;
	u32 parent_i_pos_low;
	u32 parent_i_gen;
};

struct shortname_info {
	unsigned char lower: 1;
	unsigned char upper: 1;
	unsigned char valid: 1;
};

struct iso_directory_record {
	__u8 length[1];
	__u8 ext_attr_length[1];
	__u8 extent[8];
	__u8 size[8];
	__u8 date[7];
	__u8 flags[1];
	__u8 file_unit_size[1];
	__u8 interleave[1];
	__u8 volume_sequence_number[4];
	__u8 name_len[1];
	char name[0];
};

struct iso_inode_info {
	long unsigned int i_iget5_block;
	long unsigned int i_iget5_offset;
	unsigned int i_first_extent;
	unsigned char i_file_format;
	unsigned char i_format_parm[3];
	long unsigned int i_next_section_block;
	long unsigned int i_next_section_offset;
	off_t i_section_size;
	struct inode vfs_inode;
};

struct isofs_sb_info {
	long unsigned int s_ninodes;
	long unsigned int s_nzones;
	long unsigned int s_firstdatazone;
	long unsigned int s_log_zone_size;
	long unsigned int s_max_size;
	int s_rock_offset;
	s32 s_sbsector;
	unsigned char s_joliet_level;
	unsigned char s_mapping;
	unsigned char s_check;
	unsigned char s_session;
	unsigned int s_high_sierra: 1;
	unsigned int s_rock: 2;
	unsigned int s_utf8: 1;
	unsigned int s_cruft: 1;
	unsigned int s_nocompress: 1;
	unsigned int s_hide: 1;
	unsigned int s_showassoc: 1;
	unsigned int s_overriderockperm: 1;
	unsigned int s_uid_set: 1;
	unsigned int s_gid_set: 1;
	umode_t s_fmode;
	umode_t s_dmode;
	kgid_t s_gid;
	kuid_t s_uid;
	struct nls_table *s_nls_iocharset;
};

struct scsi_sense_hdr {
	u8 response_code;
	u8 sense_key;
	u8 asc;
	u8 ascq;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	u8 additional_length;
};

struct cdrom_msf0 {
	__u8 minute;
	__u8 second;
	__u8 frame;
};

union cdrom_addr {
	struct cdrom_msf0 msf;
	int lba;
};

struct cdrom_tocentry {
	__u8 cdte_track;
	__u8 cdte_adr: 4;
	__u8 cdte_ctrl: 4;
	__u8 cdte_format;
	union cdrom_addr cdte_addr;
	__u8 cdte_datamode;
};

struct cdrom_multisession {
	union cdrom_addr addr;
	__u8 xa_flag;
	__u8 addr_format;
};

struct cdrom_mcn {
	__u8 medium_catalog_number[14];
};

struct packet_command {
	unsigned char cmd[12];
	unsigned char *buffer;
	unsigned int buflen;
	int stat;
	struct scsi_sense_hdr *sshdr;
	unsigned char data_direction;
	int quiet;
	int timeout;
	void *reserved[1];
};

struct cdrom_device_ops;

struct cdrom_device_info {
	const struct cdrom_device_ops *ops;
	struct list_head list;
	struct gendisk *disk;
	void *handle;
	int mask;
	int speed;
	int capacity;
	unsigned int options: 30;
	unsigned int mc_flags: 2;
	unsigned int vfs_events;
	unsigned int ioctl_events;
	int use_count;
	char name[20];
	__u8 sanyo_slot: 2;
	__u8 keeplocked: 1;
	__u8 reserved: 5;
	int cdda_method;
	__u8 last_sense;
	__u8 media_written;
	short unsigned int mmc3_profile;
	int for_data;
	int (*exit)(struct cdrom_device_info *);
	int mrw_mode_page;
};

struct cdrom_device_ops {
	int (*open)(struct cdrom_device_info *, int);
	void (*release)(struct cdrom_device_info *);
	int (*drive_status)(struct cdrom_device_info *, int);
	unsigned int (*check_events)(struct cdrom_device_info *, unsigned int, int);
	int (*media_changed)(struct cdrom_device_info *, int);
	int (*tray_move)(struct cdrom_device_info *, int);
	int (*lock_door)(struct cdrom_device_info *, int);
	int (*select_speed)(struct cdrom_device_info *, int);
	int (*select_disc)(struct cdrom_device_info *, int);
	int (*get_last_session)(struct cdrom_device_info *, struct cdrom_multisession *);
	int (*get_mcn)(struct cdrom_device_info *, struct cdrom_mcn *);
	int (*reset)(struct cdrom_device_info *);
	int (*audio_ioctl)(struct cdrom_device_info *, unsigned int, void *);
	const int capability;
	int (*generic_packet)(struct cdrom_device_info *, struct packet_command *);
};

struct iso_volume_descriptor {
	__u8 type[1];
	char id[5];
	__u8 version[1];
	__u8 data[2041];
};

struct iso_primary_descriptor {
	__u8 type[1];
	char id[5];
	__u8 version[1];
	__u8 unused1[1];
	char system_id[32];
	char volume_id[32];
	__u8 unused2[8];
	__u8 volume_space_size[8];
	__u8 unused3[32];
	__u8 volume_set_size[4];
	__u8 volume_sequence_number[4];
	__u8 logical_block_size[4];
	__u8 path_table_size[8];
	__u8 type_l_path_table[4];
	__u8 opt_type_l_path_table[4];
	__u8 type_m_path_table[4];
	__u8 opt_type_m_path_table[4];
	__u8 root_directory_record[34];
	char volume_set_id[128];
	char publisher_id[128];
	char preparer_id[128];
	char application_id[128];
	char copyright_file_id[37];
	char abstract_file_id[37];
	char bibliographic_file_id[37];
	__u8 creation_date[17];
	__u8 modification_date[17];
	__u8 expiration_date[17];
	__u8 effective_date[17];
	__u8 file_structure_version[1];
	__u8 unused4[1];
	__u8 application_data[512];
	__u8 unused5[653];
};

struct iso_supplementary_descriptor {
	__u8 type[1];
	char id[5];
	__u8 version[1];
	__u8 flags[1];
	char system_id[32];
	char volume_id[32];
	__u8 unused2[8];
	__u8 volume_space_size[8];
	__u8 escape[32];
	__u8 volume_set_size[4];
	__u8 volume_sequence_number[4];
	__u8 logical_block_size[4];
	__u8 path_table_size[8];
	__u8 type_l_path_table[4];
	__u8 opt_type_l_path_table[4];
	__u8 type_m_path_table[4];
	__u8 opt_type_m_path_table[4];
	__u8 root_directory_record[34];
	char volume_set_id[128];
	char publisher_id[128];
	char preparer_id[128];
	char application_id[128];
	char copyright_file_id[37];
	char abstract_file_id[37];
	char bibliographic_file_id[37];
	__u8 creation_date[17];
	__u8 modification_date[17];
	__u8 expiration_date[17];
	__u8 effective_date[17];
	__u8 file_structure_version[1];
	__u8 unused4[1];
	__u8 application_data[512];
	__u8 unused5[653];
};

struct hs_volume_descriptor {
	__u8 foo[8];
	__u8 type[1];
	char id[5];
	__u8 version[1];
	__u8 data[2033];
};

struct hs_primary_descriptor {
	__u8 foo[8];
	__u8 type[1];
	__u8 id[5];
	__u8 version[1];
	__u8 unused1[1];
	char system_id[32];
	char volume_id[32];
	__u8 unused2[8];
	__u8 volume_space_size[8];
	__u8 unused3[32];
	__u8 volume_set_size[4];
	__u8 volume_sequence_number[4];
	__u8 logical_block_size[4];
	__u8 path_table_size[8];
	__u8 type_l_path_table[4];
	__u8 unused4[28];
	__u8 root_directory_record[34];
};

enum isofs_file_format {
	isofs_file_normal = 0,
	isofs_file_sparse = 1,
	isofs_file_compressed = 2,
};

struct iso9660_options {
	unsigned int rock: 1;
	unsigned int joliet: 1;
	unsigned int cruft: 1;
	unsigned int hide: 1;
	unsigned int showassoc: 1;
	unsigned int nocompress: 1;
	unsigned int overriderockperm: 1;
	unsigned int uid_set: 1;
	unsigned int gid_set: 1;
	unsigned int utf8: 1;
	unsigned char map;
	unsigned char check;
	unsigned int blocksize;
	umode_t fmode;
	umode_t dmode;
	kgid_t gid;
	kuid_t uid;
	char *iocharset;
	s32 session;
	s32 sbsector;
};

enum {
	Opt_block = 0,
	Opt_check_r___2 = 1,
	Opt_check_s___2 = 2,
	Opt_cruft = 3,
	Opt_gid___6 = 4,
	Opt_ignore = 5,
	Opt_iocharset = 6,
	Opt_map_a = 7,
	Opt_map_n = 8,
	Opt_map_o = 9,
	Opt_mode___5 = 10,
	Opt_nojoliet = 11,
	Opt_norock = 12,
	Opt_sb___2 = 13,
	Opt_session = 14,
	Opt_uid___5 = 15,
	Opt_unhide = 16,
	Opt_utf8 = 17,
	Opt_err___4 = 18,
	Opt_nocompress = 19,
	Opt_hide = 20,
	Opt_showassoc = 21,
	Opt_dmode = 22,
	Opt_overriderockperm = 23,
};

struct isofs_iget5_callback_data {
	long unsigned int block;
	long unsigned int offset;
};

struct SU_SP_s {
	__u8 magic[2];
	__u8 skip;
};

struct SU_CE_s {
	__u8 extent[8];
	__u8 offset[8];
	__u8 size[8];
};

struct SU_ER_s {
	__u8 len_id;
	__u8 len_des;
	__u8 len_src;
	__u8 ext_ver;
	__u8 data[0];
};

struct RR_RR_s {
	__u8 flags[1];
};

struct RR_PX_s {
	__u8 mode[8];
	__u8 n_links[8];
	__u8 uid[8];
	__u8 gid[8];
};

struct RR_PN_s {
	__u8 dev_high[8];
	__u8 dev_low[8];
};

struct SL_component {
	__u8 flags;
	__u8 len;
	__u8 text[0];
};

struct RR_SL_s {
	__u8 flags;
	struct SL_component link;
};

struct RR_NM_s {
	__u8 flags;
	char name[0];
};

struct RR_CL_s {
	__u8 location[8];
};

struct RR_PL_s {
	__u8 location[8];
};

struct stamp {
	__u8 time[7];
};

struct RR_TF_s {
	__u8 flags;
	struct stamp times[0];
};

struct RR_ZF_s {
	__u8 algorithm[2];
	__u8 parms[2];
	__u8 real_size[8];
};

struct rock_ridge {
	__u8 signature[2];
	__u8 len;
	__u8 version;
	union {
		struct SU_SP_s SP;
		struct SU_CE_s CE;
		struct SU_ER_s ER;
		struct RR_RR_s RR;
		struct RR_PX_s PX;
		struct RR_PN_s PN;
		struct RR_SL_s SL;
		struct RR_NM_s NM;
		struct RR_CL_s CL;
		struct RR_PL_s PL;
		struct RR_TF_s TF;
		struct RR_ZF_s ZF;
	} u;
};

struct rock_state {
	void *buffer;
	unsigned char *chr;
	int len;
	int cont_size;
	int cont_extent;
	int cont_offset;
	int cont_loops;
	struct inode *inode;
};

struct isofs_fid {
	u32 block;
	u16 offset;
	u16 parent_offset;
	u32 generation;
	u32 parent_block;
	u32 parent_generation;
};

typedef unsigned char Byte;

typedef long unsigned int uLong;

struct internal_state;

struct z_stream_s {
	const Byte *next_in;
	uLong avail_in;
	uLong total_in;
	Byte *next_out;
	uLong avail_out;
	uLong total_out;
	char *msg;
	struct internal_state *state;
	void *workspace;
	int data_type;
	uLong adler;
	uLong reserved;
};

struct internal_state {
	int dummy;
};

typedef struct z_stream_s z_stream;

struct nfs_seqid_counter {
	ktime_t create_time;
	int owner_id;
	int flags;
	u32 counter;
	spinlock_t lock;
	struct list_head list;
	struct rpc_wait_queue wait;
};

struct nfs4_lock_state {
	struct list_head ls_locks;
	struct nfs4_state *ls_state;
	long unsigned int ls_flags;
	struct nfs_seqid_counter ls_seqid;
	nfs4_stateid ls_stateid;
	refcount_t ls_count;
	fl_owner_t ls_owner;
};

struct sockaddr_in {
	__kernel_sa_family_t sin_family;
	__be16 sin_port;
	struct in_addr sin_addr;
	unsigned char __pad[8];
};

struct sockaddr_in6 {
	short unsigned int sin6_family;
	__be16 sin6_port;
	__be32 sin6_flowinfo;
	struct in6_addr sin6_addr;
	__u32 sin6_scope_id;
};

enum rpc_auth_flavors {
	RPC_AUTH_NULL = 0,
	RPC_AUTH_UNIX = 1,
	RPC_AUTH_SHORT = 2,
	RPC_AUTH_DES = 3,
	RPC_AUTH_KRB = 4,
	RPC_AUTH_GSS = 6,
	RPC_AUTH_MAXFLAVOR = 8,
	RPC_AUTH_GSS_KRB5 = 390003,
	RPC_AUTH_GSS_KRB5I = 390004,
	RPC_AUTH_GSS_KRB5P = 390005,
	RPC_AUTH_GSS_LKEY = 390006,
	RPC_AUTH_GSS_LKEYI = 390007,
	RPC_AUTH_GSS_LKEYP = 390008,
	RPC_AUTH_GSS_SPKM = 390009,
	RPC_AUTH_GSS_SPKMI = 390010,
	RPC_AUTH_GSS_SPKMP = 390011,
};

struct xdr_netobj {
	unsigned int len;
	u8 *data;
};

struct rpc_task_setup {
	struct rpc_task *task;
	struct rpc_clnt *rpc_client;
	struct rpc_xprt *rpc_xprt;
	struct rpc_cred *rpc_op_cred;
	const struct rpc_message *rpc_message;
	const struct rpc_call_ops *callback_ops;
	void *callback_data;
	struct workqueue_struct *workqueue;
	short unsigned int flags;
	signed char priority;
};

enum rpc_display_format_t {
	RPC_DISPLAY_ADDR = 0,
	RPC_DISPLAY_PORT = 1,
	RPC_DISPLAY_PROTO = 2,
	RPC_DISPLAY_HEX_ADDR = 3,
	RPC_DISPLAY_HEX_PORT = 4,
	RPC_DISPLAY_NETID = 5,
	RPC_DISPLAY_MAX = 6,
};

enum xprt_transports {
	XPRT_TRANSPORT_UDP = 17,
	XPRT_TRANSPORT_TCP = 6,
	XPRT_TRANSPORT_BC_TCP = 2147483654,
	XPRT_TRANSPORT_RDMA = 256,
	XPRT_TRANSPORT_BC_RDMA = 2147483904,
	XPRT_TRANSPORT_LOCAL = 257,
};

struct svc_xprt_class;

struct svc_xprt_ops;

struct svc_serv;

struct svc_xprt {
	struct svc_xprt_class *xpt_class;
	const struct svc_xprt_ops *xpt_ops;
	struct kref xpt_ref;
	struct list_head xpt_list;
	struct list_head xpt_ready;
	long unsigned int xpt_flags;
	struct svc_serv *xpt_server;
	atomic_t xpt_reserved;
	atomic_t xpt_nr_rqsts;
	struct mutex xpt_mutex;
	spinlock_t xpt_lock;
	void *xpt_auth_cache;
	struct list_head xpt_deferred;
	struct __kernel_sockaddr_storage xpt_local;
	size_t xpt_locallen;
	struct __kernel_sockaddr_storage xpt_remote;
	size_t xpt_remotelen;
	char xpt_remotebuf[58];
	struct list_head xpt_users;
	struct net *xpt_net;
	const struct cred *xpt_cred;
	struct rpc_xprt *xpt_bc_xprt;
	struct rpc_xprt_switch *xpt_bc_xps;
};

struct svc_program;

struct svc_stat {
	struct svc_program *program;
	unsigned int netcnt;
	unsigned int netudpcnt;
	unsigned int nettcpcnt;
	unsigned int nettcpconn;
	unsigned int rpccnt;
	unsigned int rpcbadfmt;
	unsigned int rpcbadauth;
	unsigned int rpcbadclnt;
};

struct svc_version;

struct svc_rqst;

struct svc_process_info;

struct svc_program {
	struct svc_program *pg_next;
	u32 pg_prog;
	unsigned int pg_lovers;
	unsigned int pg_hivers;
	unsigned int pg_nvers;
	const struct svc_version **pg_vers;
	char *pg_name;
	char *pg_class;
	struct svc_stat *pg_stats;
	int (*pg_authenticate)(struct svc_rqst *);
	__be32 (*pg_init_request)(struct svc_rqst *, const struct svc_program *, struct svc_process_info *);
	int (*pg_rpcbind_set)(struct net *, const struct svc_program *, u32, int, short unsigned int, short unsigned int);
};

struct rpc_pipe_msg {
	struct list_head list;
	void *data;
	size_t len;
	size_t copied;
	int errno;
};

struct rpc_pipe_ops {
	ssize_t (*upcall)(struct file *, struct rpc_pipe_msg *, char *, size_t);
	ssize_t (*downcall)(struct file *, const char *, size_t);
	void (*release_pipe)(struct inode *);
	int (*open_pipe)(struct inode *);
	void (*destroy_msg)(struct rpc_pipe_msg *);
};

struct rpc_pipe {
	struct list_head pipe;
	struct list_head in_upcall;
	struct list_head in_downcall;
	int pipelen;
	int nreaders;
	int nwriters;
	int flags;
	struct delayed_work queue_timeout;
	const struct rpc_pipe_ops *ops;
	spinlock_t lock;
	struct dentry *dentry;
};

struct rpc_iostats {
	spinlock_t om_lock;
	long unsigned int om_ops;
	long unsigned int om_ntrans;
	long unsigned int om_timeouts;
	long long unsigned int om_bytes_sent;
	long long unsigned int om_bytes_recv;
	ktime_t om_queue;
	ktime_t om_rtt;
	ktime_t om_execute;
	long unsigned int om_error_status;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct rpc_create_args {
	struct net *net;
	int protocol;
	struct sockaddr *address;
	size_t addrsize;
	struct sockaddr *saddress;
	const struct rpc_timeout *timeout;
	const char *servername;
	const char *nodename;
	const struct rpc_program *program;
	u32 prognumber;
	u32 version;
	rpc_authflavor_t authflavor;
	u32 nconnect;
	long unsigned int flags;
	char *client_name;
	struct svc_xprt *bc_xprt;
	const struct cred *cred;
};

struct gss_api_mech;

struct gss_ctx {
	struct gss_api_mech *mech_type;
	void *internal_ctx_id;
	unsigned int slack;
	unsigned int align;
};

struct gss_api_ops;

struct pf_desc;

struct gss_api_mech {
	struct list_head gm_list;
	struct module *gm_owner;
	struct rpcsec_gss_oid gm_oid;
	char *gm_name;
	const struct gss_api_ops *gm_ops;
	int gm_pf_num;
	struct pf_desc *gm_pfs;
	const char *gm_upcall_enctypes;
};

struct auth_domain;

struct pf_desc {
	u32 pseudoflavor;
	u32 qop;
	u32 service;
	char *name;
	char *auth_domain_name;
	struct auth_domain *domain;
	bool datatouch;
};

struct auth_ops;

struct auth_domain {
	struct kref ref;
	struct hlist_node hash;
	char *name;
	struct auth_ops *flavour;
	struct callback_head callback_head;
};

struct gss_api_ops {
	int (*gss_import_sec_context)(const void *, size_t, struct gss_ctx *, time64_t *, gfp_t);
	u32 (*gss_get_mic)(struct gss_ctx *, struct xdr_buf *, struct xdr_netobj *);
	u32 (*gss_verify_mic)(struct gss_ctx *, struct xdr_buf *, struct xdr_netobj *);
	u32 (*gss_wrap)(struct gss_ctx *, int, struct xdr_buf *, struct page **);
	u32 (*gss_unwrap)(struct gss_ctx *, int, int, struct xdr_buf *);
	void (*gss_delete_sec_context)(void *);
};

struct pnfs_layout_range {
	u32 iomode;
	u64 offset;
	u64 length;
};

struct pnfs_layout_hdr;

struct pnfs_layout_segment {
	struct list_head pls_list;
	struct list_head pls_lc_list;
	struct list_head pls_commits;
	struct pnfs_layout_range pls_range;
	refcount_t pls_refcount;
	u32 pls_seq;
	long unsigned int pls_flags;
	struct pnfs_layout_hdr *pls_layout;
};

struct nfs_seqid {
	struct nfs_seqid_counter *sequence;
	struct list_head list;
	struct rpc_task *task;
};

struct nfs4_pathname {
	unsigned int ncomponents;
	struct nfs4_string components[512];
};

struct nfs4_fs_location {
	unsigned int nservers;
	struct nfs4_string servers[10];
	struct nfs4_pathname rootpath;
};

struct nfs4_fs_locations {
	struct nfs_fattr fattr;
	const struct nfs_server *server;
	struct nfs4_pathname fs_path;
	int nlocations;
	struct nfs4_fs_location locations[10];
};

struct nfs_page {
	struct list_head wb_list;
	struct page *wb_page;
	struct nfs_lock_context *wb_lock_context;
	long unsigned int wb_index;
	unsigned int wb_offset;
	unsigned int wb_pgbase;
	unsigned int wb_bytes;
	struct kref wb_kref;
	long unsigned int wb_flags;
	struct nfs_write_verifier wb_verf;
	struct nfs_page *wb_this_page;
	struct nfs_page *wb_head;
	short unsigned int wb_nio;
};

struct nfs_subversion {
	struct module *owner;
	struct file_system_type *nfs_fs;
	const struct rpc_version *rpc_vers;
	const struct nfs_rpc_ops *rpc_ops;
	const struct super_operations *sops;
	const struct xattr_handler **xattr;
	struct list_head list;
};

struct nfs_iostats {
	long long unsigned int bytes[8];
	long unsigned int events[27];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct nfs4_state_owner;

struct nfs4_state {
	struct list_head open_states;
	struct list_head inode_states;
	struct list_head lock_states;
	struct nfs4_state_owner *owner;
	struct inode *inode;
	long unsigned int flags;
	spinlock_t state_lock;
	seqlock_t seqlock;
	nfs4_stateid stateid;
	nfs4_stateid open_stateid;
	unsigned int n_rdonly;
	unsigned int n_wronly;
	unsigned int n_rdwr;
	fmode_t state;
	refcount_t count;
	wait_queue_head_t waitq;
	struct callback_head callback_head;
};

struct nlmsvc_binding {
	__be32 (*fopen)(struct svc_rqst *, struct nfs_fh *, struct file **);
	void (*fclose)(struct file *);
};

struct svc_cred {
	kuid_t cr_uid;
	kgid_t cr_gid;
	struct group_info *cr_group_info;
	u32 cr_flavor;
	char *cr_raw_principal;
	char *cr_principal;
	char *cr_targ_princ;
	struct gss_api_mech *cr_gss_mech;
};

struct cache_deferred_req;

struct cache_req {
	struct cache_deferred_req * (*defer)(struct cache_req *);
	int thread_wait;
};

struct svc_cacherep;

struct svc_pool;

struct svc_procedure;

struct svc_deferred_req;

struct svc_rqst {
	struct list_head rq_all;
	struct callback_head rq_rcu_head;
	struct svc_xprt *rq_xprt;
	struct __kernel_sockaddr_storage rq_addr;
	size_t rq_addrlen;
	struct __kernel_sockaddr_storage rq_daddr;
	size_t rq_daddrlen;
	struct svc_serv *rq_server;
	struct svc_pool *rq_pool;
	const struct svc_procedure *rq_procinfo;
	struct auth_ops *rq_authop;
	struct svc_cred rq_cred;
	void *rq_xprt_ctxt;
	struct svc_deferred_req *rq_deferred;
	size_t rq_xprt_hlen;
	struct xdr_buf rq_arg;
	struct xdr_buf rq_res;
	struct page *rq_pages[260];
	struct page **rq_respages;
	struct page **rq_next_page;
	struct page **rq_page_end;
	struct kvec rq_vec[259];
	struct bio_vec rq_bvec[259];
	__be32 rq_xid;
	u32 rq_prog;
	u32 rq_vers;
	u32 rq_proc;
	u32 rq_prot;
	int rq_cachetype;
	long unsigned int rq_flags;
	ktime_t rq_qtime;
	void *rq_argp;
	void *rq_resp;
	void *rq_auth_data;
	int rq_auth_slack;
	int rq_reserved;
	ktime_t rq_stime;
	struct cache_req rq_chandle;
	struct auth_domain *rq_client;
	struct auth_domain *rq_gssclient;
	struct svc_cacherep *rq_cacherep;
	struct task_struct *rq_task;
	spinlock_t rq_lock;
	struct net *rq_bc_net;
	void **rq_lease_breaker;
};

struct nlmclnt_initdata {
	const char *hostname;
	const struct sockaddr *address;
	size_t addrlen;
	short unsigned int protocol;
	u32 nfs_version;
	int noresvport;
	struct net *net;
	const struct nlmclnt_operations *nlmclnt_ops;
	const struct cred *cred;
};

struct cache_head {
	struct hlist_node cache_list;
	time64_t expiry_time;
	time64_t last_refresh;
	struct kref ref;
	long unsigned int flags;
};

struct cache_detail {
	struct module *owner;
	int hash_size;
	struct hlist_head *hash_table;
	spinlock_t hash_lock;
	char *name;
	void (*cache_put)(struct kref *);
	int (*cache_upcall)(struct cache_detail *, struct cache_head *);
	void (*cache_request)(struct cache_detail *, struct cache_head *, char **, int *);
	int (*cache_parse)(struct cache_detail *, char *, int);
	int (*cache_show)(struct seq_file *, struct cache_detail *, struct cache_head *);
	void (*warn_no_listener)(struct cache_detail *, int);
	struct cache_head * (*alloc)();
	void (*flush)();
	int (*match)(struct cache_head *, struct cache_head *);
	void (*init)(struct cache_head *, struct cache_head *);
	void (*update)(struct cache_head *, struct cache_head *);
	time64_t flush_time;
	struct list_head others;
	time64_t nextcheck;
	int entries;
	struct list_head queue;
	atomic_t writers;
	time64_t last_close;
	time64_t last_warn;
	union {
		struct proc_dir_entry *procfs;
		struct dentry *pipefs;
	};
	struct net *net;
};

struct cache_deferred_req {
	struct hlist_node hash;
	struct list_head recent;
	struct cache_head *item;
	void *owner;
	void (*revisit)(struct cache_deferred_req *, int);
};

struct auth_ops {
	char *name;
	struct module *owner;
	int flavour;
	int (*accept)(struct svc_rqst *, __be32 *);
	int (*release)(struct svc_rqst *);
	void (*domain_release)(struct auth_domain *);
	int (*set_client)(struct svc_rqst *);
};

struct svc_pool_stats {
	atomic_long_t packets;
	long unsigned int sockets_queued;
	atomic_long_t threads_woken;
	atomic_long_t threads_timedout;
};

struct svc_pool {
	unsigned int sp_id;
	spinlock_t sp_lock;
	struct list_head sp_sockets;
	unsigned int sp_nrthreads;
	struct list_head sp_all_threads;
	struct svc_pool_stats sp_stats;
	long unsigned int sp_flags;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct svc_serv_ops {
	void (*svo_shutdown)(struct svc_serv *, struct net *);
	int (*svo_function)(void *);
	void (*svo_enqueue_xprt)(struct svc_xprt *);
	int (*svo_setup)(struct svc_serv *, struct svc_pool *, int);
	struct module *svo_module;
};

struct svc_serv {
	struct svc_program *sv_program;
	struct svc_stat *sv_stats;
	spinlock_t sv_lock;
	unsigned int sv_nrthreads;
	unsigned int sv_maxconn;
	unsigned int sv_max_payload;
	unsigned int sv_max_mesg;
	unsigned int sv_xdrsize;
	struct list_head sv_permsocks;
	struct list_head sv_tempsocks;
	int sv_tmpcnt;
	struct timer_list sv_temptimer;
	char *sv_name;
	unsigned int sv_nrpools;
	struct svc_pool *sv_pools;
	const struct svc_serv_ops *sv_ops;
};

struct svc_procedure {
	__be32 (*pc_func)(struct svc_rqst *);
	int (*pc_decode)(struct svc_rqst *, __be32 *);
	int (*pc_encode)(struct svc_rqst *, __be32 *);
	void (*pc_release)(struct svc_rqst *);
	unsigned int pc_argsize;
	unsigned int pc_ressize;
	unsigned int pc_cachetype;
	unsigned int pc_xdrressize;
};

struct svc_deferred_req {
	u32 prot;
	struct svc_xprt *xprt;
	struct __kernel_sockaddr_storage addr;
	size_t addrlen;
	struct __kernel_sockaddr_storage daddr;
	size_t daddrlen;
	struct cache_deferred_req handle;
	size_t xprt_hlen;
	int argslen;
	__be32 args[0];
};

struct svc_process_info {
	union {
		int (*dispatch)(struct svc_rqst *, __be32 *);
		struct {
			unsigned int lovers;
			unsigned int hivers;
		} mismatch;
	};
};

struct svc_version {
	u32 vs_vers;
	u32 vs_nproc;
	const struct svc_procedure *vs_proc;
	unsigned int *vs_count;
	u32 vs_xdrsize;
	bool vs_hidden;
	bool vs_rpcb_optnl;
	bool vs_need_cong_ctrl;
	int (*vs_dispatch)(struct svc_rqst *, __be32 *);
};

struct svc_pool_map {
	int count;
	int mode;
	unsigned int npools;
	unsigned int *pool_to;
	unsigned int *to_pool;
};

struct svc_xprt_ops {
	struct svc_xprt * (*xpo_create)(struct svc_serv *, struct net *, struct sockaddr *, int, int);
	struct svc_xprt * (*xpo_accept)(struct svc_xprt *);
	int (*xpo_has_wspace)(struct svc_xprt *);
	int (*xpo_recvfrom)(struct svc_rqst *);
	int (*xpo_sendto)(struct svc_rqst *);
	int (*xpo_read_payload)(struct svc_rqst *, unsigned int, unsigned int);
	void (*xpo_release_rqst)(struct svc_rqst *);
	void (*xpo_detach)(struct svc_xprt *);
	void (*xpo_free)(struct svc_xprt *);
	void (*xpo_secure_port)(struct svc_rqst *);
	void (*xpo_kill_temp_xprt)(struct svc_xprt *);
};

struct svc_xprt_class {
	const char *xcl_name;
	struct module *xcl_owner;
	const struct svc_xprt_ops *xcl_ops;
	struct list_head xcl_list;
	u32 xcl_max_payload;
	int xcl_ident;
};

struct nfs4_state_recovery_ops {
	int owner_flag_bit;
	int state_flag_bit;
	int (*recover_open)(struct nfs4_state_owner *, struct nfs4_state *);
	int (*recover_lock)(struct nfs4_state *, struct file_lock *);
	int (*establish_clid)(struct nfs_client *, const struct cred *);
	int (*reclaim_complete)(struct nfs_client *, const struct cred *);
	int (*detect_trunking)(struct nfs_client *, struct nfs_client **, const struct cred *);
};

struct nfs4_state_maintenance_ops {
	int (*sched_state_renewal)(struct nfs_client *, const struct cred *, unsigned int);
	const struct cred * (*get_state_renewal_cred)(struct nfs_client *);
	int (*renew_lease)(struct nfs_client *, const struct cred *);
};

struct nfs4_mig_recovery_ops {
	int (*get_locations)(struct inode *, struct nfs4_fs_locations *, struct page *, const struct cred *);
	int (*fsid_present)(struct inode *, const struct cred *);
};

struct nfs4_state_owner {
	struct nfs_server *so_server;
	struct list_head so_lru;
	long unsigned int so_expires;
	struct rb_node so_server_node;
	const struct cred *so_cred;
	spinlock_t so_lock;
	atomic_t so_count;
	long unsigned int so_flags;
	struct list_head so_states;
	struct nfs_seqid_counter so_seqid;
	seqcount_t so_reclaim_seqcount;
	struct mutex so_delegreturn_mutex;
};

enum nfs_stat_bytecounters {
	NFSIOS_NORMALREADBYTES = 0,
	NFSIOS_NORMALWRITTENBYTES = 1,
	NFSIOS_DIRECTREADBYTES = 2,
	NFSIOS_DIRECTWRITTENBYTES = 3,
	NFSIOS_SERVERREADBYTES = 4,
	NFSIOS_SERVERWRITTENBYTES = 5,
	NFSIOS_READPAGES = 6,
	NFSIOS_WRITEPAGES = 7,
	__NFSIOS_BYTESMAX = 8,
};

enum nfs_stat_eventcounters {
	NFSIOS_INODEREVALIDATE = 0,
	NFSIOS_DENTRYREVALIDATE = 1,
	NFSIOS_DATAINVALIDATE = 2,
	NFSIOS_ATTRINVALIDATE = 3,
	NFSIOS_VFSOPEN = 4,
	NFSIOS_VFSLOOKUP = 5,
	NFSIOS_VFSACCESS = 6,
	NFSIOS_VFSUPDATEPAGE = 7,
	NFSIOS_VFSREADPAGE = 8,
	NFSIOS_VFSREADPAGES = 9,
	NFSIOS_VFSWRITEPAGE = 10,
	NFSIOS_VFSWRITEPAGES = 11,
	NFSIOS_VFSGETDENTS = 12,
	NFSIOS_VFSSETATTR = 13,
	NFSIOS_VFSFLUSH = 14,
	NFSIOS_VFSFSYNC = 15,
	NFSIOS_VFSLOCK = 16,
	NFSIOS_VFSRELEASE = 17,
	NFSIOS_CONGESTIONWAIT = 18,
	NFSIOS_SETATTRTRUNC = 19,
	NFSIOS_EXTENDWRITE = 20,
	NFSIOS_SILLYRENAME = 21,
	NFSIOS_SHORTREAD = 22,
	NFSIOS_SHORTWRITE = 23,
	NFSIOS_DELAY = 24,
	NFSIOS_PNFS_READ = 25,
	NFSIOS_PNFS_WRITE = 26,
	__NFSIOS_COUNTSMAX = 27,
};

struct nfs_pageio_descriptor;

struct nfs_pageio_ops {
	void (*pg_init)(struct nfs_pageio_descriptor *, struct nfs_page *);
	size_t (*pg_test)(struct nfs_pageio_descriptor *, struct nfs_page *, struct nfs_page *);
	int (*pg_doio)(struct nfs_pageio_descriptor *);
	unsigned int (*pg_get_mirror_count)(struct nfs_pageio_descriptor *, struct nfs_page *);
	void (*pg_cleanup)(struct nfs_pageio_descriptor *);
};

struct nfs_pgio_mirror {
	struct list_head pg_list;
	long unsigned int pg_bytes_written;
	size_t pg_count;
	size_t pg_bsize;
	unsigned int pg_base;
	unsigned char pg_recoalesce: 1;
};

struct nfs_pageio_descriptor {
	struct inode *pg_inode;
	const struct nfs_pageio_ops *pg_ops;
	const struct nfs_rw_ops *pg_rw_ops;
	int pg_ioflags;
	int pg_error;
	const struct rpc_call_ops *pg_rpc_callops;
	const struct nfs_pgio_completion_ops *pg_completion_ops;
	struct pnfs_layout_segment *pg_lseg;
	struct nfs_io_completion *pg_io_completion;
	struct nfs_direct_req *pg_dreq;
	unsigned int pg_bsize;
	u32 pg_mirror_count;
	struct nfs_pgio_mirror *pg_mirrors;
	struct nfs_pgio_mirror pg_mirrors_static[1];
	struct nfs_pgio_mirror *pg_mirrors_dynamic;
	u32 pg_mirror_idx;
	short unsigned int pg_maxretrans;
	unsigned char pg_moreio: 1;
};

struct nfs_clone_mount {
	struct super_block *sb;
	struct dentry *dentry;
	struct nfs_fattr *fattr;
	unsigned int inherited_bsize;
};

struct nfs_fs_context {
	bool internal;
	bool skip_reconfig_option_check;
	bool need_mount;
	bool sloppy;
	unsigned int flags;
	unsigned int rsize;
	unsigned int wsize;
	unsigned int timeo;
	unsigned int retrans;
	unsigned int acregmin;
	unsigned int acregmax;
	unsigned int acdirmin;
	unsigned int acdirmax;
	unsigned int namlen;
	unsigned int options;
	unsigned int bsize;
	struct nfs_auth_info auth_info;
	rpc_authflavor_t selected_flavor;
	char *client_address;
	unsigned int version;
	unsigned int minorversion;
	char *fscache_uniq;
	short unsigned int protofamily;
	short unsigned int mountfamily;
	struct {
		union {
			struct sockaddr address;
			struct __kernel_sockaddr_storage _address;
		};
		size_t addrlen;
		char *hostname;
		u32 version;
		int port;
		short unsigned int protocol;
	} mount_server;
	struct {
		union {
			struct sockaddr address;
			struct __kernel_sockaddr_storage _address;
		};
		size_t addrlen;
		char *hostname;
		char *export_path;
		int port;
		short unsigned int protocol;
		short unsigned int nconnect;
		short unsigned int export_path_len;
	} nfs_server;
	struct nfs_fh *mntfh;
	struct nfs_server *server;
	struct nfs_subversion *nfs_mod;
	struct nfs_clone_mount clone_data;
};

struct bl_dev_msg {
	int32_t status;
};

