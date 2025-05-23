/* 사진 확대 */
document.addEventListener("DOMContentLoaded", function () {
    const modal = document.getElementById("modal");
    const modalImg = document.getElementById("modal-img");
    const closeBtn = document.getElementById("closeBtn");

    document.querySelectorAll(".gallery-item img").forEach(img => {
        img.addEventListener("click", () => {
        modal.style.display = "block";
        modalImg.src = img.src;
        });
    });

    closeBtn.onclick = function () {
        modal.style.display = "none";
    };

    modal.onclick = function (e) {
        if (e.target === modal) {
        modal.style.display = "none";
        }
    };
});

/* 페이지 넘김 */
document.addEventListener('DOMContentLoaded', () => {
    const itemsPerPage = 6;
    let currentPage = 1;

    const items = Array.from(document.querySelectorAll('.gallery-item'));
    const totalPages = Math.ceil(items.length / itemsPerPage);

    const prevBtn = document.getElementById('prevBtn');
    const nextBtn = document.getElementById('nextBtn');
    const pageNumbers = document.getElementById('pageNumbers');

    function showPage(page) {
        items.forEach((item, index) => {
            const start = (page - 1) * itemsPerPage;
            const end = page * itemsPerPage;
        item.style.display = (index >= start && index < end) ? 'flex' : 'none';
    });

        currentPage = page;
        renderPagination();
    }

    function renderPagination() {
        pageNumbers.innerHTML = '';
    
        for (let i = 1; i <= totalPages; i++) {
            const span = document.createElement('span');
            span.textContent = i;
            span.style.margin = '0 5px';
            span.style.cursor = 'pointer';
            if (i === currentPage) span.style.fontWeight = 'bold';
            span.onclick = () => showPage(i);
            pageNumbers.appendChild(span);
        }

        prevBtn.disabled = currentPage === 1;
        nextBtn.disabled = currentPage === totalPages;
    }

    prevBtn.onclick = () => {
        if (currentPage > 1) showPage(currentPage - 1);
    };

    nextBtn.onclick = () => {
        if (currentPage < totalPages) showPage(currentPage + 1);
    };

    showPage(currentPage);
});