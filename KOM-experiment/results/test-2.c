UINT  _tx_thread_time_slice_change(TX_THREAD *thread_ptr, ULONG new_time_slice, ULONG *old_time_slice)
{
    // Committed Code of pointer range validation for thread_ptr and old_time_slice
    //Committed code
    if (thread_ptr == TX_NULL)
    {
        return TX_THREAD_ERROR;
    }
    else if (thread_ptr -> tx_thread_id != TX_THREAD_ID)
    {
        status =  TX_THREAD_ERROR;
    }
    //Committed code
    thread_ptr -> tx_thread_time_slice =      new_time_slice;
    thread_ptr -> tx_thread_new_time_slice =  new_time_slice;
    return TX_SUCCESS;
}