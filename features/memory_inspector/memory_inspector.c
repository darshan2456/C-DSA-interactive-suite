#define IN_MEMORY_INSPECTOR_C
#include "memory_inspector.h"
#include "dll.h"
#include "sll.h"
#include "trees.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hexdump(const void* ptr, size_t size)
{
    if (!ptr || size == 0)
    {
        printf("(NULL pointer or empty memory region)\n");
        return;
    }

    const unsigned char* bytes = (const unsigned char*)ptr;
    printf("\n--- Memory Layout Hexdump (%lu bytes at %p) ---\n", (unsigned long)size, ptr);
    printf("  Offset    00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  |ASCII|\n");
    printf("  --------  -----------------------------------------------  |----------------|\n");

    for (size_t i = 0; i < size; i += 16)
    {
        printf("  %08lX  ", (unsigned long)i);

        // Print hex bytes
        for (size_t j = 0; j < 16; j++)
        {
            if (j == 8)
            {
                printf(" ");
            }
            if (i + j < size)
            {
                printf("%02X ", bytes[i + j]);
            }
            else
            {
                printf("   ");
            }
        }

        printf(" |");

        // Print ASCII characters
        for (size_t j = 0; j < 16; j++)
        {
            if (i + j < size)
            {
                unsigned char c = bytes[i + j];
                printf("%c", isprint(c) ? c : '.');
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("  --------  -----------------------------------------------  |----------------|\n\n");
}

size_t format_hexdump(const void* ptr, size_t size, char* out_buf, size_t buf_size)
{
    if (!out_buf || buf_size == 0)
    {
        return 0;
    }

    if (!ptr || size == 0)
    {
        int written = snprintf(out_buf, buf_size, "(NULL pointer or empty memory region)\n");
        return (written > 0) ? (size_t)written : 0;
    }

    const unsigned char* bytes = (const unsigned char*)ptr;
    size_t offset = 0;

    int written = snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0,
                           "Address: %p (%lu bytes)\n", ptr, (unsigned long)size);
    if (written > 0)
    {
        offset += (size_t)written;
    }

    for (size_t i = 0; i < size && offset < buf_size; i += 16)
    {
        written = snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0,
                           "%08lX  ", (unsigned long)i);
        if (written > 0)
        {
            offset += (size_t)written;
        }

        for (size_t j = 0; j < 16 && offset < buf_size; j++)
        {
            if (j == 8)
            {
                written =
                    snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0, " ");
                if (written > 0)
                    offset += (size_t)written;
            }
            if (i + j < size)
            {
                written = snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0,
                                   "%02X ", bytes[i + j]);
            }
            else
            {
                written =
                    snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0, "   ");
            }
            if (written > 0)
            {
                offset += (size_t)written;
            }
        }

        written = snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0, " |");
        if (written > 0)
        {
            offset += (size_t)written;
        }

        for (size_t j = 0; j < 16 && offset < buf_size; j++)
        {
            if (i + j < size)
            {
                unsigned char c = bytes[i + j];
                written = snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0,
                                   "%c", isprint(c) ? c : '.');
            }
            else
            {
                written =
                    snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0, " ");
            }
            if (written > 0)
            {
                offset += (size_t)written;
            }
        }

        written = snprintf(out_buf + offset, buf_size > offset ? buf_size - offset : 0, "|\n");
        if (written > 0)
        {
            offset += (size_t)written;
        }
    }

    return offset;
}

void finalize_struct_layout(StructLayout* layout)
{
    if (!layout)
        return;

    size_t payload = 0;
    size_t padding = 0;

    for (size_t i = 0; i < layout->field_count; i++)
    {
        payload += layout->fields[i].size;
        if (i + 1 < layout->field_count)
        {
            size_t next_offset = layout->fields[i + 1].offset;
            size_t end_curr = layout->fields[i].offset + layout->fields[i].size;
            if (next_offset > end_curr)
            {
                layout->fields[i].padding_after = next_offset - end_curr;
            }
            else
            {
                layout->fields[i].padding_after = 0;
            }
        }
        else
        {
            size_t end_curr = layout->fields[i].offset + layout->fields[i].size;
            if (layout->total_size > end_curr)
            {
                layout->fields[i].padding_after = layout->total_size - end_curr;
            }
            else
            {
                layout->fields[i].padding_after = 0;
            }
        }
        padding += layout->fields[i].padding_after;
    }

    layout->payload_size = payload;
    layout->total_padding = padding;
}

void print_struct_layout_report(const StructLayout* layout, const void* instance_ptr)
{
    if (!layout)
    {
        printf("(NULL StructLayout pointer)\n");
        return;
    }

    printf("\n========================================================================\n");
    printf("        STRUCT MEMORY LAYOUT & ALIGNMENT ANALYSIS: %s        \n",
           layout->struct_name ? layout->struct_name : "Anonymous Struct");
    printf("========================================================================\n");
    printf("Total Size: %lu bytes | Payload: %lu bytes | Padding: %lu bytes\n",
           (unsigned long)layout->total_size, (unsigned long)layout->payload_size,
           (unsigned long)layout->total_padding);
    if (instance_ptr)
    {
        uintptr_t addr = (uintptr_t)instance_ptr;
        printf("Instance Base Address: %p (Alignment: %lu-byte boundary %s)\n", instance_ptr,
               (unsigned long)layout->alignment,
               (addr % (layout->alignment ? layout->alignment : 1) == 0) ? "[OK]" : "[MISALIGNED]");
    }
    printf("------------------------------------------------------------------------\n");
    printf("  %-18s | %-8s | %-6s | %-12s | %-12s\n", "Field Name", "Offset", "Size",
           "Padding After", "Byte Range");
    printf("  -------------------+----------+--------+---------------+--------------\n");

    for (size_t i = 0; i < layout->field_count; i++)
    {
        const StructField* f = &layout->fields[i];
        size_t end_byte = f->offset + f->size - 1;
        printf("  %-18s | +%-7lu | %-6lu | %-12lu | [%lu - %lu]\n", f->name,
               (unsigned long)f->offset, (unsigned long)f->size, (unsigned long)f->padding_after,
               (unsigned long)f->offset, (unsigned long)end_byte);
    }
    printf("========================================================================\n\n");

    if (instance_ptr && layout->total_size > 0)
    {
        print_hexdump(instance_ptr, layout->total_size);
    }
}

void inspect_sll_node_memory(const void* node_ptr)
{
    StructLayout layout = {.struct_name = "Singly LinkedList Node (Node)",
                           .total_size = sizeof(Node),
                           .alignment = _Alignof(Node),
                           .field_count = 2,
                           .fields = {{"data (void*)", offsetof(Node, data), sizeof(void*), 0},
                                      {"next (Node*)", offsetof(Node, next), sizeof(Node*), 0}}};
    finalize_struct_layout(&layout);
    print_struct_layout_report(&layout, node_ptr);
}

void inspect_dll_node_memory(const void* node_ptr)
{
    StructLayout layout = {
        .struct_name = "Doubly LinkedList Node (doubly_ll_Node)",
        .total_size = sizeof(doubly_ll_Node),
        .alignment = _Alignof(doubly_ll_Node),
        .field_count = 3,
        .fields = {{"data (void*)", offsetof(doubly_ll_Node, data), sizeof(void*), 0},
                   {"prev (Node*)", offsetof(doubly_ll_Node, prev), sizeof(doubly_ll_Node*), 0},
                   {"next (Node*)", offsetof(doubly_ll_Node, next), sizeof(doubly_ll_Node*), 0}}};
    finalize_struct_layout(&layout);
    print_struct_layout_report(&layout, node_ptr);
}

void inspect_bst_node_memory(const void* node_ptr)
{
    StructLayout layout = {
        .struct_name = "Binary Search Tree Node (bstNode)",
        .total_size = sizeof(bstNode),
        .alignment = _Alignof(bstNode),
        .field_count = 3,
        .fields = {{"data (int)", offsetof(bstNode, data), sizeof(int), 0},
                   {"left (bstNode*)", offsetof(bstNode, left), sizeof(bstNode*), 0},
                   {"right (bstNode*)", offsetof(bstNode, right), sizeof(bstNode*), 0}}};
    finalize_struct_layout(&layout);
    print_struct_layout_report(&layout, node_ptr);
}

/* ── Live Allocation Tracking & Heap Map ────────────────────── */
static AllocatedBlock tracked_blocks[MAX_TRACKED_BLOCKS];
static int tracked_block_count = 0;

void memory_inspector_clear_blocks(void)
{
    tracked_block_count = 0;
    memset(tracked_blocks, 0, sizeof(tracked_blocks));
}

void* dsa_malloc(size_t size, const char* label)
{
    void* ptr = malloc(size);
    if (ptr != NULL && tracked_block_count < MAX_TRACKED_BLOCKS)
    {
        tracked_blocks[tracked_block_count].address = ptr;
        tracked_blocks[tracked_block_count].size = size;
        tracked_blocks[tracked_block_count].label = label ? label : "Allocated Block";
        tracked_blocks[tracked_block_count].state = BLOCK_STATE_ACTIVE;
        tracked_block_count++;
    }
    return ptr;
}

void dsa_free(void* ptr)
{
    if (ptr == NULL)
        return;

    for (int i = 0; i < tracked_block_count; i++)
    {
        if (tracked_blocks[i].address == ptr)
        {
            tracked_blocks[i].state = BLOCK_STATE_FREE;
            break;
        }
    }
    free(ptr);
}

void* dsa_realloc(void* ptr, size_t size, const char* label)
{
    void* new_ptr = realloc(ptr, size);
    if (new_ptr != NULL)
    {
        int found = 0;
        for (int i = 0; i < tracked_block_count; i++)
        {
            if (tracked_blocks[i].address == ptr)
            {
                tracked_blocks[i].address = new_ptr;
                tracked_blocks[i].size = size;
                if (label)
                    tracked_blocks[i].label = label;
                tracked_blocks[i].state = BLOCK_STATE_ACTIVE;
                found = 1;
                break;
            }
        }
        if (!found && tracked_block_count < MAX_TRACKED_BLOCKS)
        {
            tracked_blocks[tracked_block_count].address = new_ptr;
            tracked_blocks[tracked_block_count].size = size;
            tracked_blocks[tracked_block_count].label = label ? label : "Reallocated Block";
            tracked_blocks[tracked_block_count].state = BLOCK_STATE_ACTIVE;
            tracked_block_count++;
        }
    }
    return new_ptr;
}

int memory_inspector_get_active_block_count(void)
{
    int active = 0;
    for (int i = 0; i < tracked_block_count; i++)
    {
        if (tracked_blocks[i].state == BLOCK_STATE_ACTIVE)
        {
            active++;
        }
    }
    return active;
}

size_t memory_inspector_get_total_allocated_bytes(void)
{
    size_t total = 0;
    for (int i = 0; i < tracked_block_count; i++)
    {
        if (tracked_blocks[i].state == BLOCK_STATE_ACTIVE)
        {
            total += tracked_blocks[i].size;
        }
    }
    return total;
}

void memory_inspector_draw_heap_map(void)
{
    printf("\n┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                      LIVE VISUAL HEAP MEMORY MAP                       │\n");
    printf("├────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Index  Status   Address            Size      Label                     │\n");
    printf("├───────--------  ------------------  --------  -------------------------┤\n");

    if (tracked_block_count == 0)
    {
        printf("│ (No active or tracked heap allocations)                                │\n");
    }
    else
    {
        for (int i = 0; i < tracked_block_count; i++)
        {
            const char* status_str = (tracked_blocks[i].state == BLOCK_STATE_ACTIVE)
                                         ? "\033[1;32m[ACTIVE]\033[0m"
                                         : "\033[1;31m[FREED]\033[0m ";
            printf("│ [%02d]  %-8s %-18p %-8lu %-25s │\n", i + 1, status_str,
                   tracked_blocks[i].address, (unsigned long)tracked_blocks[i].size,
                   tracked_blocks[i].label ? tracked_blocks[i].label : "Block");
        }
    }
    printf("├────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Total Active Blocks: %-3d | Total Active Bytes: %-15lu │\n",
           memory_inspector_get_active_block_count(),
           (unsigned long)memory_inspector_get_total_allocated_bytes());
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
}
