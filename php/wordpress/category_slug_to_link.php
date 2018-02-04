function category_slug_to_link($slug)
{
    $category = get_category_by_slug($slug);
    return esc_url(get_category_link($category->term_id));
}
